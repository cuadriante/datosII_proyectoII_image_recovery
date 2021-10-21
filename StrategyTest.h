//
// Created by cuadriante on 18/10/21.
//

#ifndef DATOSII_PROYECTOII_IMAGE_RECOVERY_STRATEGYTEST_H
#define DATOSII_PROYECTOII_IMAGE_RECOVERY_STRATEGYTEST_H

#include <iostream>

class StrategyTest {
private:
    double offset = 0.0;
    double delta = 0.0;
    double precision = 10.0;

public:
    int f(int x);
    void mutate();
    void decreasePrecision();

    void increasePrecision();
};


#endif //DATOSII_PROYECTOII_IMAGE_RECOVERY_STRATEGYTEST_H
