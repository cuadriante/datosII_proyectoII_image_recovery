//
// Created by cuadriante on 20/10/21.
//

#ifndef DATOSII_PROYECTOII_IMAGE_RECOVERY_POPULATION_H
#define DATOSII_PROYECTOII_IMAGE_RECOVERY_POPULATION_H
#include "Individual.h"
#include "ImageHandler.h"
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
    int generation = 0;
    int maxGeneration = 10;
    bool mutate = true;
    bool invert = true;
    ImageHandler * imageHandler;
    double bestFitness = -1;

public:

    Population(ImageHandler * imageHandler, ImageInfo * idealCharacteristics, vector<ColorInfo> * colorList);

    void createInitialPopulation();

    void selection();

    void crossover();

    void mutation(Individual *individual);

    void inversion(Individual *individual);

    void swapping(Individual * individual);

    int getGeneration() const;

    void setMaxGeneration(int maxGeneration);

    static bool compareFitness(Individual * a, Individual *b);

    void solution(Individual * individual);

    int getMaxGeneration() const;
};


#endif //DATOSII_PROYECTOII_IMAGE_RECOVERY_POPULATION_H
