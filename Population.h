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
    int generation = 0;
    int maxGeneration = 10;
    ImageHandler * imageHandler;

public:

    Population(ImageHandler * imageHandler);

    void createPopulation();

    double fitness(Individual individual);

    void selection(vector<Individual> searchSpace);

    void crossover(Individual parent1, Individual parent2);

    void mutation(Individual individual);

    void inversion(Individual individual);

    int getGeneration() const;

    void setMaxGeneration(int maxGeneration);
};


#endif //DATOSII_PROYECTOII_IMAGE_RECOVERY_POPULATION_H
