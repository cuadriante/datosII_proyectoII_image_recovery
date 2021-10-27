//
// Created by cuadriante on 20/10/21.
//

#include "Population.h"

Population::Population(ImageHandler *imageHandler, ImageInfo *idealCharacteristics) {
    this->imageHandler = imageHandler;
    //colorList = imageHandler->getColorList();
    maxX = imageHandler->getWhiteRectangleCoordinates()[2] - imageHandler->getWhiteRectangleCoordinates()[0];
    maxY = imageHandler->getWhiteRectangleCoordinates()[3] - imageHandler->getWhiteRectangleCoordinates()[1];
    Individual child1(maxX, maxY, colorList, idealCharacteristics);
    Individual child2(maxX, maxY, colorList, idealCharacteristics);
    offspring[0] = &child1;
    offspring[1] = &child2;
    createPopulation(idealCharacteristics);
}

void Population::createPopulation(ImageInfo *idealCharacteristics) {
    if (generation < maxGeneration) {
        if (generation == 0){ // initial generation
            imageHandler->recolorInitialWhiteRectangle();
        }
        if (generation == 1){
            for(int i = 0; i >= 10; i++){
                Individual individual(maxX, maxY, colorList, idealCharacteristics);
                searchSpace.push_back(individual);
            }
        } else {
            for(int i = 0; i >= 8; i++) {
                Individual individual(maxX, maxY, colorList, idealCharacteristics);
                searchSpace.push_back(individual);
            }
        }
        selection(searchSpace);
    }
}

bool Population::compareFitness(Individual a, Individual b){
    return a.getFitness() < b.getFitness();
}


void Population::selection(vector<Individual> searchSpace) {

    sort(searchSpace.begin(), searchSpace.end(), compareFitness);

    parents[0] = &searchSpace[0];
    parents[1] = &searchSpace[1];
    crossover(parents[0], parents[1]);
}

void Population::crossover(Individual * parent1, Individual * parent2) {
    int crossoverPoint = parent1->getGenome().size()/2;
    vector<Color> newGenome1;
    vector<Color> newGenome2;
    for (int i = 0; i <= crossoverPoint; i++){
        newGenome1[i] = parent1->getGenome()[i];
        newGenome2[i] = parent2->getGenome()[i];
    }
    for (int i = crossoverPoint + 1; i <= parent1->getGenome().size(); i++){
        newGenome1[i] = parent2->getGenome()[i];
        newGenome2[i] = parent1->getGenome()[i];
    }
    offspring[0]->setGenome(newGenome1);
    offspring[1]->setGenome(newGenome2);

    if (mutate){
        mutation(offspring[0]);
    }

    if (invert){
        inversion(offspring[0]);
    }

    searchSpace[8] = *offspring[0];
    searchSpace[9] = *offspring[1];
    // save to file
}

void Population::mutation(Individual *individual) {
    int geneIndex = rand() % individual->getGenome().size();
    Color newGene = (colorList[rand() % colorList.size()])->getColor();
    individual->setGene(geneIndex, newGene);
}

void Population::inversion(Individual *individual) {
    int startPoint = rand() % individual->getGenome().size() - 100;
    int endPoint = startPoint + 100;
    for (int i = startPoint; i <= endPoint; i++){
        Color ogColor = individual->getGenome()[i];
        int ogIndex = 0;
        for(ColorInfo * colorInfo : colorList){
            if (colorInfo->getColor() == ogColor){
                break;
            }
            ogIndex++;
        }
        int compIndex = colorList.size() - 1 - ogIndex;
        Color newGene = colorList[compIndex]->getColor();
        individual->setGene(i, newGene);
    }

}

void Population::setMaxGeneration(int maxGeneration) {
    Population::maxGeneration = maxGeneration;
}

int Population::getGeneration() const {
    return generation;
}

void Population::solution(Individual *individual) {

}







