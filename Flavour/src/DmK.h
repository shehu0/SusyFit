/* 
 * Copyright (C) 2012 SusyFit Collaboration
 * All rights reserved.
 *
 * For the licensing terms see doc/COPYING.
 */

#ifndef DMK_H
#define	DMK_H

#include <ThObservable.h>
#include "Flavour.h"
#include "AmpDK2.h"

/**
 * @addtogroup Flavour
 * @brief A project for Flavour observables.
 * @{
 */

/**
 * @class DMK
 * @brief A class for @f$\Delta M_K@f$, the difference in mass
 * of between the heavy and light mass eigenstates of the neutral
 * Kaon system.
 * @author SusyFit Collaboration
 * @copyright GNU General Public License
 * @details This class is used to compute the theoretical value of
 * @f$\Delta M_K@f$. While the short distance contributions to this 
 * parameter is calculable both in the SM and in NP models, the long distance
 * contribution can only be estimated and might contribute to as much as half the
 * value of the parameter. This long distance contribution is put in as an
 * input parameter in this code through SM.getDMK().
 */

class DmK : public ThObservable, AmpDK2 {
public:
    
    /**
     * constructor
     * @param Flavour
     */
    
    DmK(Flavour& Flavour) : ThObservable(Flavour), AmpDK2(Flavour) {};
    
    /**
     * 
     * @return theoretical value of @f$\Delta M_K@f$ 
     */
    virtual double getThValue();
};

/**
 * @}
 */

#endif	/* DMK_H */
