//
// Created by cuadriante on 20/10/21.
//

#ifndef DATOSII_PROYECTOII_IMAGE_RECOVERY_INDIVIDUAL_H
#define DATOSII_PROYECTOII_IMAGE_RECOVERY_INDIVIDUAL_H


#include "ColorInfo.h"

using namespace std;

class Individual {
private:
    vector<ColorInfo> genome;
    vector<double> colorPercentage;
    double proximity= 0;
    double fitness;
public:
};


#endif //DATOSII_PROYECTOII_IMAGE_RECOVERY_INDIVIDUAL_H
