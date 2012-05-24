/* 
 * File:   Mw.cpp
 * Author: mishima
 */

#include "Mw.h"


Mw::Mw(const EW& EW_i) : ThObservable(EW_i) {
    myMw = EW_i.getSM().Mw();    

    if ( EW_i.checkModelForSTU() ) {
        double alpha = EW_i.getSM().getAle();
        double c = sqrt(EW_i.c2());
        double c2 = EW_i.c2();
        double s2 = EW_i.s2();
        
        myMw -= alpha*c*EW_i.getSM().getMz()/4.0/(c2-s2)
                *( EW_i.S() - 2.0*c2*EW_i.T() - (c2-s2)*EW_i.U()/2.0/s2 );
    }
}

double Mw::getThValue() {   
    return myMw;
}

