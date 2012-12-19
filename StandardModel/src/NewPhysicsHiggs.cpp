/* 
 * Copyright (C) 2012 SUSYfit Collaboration
 * All rights reserved.
 *
 * For the licensing terms see doc/COPYING.
 */

#include <stdexcept>
#include "NewPhysicsHiggs.h"
#include "EWSM.h"


const std::string NewPhysicsHiggs::NPHIGGSvars[NNPHIGGSvars] 
                  = {"a", "b", "c_u", "c_d", "c_e", "d_3", "d_4"};

const std::string NewPhysicsHiggs::NPHIGGSflags[NNPHIGGSflags] 
    = {"withoutNonUniversalVCinEpsilons"};


NewPhysicsHiggs::NewPhysicsHiggs() : StandardModel() {
}


bool NewPhysicsHiggs::Update(const std::map<std::string,double>& DPars) {
    for (std::map<std::string, double>::const_iterator it = DPars.begin(); it != DPars.end(); it++)
        SetParameter(it->first, it->second);
    if(!StandardModel::Update(DPars)) return (false);

    return (true);
}


bool NewPhysicsHiggs::Init(const std::map<std::string, double>& DPars) {
    Update(DPars);
    return(CheckParameters(DPars)); 
}


bool NewPhysicsHiggs::CheckParameters(const std::map<std::string, double>& DPars) {
    for (int i = 0; i < NNPHIGGSvars; i++) {
        if (DPars.find(NPHIGGSvars[i]) == DPars.end()) {
            std::cout << "missing mandatory NewPhysicsHiggs parameter " 
                      << NPHIGGSvars[i] << std::endl;
            return false;
        }
    }
    return(StandardModel::CheckParameters(DPars));
}

    
void NewPhysicsHiggs::SetParameter(const std::string name, const double& value) {
    if (name.compare("a") == 0)
        a = value;
    else if (name.compare("b") == 0)
        b = value;
    else if (name.compare("c_u") == 0)
        c_u = value;
    else if (name.compare("c_d") == 0)
        c_d = value;
    else if (name.compare("c_e") == 0)
        c_e = value;
    else if (name.compare("d_3") == 0)
        d_3 = value;
    else if (name.compare("d_4") == 0)
        d_4 = value;
    else
        StandardModel::SetParameter(name, value);       
}


bool NewPhysicsHiggs::InitializeModel() {
    SetModelInitialized(StandardModel::InitializeModel());
    myEWepsilons = new EWepsilons(*this);
    return (IsModelInitialized());
}


void NewPhysicsHiggs::SetEWSMflags(EWSM& myEWSM) {
    /* The flags below are used to compute the SM values of the epsilons. */
    myEWSM.setSchemeMw(EWSM::APPROXIMATEFORMULA);
    myEWSM.setSchemeRhoZ(EWSM::OMSI);
    myEWSM.setSchemeKappaZ(EWSM::APPROXIMATEFORMULA);
}


bool NewPhysicsHiggs::SetFlag(const std::string name, const bool& value) {
    bool res = false;
    if (name.compare("EWBURGESS") == 0)
        throw std::runtime_error("Flag EWBURGESS is not applicable to NewPhysicsHiggs"); 
    else if (name.compare("EWCHMN") == 0) 
        throw std::runtime_error("Flag EWCHMN is not applicable to NewPhysicsHiggs"); 
    else if (name.compare("epsilon1SM") == 0) 
        throw std::runtime_error("Flag epsilon1SM is not applicable to NewPhysicsHiggs"); 
    else if (name.compare("epsilon2SM") == 0) 
        throw std::runtime_error("Flag epsilon2SM is not applicable to NewPhysicsHiggs"); 
    else if (name.compare("epsilon3SM") == 0) 
        throw std::runtime_error("Flag epsilon3SM is not applicable to NewPhysicsHiggs"); 
    else if (name.compare("epsilonbSM") == 0) 
        throw std::runtime_error("Flag epsilonbSM is not applicable to NewPhysicsHiggs"); 
    else if (name.compare("withoutNonUniversalVCinEpsilons") == 0) {
        myEWepsilons->setFlagWithoutNonUniversalVC(value);
        res = true;
    } else if (name.compare("R0bApproximate") == 0) {
        if (value) 
            throw std::runtime_error("R0bApproximate=true is not applicable to NewPhysicsHiggs"); 
    } else {
        res = StandardModel::SetFlag(name,value);
    }
    return(res);
}


double NewPhysicsHiggs::epsilon1() const{ 
    double Lambda;
    if (fabs(1.0-a*a) < pow(10.0, -32.0) ) 
        Lambda = pow(10.0, 19.0);
    else
        Lambda = 4.0*M_PI*v()/sqrt(fabs(1.0 - a*a));

    double DeltaEps1 = - 3.0/16.0/M_PI*alphaMz()/c02()*(1.0 - a*a)
                       *log(Lambda*Lambda/mHl/mHl);
    return ( epsilon1_SM() + DeltaEps1 );
}


