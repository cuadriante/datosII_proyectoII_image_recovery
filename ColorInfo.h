//
// Created by cuadriante on 11/10/21.
//

#ifndef DATOSII_PROYECTOII_IMAGE_RECOVERY_COLORINFO_H
#define DATOSII_PROYECTOII_IMAGE_RECOVERY_COLORINFO_H

#include <iostream>
#include<SFML/Graphics.hpp>

using namespace sf;

class ColorInfo {
private:


    const int GRAY_DELTA = 10;
    const int MIN_GRAY_LEVEL = 100;
    const int WHITE_MINIMUM = 195;
    int red = 0;
    int green = 0;
    int blue = 0;
    int nRed = 0;
    int nGreen = 0;
    int nBlue = 0;
    Color color;

    int normalize(int color);

public:
    const int NORMALIZED_RANGE = 3;

    ColorInfo(Color color);

    int getRed() const;

    int getGreen() const;

    int getBlue() const;

    void setColor(const Color &newColor);

    int getNRed() const;

    int getNGreen() const;

    int getNBlue() const;

    const Color &getColor() const;

    bool isSimilar(ColorInfo * colorInfo);

    bool isGrayScale();
};


#endif //DATOSII_PROYECTOII_IMAGE_RECOVERY_COLORINFO_H
