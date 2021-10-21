//
// Created by cuadriante on 18/10/21.
//

#include <cstdlib>
#include "StrategyTest.h"

using namespace std;

int StrategyTest::f(int x) {
    int y = delta*x + offset;
    return y;
}

void StrategyTest::mutate() {
    int r = (rand() % 3) - 1;
    int r2 = (rand() % 3) - 1;
    offset = offset + r/precision;
    delta = delta + r2/precision;
    cout << "offset " << offset << endl;
    cout << "delta " << delta << endl;
}

void StrategyTest::decreasePrecision() {
    precision = precision/10.0;

}

void StrategyTest::increasePrecision() {
    precision = precision*10.0;

}
