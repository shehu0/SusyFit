/*
 * Copyright (C) 2015 HEPfit Collaboration
 * All rights reserved.
 *
 * For the licensing terms see doc/COPYING.
 */

#include "li_3lj.h"
#include "StandardModel.h"
// #include "SUSYMatching.h"

li_3lj::li_3lj(const StandardModel& SM_i): ThObservable(SM_i)
{
};

double li_3lj::computeThValue()
{
    return 0;
}

mu_3e::mu_3e(const StandardModel& SM_i)
: li_3lj(SM_i), mySM(SM_i)
{}

double mu_3e::computeThValue()
{
    double alph = mySM.getAle();
    double mE = mySM.getLeptons(StandardModel::ELECTRON).getMass();
    double mMU = mySM.getLeptons(StandardModel::MU).getMass();
    gslpp::vector<complex> ** allcoeff_m3e = mySM.getMyLeptonFlavour()->ComputeCoeffli_3lj(1);
    double Brmu3e = ((*(allcoeff_m3e[LO])) * (*(allcoeff_m3e[LO])).conjugate()).abs();
    
//    	Mu3Erate = (alph**2.d0/(32.d0*pi))*(mMu**5.d0)*(VLMuE**2.d0 
//     .	+ VRMuE**2.d0 - 4.d0*(VLMuE*ARMuE + VRMuE*ALMuE) + 
//     . 	(ALMuE**2.d0 + ARMuE**2.d0)*((16.d0/3.d0)*dlog(mMU/(2.d0*mE))- 
//     . 14.d0/9.d0) + (1.d0/6.d0)*(B1LMu3E**2.d0 + B1RMu3E**2.d0) +
//     . (1.d0/3.d0)*(B2LMu3E**2.d0 + B2RMu3E**2.d0) + (1.d0/24.d0)* 
//     . (B3LMu3E**2.d0 + B3RMu3E**2.d0) + 6.d0*(B4LMu3E**2.d0 + 
//     . B4RMu3E**2.d0) - (B3LMu3E*B4LMu3E + B3RMu3E*B4RMu3E) + 
//     . (2.d0/3.d0)*(VLMuE*B1LMu3E + VRMuE*B1RMu3E + VLMuE*B2LMu3E 
//     . + VRMuE*B2RMu3E) - (4.d0/3.d0)*(ARMuE*B1LMu3E + ALMuE*B1RMu3E 
//     . + ARMuE*B2LMu3E + ALMuE*B2RMu3E) + (1.d0/3.d0)*(2.d0*(
//     . FLLMu3E**2.d0 + FRRMu3E**2.d0) + FLRMu3E**2.d0 + FRLMu3E**2.d0
//     . + 2.d0*(B1LMu3E*FLLMu3E + B1RMu3E*FRRMu3E + B2LMu3E*FLRMu3E 
//     . + B2RMu3E*FRLMu3E) + 4.d0*(VLMuE*FLLMu3E + VRMuE*FRRMu3E)
//     . + 2.d0*(VLMuE*FLRMu3E + VRMuE*FRLMu3E) - 8.d0*(ARMuE*FLLMu3E 
//     . + ALMuE*FRRMu3E) - 4.d0*(ALMuE*FRLMu3E + ARMuE*FLRMu3E)))
//
//	Brmu3E = Mu3Erate/(3.d0*(10.d0**(-19.d0)))
//
                
//    double Mu3Erate = (alph*alph/(32.0*M_PI))*(pow(mMU,5.0))*
//                       (VLMuE**2.0 + VRMuE**2.0 - 4.0*(VLMuE*ARMuE + VRMuE*ALMuE)
//                        + (ALMuE**2.0 + ARMuE**2.0)*((16.0/3.0)*log(mMU/(2.0*mE))-14.0/9.0)
//                        + (1.d0/6.0)*(B1LMu3E**2.0 + B1RMu3E**2.0)
//                        + (1.d0/3.0)*(B2LMu3E**2.0 + B2RMu3E**2.0)
//                        + (1.d0/24.0)*(B3LMu3E**2.0 + B3RMu3E**2.0)
//                        + 6.0*(B4LMu3E**2.0 + B4RMu3E**2.0)
//                        - (B3LMu3E*B4LMu3E + B3RMu3E*B4RMu3E)
//                        + (2.0/3.0)*(VLMuE*B1LMu3E + VRMuE*B1RMu3E + VLMuE*B2LMu3E + VRMuE*B2RMu3E)
//                        - (4.0/3.0)*(ARMuE*B1LMu3E + ALMuE*B1RMu3E + ARMuE*B2LMu3E + ALMuE*B2RMu3E)
//                        + (1.0/3.0)*(2.0*(FLLMu3E**2.0 + FRRMu3E**2.0)
//                         + FLRMu3E**2.0 + FRLMu3E**2.0
//                         + 2.0*(B1LMu3E*FLLMu3E + B1RMu3E*FRRMu3E + B2LMu3E*FLRMu3E + B2RMu3E*FRLMu3E)
//                         + 4.0*(VLMuE*FLLMu3E + VRMuE*FRRMu3E)
//                         + 2.0*(VLMuE*FLRMu3E + VRMuE*FRLMu3E) 
//                         - 8.0*(ARMuE*FLLMu3E + ALMuE*FRRMu3E) 
//                         - 4.0*(ALMuE*FRLMu3E + ARMuE*FLRMu3E)))
//
//    double Brmu3e = Mu3Erate/(3.0*(pow(10.0,-19.0)))

                
//
//    C_1 = ((*(allcoeff[LO]))(0) + (*(allcoeff[NLO]))(0));
//    C_2 = ((*(allcoeff[LO]))(1) + (*(allcoeff[NLO]))(1));
//    C_2L = (*(allcoeff[LO]))(1);
//    C_3 = ((*(allcoeff[LO]))(2) + (*(allcoeff[NLO]))(2));
//    C_4 = ((*(allcoeff[LO]))(3) + (*(allcoeff[NLO]))(3));
//    C_5 = ((*(allcoeff[LO]))(4) + (*(allcoeff[NLO]))(4));
//    C_6 = ((*(allcoeff[LO]))(5) + (*(allcoeff[NLO]))(5));
//    C_7 = ((*(allcoeff[LO]))(6) + (*(allcoeff[NLO]))(6));
//    C_8L = (*(allcoeff[LO]))(7);
//    C_9 = ((*(allcoeff[LO]))(8) + (*(allcoeff[NLO]))(8));
//    C_10 = ((*(allcoeff[LO]))(9) + (*(allcoeff[NLO]))(9));
//    C_S = ((*(allcoeff[LO]))(10) + (*(allcoeff[NLO]))(10));
//    C_P = ((*(allcoeff[LO]))(11) + (*(allcoeff[NLO]))(11));
//
    return Brmu3e;
}

