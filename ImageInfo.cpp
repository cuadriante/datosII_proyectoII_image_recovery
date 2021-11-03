//
// Created by cuadriante on 24/10/21.
//

#include "ImageInfo.h"

ImageInfo::ImageInfo(const vector<char> &imageContent, int width, int height, vector<ColorInfo> * colorList) {
    this->imageContent.clear();
    this->imageContent.reserve(imageContent.size());
    for(char i : imageContent){
        this->imageContent.push_back(i);
    }
    //this->imageContent = imageContent;
    this->width = width;
    this->height = height;
    this->colorList = colorList;
    initialize();
    //calculateColorDistributionSum();
    //calculateColorPercentages();
}

void ImageInfo::initialize(){
    colorFrequencyPercentages.clear();
    colorFrequencyPercentages.reserve(colorList->size());
    colorRelationsPercentage.clear();
    colorRelationsPercentage.reserve(colorList->size()^2);

    for(int c = 0; c < colorList->size(); c++){
        colorFrequencyPercentages.push_back(0);
        for(int c2 = 0; c2 < colorList->size(); c2++){
           // colorRelationsPercentage.push_back(0);
        }
    }
}



void ImageInfo::calculateColorDistributionSum(){
    validPixelQuantity = 0;
    char previousColorIndex = -1;
    //Color previousColorIndex = imageContent->at(0);
    for(int x = 0; x < width; x++){
        for(int y = 0; y < height; y++){
            char colorIndex = imageContent.at(x + y * width);
            if (colorIndex >= 0){
                //int colorIndex = findColor(colorIndex);
                validPixelQuantity ++;
                colorFrequencyPercentages[colorIndex]++;
                //colorRelationsPercentage[colorIndex + previousColorIndex * colorList->size()]++;
                previousColorIndex = colorIndex;
            }
        }
    }
}

void ImageInfo::calculateColorPercentages(){
    int size = validPixelQuantity;
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

vector<char> ImageInfo::getImageContent() {
    return imageContent;
}

char ImageInfo::getImageContentElement(int index) {
    return imageContent.at(index);
}
