//
// Created by cuadriante on 20/10/21.
//

#include "Individual.h"


Individual::Individual(int width, int height, vector<ColorInfo> * colorList) {
    this->colorList = colorList;
    this->width = width;
    this->height = height;
    createIndividual();
}

void Individual::createIndividual() {
    srand((unsigned int)time(NULL));
    for (int x = 0; x <= width; x++){
        for (int y = 0; y <= height; y++){

            int index = rand() % colorList->size();
            //vector<ColorInfo>& cl = colorList;
            Color newColor = colorList->at(index).getColor();
            genome.push_back(newColor);
        }
    }
    this->imageInfo = new ImageInfo(genome, width, height, colorList);
}

// return fitness in relation to idealCharacteristics
void Individual::updateFitness(ImageInfo *idealCharacteristics) {
    int colorFrequenceAcum = 0;
    frequencyFitnessParameter = 0;
    relationFitnessParameter = 0;
    fitness = 0;
    for (int index = 0; index <= idealCharacteristics->getColorFrequencyPercentages().size(); index++){
        double colorDifference = sqrt(abs(idealCharacteristics->getColorFrequencyPercentages()[index]-imageInfo->getColorFrequencyPercentages()[index]));
        frequencyFitnessParameter = frequencyFitnessParameter + colorDifference;
        //imageInfo->debug();
    }
    for (int index = 0; index < idealCharacteristics->getColorRelationsPercentage().size(); index++){
        for (int index2 = 0; index2 < idealCharacteristics->getColorRelationsPercentage()[index].size(); index2++){
            double colorDifference = sqrt(abs(idealCharacteristics->getColorRelationsPercentage()[index][index2] - imageInfo->getColorRelationsPercentage()[index][index2]));
            relationFitnessParameter = relationFitnessParameter + colorDifference;
        }
    }

    int size = colorList->size();
    frequencyFitnessParameter = frequencyFitnessParameter/size;
    relationFitnessParameter = relationFitnessParameter/(size^2);
    fitness = frequencyFitnessParameter + relationFitnessParameter;
}

double Individual::getFitness() const {
    return fitness;
}

const vector<Color> &Individual::getGenome() const {
    return genome;
}

void Individual::setGenome(const vector<Color> * newGenome, ImageInfo *idealCharacteristics) {
    int i = 0;
    for(Color c : genome){
        c = newGenome->at(i);
        i++;
    }
    updateFitness(idealCharacteristics);
}

void Individual::setGene(int index, Color newGene) {
    genome[index] = newGene;
}


