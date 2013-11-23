/*
 * Copyright (C) 2012-2013 SusyFit Collaboration
 * All rights reserved.
 *
 * For the licensing terms see doc/COPYING.
 */

#include <stdexcept>
#include <EWSM.h>
#include "NPSTU.h"


const std::string NPSTU::STUvars[NSTUvars]
= {"obliqueS", "obliqueT", "obliqueU"};

const std::string NPSTU::STUflags[NSTUflags]
= {"EWBURGESS"};

NPSTU::NPSTU()
: NPbase(), myEW_BURGESS(*this)
{
    FlagEWBURGESS = false;
}


bool NPSTU::InitializeModel()
{
    setModelInitialized(NPbase::InitializeModel());
    return (IsModelInitialized());
}


void NPSTU::setEWSMflags(EWSM& myEWSM)
{
    NPbase::setEWSMflags(myEWSM);
}


bool NPSTU::Init(const std::map<std::string, double>& DPars)
{
    Update(DPars);
    return(CheckParameters(DPars));
}


bool NPSTU::Update(const std::map<std::string,double>& DPars)
{
    for (std::map<std::string, double>::const_iterator it = DPars.begin(); it != DPars.end(); it++)
        setParameter(it->first, it->second);
    if(!NPbase::Update(DPars)) return (false);
    return (true);
}


void NPSTU::setParameter(const std::string name, const double& value)
{
    if (name.compare("obliqueS") == 0)
        myObliqueS = value;
    else if (name.compare("obliqueT") == 0)
        myObliqueT = value;
    else if (name.compare("obliqueU") == 0)
        myObliqueU = value;
    else
        NPbase::setParameter(name, value);
}


bool NPSTU::CheckParameters(const std::map<std::string, double>& DPars)
{
    for (int i = 0; i < NSTUvars; i++) {
        if (DPars.find(STUvars[i]) == DPars.end()) {
            std::cout << "ERROR: Missing mandatory NPSTU parameter "
                      << STUvars[i] << std::endl;
            return false;
        }
    }
    return(NPbase::CheckParameters(DPars));
}


bool NPSTU::setFlag(const std::string name, const bool& value)
{
    bool res = false;
    if (name.compare("EWBURGESS") == 0) {
        FlagEWBURGESS = value;
        res = true;
    } else
        res = NPbase::setFlag(name,value);

    return(res);
}

bool NPSTU::CheckFlags() const
{
    if ( FlagEWBURGESS && IsFlagEWCHMN() )
        throw std::runtime_error("ERROR: Flags EWBURGESS and EWCHMN are incompatible with each other.");

    return(NPbase::CheckFlags());
}


////////////////////////////////////////////////////////////////////////

double NPSTU::Mw() const
{
    double myMw = myEWSM->Mw_SM();

    if (IsFlagEWBURGESS())
        return myEW_BURGESS.Mw(myMw);

    double alpha = StandardModel::alphaMz();
    double c2 = myEWSM->cW2_SM();
    double s2 = myEWSM->sW2_SM();

    myMw *= 1.0 - alpha/4.0/(c2-s2)
            *( obliqueS() - 2.0*c2*obliqueT() - (c2-s2)*obliqueU()/2.0/s2 );

    //std::cout << "Mw: c_S=" << - alpha/4.0/(c2-s2) << std::endl;
    //std::cout << "Mw: c_T=" << - alpha/4.0/(c2-s2)*(- 2.0*c2) << std::endl;
    //std::cout << "Mw: c_U=" << - alpha/4.0/(c2-s2)*(- (c2-s2)/2.0/s2) << std::endl;

    return myMw;
}


double NPSTU::cW2() const
{
    return ( Mw()*Mw()/Mz/Mz );
}


double NPSTU::sW2() const
{
    return ( 1.0 - cW2() );
}


double NPSTU::GammaW() const
{
    double Gamma_W = myEWSM->GammaW_SM();

    if (IsFlagEWBURGESS())
        return myEW_BURGESS.GammaW(Gamma_W);

    double alpha = StandardModel::alphaMz();
    double c2 = myEWSM->cW2_SM();
    double s2 = myEWSM->sW2_SM();

    Gamma_W *= 1.0 - 3.0*alpha/4.0/(c2-s2)
               *( obliqueS() - 2.0*c2*obliqueT()
                  - (c2-s2)*obliqueU()/2.0/s2 );

    //std::cout << "Gw: c_S=" << - 3.0*alpha/4.0/(c2-s2) << std::endl;
    //std::cout << "Gw: c_T=" << - 3.0*alpha/4.0/(c2-s2)*(- 2.0*c2) << std::endl;
    //std::cout << "Gw: c_U=" << - 3.0*alpha/4.0/(c2-s2)*(- (c2-s2)/2.0/s2) << std::endl;

    return Gamma_W;
}



