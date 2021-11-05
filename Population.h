/**
 * @file Population.h
 * @version 1.0
 * @date 04 de noviembre de 2021
 * @author Adriana Calderón
 * @title Población de individuos
 */

#ifndef DATOSII_PROYECTOII_IMAGE_RECOVERY_POPULATION_H
#define DATOSII_PROYECTOII_IMAGE_RECOVERY_POPULATION_H
#include "Individual.h"
#include "ImageHandler.h"
#include "XMLConfig.h"
#include <unistd.h>

class Population {
private:
    const int POPULATION_SIZE = 100;
    vector<Individual *> searchSpace;
    vector<ColorInfo> * colorList;
    ImageInfo * idealCharacteristics;
    Individual * offspring[2];
    const double CROSSOVER_POINT = 0.6;
    int width = 0;
    int height = 0;
    int genomeSize = 0;
    int generation = 0;
    int maxGeneration = 10;
    ImageHandler * imageHandler;
    double bestFitness = -1;
    int startPointX = 0;
    int startPointY = 0;
    XMLConfig * XMLFile;

public:

    Population(ImageHandler * imageHandler, ImageInfo * idealCharacteristics, vector<ColorInfo> * colorList);

    void createInitialPopulation();

    void selection();

    void crossover();

    void mutation(Individual *individual);

    void inversion(Individual *individual);

    void solution(Individual * individual);

    void CreateXMLFile();

    int getGeneration() const;

    void setMaxGeneration(int maxGeneration);

    static bool compareFitness(Individual * a, Individual *b);



    int getMaxGeneration() const;



};


#endif //DATOSII_PROYECTOII_IMAGE_RECOVERY_POPULATION_H
