/* 
 * Copyright (C) 2012-2013 SusyFit Collaboration
 * All rights reserved.
 *
 * For the licensing terms see doc/COPYING.
 */

#ifndef THFACTORY_H
#define	THFACTORY_H

#include <ThObservable.h>
#include <ModelObservable.h>
#include <StandardModel.h>
#include <StandardModelMatching.h>
#include <Flavour.h>
#include <EW.h>
//#include <ZFitterWrapper.h>

/**
 * @class ThFactory
 * @ingroup InputParser 
 * @brief A class for an interface to theoretical predictions for observables. 
 * @author SusyFit Collaboration
 * @copyright GNU General Public License
 * @details  
 */
class ThFactory {
public:
    
    /**
     * @brief The default constructor.
     */
    ThFactory(const StandardModel& myModel);
    
    /**
     * @brief The default destructor.
     */
    virtual ~ThFactory();
    
    /**
     * @brief
     * @param[in]
     */
    ThObservable* getThMethod(const std::string& name);
private:
    std::map<std::string, ThObservable *> thobs; /**< */
    Flavour myFlavour; /**< */
    EW myEW; /**< */
    ModelObservable myMO; /**< */
    //ZFitterWrapper myZFitter;
};

#endif	/* THFACTORY_H */