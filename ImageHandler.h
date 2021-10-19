//
// Created by cuadriante on 10/10/21.
//

#ifndef DATOSII_PROYECTOII_IMAGE_RECOVERY_IMAGEHANDLER_H
#define DATOSII_PROYECTOII_IMAGE_RECOVERY_IMAGEHANDLER_H

#include<SFML/Graphics.hpp>
#include <iostream>
#include "ColorInfo.h"

using namespace sf;
using namespace std;



class ImageHandler {

private:
    Image image;
    vector<int> ogImage;
    vector<int> newImage;
    vector<ColorInfo> whiteRectangle;
    vector<ColorInfo> colorList;
    int whiteRectangleCoordinates [4] = {0, 0, 0, 0}; //x1 y1 x2 y2
    const int WHITE_MINIMUM = 195;

public:
    explicit ImageHandler(String imageName);

    [[noreturn]] void storeImageAsPixels();

    void recolorWhiteRectangle();

    void saveChangesToImageFile();

    void printContents();

    const Image &getImage() const;
};


#endif //DATOSII_PROYECTOII_IMAGE_RECOVERY_IMAGEHANDLER_H
