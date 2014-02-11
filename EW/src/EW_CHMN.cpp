/* 
 * Copyright (C) 2012-2013 SusyFit Collaboration
 * All rights reserved.
 *
 * For the licensing terms see doc/COPYING.
 */

#include <NPbase.h>
#include "EW_CHMN.h"


EW_CHMN::EW_CHMN(const StandardModel& SM_i) 
: SM(SM_i) 
{
    if ( SM.ModelName().compare("StandardModel") != 0
            && SM.ModelName().compare("NPSTU") != 0 )
        throw std::runtime_error("EW_CHMN::EW_CHMN() is not applicable for the model " + SM.ModelName());
}


////////////////////////////////////////////////////////////////////////   

double EW_CHMN::Mw() const 
{
    return ( 80.365 + DeltaMw() );
}


double EW_CHMN::GammaW() const 
{
    double Rw = 2.1940 + DeltaRw();
    return ( 0.33904*pow(Mw(), 3.0)
             *SM.getGF()*(1.0 + 0.008478*Rw + 0.00065*x_s()) );
}


double EW_CHMN::DeltaSz() const 
{
    return ( S() + DeltaRz() + DeltaSz_SM() );
}


double EW_CHMN::DeltaTz() const 
{
    // \Delta\bar\delta_G = 0
    return ( T() + 1.49*DeltaRz() + DeltaTz_SM() );
}


double EW_CHMN::gL_l(const StandardModel::lepton l) const 
{
    double c1, c2, c3;
    switch (l) {
        case StandardModel::NEUTRINO_1:
        case StandardModel::NEUTRINO_2:
        case StandardModel::NEUTRINO_3:
            c1 = 0.50199;
            c2 = 0.45250;
            c3 = 0.00469;
            break;
        case StandardModel::ELECTRON:
        case StandardModel::MU:
        case StandardModel::TAU:
            c1 = -0.26920;
            c2 = -0.24338;
            c3 = 1.00413;
            break;
        default: 
            throw std::runtime_error("Error in EW_CHMN::gL_l()");  
    }

    double deltaGVl = 0.0, deltaGAl = 0.0;
    if (SM.ModelName().compare("StandardModel") != 0) {
        deltaGVl = (static_cast<const NPbase*> (&SM))->deltaGVl(l);
        deltaGAl = (static_cast<const NPbase*> (&SM))->deltaGAl(l);
    }

    return ( c1 + c2*Delta_gbarZ2() + c3*Delta_sbar2()
             + (deltaGVl + deltaGAl)/2.0 );
}


double EW_CHMN::gR_l(const StandardModel::lepton l) const 
{
    double c1, c2, c3;
    switch (l) {
        case StandardModel::NEUTRINO_1:
        case StandardModel::NEUTRINO_2:
        case StandardModel::NEUTRINO_3:
            c1 = 0.0;
            c2 = 0.0;
            c3 = 0.0;
            break;
        case StandardModel::ELECTRON:
        case StandardModel::MU:
        case StandardModel::TAU:
            c1 = 0.23207;
            c2 = 0.20912;
            c3 = 1.00784;
            break;
        default: 
            throw std::runtime_error("Error in EW_CHMN::gR_l()");  
    }

    double deltaGVl = 0.0, deltaGAl = 0.0;
    if (SM.ModelName().compare("StandardModel") != 0) {
        deltaGVl = (static_cast<const NPbase*> (&SM))->deltaGVl(l);
        deltaGAl = (static_cast<const NPbase*> (&SM))->deltaGAl(l);
    }

    return ( c1 + c2*Delta_gbarZ2() + c3*Delta_sbar2()
             + (deltaGVl - deltaGAl)/2.0 );
}


double EW_CHMN::gL_q(const QCD::quark q) const
{
    double c1, c2, c3;
    switch (q) {
        case StandardModel::UP:
        case StandardModel::CHARM:
            c1 = 0.34675;
            c2 = 0.31309;
            c3 = -0.66793;
            break;
        case StandardModel::DOWN:
        case StandardModel::STRANGE:
            c1 = -0.42434;
            c2 = -0.38279;
            c3 = 0.33166;
            break;
        case StandardModel::BOTTOM:
            c1 = -0.42116;
            c2 = -0.38279;
            c3 = 0.33166;
            c1 += -0.000058*x_h() + 0.000128*x_t();
            break;
        case StandardModel::TOP:
        default: 
            throw std::runtime_error("Error in EW_CHMN::gL_q()");  
    }

    double deltaGVq = 0.0, deltaGAq = 0.0;
    if (SM.ModelName().compare("StandardModel") != 0) {
        deltaGVq = (static_cast<const NPbase*> (&SM))->deltaGVq(q);
        deltaGAq = (static_cast<const NPbase*> (&SM))->deltaGAq(q);
    }

    return ( c1 + c2*Delta_gbarZ2() + c3*Delta_sbar2()
             + (deltaGVq + deltaGAq)/2.0 );
}


