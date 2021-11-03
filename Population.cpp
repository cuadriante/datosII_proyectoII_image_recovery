//
// Created by cuadriante on 20/10/21.
//

#include "Population.h"

Population::Population(ImageHandler *imageHandler, ImageInfo *idealCharacteristics, vector<ColorInfo> * colorList) {
    this->imageHandler = imageHandler;
    this->idealCharacteristics = idealCharacteristics;
    this->colorList = colorList;
    width = imageHandler->getWhiteRectangleCoordinates()[2] - imageHandler->getWhiteRectangleCoordinates()[0] + 1;
    height = imageHandler->getWhiteRectangleCoordinates()[3] - imageHandler->getWhiteRectangleCoordinates()[1] + 1;
    startPointX = imageHandler->getWhiteRectangleCoordinates()[0];
    startPointY = imageHandler->getWhiteRectangleCoordinates()[1];
    genomeSize = width*height;
    //createInitialPopulation();
}

void Population::createInitialPopulation() {
    while(searchSpace.size() < POPULATION_SIZE){
        Individual * individual = new Individual(width, height, colorList, true, startPointX, startPointY);
        individual->updateFitness(idealCharacteristics);
        searchSpace.push_back(individual);
    }
}

bool Population::compareFitness(Individual *a, Individual *b){
    return a->getFitness() < b->getFitness();
}


void Population::selection() {
    sort(searchSpace.begin(), searchSpace.end(), compareFitness);
    while(searchSpace.size() > 2){
        Individual * x = searchSpace.at(searchSpace.size()-1);
        searchSpace.pop_back();
        //delete x;
    }
}

void Population::crossover() {
    Individual * parent1 = searchSpace[0];
    Individual * parent2 = searchSpace[1];



    //int crossoverPoint = parent1->getGenome().size()/2;
    vector<char> newGenome1; // = new vector<char>;
    newGenome1.reserve(genomeSize);
    vector<char> newGenome2; // = new vector<char>;
    newGenome2.reserve(genomeSize);

    for (int i = 0; i < genomeSize; i++){
        if (i % 2 == 0){
            newGenome1.push_back(parent1->getGene(i));
            newGenome2.push_back(parent2->getGene(i));
        } else {
            newGenome1.push_back(parent2->getGene(i));
            newGenome2.push_back(parent1->getGene(i));
        }

    }

//    for (int i = 0; i < crossoverPoint; i++){
//        newGenome1->push_back(parent1->getGenome()->at(i));
//        newGenome2->push_back(parent2->getGenome()->at(i));
//    }
//    for (int i = crossoverPoint; i < parent1->getGenome()->size(); i++){
//        newGenome1->push_back(parent2->getGenome()->at(i));
//        newGenome2->push_back(parent1->getGenome()->at(i));
//    }


    Individual * child1 = new Individual(width, height, colorList, false, startPointX, startPointY);
    Individual * child2 = new Individual(width, height, colorList, false, startPointX, startPointY);
    child1->setGenome(newGenome1, idealCharacteristics);
    child2->setGenome(newGenome2, idealCharacteristics);

    //delete newGenome1;
    //delete newGenome2;

    searchSpace.push_back(child1);
    searchSpace.push_back(child2);

    while(searchSpace.size() < POPULATION_SIZE){
        Individual * individual = new Individual(width, height, colorList, false, startPointX, startPointY);
        //individual->updateFitness(idealCharacteristics);
        individual->setGenome(parent1->getGenome(), idealCharacteristics);
        searchSpace.push_back(individual);
    }

    if (mutate){
        for(int i = 3; i < searchSpace.size(); i++){
            //swapping(searchSpace.at(i));
            mutation(searchSpace.at(i));
        }

    }
    if (invert){
        for(int i = 3; i < searchSpace.size(); i++){
            inversion(searchSpace.at(i));
        }
    }


    for(Individual * individual : searchSpace){
        individual->updateFitness(idealCharacteristics);
    }

    sort(searchSpace.begin(), searchSpace.end(), compareFitness);

    solution(searchSpace.at(0));
}

void Population::mutation(Individual *individual) {
    srand((unsigned int)time(NULL));
    int mutations = rand() % (int)(genomeSize*0.1);
    while(mutations > 0){
        int geneIndex = rand() % genomeSize;
        char newColorIndex = rand() % colorList->size();
        individual->setGene(geneIndex, newColorIndex);
        mutations--;
    }
}

void Population::inversion(Individual *individual) {
    srand((unsigned int)time(NULL));
    int startPoint = rand() % (genomeSize - 101);
    int endPoint = startPoint + 100;
    for (int i = startPoint; i <= endPoint; i++){
        //int in = rand() % (colorList->size() - 1);
        char newGene = rand() % (colorList->size() - 1);
        //char newGene = (colorList->size() + i) % colorList->size();
        //char newGene = (colorList->size() + i) % colorList->size();
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
    //cout << "Gen: " << generation << endl;
    //cout << "fitness: " << individual->getFitness() << endl;
    //sleep(1.0);
    if (bestFitness < 0 || individual->getFitness() < bestFitness){
        bestFitness = individual->getFitness();
        cout << "Gen: " << generation << endl;
        cout << "fitness: " << individual->getFitness() << endl;
        imageHandler->recolorWhiteRectangle(individual->getGenome(), width, height);
    }
    generation ++;
    if (generation <= maxGeneration){
       // createInitialPopulation();
    } else {
        cout << "Process finished." << endl;
    }
}

int Population::getMaxGeneration() const {
    return maxGeneration;
}

void Population::swapping(Individual *individual) {
    srand((unsigned int)time(NULL));
    int p1 = rand() % individual->getGenome().size();
    int p2 = rand() % individual->getGenome().size();
   // Color temp1 = individual->getGenome()->at(p1);
  //  individual->getGenome()->at(p1) = individual->getGenome()->at(p2);
   // individual->getGenome()->at(p2) = temp1;
}







