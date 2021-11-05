/**
 * @file ImageHandler.h
 * @version 1.0
 * @date 04 de noviembre de 2021
 * @author Adriana Calderón
 * @title Análisis de imágenes
 */

#ifndef DATOSII_PROYECTOII_IMAGE_RECOVERY_IMAGEHANDLER_H
#define DATOSII_PROYECTOII_IMAGE_RECOVERY_IMAGEHANDLER_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <random>
#include "ColorInfo.h"
#include "ImageInfo.h"

using namespace sf;
using namespace std;



class ImageHandler {

private:
    Image image;
    vector<int> ogImage;
    vector<int> newImage;
    vector<ColorInfo> whiteRectangle;
    vector<ColorInfo> colorList;
    vector<char> imageContent;
    int whiteRectangleCoordinates [4] = {0, 0, 0, 0}; //x1 y1 x2 y2
    int whiteRectangleWidth = 0;
    int whiteRectangleHeight = 0;
    const int WHITE_MINIMUM = 195;

public:
    /**
     * @brief Constructor
     * @param imageName
     */
    explicit ImageHandler(String imageName);

    /**
     * ANaliza todos los pixeles de la imagen y la vuelve a dibujar
     * @param imageName
     */
    [[noreturn]] void analyzeImage(String imageName);

    /**
     * @brief recolorea el rectangulo blanco de la imagen segun el vector de pixeles dado
     */
    void recolorInitialWhiteRectangle();

    /**
     * @brief guarda los cambios en los pixeles de la imagen en la nueva imagen
     * @param generation
     */
    void saveChangesToImageFile(int generation);

    void calculateColorPercentages();

    /**
     * @brief Imprime el contenido de la imagen
     */
    void printContents();

    const vector<ColorInfo> &getWhiteRectangle() const;

    vector<ColorInfo> &getColorList();

    /**
     * @brief obtiene coordenadas del rectangulo blanco
     * @return
     */
    const int *getWhiteRectangleCoordinates() const;

    const Image &getImage() const;
    /**
     * @brief recolorea rectangulo blanco segun vector de pixeles dado
     * @param newPixelSetIndex
     * @param width
     * @param height
     * @param generation
     */

    void recolorWhiteRectangle(const vector<char> &newPixelSetIndex, int width, int height, int generation);

    /**
     * @brief inicia algoritmo genetico hasta llegar a la maxima generacion
     * @param maxGeneration
     */
    void startGeneticAlgorithm(int maxGeneration);

    /**
     * @brief crea genoma ideal con base en especificaciones
     * @return
     */
    vector<char> createIdealGenome();

    /**
     * @brief Constructor
     */
    ImageHandler();
};


#endif //DATOSII_PROYECTOII_IMAGE_RECOVERY_IMAGEHANDLER_H
