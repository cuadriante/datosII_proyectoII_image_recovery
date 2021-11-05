/**
 * @file Individual.h
 * @version 1.0
 * @date 04 de noviembre de 2021
 * @author Adriana Calderón
 * @title Individuo de una población
 */

#ifndef DATOSII_PROYECTOII_IMAGE_RECOVERY_INDIVIDUAL_H
#define DATOSII_PROYECTOII_IMAGE_RECOVERY_INDIVIDUAL_H


#include "ColorInfo.h"
#include "ImageHandler.h"
#include "ImageInfo.h"

using namespace std;

class Individual {
private:

    vector<ColorInfo> * colorList;
    vector<char> genome;
    double frequencyFitnessParameter = 0;
    double relationFitnessParameter = 0;
    double fitness = 0;
    ImageInfo * imageInfo;

    int width = 0;
    int height = 0;
    int startPointX = 0;
    int startPointY = 0;

public:
    Individual(int width, int height, vector<ColorInfo> *colorList, bool randomize, int startPointX,
               int startPointY);

    void createIndividual(bool randomize);

    void updateFitness3(ImageInfo * idealCharacteristics);

    void updateFitness2(ImageInfo * idealCharacteristics);

    void updateFitness(ImageInfo *idealCharacteristics);

    double getFitness() const;

    vector<char> getGenome() const;

    void setGenome(const vector<char> & newGenome, ImageInfo *idealCharacteristics);

    void setGene(int index, char newGene);

    char getGene(int index);

};


#endif //DATOSII_PROYECTOII_IMAGE_RECOVERY_INDIVIDUAL_H
