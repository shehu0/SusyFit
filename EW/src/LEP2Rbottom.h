/* 
 * File:   LEP2Rbottom.h
 * Author: mishima
 */

#ifndef LEP2RBOTTOM_H
#define	LEP2RBOTTOM_H

#include <ThObservable.h>
#include "EW.h"


class LEP2Rbottom : public ThObservable {
public:

    /**
     * @brief LEP2Rbottom constructor
     * @param[in] EW_i an object of EW class
     * @param[in] sqrt_s_i the CM energy of the e^+ e^- pair
     */
    LEP2Rbottom(const EW& EW_i, const double sqrt_s_i);

    /**
     * @return the ratio of the b-bbar cross section to the hadronic cross section at sqrt_s
     */
    double getThValue();

    /**
     * @brief set flags for radiative corrections
     * @param[in] bDP_i with/without dressed gauge-boson propagators
     * @param[in] bWEAK_i with/without weak corrections
     * @param[in] bQED_i with/without QED corrections
     */
    void setFlags(const bool bDP_i, const bool bWEAK_i, const bool bQED_i) {
        this->bDP = bDP_i;
        this->bWEAK = bWEAK_i;
        this->bQED = bQED_i;
    }
    

private:
    const EW& myEW;
    const double sqrt_s;
    bool bDP, bWEAK, bQED;
};

#endif	/* LEP2RBOTTOM_H */

