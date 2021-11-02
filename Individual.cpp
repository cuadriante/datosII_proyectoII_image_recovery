//
// Created by cuadriante on 20/10/21.
//

#include "Individual.h"


Individual::Individual(int width, int height, vector<ColorInfo> *colorList, bool randomize, int startPoint,
                       int endPoint) {
    this->colorList = colorList;
    this->width = width;
    this->height = height;
    this->startPoint = startPoint;
    this->endPoint = endPoint;
    createIndividual(randomize);
}

void Individual::createIndividual(bool randomize) {
    genome = new vector<Color>;
    srand((unsigned int)time(NULL));
    for (int x = 0; x <= width; x++){
        for (int y = 0; y <= height; y++){
            if (randomize){
                int index = rand() % colorList->size();
                //vector<ColorInfo>& cl = colorList;
                Color newColor = colorList->at(index).getColor();
                genome->push_back(newColor);
            } else {
                genome->push_back(Color::White);
            }
        }
    }
    this->imageInfo = new ImageInfo(genome, width, height, colorList);
}

// return fitness in relation to idealCharacteristics
void Individual::updateFitness(ImageInfo *idealCharacteristics) {

    //delete imageInfo;
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
    fitness = (frequencyFitnessParameter + relationFitnessParameter)/2;
}

double Individual::getFitness() const {
    return fitness;
}


void Individual::setGenome(const vector<Color> * newGenome, ImageInfo *idealCharacteristics) {

    genome->clear();
    for(int i = 0; i < newGenome->size(); i++){
        genome->push_back(newGenome->at(i));
    }

    updateFitness(idealCharacteristics);

}

void Individual::setGene(int index, Color newGene) {
    genome->at(index) = newGene;

}

vector<Color> *Individual::getGenome() const {
    return genome;
}


