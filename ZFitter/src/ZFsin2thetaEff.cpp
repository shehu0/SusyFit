/* 
 * Copyright (C) 2012 SUSYfit Collaboration
 * All rights reserved.
 *
 * For the licensing terms see doc/COPYING.
 */

#include "ZFsin2thetaEff.h"


double ZFsin2thetaEff::getThValue() {
    return myZF.s2teff_f(1);
}

