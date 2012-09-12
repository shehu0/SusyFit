/* 
 * File:   AFBcharm.cpp
 * Author: mishima
 */

#include "AFBcharm.h"


double AFBcharm::getThValue() {   
    double AFB_c = 3.0/4.0*myEW.A_l(SM.ELECTRON)*myEW.A_q(SM.CHARM);

    if ( myEW.checkModelForSTU() ) {
        double alpha = myEW.getSM().alphaMz();
        double c2 = myEW.c2();
        double s2 = myEW.s2();
        double s4 = s2*s2;
        double s6 = s4*s2;        
        double s8 = s6*s2;

        AFB_c -= 9.0*alpha*s2*(39.0-310.0*s2+992.0*s4-1600.0*s6+1024.0*s8)
                /pow(1.0-4.0*s2+8.0*s4, 2.0)
                /pow(9.0-24.0*s2+32.0*s4, 2.0)/(c2-s2)
                 *( myEW.S() - 4.0*c2*s2*myEW.T() );
    }

    return AFB_c;
}
        
