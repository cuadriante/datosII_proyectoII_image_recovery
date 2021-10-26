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
    }

    void setBackground (string location, Vector2f size) {
        backgroundTexture.loadFromFile(location);
        background.setSize(size);
        background.setPosition({0,0});
        background.setTexture(&backgroundTexture);
    }

    void setDisplay(RenderWindow &window) {
//        window.clear(Color::Black);
        userEntry.setFont(GistLight);
        if (screen == 1) {
            userEntry.setPosition({110,430});
            textbox.setSize({800,40});
            textbox.setFillColor(Color(189,195,199,100));
            textbox.setPosition(97,430);
            btn.setPosition({655,480});
            btn.setImage("appMedia/images/RecovButton.png");
            titleTexture.loadFromFile("appMedia/images/Name.png");
            title.setTexture(&titleTexture);
            title.setPosition({100,200});
            title.setSize({800,229});
        } else if (screen = 2) {
            userEntry.setSelected(false);
            setBackground("appMedia/images/generation background.png", Vector2f(1000,800));
            userEntry.setPosition({110,430});
            textbox.setSize({800,40});
            textbox.setFillColor(Color(189,195,199,100));
            textbox.setPosition(97,430);
            btn.setPosition({655,480});
            btn.setImage("appMedia/images/choose.png");
        }
    }

    void setSelected(bool sel) {
        userEntry.setSelected(sel);
    }

    void typedOn(Event input) {
        userEntry.typedOn(input);
    }

    bool isMouseOver(RenderWindow &window) {
        btn.isMouseOver(window);
    }

    void setBtnImage(string location) {
        btn.setImage(location);
    }

    void drawTo(RenderWindow &window) {
        if (screen == 1){
            window.draw(background);
            window.draw(textbox);
            userEntry.drawTo(window);
            btn.drawTo(window);
            window.draw(title);
        } else if (screen == 2) {
            window.draw(background);
            window.draw(textbox);
            userEntry.drawTo(window);
            btn.drawTo(window);
        }
//        window.clear(Color::Black);

    }

    string getText() {
        return userEntry.getText();
    }

    void setScreen(int interface) {
        screen = interface;
    }

private:
    Texture backgroundTexture, titleTexture;
    RectangleShape background, textbox, title;
    Textbox userEntry;
    int screen;
    Font GistLight;
    Button btn;
};

#endif