double EW_CHMN::gR_q(const QCD::quark q) const
{
    double c1, c2, c3;
    switch (q) {
        case StandardModel::UP:
        case StandardModel::CHARM:
            c1 = -0.15470;
            c2 = -0.13942;
            c3 = -0.67184;
            break;
        case StandardModel::DOWN:
        case StandardModel::STRANGE:
            c1 = 0.07734;
            c2 = 0.06971;
            c3 = 0.33590;
            break;
        case StandardModel::BOTTOM:
            c1 = 0.07742;
            c2 = 0.06971;
            c3 = 0.33590;
            c1 += -0.000042*x_h() - 0.000025*pow(x_h(), 4.0);
            break;
        case StandardModel::TOP:
        default: 
            throw std::runtime_error("Error in EW_CHMN::gR_q()");  
    }

    double deltaGVq = 0.0, deltaGAq = 0.0;
    if (SM.ModelName().compare("StandardModel") != 0) {
        deltaGVq = (static_cast<const NPbase*> (&SM))->deltaGVq(q);
        deltaGAq = (static_cast<const NPbase*> (&SM))->deltaGAq(q);
    }

    return ( c1 + c2*Delta_gbarZ2() + c3*Delta_sbar2()
             + (deltaGVq - deltaGAq)/2.0 );
}


double EW_CHMN::GammaZ_l(StandardModel::lepton l) const 
{
    double Qf = SM.getLeptons(l).getCharge();
    double gL = gL_l(l);
    double gR = gR_l(l);
    double GammaZ = SM.getGF()*pow(SM.getMz(), 3.0)/(6.0*sqrt(2.0)*M_PI);
    GammaZ *= ( (gL + gR)*(gL + gR) + deltaImKappa_l(l) )*CV_l(l) 
              + (gL - gR)*(gL - gR)*CA_l(l);
    GammaZ *= 1.0 + 3.0/4.0*Qf*Qf*SM.alphaMz()/M_PI;
    GammaZ += DeltaEWQCD_l(l);
    return GammaZ;
}


double EW_CHMN::GammaZ_q(QCD::quark q) const
{
    double Qf = SM.getQuarks(q).getCharge();
    double gL = gL_q(q);
    double gR = gR_q(q);
    double GammaZ = SM.getGF()*pow(SM.getMz(), 3.0)/(6.0*sqrt(2.0)*M_PI);
    GammaZ *= ( (gL + gR)*(gL + gR) + deltaImKappa_q(q) )*CV_q(q) 
              + (gL - gR)*(gL - gR)*CA_q(q);
    GammaZ *= 1.0 + 3.0/4.0*Qf*Qf*SM.alphaMz()/M_PI;
    GammaZ += DeltaEWQCD_q(q);
    return GammaZ;
}


double EW_CHMN::GammaZ_had() const
{
    return ( GammaZ_q(StandardModel::UP) 
             + GammaZ_q(StandardModel::DOWN) 
             + GammaZ_q(StandardModel::CHARM) 
             + GammaZ_q(StandardModel::STRANGE) 
             + GammaZ_q(StandardModel::BOTTOM) );
}


double EW_CHMN::GammaZ() const 
{
    return ( GammaZ_l(StandardModel::NEUTRINO_1)*3.0 
             + GammaZ_l(StandardModel::ELECTRON) 
             + GammaZ_l(StandardModel::MU) 
             + GammaZ_l(StandardModel::TAU) 
             + GammaZ_had() );
}


double EW_CHMN::R_l(const StandardModel::lepton l) const
{
    return ( GammaZ_had()/GammaZ_l(l) );
}


double EW_CHMN::R_c() const 
{
    return ( GammaZ_q(StandardModel::CHARM)/GammaZ_had() );
}


double EW_CHMN::R_b() const 
{
    return ( GammaZ_q(StandardModel::BOTTOM)/GammaZ_had() );    
}


