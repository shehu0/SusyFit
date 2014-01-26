/*
 * Copyright (C) 2013-2014 SusyFit Collaboration
 * All rights reserved.
 *
 * For the licensing terms see doc/COPYING.
 */

#ifndef NPEFFECTIVE1_H
#define	NPEFFECTIVE1_H

#include "NPEffective.h"

/**
 * @class NPEffective1
 * @brief A base class for new physics in the form of contributions to the dimension-six effective Lagrangian.
 * @ingroup NewPhysics
 * @author SusyFit Collaboration
 * @copyright GNU General Public License
 * @details
 */
class NPEffective1 : public NPEffective {
public:
    static const int NNPEffectiveVars = 11;
    static const std::string NPEffectiveVars[NNPEffectiveVars];

    /**
     * @brief Constructor.
     */
    NPEffective1()
    : NPEffective()
    {
    }

    virtual std::string ModelName() const
    {
        return "NPEffective1";
    }

    virtual bool CheckParameters(const std::map<std::string, double>& DPars);


protected:
    virtual void setParameter(const std::string name, const double& value);
      
};

#endif	/* NPEFFECTIVE1_H */

