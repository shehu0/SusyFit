/* 
 * Copyright (C) 2012 SusyFit Collaboration
 * All rights reserved.
 *
 * For the licensing terms see doc/COPYING.
 */

#include "DmBs.h"

double  DmBs::getThValue() {
    return(2. * AmpBs(FULLNLO).abs());
}