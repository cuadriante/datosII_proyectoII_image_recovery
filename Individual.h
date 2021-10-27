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

    vector<ColorInfo> * colorList;
    vector<Color> genome;
    double frequencyFitnessParameter = 0;
    double relationFitnessParameter = 0;
    double fitness = 0;
    ImageInfo * imageInfo;

    int width = 0;
    int height = 0;

public:
    Individual(int width, int height, vector<ColorInfo> *colorList);

    void createIndividual();

    void updateFitness(ImageInfo *idealCharacteristics);

    double getFitness() const;

    const vector<Color> &getGenome() const;

    void setGenome(const vector<Color> &genome, ImageInfo *idealCharacteristics);

    void setGene(int index, Color newGene);
};


#endif //DATOSII_PROYECTOII_IMAGE_RECOVERY_INDIVIDUAL_H
