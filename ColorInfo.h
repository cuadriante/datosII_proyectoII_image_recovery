/**
 * @file ColorInfo.h
 * @version 1.0
 * @date 04 de noviembre de 2021
 * @author Adriana Calderón
 * @title Administración de color
 */

#ifndef DATOSII_PROYECTOII_IMAGE_RECOVERY_COLORINFO_H
#define DATOSII_PROYECTOII_IMAGE_RECOVERY_COLORINFO_H

#include <iostream>
#include<SFML/Graphics.hpp>

using namespace sf;

class ColorInfo {
private:
    const int GRAY_DELTA = 10;
    const int MIN_GRAY_LEVEL = 100;
    const int WHITE_MINIMUM = 195;
    int red = 0;
    int green = 0;
    int blue = 0;
    int nRed = 0;
    int nGreen = 0;
    int nBlue = 0;
    Color color;

    int normalize(int color);

public:
    const int NORMALIZED_RANGE = 3;

    /**
     * @brief Constructor
     * @param color Color con formato de SFML
     */
    ColorInfo(Color color);

    /**
     * @brief Getter del código para el color rojo
     * @return Un entero correspondiente al color rojo
     */
    int getRed() const;

    /**
     * @brief Getter del código para el color verde
     * @return Un entero correspondiente al color verde
     */
    int getGreen() const;

    /**
     * @brief Getter del código para el color azul
     * @return Un entero correspondiente al color azul
     */
    int getBlue() const;

    /**
     * @brief Establece el color de un pixel
     * @param newColor Color elegido por el usuario
     */
    void setColor(const Color &newColor);

    /**
     * @brief Getter del color rojo normalizado
     * @return Un entero correspondiente al color rojo normalizado
     */
    int getNRed() const;

    /**
     * @brief Getter del color verde normalizado
     * @return Un entero correspondiente al color verde normalizado
     */
    int getNGreen() const;

    /**
     * @brief Getter del color azul normalizado
     * @return Un entero correspondiente al color azul normalizado
     */
    int getNBlue() const;

    /**
     * @brief Getter del color de un pixel en formato SFML
     * @return Un valor del tipo Color
     */
    const Color &getColor() const;

    /**
     * @brief Determina si dos objetos ColorInfo poseen colores similares
     * @param colorInfo Color a comparar
     * @return Una respuesta afirmativa o negativa de la comparación
     */
    bool isSimilar(ColorInfo * colorInfo);

    /**
     * @brief Determina si un pixel se encuentra en escala de grises
     * @return Una respuesta afirmativa o negativa de la comprobación
     */
    bool isGrayScale();



};


#endif //DATOSII_PROYECTOII_IMAGE_RECOVERY_COLORINFO_H
