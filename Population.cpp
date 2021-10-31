//
// Created by cuadriante on 20/10/21.
//

#include "Population.h"

Population::Population(ImageHandler *imageHandler, ImageInfo *idealCharacteristics, vector<ColorInfo> * colorList) {
    this->imageHandler = imageHandler;
    this->idealCharacteristics = idealCharacteristics;
    this->colorList = colorList;
    width = imageHandler->getWhiteRectangleCoordinates()[2] - imageHandler->getWhiteRectangleCoordinates()[0];
    height = imageHandler->getWhiteRectangleCoordinates()[3] - imageHandler->getWhiteRectangleCoordinates()[1];
    Individual * child1 = new Individual(width, height, colorList);
    Individual * child2 = new Individual(width, height, colorList);
    offspring[0] = child1;
    offspring[1] = child2;
    //createPopulation();
}

void Population::createPopulation() {
    while(searchSpace.size() < POPULATION_SIZE){
        Individual * individual = new Individual(width, height, colorList);
        individual->updateFitness(idealCharacteristics);
        searchSpace.push_back(individual);
    }
    selection();

//    if (generation < maxGeneration) {
////        if (generation == 0){ // initial generation
////            imageHandler->recolorInitialWhiteRectangle();
////            generation++;
////            createPopulation();
////        }
//        if (generation == 0){
//            for(int i = 0; i < POPULATION_SIZE; i++){
//                Individual individual(width, height, colorList);
//                individual.updateFitness(idealCharacteristics);
//                searchSpace.push_back(individual);
//            }
//        } else {
//            for(int i = 0; i < POPULATION_SIZE - 2; i++) {
//                Individual individual(width, height, colorList);
//                individual.updateFitness(idealCharacteristics);
//                searchSpace.at(i) = individual;
//            }
//        }
//        cout << "Gen: " << generation << endl;
//        selection();
//    } else {
//        cout << "Process finished." << endl;
//    }
}

bool Population::compareFitness(Individual *a, Individual *b){
    return a->getFitness() < b->getFitness();
}


void Population::selection() {
    sort(searchSpace.begin(), searchSpace.end(), compareFitness);
    crossover();
}

void Population::crossover() {
    Individual * parent1 = searchSpace[0];
    Individual * parent2 = searchSpace[1];

    while(searchSpace.size() > 2){
        delete searchSpace[searchSpace.size() - 1];
        searchSpace.pop_back();
    }

    int crossoverPoint = parent1->getGenome().size()/2;
    vector<Color> newGenome1;
    vector<Color> newGenome2;
    for (int i = 0; i <= crossoverPoint; i++){
        newGenome1.push_back(parent1->getGenome()[i]);
        newGenome2.push_back(parent2->getGenome()[i]);
    }
    for (int i = crossoverPoint + 1; i < parent1->getGenome().size(); i++){
        newGenome1.push_back(parent2->getGenome()[i]);
        newGenome2.push_back(parent1->getGenome()[i]);
    }
    Individual * child1 = new Individual(width, height, colorList);
    Individual * child2 = new Individual(width, height, colorList);
    child1->setGenome(&newGenome1, idealCharacteristics);
    child2->setGenome(&newGenome2, idealCharacteristics);

    if (mutate){
      //  mutation(offspring[0]);
    }

    if (invert){
       // inversion(offspring[0]);
    }

    searchSpace.push_back(child1);
    searchSpace.push_back(child2);

    while(searchSpace.size() < POPULATION_SIZE){
        Individual * individual = new Individual(width, height, colorList);
        individual->updateFitness(idealCharacteristics);
        searchSpace.push_back(individual);
    }

    sort(searchSpace.begin(), searchSpace.end(), compareFitness);

    solution(searchSpace[0]);
}

void Population::mutation(Individual *individual) {
    srand((unsigned int)time(NULL));
    int geneIndex = rand() % individual->getGenome().size();
    Color newGene = colorList->at(rand() % colorList->size()).getColor();
    //individual->setGene(geneIndex, newGene);
}

void Population::inversion(Individual *individual) {
    srand((unsigned int)time(NULL));
    int startPoint = rand() % individual->getGenome().size() - 100;
    int endPoint = startPoint + 100;
    for (int i = startPoint; i <= endPoint; i++){
        Color ogColor = individual->getGenome()[i];
        int ogIndex = 0;
        for(ColorInfo colorInfo : *colorList){
            if (colorInfo.getColor() == ogColor){
                break;
            }
            ogIndex++;
        }
        int compIndex = colorList->size() - 1 - ogIndex;
        Color newGene = colorList->at(compIndex).getColor();;
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
    //sleep(1.0);
    if (generation % 100 == 0) {
        cout << "Gen: " << generation << endl;
        cout << "fitness: " << individual->getFitness() << endl;
        imageHandler->recolorWhiteRectangle(individual->getGenome());
    }
    generation ++;
    if (generation <= maxGeneration){
        createPopulation();
    } else {
        cout << "Process finished." << endl;
    }
}