double EW_CHMN::sigma0_had() const
{
    return ( 12.0*M_PI/SM.getMz()/SM.getMz()
             *GammaZ_l(StandardModel::ELECTRON)*GammaZ_had()/GammaZ()/GammaZ() );
}


double EW_CHMN::A_l(const StandardModel::lepton l) const
{
    double gL = gL_l(l);
    double gR = gR_l(l);
    return ( (gL*gL - gR*gR)/(gL*gL + gR*gR) );
}


double EW_CHMN::A_q(const QCD::quark q) const
{
    double gL = gL_q(q);
    double gR = gR_q(q);
    return ( (gL*gL - gR*gR)/(gL*gL + gR*gR) );
}


double EW_CHMN::AFB_l(const StandardModel::lepton l) const
{
    return ( 3.0/4.0*A_l(StandardModel::ELECTRON)
             *A_l(l) );   
}


double EW_CHMN::AFB_q(const QCD::quark q) const
{
    return ( 3.0/4.0*A_l(StandardModel::ELECTRON)
             *A_q(q) );    
}
    

double EW_CHMN::sin2thetaEff() const 
{
    double gL = gL_l(StandardModel::ELECTRON);
    double gR = gR_l(StandardModel::ELECTRON);
    return ( gR/(gR - gL)/2.0 );
}


double EW_CHMN::S() const
{
    if (SM.ModelName().compare("StandardModel") != 0)
        return ( (static_cast<const NPbase*> (&SM))->obliqueS() );
    else
        return 0.0;
}


double EW_CHMN::T() const
{
    if (SM.ModelName().compare("StandardModel") != 0)
        return ( (static_cast<const NPbase*> (&SM))->obliqueT() );
    else
        return 0.0;
}


double EW_CHMN::U() const
{
    if (SM.ModelName().compare("StandardModel") != 0)
        return ( (static_cast<const NPbase*> (&SM))->obliqueU() );
    else
        return 0.0;
}
    
    
////////////////////////////////////////////////////////////////////////   

double EW_CHMN::x_alpha() const 
{
    return ( (SM.getDAle5Mz() - 0.0277)/0.0003 );
}


double EW_CHMN::x_t() const 
{
    return ( (SM.getMtpole() - 172.0)/3.0 );
}


double EW_CHMN::x_h() const
{
    return ( log(SM.getMHl()/100.0)/log(10.0) );
}


double EW_CHMN::x_s() const 
{
    return ( (SM.getAlsMz() - 0.118)/0.003 );
}
    
    
double EW_CHMN::DeltaRz() const 
{
    return DeltaRz_SM();
}

double EW_CHMN::DeltaRw() const 
{
    return DeltaRw_SM();    
}


double EW_CHMN::DeltaMw() const 
{
    // \Delta\bar\delta_G = 0
    return ( - 0.288*S() + 0.418*T() + 0.337*U() - 0.0055*x_alpha()
             + DeltaMw_SM() );
}


double EW_CHMN::Delta_gbarZ2() const
{
    return ( 0.00412*DeltaTz() ); 
}


double EW_CHMN::Delta_sbar2() const
{
    return ( 0.00360*DeltaSz() - 0.00241*DeltaTz() + 0.00011*x_alpha() );
}


double EW_CHMN::DeltaSz_SM() const 
{ 
    return ( 0.2217*x_h() - 0.1188*x_h()*x_h() + 0.0320*x_h()*x_h()*x_h() 
             - 0.0014*x_t() + 0.0005*x_s() );
}


double EW_CHMN::DeltaTz_SM() const 
{
    return ( - 0.0995*x_h() - 0.2858*x_h()*x_h() + 0.1175*x_h()*x_h()*x_h() 
             + 0.0367*x_t() + 0.00026*x_t()*x_t() - 0.0017*x_h()*x_t() 
             - 0.0033*x_s() - 0.0001*x_t()*x_s() );
}
    
    
double EW_CHMN::DeltaMw_SM() const 
{ 
    return ( - 0.137*x_h() - 0.019*x_h()*x_h() + 0.018*x_t() 
             - 0.005*x_alpha() - 0.002*x_s() );
}


double EW_CHMN::DeltaRz_SM() const
{
    return ( -0.124*(log(1.0 + (26.0/SM.getMHl())*(26.0/SM.getMHl())) 
                     - log(1.0 + (26.0/100.0)*(26.0/100.0))) );
}


double EW_CHMN::DeltaRw_SM() const 
{
    return ( -0.16*(log(1.0 + (23.0/SM.getMHl())*(23.0/SM.getMHl())) 
                    - log(1.0 + (23.0/100.0)*(23.0/100.0))) );    
}


