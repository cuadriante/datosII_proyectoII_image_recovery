/**
 * @file Button.h
 * @version 1.0
 * @date 04 de noviembre de 2021
 * @author Gregory Alpízar
 * @title Botones para GUI
 * @brief Crea botones solicitados por la clase ScreenSetter
 */

#ifndef DATOSII_PROYECTOII_IMAGE_RECOVERY_BUTTON_H
#define DATOSII_PROYECTOII_IMAGE_RECOVERY_BUTTON_H

#include <iostream>
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

class Button {
public:

    /**
     * @brief Constructor
     */
    Button() {
        button.setSize({230, 59});
    }

    /**
     * @brief Establece la imagen mostrada sobre el botón
     * @param directory Directorio de la imagen elegida
     */
    void setImage(string directory) {
        image.loadFromFile(directory);
        button.setTexture(&image);
    }

    /**
     * @brief Establece la posición en pantalla
     * @param pos Vector de dos fraccionarias para las posiciones X y Y
     */
    void setPosition(Vector2f pos) {
        button.setPosition(pos);
    }

    /**
     * @brief Dibuja el botón en la pantalla
     * @param window Pantalla a utilizar
     */
    void drawTo(RenderWindow &window) {
        window.draw(button);
    }

    /**
     * @brief Detecta la posición del mouse para determinar si este se encuentra sobre el botón
     * @param window Ventana en uso
     * @return Un valor afirmativo o negativo
     */
    bool isMouseOver(RenderWindow &window) {
        float mouseX = Mouse::getPosition(window).x;
        float mouseY = Mouse::getPosition(window).y;

        float btnPosX = button.getPosition().x;
        float btnPosY = button.getPosition().y;

        float btnxPosWidth = button.getPosition().x + button.getLocalBounds().width;
        float btnyPosHeight = button.getPosition().y + button.getLocalBounds().height;

        if(mouseX < btnxPosWidth && mouseX > btnPosX && mouseY < btnyPosHeight && mouseY > btnPosY) {
            return true;
        }

        return false;
    }

private:
    RectangleShape button;
    Texture image;
};

#endif