/* 
 * Copyright (C) 2015 HEPfit Collaboration
 * All rights reserved.
 *
 * For the licensing terms see doc/COPYING.
 */

#ifndef LAMBDA1_H
#define	LAMBDA1_H

#include <stdexcept>
#include <ThObservable.h>
#include "THDM.h"

/**
 * @class lambda1 
 * @ingroup THDM 
 * @brief An observable class for the quartic Higgs potential coupling @f$\lambda_1@f$.
 * @author HEPfit Collaboration
 * @copyright GNU General Public License
 * @details This class is used to compute the quartic Higgs potential coupling @f$\lambda_1@f$.
 */
class lambda1 : public ThObservable {
public:

    /**
     * @brief Constructor.
     * @param[in] ?
     */
    lambda1(const StandardModel& SM_i) 
    : ThObservable(SM_i), myTHDM(static_cast<const THDM*> (&SM_i))
    {
    };

    /**
     * @brief The quartic coupling @f$\lambda_1@f$.
     * @return @f$\lambda_1@f$
     */
    double computeThValue();

    private:
        const THDM * myTHDM;
};

#endif	/* LAMBDA1_H */
