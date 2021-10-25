//
// Created by cuadriante on 20/10/21.
//

#include "Individual.h"


Individual::Individual(int maxX, int maxY, vector<ColorInfo> * colorList, ImageInfo * idealCharacteristics) {
    this->colorList = colorList;
    this->maxX = maxX;
    this->maxY = maxY;
    createIndividual(idealCharacteristics);
}

void Individual::createIndividual(ImageInfo * idealCharacteristics) {
    for (int x = 0; x <= maxX; x++){
        for (int y = 0; y <= maxY; y++){
            int index = rand() % colorList->size();
            vector<ColorInfo>& cl = *colorList;
            Color newColor = cl[index].getColor();
            genome.push_back(newColor);
        }
    }
    ImageInfo imageInfo(genome, maxX, maxY, colorList);
    calculateFitness(&imageInfo, idealCharacteristics);
}

void Individual::calculateFitness(ImageInfo * imageInfo, ImageInfo * idealCharacteristics) {
    for (int index = 0; index <= idealCharacteristics->getColorFrequencyPercentages().size(); index++){
        double colorDifference = abs(idealCharacteristics->getColorFrequencyPercentages()[index]-imageInfo->getColorFrequencyPercentages()[index]);
        frequencyFitnessParameter = frequencyFitnessParameter + colorDifference;
    }
    for (int index = 0; index <= idealCharacteristics->getColorRelationsPercentage().size(); index++){
        for (int index2 = 0; index2 <= idealCharacteristics->getColorRelationsPercentage()[index].size(); index2++){
            double colorDifference = abs(idealCharacteristics->getColorRelationsPercentage()[index][index2] -
                    imageInfo->getColorRelationsPercentage()[index][index2]);
            relationFitnessParameter = relationFitnessParameter + colorDifference;
        }
    }
    fitness = frequencyFitnessParameter + relationFitnessParameter;
}

double Individual::getFitness() const {
    return fitness;
}


