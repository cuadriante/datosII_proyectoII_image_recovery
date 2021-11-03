//
// Created by cuadriante on 20/10/21.
//

#include "Individual.h"


Individual::Individual(int width, int height, vector<ColorInfo> *colorList, bool randomize, int startPointX,
                       int startPointY) {
    this->colorList = colorList;
    this->width = width;
    this->height = height;
    this->startPointX = startPointX;
    this->startPointY = startPointY;
    createIndividual(randomize);
}

void Individual::createIndividual(bool randomize) {
    int capacity = width*height;
    //genome = new vector<char>;
    genome.reserve(capacity);
    srand((unsigned int)time(NULL));
    for (int x = 0; x < width; x++){
        for (int y = 0; y < height; y++){
            if (randomize){
                int index = rand() % colorList->size();
                //vector<ColorInfo>& cl = colorList;
                //Color newColor = colorList->at(index).getColor();
                genome.push_back(index);
            } else {
                genome.push_back(-1);
            }
        }
    }
    this->imageInfo = new ImageInfo(genome, width, height, colorList);
}



void Individual::updateFitness(ImageInfo *idealCharacteristics) {
    imageInfo = new ImageInfo(genome, width, height, colorList);
    frequencyFitnessParameter = 0;
    fitness = 0;

    for(int x = 0; x < width; x++){
        for(int y = 0; y < height; y++){
            if (genome.at(y + x * height) != idealCharacteristics->getImageContentElement(y + x * height)){
                fitness++;
            }
        }
    }
}

void Individual::updateFitness3(ImageInfo *idealCharacteristics) {
    imageInfo = new ImageInfo(genome, width, height, colorList);
    frequencyFitnessParameter = 0;
    fitness = 0;

    for(int x = 0; x < width; x++){
        for(int y = 0; y < height; y++){
            if (genome.at(y + x * height) != idealCharacteristics->getImageContentElement(startPointY - 1)){
                fitness++;
            }
        }
    }
}

// return fitness in relation to idealCharacteristics
void Individual::updateFitness2(ImageInfo *idealCharacteristics) {

    delete imageInfo;
    imageInfo = new ImageInfo(genome, width, height, colorList);

    frequencyFitnessParameter = 0;
    relationFitnessParameter = 0;
    fitness = 0;

    for (int index = 0; index <= colorList->size(); index++){
        double colorDifference = abs(idealCharacteristics->getColorFrequencyPercentages()[index]-imageInfo->getColorFrequencyPercentages()[index]);
        frequencyFitnessParameter = frequencyFitnessParameter + colorDifference;
        //imageInfo->debug();
    }
    for (int index = 0; index < colorList->size(); index++){
        for (int index2 = 0; index2 < colorList->size(); index2++){
            double colorDifference = abs(idealCharacteristics->getColorRelationsPercentage(index, index2) - imageInfo->getColorRelationsPercentage(index, index2));
            relationFitnessParameter = relationFitnessParameter + colorDifference;
        }
    }

    int size = colorList->size();
    frequencyFitnessParameter = frequencyFitnessParameter/size;
    relationFitnessParameter = relationFitnessParameter/(size^2);
    fitness = (2*frequencyFitnessParameter + relationFitnessParameter)/2;
}

double Individual::getFitness() const {
    return fitness;
}


void Individual::setGenome(const vector<char> &newGenome, ImageInfo *idealCharacteristics) {

    //delete genome;
    genome.clear();
    genome.reserve(newGenome.size());
    //std::copy(genome->begin(), genome->end(), back_inserter(newGenome);

    for(char i : newGenome){
        genome.push_back(i);
    }

    updateFitness(idealCharacteristics);

}

void Individual::setGene(int index, char newGene) {
    genome.at(index) = newGene;

}

vector<char> Individual::getGenome() const {
    return genome;
}

char Individual::getGene(int index) {
    return genome.at(index);
}



