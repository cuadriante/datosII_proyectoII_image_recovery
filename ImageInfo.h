//
// Created by cuadriante on 24/10/21.
//

#ifndef DATOSII_PROYECTOII_IMAGE_RECOVERY_IMAGEINFO_H
#define DATOSII_PROYECTOII_IMAGE_RECOVERY_IMAGEINFO_H


#include "ColorInfo.h"

using namespace std;

class ImageInfo {
private:
    int width = 0;
    int height = 0;
    vector<ColorInfo> * colorList;
    vector<double> colorFrequencyPercentages;
    vector<vector<double>> colorRelationsPercentage;
    vector<Color> imageContent;

public:
    ImageInfo(vector<Color> imageContent, int width, int height, vector<ColorInfo> * colorList);

    void calculateColorDistribution();

    int findColor(Color color);

    void initialize();

    void calculateColorPercentages();

    const vector<double> &getColorFrequencyPercentages() const;

    const vector<vector<double>> &getColorRelationsPercentage() const;
};


#endif //DATOSII_PROYECTOII_IMAGE_RECOVERY_IMAGEINFO_H
