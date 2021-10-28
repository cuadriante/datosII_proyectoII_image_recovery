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
    Textbox() {
        textbox.setCharacterSize(27);
        textbox.setColor(Color::Black);
        isSelected = false;

        textbox.setString("Press 'Enter' key and write the image path");
    }

//    Textbox(int size, Color color, bool sel) {
//        background.setSize({800,20});
//        background.setFillColor(Color(189,195,199,255));
//        background.setPosition(100,600);
//        textbox.setCharacterSize(size);
//        textbox.setColor(color);
//        textbox.setCharacterSize(27);
//        isSelected = sel;
//
//        if (sel) {
//            textbox.setString("_");
//        } else {
//            textbox.setString("Press 'Enter' key and write the image path");
//        }
//    }

    void setFont(Font &font) {
        textbox.setFont(font);
    }

    void setPosition(Vector2f pos) {
        background.setPosition(95,100);
        textbox.setPosition(pos);
    }

    void setLimit(bool ToF) {
        hasLimit = ToF;
    }

    void setLimit(bool ToF, int lim) {
        hasLimit = ToF;
        limit = lim - 1;
    }

    void setSelected(bool sel, int screen) {
        isSelected = sel;
        if (!sel) {
//            string t = text.str();
            string newT;
            if (screen == 1) {
                newT = "Press 'Enter' key and write the image path";
            } else if (screen == 2) {
                newT = "Press 'Enter' key and write the number of generations";
            }

//            for (int i = 0; i < t.length(); ++i) {
//                newT += t[i];
//            }

            textbox.setString(newT);
        } else {
            textbox.setString("");
        }
    }

    string getText() {
        return text.str();
    }

    void drawTo(RenderWindow &window) {
        window.draw(background);
        window.draw(textbox);
    }

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