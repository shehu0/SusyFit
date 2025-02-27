/* 
 * Copyright (C) 2012 HEPfit Collaboration
 * All rights reserved.
 *
 * For the licensing terms see doc/COPYING.
 */

#include <math.h>
#include <sstream>
#include <stdexcept>
#include <StandardModelMatching.h>
#include "SUSY.h"
//#include "SUSYMatching.h"
#include "SUSYSpectrum.h"
#include "EWSUSY.h"
#include "FeynHiggsWrapper.h"


const std::string SUSY::SUSYvars[NSUSYvars] = {
    "m1r", "m1i", "m2r", "m2i", "m3" , "muHr", "muHi", "mHptree", "tanb", "Q_SUSY"
};

SUSY::SUSY()
: StandardModel(),
        msQhat2(3,3,0.), msUhat2(3,3,0.), msDhat2(3,3,0.),msLhat2(3,3,0.), msNhat2(3,3,0.), msEhat2(3,3,0.),
        TUhat(3,3,0.), TDhat(3,3,0.), TNhat(3,3,0.), TEhat(3,3,0.),
        mch(2,0.), mneu(4,0.), m_su2(6,0.), m_sd2(6,0.), m_sdresum2(6,0.), m_sn2(6,0.), m_se2(6,0.),
        U(2,2,0.), V(2,2,0.), N(4,4,0.),
        Ru(6,6,0.), Rd(6,6,0.), Rdresum(6,6,0.), Rn(6,6,0.), Rl(6,6,0.)
{
    ModelParamMap.insert(std::pair<std::string, boost::reference_wrapper<const double> >("m1r", boost::cref(m1.real())));
    ModelParamMap.insert(std::pair<std::string, boost::reference_wrapper<const double> >("m1i", boost::cref(m1.imag())));
    ModelParamMap.insert(std::pair<std::string, boost::reference_wrapper<const double> >("m2r", boost::cref(m2.real())));
    ModelParamMap.insert(std::pair<std::string, boost::reference_wrapper<const double> >("m2i", boost::cref(m2.imag())));
    ModelParamMap.insert(std::pair<std::string, boost::reference_wrapper<const double> >("m3", boost::cref(m3)));
    ModelParamMap.insert(std::pair<std::string, boost::reference_wrapper<const double> >("muHr", boost::cref(muH.real())));
    ModelParamMap.insert(std::pair<std::string, boost::reference_wrapper<const double> >("muHi", boost::cref(muH.imag())));
    ModelParamMap.insert(std::pair<std::string, boost::reference_wrapper<const double> >("mHptree", boost::cref(mHptree)));
    ModelParamMap.insert(std::pair<std::string, boost::reference_wrapper<const double> >("tanb", boost::cref(tanb)));
    ModelParamMap.insert(std::pair<std::string, boost::reference_wrapper<const double> >("Q_SUSY", boost::cref(Q_SUSY)));
}

SUSY::~SUSY(){
    if (IsModelInitialized()) {
            if (mySUSYMatching != NULL) delete(mySUSYMatching);
            if (myFH != NULL) delete(myFH);
            if (mySUSYSpectrum != NULL) delete(mySUSYSpectrum);
            if (myEWSUSY != NULL) delete(myEWSUSY);
        }
}
///////////////////////////////////////////////////////////////////////////
// Initialization

bool SUSY::InitializeModel()
{
    mySUSYMatching = new SUSYMatching(*this);
    mySUSYSpectrum = new SUSYSpectrum(*this);
    myFH = new FeynHiggsWrapper(*this);
    myEWSUSY = new EWSUSY(*this);
    setFlagStr("Mw", "NORESUM");
    setModelInitialized(StandardModel::InitializeModel());
    setModelSUSY();
    return(true);
}

///////////////////////////////////////////////////////////////////////////
// Parameters 

bool SUSY::Init(const std::map<std::string, double>& DPars)
{
    return(StandardModel::Init(DPars));
}

bool SUSY::PreUpdate()
{
    if(!StandardModel::PreUpdate()) return (false);

    return (true);
}

bool SUSY::Update(const std::map<std::string, double>& DPars)
{
    if(!PreUpdate()) return (false);
    
    UpdateError = false;

    for (std::map<std::string, double>::const_iterator it = DPars.begin(); it != DPars.end(); it++)
        setParameter(it->first, it->second);

    if (UpdateError) return (false);

    if(!PostUpdate()) return (false);

    return (true);
}

