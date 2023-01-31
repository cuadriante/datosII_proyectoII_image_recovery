/**
 * @file ScreenSetter.h
 * @version 1.0
 * @date 04 de noviembre de 2021
 * @author Gregory Alpízar
 * @title Configurador de pantallas
 */

#ifndef DATOSII_PROYECTOII_IMAGE_RECOVERY_SCREENSETTER_H
#define DATOSII_PROYECTOII_IMAGE_RECOVERY_SCREENSETTER_H

#include <iostream>
#include <SFML/Graphics.hpp>
#include <sstream>
#include "Textbox.h"
#include "Button.h"

using namespace sf;
using namespace std;

class ScreenSetter {
public:
    ScreenSetter() {}

    /**
     * @brief Constructor
     * @param interface Nivel de pantalla mostrada (1, 2 ó 3)
     */
    ScreenSetter(int interface) {
        screen = interface;
        GistLight.loadFromFile("/home/dimi/CLionProjects/datosII_proyectoII_image_recovery/fonts/arial.ttf");
        index.setFont(GistLight);
        index.setCharacterSize(45);
        index.setColor(Color(39,137,179,255));
        index.setPosition({625,716});
    }

    /**
     * @brief Almacena la imagen que se coloca en el fondo
     * @param location Ubicación de la imagen de fondo
     * @param size Tamaño para el fondo, de acuerdo con el tamaño de la ventana
     */
    void setBackground (string location, Vector2f size) {
        backgroundTexture.loadFromFile(location);
        background.setSize(size);
        background.setPosition({0,0});
        background.setTexture(&backgroundTexture);
    }

    /**
     * @brief Ordena todos los elementos en pantalla de acuerdo al nivel de progreso
     * @param window Ventana en uso
     */
    void setDisplay(RenderWindow &window) {
        if (screen == 1) {
            pathEntry.setFont(GistLight);
            pathEntry.setPosition({110, 430});
            textbox.setSize({800,40});
            textbox.setFillColor(Color(189,195,199,100));
            textbox.setPosition(97,430);
            btn.setPosition({655,480});
            btn.setImage("/home/dimi/CLionProjects/datosII_proyectoII_image_recovery/appMedia/images/RecovButton.png");
            titleTexture.loadFromFile("/home/dimi/CLionProjects/datosII_proyectoII_image_recovery/appMedia/images/Name.png");
            title.setTexture(&titleTexture);
            title.setPosition({100,200});
            title.setSize({800,229});
        } else if (screen == 2) {
            generationsEntry.setFont(GistLight);
            generationsEntry.setSelected(false, screen);
            setBackground("/home/dimi/CLionProjects/datosII_proyectoII_image_recovery/appMedia/images/generation background.png", Vector2f(1000,800));
            image.setSize({250,250});
            image.setPosition(110,490);
            generationsEntry.setPosition({110, 430});
            textbox.setSize({808,40});
            textbox.setFillColor(Color(189,195,199,100));
            textbox.setPosition(97,430);
            btn.setPosition({655,480});
            btn.setImage("/home/dimi/CLionProjects/datosII_proyectoII_image_recovery/appMedia/images/choose.png");
        } else if (screen == 3) {
            setBackground("/home/dimi/CLionProjects/datosII_proyectoII_image_recovery/appMedia/images/generation display.png", Vector2f(1000,800));
        }
    }

    /**
     * @brief Activa y desactiva la entrada de texto del usuario
     * @param sel Indica si se activa o se desactiva
     */
    void setSelected(bool sel) {
        if (screen == 1) {
            pathEntry.setSelected(sel, screen);
        } else if (screen == 2) {
            generationsEntry.setSelected(sel, screen);
        }
    }

    /**
     * @brief Indica cuál es la generación mostrada en pantalla
     * @param indx Imagen mostrada
     */
    void setIndex(int indx) {
        generationIndex = indx;
        index.setString(to_string(generationIndex + 1));
    }

    /**
     * @brief Ingresa los caracteres seleccionados por el usuario
     * @param input Caracter del usuario
     */
    void typedOn(Event input) {
        if (screen == 1) {
            pathEntry.typedOn(input);
        } else if (screen == 2) {
            generationsEntry.typedOn(input);
        }
    }

    /**
     * @brief Consulta a la clase Button si el mouse está posicionado sobre el botón
     * @param window Ventana en uso
     * @return Una respuesta afirmativa o negativa
     */
    bool isMouseOver(RenderWindow &window) {
        btn.isMouseOver(window);
    }

    /**
     * @brief Llama al método setImage de la clase Button
     * @param location Ubicación de la imagen
     */
    void setBtnImage(string location) {
        btn.setImage(location);
    }

    /**
     * @brief Establce la imagen que se muestra mediante la variable image
     * @param path Ubicación de la imagen seleccionada
     */
    void setImage(string path) {
        imageTexture.loadFromFile(path);
        image.setTexture(&imageTexture);
    }

    /**
     * @brief Establece el tamaño de la imagen
     * @param size Vector de dos fraccionarios que indican el ancho y alto de la imagen
     */
    void setImageSize(Vector2f size) {
        image.setSize(size);
    }

    /**
     * @brief Establece la posición de la imagen en pantalla
     * @param pos Vector de dos fraccionarios que indican la posición de la imagen en X y Y
     */
    void setImagePosition(Vector2f pos) {
        image.setPosition(pos);
    }

    /**
     * @brief Dibuja todos los elementos de acuerdo a la pantalla actual
     * @param window Ventana en uso
     */
    void drawTo(RenderWindow &window) {
        if (screen == 1){
            window.draw(background);
            window.draw(textbox);
            pathEntry.drawTo(window);
            btn.drawTo(window);
            window.draw(title);
        } else if (screen == 2) {
            window.draw(background);
            window.draw(textbox);
            generationsEntry.drawTo(window);
            btn.drawTo(window);
            window.draw(image);
        } else if (screen == 3) {
            window.draw(background);
            window.draw(image);
            window.draw(index);
        }
    }

    /**
     * @brief Llama al método getText de la clases Textbox
     * @return El texto ingresado por el usuario
     */
    string getText() {
        if (screen == 1) {
            return pathEntry.getText();
        } else if (screen == 2) {
            return generationsEntry.getText();
        }
    }

    /**
     * @brief Establece el nivel de pantalla actual
     * @param interface Nivel de progreso en pantalla
     */
    void setScreen(int interface) {
        screen = interface;
    }

private:
    Texture backgroundTexture, titleTexture, imageTexture;
    RectangleShape background, textbox, title, image;
    Textbox pathEntry, generationsEntry;
    int screen, generationIndex;
    Font GistLight;
    Button btn;
    Text index;
};

#endif