//
// Created by cuadriante on 11/10/21.
//

#include "ColorInfo.h"

ColorInfo::ColorInfo(Color color) {
    this->color = color;
    this->red = color.r;
    this->green = color.g;
    this->blue = color.b;
    nRed = normalize(red);
    nGreen = normalize(green);
    nBlue = normalize(blue);

}

int ColorInfo::normalize(int color) {
    double i = color / 255.0;
    i = i*NORMALIZED_RANGE;
    return (int) i;
}

int ColorInfo::getRed() const {
    return red;
}

int ColorInfo::getGreen() const {
    return green;
}

int ColorInfo::getBlue() const {
    return blue;
}

int ColorInfo::getNRed() const {
    return nRed;
}

int ColorInfo::getNGreen() const {
    return nGreen;
}

int ColorInfo::getNBlue() const {
    return nBlue;
}

bool ColorInfo::isSimilar(ColorInfo * colorInfo){
    return  nRed == colorInfo->getNRed() &&
            nGreen == colorInfo->getNGreen() &&
            nBlue == colorInfo->getNBlue();
}

bool ColorInfo::isGrayScale() {

    if (red >= WHITE_MINIMUM && green >= WHITE_MINIMUM && blue >= WHITE_MINIMUM){
        return true;
    }
    if (red <= MIN_GRAY_LEVEL || green <= MIN_GRAY_LEVEL || blue <= MIN_GRAY_LEVEL){
        return false;
    }
    int differencerb = std::abs(red - blue);
    int differencerg = std::abs(red - green);
    int differencegb = std::abs(green - blue);

    return  differencerb <= GRAY_DELTA ||
            differencerg <= GRAY_DELTA ||
            differencegb <= GRAY_DELTA;

}

const Color &ColorInfo::getColor() const {
    return color;
}

void ColorInfo::setColor(const Color &newColor) {
    this->color = newColor;
    this->red = newColor.r;
    this->green = newColor.g;
    this->blue = newColor.b;
    nRed = normalize(red);
    nGreen = normalize(green);
    nBlue = normalize(blue);
}

int ColorInfo::getFrequency()  {
    return frequency;
}

void ColorInfo::setFrequency(int frequency) {
    this->frequency = frequency;
}

double ColorInfo::getPercentage() const {
    return percentage;
}

void ColorInfo::setPercentage(double percentage) {
    ColorInfo::percentage = percentage;
}


