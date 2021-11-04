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
//    for (char colorIndex = 0; colorIndex < colorList->size(); colorIndex++){
//        Individual * individual = new Individual(width, height, colorList, false, startPointX, startPointY);
//        for(int i = 0; i < height*width; i++){
//            individual->setGene(i, colorIndex);
//        }
//        individual->updateFitness(idealCharacteristics);
//        searchSpace.push_back(individual);
//    }

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

    Individual * child1 = new Individual(width, height, colorList, false, startPointX, startPointY);
    Individual * child2 = new Individual(width, height, colorList, false, startPointX, startPointY);
    child1->setGenome(newGenome1, idealCharacteristics);
    child2->setGenome(newGenome2, idealCharacteristics);

    searchSpace.push_back(child1);
    searchSpace.push_back(child2);

    while(searchSpace.size() < POPULATION_SIZE){
        Individual * individual = new Individual(width, height, colorList, false, startPointX, startPointY);
        individual->setGenome(parent1->getGenome(), idealCharacteristics);
        searchSpace.push_back(individual);
    }

    for(int i = 4; i < searchSpace.size(); i++){
        mutation(searchSpace.at(i));
    }

    for(int i = 4; i < searchSpace.size(); i++){
        inversion(searchSpace.at(i));
    }

    for(Individual * individual : searchSpace){
        individual->updateFitness(idealCharacteristics);
    }

    sort(searchSpace.begin(), searchSpace.end(), compareFitness);

    CreateXMLFile();

    solution(searchSpace.at(0));
}

void Population::mutation(Individual *individual) {
    srand((unsigned int)time(NULL));
    srand((unsigned int)time(NULL));
    bool mutate = (rand()% 1) == 0;
    if (mutate) {
        bool mutated = false;
        int tries = 100;
        while(!mutated && tries > 0){
            int geneIndex = rand() % genomeSize;
            char ogGene = individual->getGene(geneIndex);
            if (idealCharacteristics->getImageContentElement(geneIndex) != ogGene){
                char newColorIndex = (ogGene + 1) % colorList->size();
                individual->setGene(geneIndex, newColorIndex);
                mutated = true;
            }
            tries--;
        }
        //int mutations = rand() % (int) (genomeSize * 0.1);
        //while (mutations > 0) {
//            int geneIndex = rand() % genomeSize;
//            char ogGene = individual->getGene(geneIndex);
//            char newColorIndex = (ogGene + 1) % colorList->size();
//            individual->setGene(geneIndex, newColorIndex);
         //   mutations--;
       // }
    }
}

void Population::inversion(Individual *individual) {
    srand((unsigned int)time(NULL));
    bool invert = (rand()% 10) == 0;
    if (invert){
        int y = rand()% height;
        for (int x = 0; x < width; x++){
            char ogGene = individual->getGene(y + x*height);
            char newGene = (ogGene + 1) % (colorList->size() - 1);
            individual->setGene(y + x*height, newGene);
        }
//        int startPoint = rand() % (genomeSize - 101);
//        int endPoint = startPoint + 100;
//        for (int i = startPoint; i <= endPoint; i++){
//            char newGene = rand() % (colorList->size() - 1);
//            //char newGene = (colorList->size() + i) % colorList->size();
//            //char newGene = (colorList->size() + i) % colorList->size();
//            individual->setGene(i, newGene);
//        }
    }
}

void Population::setMaxGeneration(int maxGeneration) {
    Population::maxGeneration = maxGeneration;
}

int Population::getGeneration() const {
    return generation;
}

void Population::solution(Individual *individual) {
    if (bestFitness < 0 || individual->getFitness() < bestFitness){
        bestFitness = individual->getFitness();
        cout << "Gen: " << generation << endl;
        cout << "fitness: " << individual->getFitness() << endl;
    }
    imageHandler->recolorWhiteRectangle(individual->getGenome(), width, height, generation);
    generation ++;
    //XMLFile->clearFile();

}

int Population::getMaxGeneration() const {
    return maxGeneration;
}

void Population::CreateXMLFile() {
//    XMLFile = new XMLConfig(searchSpace, genomeSize, generation);
}








