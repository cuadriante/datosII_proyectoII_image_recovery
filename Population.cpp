//
// Created by cuadriante on 20/10/21.
//

#include "Population.h"

Population::Population(ImageHandler  * imageHandler) {
    this->imageHandler = imageHandler;
    createPopulation();
}


void Population::createPopulation() {
    if (generation < maxGeneration) {
        if (generation == 0){ // initial generation
            imageHandler->recolorWhiteRectangle();
        }
        for(int i = 0; i >= 10; i++){
            Individual individual(imageHandler);
            searchSpace.push_back(individual);
        }
    }
}

double Population::fitness(Individual individual) {
    return 0;
}

void Population::selection(vector<Individual> searchSpace) {

}

void Population::crossover(Individual parent1, Individual parent2) {

}

void Population::mutation(Individual individual) {

}

void Population::inversion(Individual individual) {

}

void Population::setMaxGeneration(int maxGeneration) {
    Population::maxGeneration = maxGeneration;
}

int Population::getGeneration() const {
    return generation;
}