bool SUSY::PostUpdate()
{
    if(!StandardModel::PostUpdate()) return (false);

    /* Set the squark and slepton mass matrices and the trilinear-coupling matrices */
    SetSoftTerms();
    computeYukawas();

    /* use approximate GUT relation if M1 & M2 are zero */
    if(m1.abs() == 0. && m2.abs() == 0.) {
        m1.real() = m3/6.;
        m2.real() = m3/3.;
    }
    
    /* Compute Higgs and sparticle spectra with FeynHiggs */
    if(!myFH->SetFeynHiggsPars()) return (false);
    if(!myFH->CalcHiggsSpectrum()) return (false);
    if(!myFH->CalcSpectrum()) return (false); /* Using SUSYSpectrum instead, because FH does not calculate Sneutrino masses. */
    if(!mySUSYSpectrum->CalcSneutrino(Rn,m_sn2)) return (false);
    myFH->SortSfermionMasses(m_sn2, Rn);

    /* Set the mass of the SM-like Higgs */
    mHl = mh[0];
    /* allowed range for the use of EWSMApproximateFormulae class */
    if (mHl < 10. || mHl > 1000.) {
        std::cout << "WARNING: mh=" << mHl << " in SUSY::PostUpdate" << std::endl;
        return (false);
    }
    
    if( Q_SUSY == -1 || Q_SUSY == 0) Q_SUSY = sqrt( sqrt(m_su2(2) * m_su2(5)) );

    /* For EWSUSY class */
    myEWSUSY->SetRosiekParameters();

    /* Necessary for updating StandardModel parameters in StandardModelMatching,
     * and SUSY and SUSY-derived parameters in SUSYMatching */
    mySUSYMatching->StandardModelMatching::updateSMParameters();
    mySUSYMatching->updateSUSYParameters();

    mySUSYMatching->Comp_mySUSYMQ();

    if (IsFlag_ne()) mySUSYMatching->Comp_VdDNL(0);
    if (IsFlag_ne()) mySUSYMatching->Comp_VdDNR(0);
    if (IsFlag_ch()) mySUSYMatching->Comp_VdUCL();
    if (IsFlag_ch()) mySUSYMatching->Comp_VdUCR(0);

    mySUSYMatching->Comp_DeltaMd();
    mySUSYMatching->Comp_DeltaDL();
    mySUSYMatching->Comp_Eps_J();
    mySUSYMatching->Comp_Lambda0EpsY();
    mySUSYMatching->Comp_mySUSY_CKM();

    if (IsFlag_h()) {
        mySUSYMatching->Comp_PHLR();
        mySUSYMatching->Comp_VUDHH();
        mySUSYMatching->Comp_PHRL();
    }
    if (IsFlag_ne()) {
        mySUSYMatching->Comp_VdDNL(1);
        mySUSYMatching->Comp_VdDNR(1);
        mySUSYMatching->Comp_VuUN();
    }
    if (IsFlag_ch()) {
        mySUSYMatching->Comp_VdUCR(1);
        mySUSYMatching->Comp_VuDCL();
        mySUSYMatching->Comp_VuDCR();
    }

    return (true);
}

void SUSY::setParameter(const std::string name, const double& value)
{
    if (name.compare("m1r") == 0)
        m1.real() = value;
    else if (name.compare("m1i") == 0)
        m1.imag() = value;
    else if (name.compare("m2r") == 0)
        m2.real() = value;
    else if (name.compare("m2i") == 0)
        m2.imag() = value;
    else if (name.compare("m3") == 0)
        m3 = value;
    else if (name.compare("muHr") == 0)
        muH.real() = value;
    else if (name.compare("muHi") == 0)
        muH.imag() = value;
    else if (name.compare("mHptree") == 0)
        mHptree = value;
    else if (name.compare("tanb") == 0)
        SetTanb(value);
    else if (name.compare("Q_SUSY") == 0)
        Q_SUSY = value;
    else
        StandardModel::setParameter(name, value);
}

bool SUSY::CheckParameters(const std::map<std::string, double>& DPars)
{
    for(int i=0; i<NSUSYvars; i++)
        if(DPars.find(SUSYvars[i])==DPars.end()) {
            std::cout << "missing mandatory SUSY parameter " << SUSYvars[i] << std::endl;
            return false;
        }
    return(StandardModel::CheckParameters(DPars));
}