double NewPhysicsHiggs::epsilon2() const {
    return epsilon2_SM();    
}
    

double NewPhysicsHiggs::epsilon3() const {
    double Lambda;
    if (fabs(1.0-a*a) < pow(10.0, -32.0) ) 
        Lambda = pow(10.0, 19.0);
    else
        Lambda = 4.0*M_PI*v()/sqrt(fabs(1.0 - a*a));

    double DeltaEps3 = 1.0/48.0/M_PI*alphaMz()/s02()*(1.0 - a*a)
                       *log(Lambda*Lambda/mHl/mHl);
    return ( epsilon3_SM() + DeltaEps3 );
}


double NewPhysicsHiggs::epsilonb() const {
    return epsilonb_SM();    
}


////////////////////////////////////////////////////////////////////////     

double NewPhysicsHiggs::Mw() const {
    return myEWepsilons->Mw(epsilon1(), epsilon2(), epsilon3());
}


double NewPhysicsHiggs::cW2() const {
    return ( Mw()*Mw()/Mz/Mz );
}

    
double NewPhysicsHiggs::sW2() const {
    return ( 1.0 - cW2() );
}

    
complex NewPhysicsHiggs::rhoZ_l(const StandardModel::lepton l) const {
    return myEWepsilons->rhoZ_l(l, epsilon1());
}

    
complex NewPhysicsHiggs::rhoZ_q(const StandardModel::quark q) const {
    switch (q) {
        case StandardModel::UP:
        case StandardModel::DOWN:
        case StandardModel::CHARM:
        case StandardModel::STRANGE:
            return myEWepsilons->rhoZ_q(q, epsilon1());
        case StandardModel::BOTTOM:
            return myEWepsilons->rhoZ_b(epsilon1(), epsilonb());
        case StandardModel::TOP:
            return complex(0.0, 0.0, false);
        default:
            throw std::runtime_error("Error in NewPhysicsHiggs::rhoZ_q()");        
    }
}


complex NewPhysicsHiggs::kappaZ_l(const StandardModel::lepton l) const {
    return myEWepsilons->kappaZ_l(l, epsilon1(), epsilon3());
}


complex NewPhysicsHiggs::kappaZ_q(const StandardModel::quark q) const {
    switch (q) {
        case StandardModel::UP:
        case StandardModel::DOWN:
        case StandardModel::CHARM:
        case StandardModel::STRANGE:
            return myEWepsilons->kappaZ_q(q, epsilon1(), epsilon3());
        case StandardModel::BOTTOM:
            return myEWepsilons->kappaZ_b(epsilon1(), epsilon3(), epsilonb());
        case StandardModel::TOP:
            return complex(0.0, 0.0, false);
        default:
            throw std::runtime_error("Error in NewPhysicsHiggs::kappaZ_q()");        
    }
}
      
    
complex NewPhysicsHiggs::gVl(const StandardModel::lepton l) const {
    return myEWepsilons->gVl(l, epsilon1(), epsilon3());
}


complex NewPhysicsHiggs::gVq(const StandardModel::quark q) const {
    switch (q) {
        case StandardModel::UP:
        case StandardModel::DOWN:
        case StandardModel::CHARM:
        case StandardModel::STRANGE:
            return myEWepsilons->gVq(q, epsilon1(), epsilon3());
        case StandardModel::BOTTOM:
            return myEWepsilons->gVb(epsilon1(), epsilon3(), epsilonb());
        case StandardModel::TOP:
            return complex(0.0, 0.0, false);
        default:
            throw std::runtime_error("Error in NewPhysicsHiggs::gVq()");        
    }
}


complex NewPhysicsHiggs::gAl(const StandardModel::lepton l) const {
    return myEWepsilons->gAl(l, epsilon1());
}


complex NewPhysicsHiggs::gAq(const StandardModel::quark q) const {
    switch (q) {
        case StandardModel::UP:
        case StandardModel::DOWN:
        case StandardModel::CHARM:
        case StandardModel::STRANGE:
            return myEWepsilons->gAq(q, epsilon1());
        case StandardModel::BOTTOM:
            return myEWepsilons->gAb(epsilon1(), epsilonb());
        case StandardModel::TOP:
            return complex(0.0, 0.0, false);
        default:
            throw std::runtime_error("Error in NewPhysicsHiggs::gAq()");        
    }
}

    
double NewPhysicsHiggs::GammaW() const {
    throw std::runtime_error("NewPhysicsHiggs::GammaW() is not implemented.");         
}
 


