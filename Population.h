//
// Created by cuadriante on 20/10/21.
//

#ifndef DATOSII_PROYECTOII_IMAGE_RECOVERY_POPULATION_H
#define DATOSII_PROYECTOII_IMAGE_RECOVERY_POPULATION_H
#include "Individual.h"
#include "ImageHandler.h"

class Population {
private:
    vector<Individual> searchSpace;
    vector<ColorInfo> colorList;
    Individual * parents[2];
    Individual * lowestCandidates[2];
    Individual * offspring[2];
    const double CROSSOVER_POINT = 0.6;
    int maxX = 0;
    int maxY = 0;
    int generation = 0;
    int maxGeneration = 10;
    bool mutate = true;
    bool invert = true;
    ImageHandler * imageHandler;

public:

    Population(ImageHandler * imageHandler, ImageInfo * idealCharacteristics);

    void createPopulation(ImageInfo *idealCharacteristics);

    void selection(vector<Individual> searchSpace);

    void crossover(Individual * parent1, Individual * parent2);

    void mutation(Individual *individual);

    void inversion(Individual *individual);

    int getGeneration() const;

    void setMaxGeneration(int maxGeneration);

    static bool compareFitness(Individual a, Individual b);
};


#endif //DATOSII_PROYECTOII_IMAGE_RECOVERY_POPULATION_H
