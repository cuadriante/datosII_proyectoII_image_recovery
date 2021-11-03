//
// Created by cuadriante on 10/10/21.
//

#ifndef DATOSII_PROYECTOII_IMAGE_RECOVERY_IMAGEHANDLER_H
#define DATOSII_PROYECTOII_IMAGE_RECOVERY_IMAGEHANDLER_H

#include<SFML/Graphics.hpp>
#include <iostream>
#include <random>
#include "ColorInfo.h"
#include "ImageInfo.h"

using namespace sf;
using namespace std;



class ImageHandler {

private:
    Image image;
    vector<int> ogImage;
    vector<int> newImage;
    vector<ColorInfo> whiteRectangle;
    vector<ColorInfo> colorList;
    vector<char> imageContent;
    int whiteRectangleCoordinates [4] = {0, 0, 0, 0}; //x1 y1 x2 y2
    int whiteRectangleWidth = 0;
    int whiteRectangleHeight = 0;
    const int WHITE_MINIMUM = 195;

public:
    explicit ImageHandler(String imageName);

    [[noreturn]] void analyzeImage();

    void recolorInitialWhiteRectangle();

    void saveChangesToImageFile();

    void calculateColorPercentages();

    void printContents();

    const vector<ColorInfo> &getWhiteRectangle() const;

    vector<ColorInfo> &getColorList();

    const int *getWhiteRectangleCoordinates() const;

    const Image &getImage() const;

    void recolorWhiteRectangle(const vector<char> &newPixelSetIndex, int width, int height);

    void startGeneticAlgorithm();

    vector<char> createIdealGenome();
};


#endif //DATOSII_PROYECTOII_IMAGE_RECOVERY_IMAGEHANDLER_H
