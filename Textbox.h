/**
 * @file Textbox.h
 * @version 1.0
 * @date 04 de noviembre de 2021
 * @author Gregory Alpízar
 * @title Entradas de texto para usuario
 */

#ifndef DATOSII_PROYECTOII_IMAGE_RECOVERY_TEXTBOX_H
#define DATOSII_PROYECTOII_IMAGE_RECOVERY_TEXTBOX_H
#define DELETE_KEY 8
#define ENTER_KEY 13
#define ESCAPE_KEY 27
#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include <sstream>

using namespace sf;
using namespace std;

class Textbox {
public:

    /**
     * @brief Constructor
     */
    Textbox() {
        textbox.setCharacterSize(27);
        textbox.setColor(Color::Black);
        isSelected = false;

        textbox.setString("Press 'Enter' key and write the image path");
    }

    /**
     * @brief Establece la fuente de texto a utilizar
     * @param font Fuente a utilizar
     */
    void setFont(Font &font) {
        textbox.setFont(font);
    }

    /**
     * @brief Establece la posición de la entrada de texto en la pantalla
     * @param pos Vector de dos fraccionarios con los valores para X y Y
     */
    void setPosition(Vector2f pos) {
        background.setPosition(95,100);
        textbox.setPosition(pos);
    }

    /**
     * @brief Establece si el usuario puede escribir o no
     * @param sel Indicación para habilitar o deshabilitar
     * @param screen pantalla mostrada
     */
    void setSelected(bool sel, int screen) {
        isSelected = sel;
        if (!sel) {
            string newT;
            if (screen == 1) {
                newT = "Press 'Enter' key and write the image path";
            } else if (screen == 2) {
                newT = "Press 'Enter' key and write the number of generations";
            }

            textbox.setString(newT);

        } else {
            textbox.setString("");
        }
    }

    /**
     * @brief Obtiene la entrada de texto del usuario
     * @return Cadena de texto del usuario
     */
    string getText() {
        return text.str();
    }

    /**
     * @brief Dibuja los elementos en pantalla
     * @param window Ventana en uso
     */
    void drawTo(RenderWindow &window) {
        window.draw(background);
        window.draw(textbox);
    }

    /**
     * @brief Ingresa los caracteres seleccionados por el usuario
     * @param input 
     */
    void typedOn(Event input) {
        if (isSelected) {
            int charTyped = input.text.unicode;

            if (charTyped < 128) {

                if (hasLimit) {

                    if (text.str().length() <= limit) {
                        inputLogic(charTyped);
                    } else if (text.str().length() >= limit && charTyped == DELETE_KEY) {
                        deleteLastChar();
                    }
                }

                else {
                    inputLogic(charTyped);
                }
            }
        }
    }

private:
    RectangleShape background;
    Text textbox;
    ostringstream text;
    bool isSelected = false;
    bool hasLimit = false;
    int limit;
    string generationIndex;

    void inputLogic(int charTyped) {
        if (charTyped != DELETE_KEY && charTyped != ENTER_KEY && charTyped != ESCAPE_KEY) {
            text << static_cast<char>(charTyped);
        } else if (charTyped == DELETE_KEY) {
            if (text.str().length() > 0) {
                deleteLastChar();
            }
        }

        textbox.setString(text.str() + "_");
    }

    void deleteLastChar() {
        string t = text.str();
        string newT = "";
        for (int i = 0; i < t.length() - 1; ++i) {
            newT += t[i];
        }

        text.str("");
        text << newT;

        textbox.setString(text.str());
    }
};

#endif