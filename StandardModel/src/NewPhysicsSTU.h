/* 
 * Copyright (C) 2012 SUSYfit Collaboration
 * All rights reserved.
 *
 * For the licensing terms see doc/COPYING.
 */

#ifndef NEWPHYSICSSTU_H
#define	NEWPHYSICSSTU_H

#include "StandardModel.h"


class NewPhysicsSTU : public StandardModel {
public:
    static const int NSTUvars = 3;
    static const std::string STUvars[NSTUvars];
    
    /**
     * @brief NewPhysicsSTU constructor
     */
    NewPhysicsSTU();

    virtual std::string ModelName() const {
        return "NewPhysicsSTU";
    }

    virtual bool Update(const std::map<std::string, double>& DPars);
    virtual bool Init(const std::map<std::string, double>& DPars);    
    virtual bool CheckParameters(const std::map<std::string, double>& DPars);

    
    ////////////////////////////////////////////////////////////////////////     

    bool SetFlag(const std::string, const bool&); 

    
    ////////////////////////////////////////////////////////////////////////     

    /**
     * @return Oblique parameter S
     */
    double obliqueS() const {
        return myObliqueS;
    }

    /**
     * @return Oblique parameter T
     */
    double obliqueT() const {
        return myObliqueT;
    }

    /**
     * @return Oblique parameter U
     */
    double obliqueU() const {
        return myObliqueU;
    }
    
    
    ////////////////////////////////////////////////////////////////////////     
    
    /**
     * @return Oblique parameter \hat{S}
     */
    double obliqueShat() const {
        return ( alphaMz()/(4.0*s02())*obliqueS() );
    }

    /**
     * @return Oblique parameter \hat{T}
     */
    double obliqueThat() const {
        return ( alphaMz()*obliqueT() );
    }

    /**
     * @return Oblique parameter \hat{U}
     */
    double obliqueUhat() const {
        return ( - alphaMz()/(4.0*s02())*obliqueU() );
    }

    /**
     * @return Oblique parameter V
     */
    double obliqueV() const {
        return 0.0;
    }

    /**
     * @return Oblique parameter W
     */
    double obliqueW() const {
        return 0.0;
    }

    /**
     * @return Oblique parameter X
     */
    double obliqueX() const {
        return 0.0;
    }

    /**
     * @return Oblique parameter Y
     */
    double obliqueY() const {
        return 0.0;
    }


    ////////////////////////////////////////////////////////////////////////     
    
protected:    
    double myObliqueS, myObliqueT, myObliqueU;
    virtual void SetParameter(const std::string name, const double& value);
    
    ////////////////////////////////////////////////////////////////////////     
    
private:

};

#endif	/* NEWPHYSICSSTU_H */

