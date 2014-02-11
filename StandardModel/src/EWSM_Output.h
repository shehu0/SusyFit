/*
 * Copyright (C) 2013-2014 SusyFit Collaboration
 * All rights reserved.
 *
 * For the licensing terms see doc/COPYING.
 */

#ifndef EWSM_OUTPUT_H
#define	EWSM_OUTPUT_H

#include "EWSM.h"

using namespace gslpp;

/**
 * @class EWSM_Output
 * @ingroup StandardModel
 * @brief A class for testing SM radiative corrections to the %EW precision
 * obsrvables. 
 * @author SusyFit Collaboration
 * @copyright GNU General Public License
 * @details
 */
class EWSM_Output {
public:

    /**
     * @brief Constructor.
     * @param[in] EWSM_in a reference to an object of type EWSM
     */
    EWSM_Output(const EWSM& EWSM_in);

    
    ////////////////////////////////////////////////////////////////////////

    void outputEachDeltaR(const double Mw_i) const;

    void outputEachDeltaRhoZ_l(const StandardModel::lepton l, const double Mw_i) const;

    void outputEachDeltaRhoZ_q(const QCD::quark q, const double Mw_i) const;

    void outputEachDeltaRhoZ(const double f_AlphaToGF,
                             const double DeltaRho[EWSM::orders_EW_size],
                             const double deltaRho_rem[EWSM::orders_EW_size],
                             const double DeltaRbar_rem, const bool bool_Zbb,
                             const double taub[EWSM::orders_EW_size],
                             const double ZbbSubtract) const;

    void outputEachDeltaKappaZ_l(const StandardModel::lepton l, const double Mw_i) const;

    void outputEachDeltaKappaZ_q(const QCD::quark q, const double Mw_i) const;

    void outputEachDeltaKappaZ(const double f_AlphaToGF,
                               const double cW2overSW2,
                               const double DeltaRho[EWSM::orders_EW_size],
                               const double deltaKappa_rem[EWSM::orders_EW_size],
                               const double DeltaRbar_rem, const bool bool_Zbb,
                               const double taub[EWSM::orders_EW_size],
                               const double ZbbSubtract,
                               const double Zgamma_EW2) const;

    
    ////////////////////////////////////////////////////////////////////////
private:
    const EWSM& myEWSM;///< A reference to an object of type EWSM.
    const StandardModel& SM;///< A reference to an object of type StandardModel.


};

#endif	/* EWSM_OUTPUT_H */

