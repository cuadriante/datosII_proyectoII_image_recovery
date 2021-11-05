/**
 * @file ImageInfo.h
 * @version 1.0
 * @date 04 de noviembre de 2021
 * @author Adriana Calderón
 * @title Análisis de la información de la imagen
 */

#ifndef DATOSII_PROYECTOII_IMAGE_RECOVERY_IMAGEINFO_H
#define DATOSII_PROYECTOII_IMAGE_RECOVERY_IMAGEINFO_H


#include "ColorInfo.h"

using namespace std;

class ImageInfo {
private:
    int width = 0;
    int height = 0;
    int validPixelQuantity = 0;
    vector<ColorInfo> * colorList;
    vector<double> colorFrequencyPercentages;
    vector<double> colorRelationsPercentage;
    vector<char> imageContent;

public:
    ImageInfo(const vector<char> &imageContent, int width, int height, vector<ColorInfo> * colorList);

    void calculateColorDistributionSum();

    int findColor(Color color);

    void initialize();

    void calculateColorPercentages();

    const vector<double> &getColorFrequencyPercentages() const;

    double getColorRelationsPercentage(int x, int y) const;

    void setColorRelationsPercentage(int x, int y, double percentage);

    void debug();

    vector<char> getImageContent();

    char getImageContentElement(int index);
};


#endif //DATOSII_PROYECTOII_IMAGE_RECOVERY_IMAGEINFO_H