void SUSY::SetTanb(const double tanb)
{
    this->tanb = tanb;
    if (tanb < 0.)
        throw std::runtime_error("SUSY::setTanb(): Negative tanb is not allowed");

    /* cosb and sinb are defined to be positive, corresponding to 0<=beta<=pi/2 */
    cosb = sqrt(1. / (1. + tanb * tanb));
    sinb = tanb * cosb;
}

void SUSY::computeYukawas()
{
    /* initializations */
    Yu = matrix<complex>::Id(3);
    Yd = matrix<complex>::Id(3);
    Ye = matrix<complex>::Id(3);
    Yn = matrix<complex>::Id(3);

    /* Convert the top-quark pole mass to the MSbar mass */
    double mtbar = Mp2Mbar(mtpole, FULLNLO);

    double Q_SUSY_temp = Q_SUSY;
    if( Q_SUSY == -1 || Q_SUSY == 0) Q_SUSY = sqrt( sqrt(msQhat2(2,2).abs() * msUhat2(2,2).abs() ) );

    for (int i = 0; i < 3; i++) {
        /* Run the quark masses to scale Q */
        if (i != 2)
            mu_Q[i] = Mrun(Q_SUSY, getQuarks((quark)(UP + 2 * i)).getMass_scale(),
                           getQuarks((quark)(UP + 2 * i)).getMass(), FULLNLO);
        else
            mu_Q[i] = Mrun(Q_SUSY, mtbar, FULLNLO);
        md_Q[i] = Mrun(Q_SUSY, getQuarks((quark)(DOWN + 2 * i)).getMass_scale(),
                       getQuarks((quark)(DOWN + 2 * i)).getMass(), FULLNLO);
        me_Q[i] = getLeptons((lepton)(ELECTRON + 2 * i)).getMass();
        mn_Q[i] = getLeptons((lepton)(NEUTRINO_1 + 2 * i)).getMass();

        /* Convert MSbar to DRbar */
        mu_Q[i] = MS2DRqmass(Q_SUSY, mu_Q[i]);
        md_Q[i] = MS2DRqmass(Q_SUSY, md_Q[i]);

        Yu.assign(i, i, mu_Q[i] / v2() * sqrt(2.));
        Yd.assign(i, i, md_Q[i] / v1() * sqrt(2.));
        Ye.assign(i, i, me_Q[i] / v1() * sqrt(2.));
        Yn.assign(i, i, mn_Q[i] / v2() * sqrt(2.));
    }

    Yu = VCKM.transpose()*Yu;
    Yn = Yn * UPMNS.hconjugate();

    Q_SUSY = Q_SUSY_temp;
    
}

void SUSY::SetSoftTerms()
{
    // MsQ2, MsU2, MsD2, MsL2, MsN2, MsE2, TU, TD, TN and TE are set to 0 in the constructor.
    // See also GeneralSUSY::SetSoftTerms().
}


///////////////////////////////////////////////////////////////////////////
// Flags

bool SUSY::setFlag(const std::string name, const bool value)
{
    bool res = false;
    if(name.compare("Flag_H") == 0) {
        flag_h = value;
        res = true;
    }
    else if(name.compare("Flag_g") == 0) {
        flag_g = value;
        res = true;
    }
    else if(name.compare("Flag_Chi") == 0) {
        flag_ch = value;
        res = true;
    }
    else if(name.compare("Flag_Chi0") == 0) {
        flag_ne = value;
        res = true;
    }
    else
        res = StandardModel::setFlag(name,value);

    return(res);
}


///////////////////////////////////////////////////////////////////////////

double SUSY::v1() const
{
    return (v() * cosb);
}

double SUSY::v2() const
{
    return (v() * sinb);
}

double SUSY::getMGl() const
{
    return myFH->getMGl();
}


///////////////////////////////////////////////////////////////////////////

double SUSY::Mw() const
{
    return myEWSUSY->Mw_MSSM();
}

double SUSY::Mw_dRho() const
{
    //double delRho = myFH->getFHdeltarho();
    //std::cout << "DeltaRho = " << delRho << std::endl;

    /* Delta rho approximation */
    double Mw_SM = StandardModel::Mw();
    double cW2_SM = Mw_SM*Mw_SM/Mz/Mz;
    double sW2_SM = 1.0 - cW2_SM;
    return ( Mw_SM*(1.0 + cW2_SM/2.0/(cW2_SM - sW2_SM)*myFH->getFHdeltarho()) );
}
