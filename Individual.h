/**
 * @file Individual.h
 * @version 1.0
 * @date 04 de noviembre de 2021
 * @author Adriana Calderón
 * @title Individuo de una población
 */

#ifndef DATOSII_PROYECTOII_IMAGE_RECOVERY_INDIVIDUAL_H
#define DATOSII_PROYECTOII_IMAGE_RECOVERY_INDIVIDUAL_H


#include "ColorInfo.h"
#include "ImageHandler.h"
#include "ImageInfo.h"

using namespace std;

class Individual {
private:

    vector<ColorInfo> * colorList;
    vector<char> genome;
    double frequencyFitnessParameter = 0;
    double relationFitnessParameter = 0;
    double fitness = 0;
    ImageInfo * imageInfo;

    int width = 0;
    int height = 0;
    int startPointX = 0;
    int startPointY = 0;

public:
    /**
* @brief Constructor
* @param width, height, colorList, randomize, startPointX, startPointY
*/
    Individual(int width, int height, vector<ColorInfo> *colorList, bool randomize, int startPointX,
               int startPointY);
    /**
     * @brief crea individuo con genoma vacio o aleatorio
     * @param randomize
     */

    void createIndividual(bool randomize);


    void updateFitness3(ImageInfo * idealCharacteristics);

    void updateFitness2(ImageInfo * idealCharacteristics);

    /**
     * @brief actualiza el fitness del individuo segun caracteristicas ideales
     * @param idealCharacteristics
     */
    void updateFitness(ImageInfo *idealCharacteristics);
/**
 * @brief obtiene el fitness del individuo
 * @return
 */
    double getFitness() const;

    /**
     * @brief obtiene el genoma del individuo
     * @return
     */
    vector<char> getGenome() const;

    /**
     * @brief actualiza el genoma del individuo
     * @param newGenome
     * @param idealCharacteristics
     */
    void setGenome(const vector<char> & newGenome, ImageInfo *idealCharacteristics);

    /**
     * @brief actualiza un gen del genoma del individuo
     * @param index
     * @param newGene
     */
    void setGene(int index, char newGene);

    /**
     * @brief obtiene gen del genoma del individuo segun index
     * @param index
     * @return
     */
    char getGene(int index);

};


#endif //DATOSII_PROYECTOII_IMAGE_RECOVERY_INDIVIDUAL_H
