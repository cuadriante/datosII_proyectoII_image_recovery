//
// Created by cuadriante on 24/10/21.
//

#include "ImageInfo.h"

ImageInfo::ImageInfo(vector<Color> *imageContent, int width, int height, vector<ColorInfo> * colorList) {
    this->imageContent = imageContent;
    this->width = width;
    this->height = height;
    this->colorList = colorList;
    initialize();
    calculateColorDistributionSum();
    calculateColorPercentages();
}

void ImageInfo::initialize(){
    colorFrequencyPercentages.clear();
    colorRelationsPercentage.clear();
    for(int c = 0; c < colorList->size(); c++){
        colorFrequencyPercentages.push_back(0);
        for(int c2 = 0; c2 < colorList->size(); c2++){
            colorRelationsPercentage.push_back(0);
        }
    }
}



void ImageInfo::calculateColorDistributionSum(){
    pixelQuantity = 0;
    Color previousColor = imageContent->at(0);
    for(int x = 0; x < width; x++){
        for(int y = 0; y < height; y++){
            Color c = imageContent->at(x + y*width);
            if (c != Color::White){
                int colorIndex = findColor(c);
                if(colorIndex != -1){
                    pixelQuantity ++;
                    colorFrequencyPercentages[colorIndex]++;
                    int previousColorIndex = findColor(previousColor);
                    colorRelationsPercentage[colorIndex + previousColorIndex*colorList->size()]++;
                    previousColor = c;
                }
            }
        }
    }
}

void ImageInfo::calculateColorPercentages(){
    int size = pixelQuantity;
    for(int c = 0; c < colorList->size(); c++){
        colorFrequencyPercentages[c] = (colorFrequencyPercentages[c]/size)* 100;
        for(int c2 = 0; c2 < colorList->size(); c2++){
            setColorRelationsPercentage(c, c2, (getColorRelationsPercentage(c,c2)/size)* 100);
            //colorRelationsPercentage[] = (colorRelationsPercentage[c][c2]/size);// * 100;
        }
    }
}


int ImageInfo::findColor(Color color) {
    int i = 0;
    for(ColorInfo colorInfo : *colorList){
        if (colorInfo.getColor() == color){
            return i;
        }
        i++;
    }
    return - 1;
}

const vector<double> &ImageInfo::getColorFrequencyPercentages() const {
    return colorFrequencyPercentages;
}

double ImageInfo::getColorRelationsPercentage(int x, int y) const {
    return colorRelationsPercentage[x + y*colorList->size()];
}

void ImageInfo::debug(){
    int size = colorList->size();
    for(int c = 0; c < size; c++){
        cout << "fp: " << colorFrequencyPercentages[c] << endl;
        for(int c2 = 0; c2 < size; c2++){
            cout <<"rp: " << getColorRelationsPercentage(c, c2) << endl;
        }
    }
}

void ImageInfo::setColorRelationsPercentage(int x, int y, double percentage) {
    colorRelationsPercentage[x+y*colorList->size()] = percentage;
}
