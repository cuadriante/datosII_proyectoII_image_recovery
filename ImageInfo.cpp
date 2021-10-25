//
// Created by cuadriante on 24/10/21.
//

#include "ImageInfo.h"

ImageInfo::ImageInfo(vector<Color> imageContent, int width, int height, vector<ColorInfo> * colorList) {
    this->imageContent = imageContent;
    this->width = width;
    this->height = height;
    this->colorList = colorList;
    initialize();
    calculateColorDistribution();
    calculateColorPercentages();
}

void ImageInfo::initialize(){
    for(int c = 0; c <= colorList->size(); c++){
        colorFrequencyPercentages.push_back(0);
        vector<double> v;
        for(int c2 = 0; c2 <= colorList->size(); c2++){
            v.push_back(0);
        }
        colorRelationsPercentage.push_back(v);
    }
}

void ImageInfo::calculateColorDistribution(){
    Color previousColor = imageContent[0];
    for(int x = 0; x <= width; x++){
        for(int y = 0; y <= height; y++){
            Color c = imageContent[x + y*width];
            if (c != Color::White){
                int colorIndex = findColor(c);
                if(colorIndex != -1){
                    colorFrequencyPercentages[colorIndex]++;
                    int previousColorIndex = findColor(previousColor);
                    colorRelationsPercentage[colorIndex][previousColorIndex]++;
                    previousColor = c;
                }
            }
        }
    }
}

void ImageInfo::calculateColorPercentages(){
    for(int c = 0; c <= colorList->size(); c++){
        colorFrequencyPercentages[c] = (colorFrequencyPercentages[c]/colorList->size()) * 100;
        for(int c2 = 0; c2 <= colorList->size(); c2++){
            colorRelationsPercentage[c][c2] = (colorRelationsPercentage[c][c2]/imageContent.size()) * 100;
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

const vector<vector<double>> &ImageInfo::getColorRelationsPercentage() const {
    return colorRelationsPercentage;
}