tau_3mu::tau_3mu(const StandardModel& SM_i)
: li_3lj(SM_i), mySM(SM_i)
{}

double tau_3mu::computeThValue()
{
//    double alph = mySM.getAle();
//    double mTAU = mySM.getLeptons(StandardModel::TAU).getMass();
//    gslpp::vector<complex> ** allcoeff_tm = mySM.getMyLeptonFlavour()->ComputeCoeffli_lj_gamma(2);
//    double BR_tau_mu_gamma = (alph*pow(mTAU,5.0) * ((*(allcoeff_tm[LO])) * (*(allcoeff_tm[LO])).conjugate()).abs() / (2.26e-12) );
    return 0.0;
}

tau_3e::tau_3e(const StandardModel& SM_i)
: li_3lj(SM_i), mySM(SM_i)
{}

double tau_3e::computeThValue()
{
//    double alph = mySM.getAle();
//    double mTAU = mySM.getLeptons(StandardModel::TAU).getMass();
//    gslpp::vector<complex> ** allcoeff_te = mySM.getMyLeptonFlavour()->ComputeCoeffli_lj_gamma(3);
//    double BR_tau_e_gamma = (alph*pow(mTAU,5.0) * ((*(allcoeff_te[LO])) * (*(allcoeff_te[LO])).conjugate()).abs() / (2.26e-12) );
    return 0.0;
}
