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

    ScreenSetter(int interface) {
        screen = interface;
        GistLight.loadFromFile("GistLight.otf");
        index.setFont(GistLight);
        index.setCharacterSize(45);
        index.setColor(Color(39,137,179,255));
        index.setPosition({625,716});
    }

    void setBackground (string location, Vector2f size) {
        backgroundTexture.loadFromFile(location);
        background.setSize(size);
        background.setPosition({0,0});
        background.setTexture(&backgroundTexture);
    }

    void setDisplay(RenderWindow &window) {
        if (screen == 1) {
            pathEntry.setFont(GistLight);
            pathEntry.setPosition({110, 430});
            textbox.setSize({800,40});
            textbox.setFillColor(Color(189,195,199,100));
            textbox.setPosition(97,430);
            btn.setPosition({655,480});
            btn.setImage("appMedia/images/RecovButton.png");
            titleTexture.loadFromFile("appMedia/images/Name.png");
            title.setTexture(&titleTexture);
            title.setPosition({100,200});
            title.setSize({800,229});
        } else if (screen == 2) {
            generationsEntry.setFont(GistLight);
            generationsEntry.setSelected(false, screen);
            setBackground("appMedia/images/generation background.png", Vector2f(1000,800));
            image.setSize({250,250});
            image.setPosition(110,490);
            generationsEntry.setPosition({110, 430});
            textbox.setSize({808,40});
            textbox.setFillColor(Color(189,195,199,100));
            textbox.setPosition(97,430);
            btn.setPosition({655,480});
            btn.setImage("appMedia/images/choose.png");
        } else if (screen == 3) {
            setBackground("appMedia/images/generation display.png", Vector2f(1000,800));
        }
    }

    void setSelected(bool sel) {
        if (screen == 1) {
            pathEntry.setSelected(sel, screen);
        } else if (screen == 2) {
            generationsEntry.setSelected(sel, screen);
        }
    }

    void setIndex(int indx) {
        generationIndex = indx;
        index.setString(to_string(generationIndex + 1));
    }

    void typedOn(Event input) {
        if (screen == 1) {
            pathEntry.typedOn(input);
        } else if (screen == 2) {
            generationsEntry.typedOn(input);
        }
    }

    bool isMouseOver(RenderWindow &window) {
        btn.isMouseOver(window);
    }

    void setBtnImage(string location) {
        btn.setImage(location);
    }

    void setImage(string path) {
        imageTexture.loadFromFile(path);
        image.setTexture(&imageTexture);
    }

    void setImageSize(Vector2f size) {
        image.setSize(size);
    }

    void setImagePosition(Vector2f pos) {
        image.setPosition(pos);
    }

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

    string getText() {
        if (screen == 1) {
            return pathEntry.getText();
        } else if (screen == 2) {
            return generationsEntry.getText();
        }
    }

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