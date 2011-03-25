/* 
 * File:   ModelParameter.cpp
 * Author: silvest
 * 
 * Created on March 15, 2011, 2:59 PM
 */

#include "ModelParameter.h"

ModelParameter::ModelParameter(std::string name_in, double ave_in, double 
errg_in, double errf_in) {
    name = name_in;
    ave = ave_in;
    errg = errg_in;
    errf = errf_in;
    min = ave - errf - 5.*errg;
    max = ave + errf + 5.*errg;
}

ModelParameter::~ModelParameter() {
}

std::ostream& operator<<(std::ostream& output, const ModelParameter& m)
  {
    output << "ModelParameter name, average, gaussian error, flat error" << std::endl;
    output << m.name << " " << m.ave << " " << m.errg << " " << m.errf << std::endl;
    return output;
  }
