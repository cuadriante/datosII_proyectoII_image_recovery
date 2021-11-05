/**
 * @file Population.h
 * @version 1.0
 * @date 04 de noviembre de 2021
 * @author Adriana Calderón
 * @title Población de individuos
 */

#ifndef DATOSII_PROYECTOII_IMAGE_RECOVERY_POPULATION_H
#define DATOSII_PROYECTOII_IMAGE_RECOVERY_POPULATION_H
#include "Individual.h"
#include "ImageHandler.h"
#include "XMLConfig.h"
#include <unistd.h>

class Population {
private:
    const int POPULATION_SIZE = 100;
    vector<Individual *> searchSpace;
    vector<ColorInfo> * colorList;
    ImageInfo * idealCharacteristics;
    Individual * offspring[2];
    const double CROSSOVER_POINT = 0.6;
    int width = 0;
    int height = 0;
    int genomeSize = 0;
    int generation = 0;
    int maxGeneration = 10;
    ImageHandler * imageHandler;
    double bestFitness = -1;
    int startPointX = 0;
    int startPointY = 0;
    XMLConfig * XMLFile;

public:

    /**
 * @brief Constructor
 * @param imageHandler, idealCharacteristics, colorList
 */
    Population(ImageHandler * imageHandler, ImageInfo * idealCharacteristics, vector<ColorInfo> * colorList);

    /**
 * @brief Crea poblacion inicial
 */
    void createInitialPopulation();
    /**
  * @brief Selecciona mejores individuos segun fitness
  */
    void selection();
    /**
  * @brief Combina genoma de dos individuos padres para formar hijos, aplica inversion y mutacion
  */
    void crossover();
    /**
  * @brief Cambia ciertos pixeles de ciertos individuos por el siguiente color en la lista
  * @param individual
  */
    void mutation(Individual *individual);
    /**
  * @brief Cambia una fila de pixeles de ciertos individuos por diferentes colores en la lista
   * @param individual
     */
    void inversion(Individual *individual);
    /**
  * @brief Despliega la solucion final en la imagen
   * @param individual
     */
    void solution(Individual * individual);
    /**
  * @brief Crea archivo XML de la generacion actual
  */
    void CreateXMLFile();
    /**
  * @brief Obtiene la generacion
  */
    int getGeneration() const;
    /**
   * @brief ACtualiza la maxima generacion
   */
    void setMaxGeneration(int maxGeneration);
    /**
   * @brief Compara dos individuos segun su fitness
    * @param a, b
     */
    static bool compareFitness(Individual * a, Individual *b);
    /**
   * @brief obtiene la maxima generacion
   */

    int getMaxGeneration() const;



};


#endif //DATOSII_PROYECTOII_IMAGE_RECOVERY_POPULATION_H
