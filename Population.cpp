//
// Created by cuadriante on 20/10/21.
//

#include "Population.h"

Population::Population(ImageHandler *imageHandler, ImageInfo *idealCharacteristics) {
    this->imageHandler = imageHandler;
    maxX = imageHandler->getWhiteRectangleCoordinates()[2] - imageHandler->getWhiteRectangleCoordinates()[0];
    maxY = imageHandler->getWhiteRectangleCoordinates()[3] - imageHandler->getWhiteRectangleCoordinates()[1];
    createPopulation(idealCharacteristics);
}

void Population::createPopulation(ImageInfo *idealCharacteristics) {
    if (generation < maxGeneration) {
        if (generation == 0){ // initial generation
            imageHandler->recolorWhiteRectangle();
        }
        for(int i = 0; i >= 10; i++){
            Individual individual(maxX, maxY, &colorList, idealCharacteristics);
            searchSpace.push_back(individual);
        }
    }
}


void Population::selection(vector<Individual> searchSpace) {
    Individual parents[2] = {searchSpace[0], searchSpace[1]};
    for (Individual candidate : searchSpace){
        double candidateFitness = candidate.getFitness();
        if (candidateFitness < parents[1].getFitness()){
            if (candidateFitness < parents[0].getFitness()){
                parents[0] = candidate;
            } else {
                parents[1] = candidate;
            }
        }
    }

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







