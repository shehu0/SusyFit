/* 
 * Copyright (C) 2012-2013 SusyFit Collaboration
 * All rights reserved.
 *
 * For the licensing terms see doc/COPYING.
 */

#include "Mw.h"


double Mw::computeThValue() 
{
    double myMw;
    EW::EWTYPE myEWTYPE = myEW.getEWTYPE();
    
    if (myEWTYPE==EW::EWCHMN)  
        myMw = myEW.getMyEW_CHMN().Mw();
    else if (myEWTYPE==EW::EWABC)
        myMw = myEW.getMyEW_ABC().Mw(false);
    else if (myEWTYPE==EW::EWABC2)
        myMw = myEW.getMyEW_ABC().Mw(true);
    else
        myMw = SM.Mw();

    return myMw;
}

