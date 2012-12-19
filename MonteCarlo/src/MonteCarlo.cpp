/* 
 * Copyright (C) 2012 SUSYfit Collaboration
 * All rights reserved.
 *
 * For the licensing terms see doc/COPYING.
 */

#include "MonteCarlo.h"
#include <BAT/BCAux.h>
#include <BAT/BCLog.h>
#include <BAT/BCSummaryTool.h>
#include <mpi.h>

MonteCarlo::MonteCarlo(const std::string& ModelConf_i,
        const std::string& MonteCarloConf_i, const std::string& OutFile_i, const std::string& JobTag_i) :
myInputParser(), MCEngine(ModPars, Obs, Obs2D) {
    ModelConf = ModelConf_i;
    MCMCConf = MonteCarloConf_i;
    JobTag = JobTag_i;
    OutFile = OutFile_i + JobTag + ".root";
    PrintAllMarginalized = false;
}

MonteCarlo::~MonteCarlo() {
}

void MonteCarlo::Run(const int rank) {
    try {
        MCEngine.SetName(myInputParser.ReadParameters(ModelConf, ModPars, Obs, Obs2D).c_str());
        int buffsize = 0;
        std::map<std::string, double> DP;
        for (std::vector<ModelParameter>::iterator it = ModPars.begin(); it < ModPars.end(); it++) {
            DP[it->name] = it->ave;
            if (it->errg > 0. || it->errf > 0.)
                buffsize++;
        }
        buffsize++;
        if (!myInputParser.getMyModel()->Init(DP)) {
            std::cout << "parameter(s) missing in model initialization" << std::endl;
            exit(EXIT_FAILURE);
        }
        MCEngine.Initialize(myInputParser.getMyModel());
        double *recvbuff = new double[buffsize];

        if (rank != 0) {

            double **sendbuff = new double*[1];
            sendbuff[0] = new double[1];

            std::vector<double> pars;
            double * buff = new double[1024];
            double ll;
            while (true) {
                MPI::COMM_WORLD.Scatter(sendbuff[0], buffsize, MPI::DOUBLE,
                        recvbuff, buffsize, MPI::DOUBLE,
                        0);

                if (recvbuff[0] == 0.)
                    ll = log(0.);
                else if (recvbuff[0] == 1.) {
                    pars.assign(recvbuff + 1, recvbuff + buffsize);
                    ll = MCEngine.LogEval(pars);
                } else if (recvbuff[0] == -1.)
                    break;
                else 
                {
                    std::cout << "recvbuff = " << recvbuff[0] << " rank " << rank << std::endl;
                    throw "error in MPI message!";
                }

                MPI::COMM_WORLD.Gather(&ll, 1, MPI::DOUBLE, buff, 1, MPI::DOUBLE,
                        0);
            }
        } else {

            bool writechains = false;
            std::cout << ModPars.size() << " parameters defined." << std::endl;
            std::cout << Obs.size() << " observables defined." << std::endl;
            //MonteCarlo configuration parser
            std::ifstream ifile(MCMCConf.c_str());
            std::string line;
            while (!getline(ifile, line).eof()) {
                if (line.at(0) == '#') continue;
                boost::char_separator<char> sep(" ");
                boost::tokenizer<boost::char_separator<char> > tok(line, sep);
                boost::tokenizer<boost::char_separator<char> >::iterator beg = tok.begin();
                if (beg->compare("NChains") == 0) {
                    ++beg;
                    MCEngine.SetNChains(atoi((*beg).c_str()));
                } else if (beg->compare("PrerunMaxIter") == 0) {
                    ++beg;
                    MCEngine.MCMCSetNIterationsMax(atoi((*beg).c_str()));
                } else if (beg->compare("Seed") == 0) {
                    ++beg;
                    int seed = atoi((*beg).c_str());
                    if (seed != 0)
                        MCEngine.MCMCGetTRandom3()->SetSeed(seed);
                } else if (beg->compare("Iterations") == 0) {
                    ++beg;
                    MCEngine.MCMCSetNIterationsRun(atoi((*beg).c_str()));
                } else if (beg->compare("WriteChain") == 0) {
                    ++beg;
                    if (beg->compare("true") == 0)
                        writechains = true;
                } else if (beg->compare("PrintAllMarginalized") == 0) {
                    ++beg;
                    if (beg->compare("true") == 0) {
                        PrintAllMarginalized = true;
                    }
                } else {
                    std::cout << "wrong keyword in MonteCarlo config file: " << *beg << std::endl;
                    exit(EXIT_FAILURE);
                }
            }

            BCModelOutput out(&MCEngine, OutFile.c_str());
            if (writechains) {
                out.WriteMarkovChain(true);
                //            MCEngine.AddChains();
            }

            // set nicer style for drawing than the ROOT default
            BCAux::SetStyle();

            // open log file
            BCLog::OpenLog(("log" + JobTag + ".txt").c_str());
            BCLog::SetLogLevel(BCLog::debug);

            // run the MCMC and marginalize w.r.t. to all parameters
            MCEngine.MarginalizeAll();

            // find mode using the best fit parameters as start values
            //    MCEngine.FindMode(MCEngine.GetBestFitParameters());

            // draw all marginalized distributions into a PostScript file
            if (PrintAllMarginalized)
                MCEngine.PrintAllMarginalized(("MonteCarlo_plots" + JobTag + ".ps").c_str());

            // print results of the analysis into a text file
            MCEngine.PrintResults(("MonteCarlo_results" + JobTag + ".txt").c_str());

            // print ratio
            MCEngine.PrintHistogram(out);
            // output the correlation matrix to a eps file
            BCSummaryTool myBCSummaryTool(&MCEngine);
            myBCSummaryTool.PrintCorrelationMatrix("correlations" + JobTag + ".eps");

            out.WriteMarginalizedDistributions();
            //out.FillAnalysisTree();
            out.Close();

            // close log file
            BCLog::CloseLog();
            double ** sendbuff = new double *[MCEngine.procnum];
            sendbuff[0] = new double[MCEngine.procnum * buffsize];
            for (int il = 1; il < MCEngine.procnum; il++) {
                sendbuff[il] = sendbuff[il - 1] + buffsize;
                sendbuff[il][0] = -1.; //Exit command
            }
                MPI::COMM_WORLD.Scatter(sendbuff[0], buffsize, MPI::DOUBLE,
                        recvbuff, buffsize, MPI::DOUBLE,
                        0);
        }
        
    } catch (std::string message) {
        std::cerr << message << std::endl;
        exit(EXIT_FAILURE);
    }
}