double EW_CHMN::CV_l(StandardModel::lepton l) const 
{
    switch (l) {
        case StandardModel::NEUTRINO_1:
        case StandardModel::NEUTRINO_2:
        case StandardModel::NEUTRINO_3:
        case StandardModel::ELECTRON:
        case StandardModel::MU:
        case StandardModel::TAU:
            return 1.0;
        default: 
            throw std::runtime_error("Error in EW_CHMN::CV_l()");  
    }
}


double EW_CHMN::CV_q(QCD::quark q) const 
{
    switch (q) {
        case StandardModel::UP:
            return ( 3.1166 + 0.0030*x_s() );
        case StandardModel::DOWN:
        case StandardModel::STRANGE:
        case StandardModel::CHARM:
            return ( 3.1167 + 0.0030*x_s() );
        case StandardModel::BOTTOM:
            return ( 3.1185 + 0.0030*x_s() );
        case StandardModel::TOP:
        default: 
            throw std::runtime_error("Error in EW_CHMN::CV_q()");  
    }
}


double EW_CHMN::CA_l(StandardModel::lepton l) const
{
    switch (l) {
        case StandardModel::NEUTRINO_1:
        case StandardModel::NEUTRINO_2:
        case StandardModel::NEUTRINO_3:
        case StandardModel::ELECTRON:
        case StandardModel::MU:
            return 1.0;
        case StandardModel::TAU:
            return 0.9977;
        default: 
            throw std::runtime_error("Error in EW_CHMN::CA_l()");  
    }
}


double EW_CHMN::CA_q(QCD::quark q) const 
{
    switch (q) {
        case StandardModel::UP:
            return ( 3.1377 + 0.00014*x_t() + 0.0041*x_s() );
        case StandardModel::DOWN:
        case StandardModel::STRANGE:
            return ( 3.0956 - 0.00015*x_t() + 0.0019*x_s() );
        case StandardModel::CHARM:
            return ( 3.1369 + 0.00014*x_t() + 0.0043*x_s() );
        case StandardModel::BOTTOM:
            return ( 3.0758 - 0.00015*x_t() + 0.0028*x_s() );
        case StandardModel::TOP:
        default: 
            throw std::runtime_error("Error in EW_CHMN::CA_q()");  
    }
}


double EW_CHMN::deltaImKappa_l(StandardModel::lepton l) const 
{
    switch (l) {
        case StandardModel::NEUTRINO_1:
        case StandardModel::NEUTRINO_2:
        case StandardModel::NEUTRINO_3:
            return 0.0;
        case StandardModel::ELECTRON:
        case StandardModel::MU:
        case StandardModel::TAU:
            return 0.0000368;
        default: 
            throw std::runtime_error("Error in EW_CHMN::deltaImKappa_l()");  
    }
}
    
    
double EW_CHMN::deltaImKappa_q(QCD::quark q) const 
{
    switch (q) {
        case StandardModel::UP:
        case StandardModel::CHARM:
            return 0.0000146; 
        case StandardModel::DOWN:
        case StandardModel::STRANGE:
            return 0.0000032;
        case StandardModel::BOTTOM:
            return 0.0000026;
        case StandardModel::TOP:
        default: 
            throw std::runtime_error("Error in EW_CHMN::deltaImKappa_q()");  
    }
}


double EW_CHMN::DeltaEWQCD_l(StandardModel::lepton l) const 
{
    switch (l) {
        case StandardModel::NEUTRINO_1:
        case StandardModel::NEUTRINO_2:
        case StandardModel::NEUTRINO_3:
        case StandardModel::ELECTRON:
        case StandardModel::MU:
        case StandardModel::TAU:
            return 0.0;
        default: 
            throw std::runtime_error("Error in EW_CHMN::DeltaEWQCD_l()");  
    }
}
    

double EW_CHMN::DeltaEWQCD_q(QCD::quark q) const 
{
    switch (q) {
        case StandardModel::UP:
        case StandardModel::CHARM:
            return ( - 0.000113 ); 
        case StandardModel::DOWN:
        case StandardModel::STRANGE:
            return ( - 0.000160 ); 
        case StandardModel::BOTTOM:
            return ( - 0.000040 ); 
        case StandardModel::TOP:
        default: 
            throw std::runtime_error("Error in EW_CHMN::DeltaEWQCD_q()");  
    }
}

