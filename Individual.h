//
// Created by cuadriante on 20/10/21.
//

#ifndef DATOSII_PROYECTOII_IMAGE_RECOVERY_INDIVIDUAL_H
#define DATOSII_PROYECTOII_IMAGE_RECOVERY_INDIVIDUAL_H


#include "ColorInfo.h"
#include "ImageHandler.h"
#include "ImageInfo.h"

using namespace std;

class Individual {
private:
    ImageHandler * imageHandler;
    vector<ColorInfo> * colorList;
    vector<Color> genome;
    double frequencyFitnessParameter = 0;
    double relationFitnessParameter = 0;
    double fitness = 0;

    int maxX = 0;
    int maxY = 0;

public:
    Individual(int maxX, int maxY, vector<ColorInfo> * colorList, ImageInfo * idealCharacteristics);
    void createIndividual(ImageInfo * idealCharacteristics);
    void calculateFitness(ImageInfo *imageInfo, ImageInfo * idealCharacteristics);

    double getFitness() const;

    const vector<Color> &getGenome() const;

    void setGenome(const vector<Color> &genome);

    void setGene(int index, Color newGene);
};


#endif //DATOSII_PROYECTOII_IMAGE_RECOVERY_INDIVIDUAL_H
