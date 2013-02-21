/* 
 * File:   CorrelatedGaussianObservables.h
 * Author: silvest
 *
 * Created on February 19, 2013, 10:08 AM
 */

#ifndef CORRELATEDGAUSSIANOBSERVABLES_H
#define	CORRELATEDGAUSSIANOBSERVABLES_H

#include "Observable.h"

class CorrelatedGaussianObservables {
public:
    CorrelatedGaussianObservables(std::string name_i);
    CorrelatedGaussianObservables(const CorrelatedGaussianObservables& orig);
    virtual ~CorrelatedGaussianObservables();

    void ComputeCov(gslpp::matrix<double> Corr);

    void AddObs(Observable& Obs_i);

    std::vector<Observable> GetObs() const {
        return Obs;
    }

    std::string GetName() const {
        return name;
    }

    void SetName(std::string name) {
        this->name = name;
    }

    gslpp::matrix<double> GetCov() const {
        return *Cov;
    }
    
private:
    std::vector<Observable> Obs;
    gslpp::matrix<double>* Cov;
    std::string name;
};

#endif	/* CORRELATEDGAUSSIANOBSERVABLES_H */

