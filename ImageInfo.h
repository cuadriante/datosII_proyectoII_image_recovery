/**
 * @file ImageInfo.h
 * @version 1.0
 * @date 04 de noviembre de 2021
 * @author Adriana Calderón
 * @title Análisis de la información de la imagen
 */

#ifndef DATOSII_PROYECTOII_IMAGE_RECOVERY_IMAGEINFO_H
#define DATOSII_PROYECTOII_IMAGE_RECOVERY_IMAGEINFO_H


#include "ColorInfo.h"

using namespace std;

class ImageInfo {
private:
    int width = 0;
    int height = 0;
    int validPixelQuantity = 0;
    vector<ColorInfo> * colorList;
    vector<double> colorFrequencyPercentages;
    vector<double> colorRelationsPercentage;
    vector<char> imageContent;

public:
    /**
     * @brief Constructor
     * @param imageContent
     * @param width
     * @param height
     * @param colorList
     */
    ImageInfo(const vector<char> &imageContent, int width, int height, vector<ColorInfo> * colorList);

    void calculateColorDistributionSum();

    int findColor(Color color);

    /**
     * Inicializa analisis de la imagen
     */
    void initialize();

    void calculateColorPercentages();
    /**
     * @brief retorna porcentaje de frecuencia de los colores
     * @return
     */
    const vector<double> &getColorFrequencyPercentages() const;

    /**
     * retorna porcentaje de relaciones de los colores
     * @param x
     * @param y
     * @return
     */
    double getColorRelationsPercentage(int x, int y) const;

    /**
     * actualiza porcentaje de relaciones de los colores
     * @param x
     * @param y
     * @param percentage
     */
    void setColorRelationsPercentage(int x, int y, double percentage);

    void debug();

    /**
     * obtiene contenido de la imagen
     * @return
     */
    vector<char> getImageContent();

    /**
     * @brief obtiene elemento del contenido de la imagen
     * @param index
     * @return
     */
    char getImageContentElement(int index);
};


#endif //DATOSII_PROYECTOII_IMAGE_RECOVERY_IMAGEINFO_H
