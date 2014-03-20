/* 
 * Copyright (C) 2014 SusyFit Collaboration
 * All rights reserved.
 *
 * For the licensing terms see doc/COPYING.
 */

#include <iostream>
#include <SusyFit_noMCMC.h>
#include <InputParameters.h>

int main(int argc, char** argv) 
{
    try {

        /* Define the name of the model to be used. */
        std::string ModelName = "NPEpsilons";
        
        /* Create an object of the class InputParameters. */
        InputParameters IP;
        
        /* Read a map for the mandatory model parameters. (Default values in InputParameters.h) */ 
        std::map<std::string, double> DPars_IN = IP.getInputParameters(ModelName);
        
        /* Change the default values of the mandatory model parameters if necessary.        */
        /* This can also be done with DPars after creating an object of ComputeObservables. */
        DPars_IN["mcharm"] = 1.3;
        DPars_IN["mub"] = 4.2;
        
        /* Create an object of the class ComputeObservables. */
        ComputeObservables CO(ModelName, DPars_IN);
        
        /* Add the observables to be returned. */
        CO.AddObservable("Mw");
        CO.AddObservable("GammaZ");
        CO.AddObservable("AFBbottom");
        
        /* Remove a previously added observables if necessary. */
        //CO.RemoveObservable("AFBbottom");
        
        /* Set the flags for the model being used, if necessary. */
        std::map<std::string, std::string> DFlags;
        DFlags["epsilon2SM"] = "TRUE";
        DFlags["epsilonbSM"] = "TRUE";
        CO.setFlags(DFlags);
        
        /* Get the map of observables if necessary. */
        std::map<std::string, double> DObs = CO.getObservables();
        
        /* Define a map for the parameters to be varied. */
        std::map<std::string, double> DPars;
        
        for (int i = 0; i < 2; i++) {
            
            /* Vary the parameters that need to be varied in the analysis. */ 
            DPars["mtop"] = 170.0 + i * 0.1;
            DPars["dAle5Mz"] = 0.02750 - i * 0.0001;
            
            /* Get the map of observables with the parameter values defined above. */
            DObs = CO.compute(DPars);
        
            std::cout << "\nParameters[" << i + 1 << "]:"<< std::endl;
            for (std::map<std::string, double>::iterator it = DPars.begin(); it != DPars.end(); it++) {
                std::cout << it->first << " = " << it->second << std::endl;
            }
            std::cout << "\nObservables[" << i + 1 << "]:" << std::endl;
            for (std::map<std::string, double>::iterator it = DObs.begin(); it != DObs.end(); it++) {
                std::cout << it->first << " = " << it->second << std::endl;
            }
        }
        
        return EXIT_SUCCESS;
    } catch (const std::runtime_error& e) {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }
}
