#include <iostream>
#include <SFML/Graphics.hpp>
#include <string.h>

#include "ScreenSetter.h"

using namespace sf;

Texture backgroundTexture;
RectangleShape background, textbox;
string emptyText = "";
int interface = 1;
string userEntry = "";

int main() {

//    ImageHandler imageHandler("greenPattern.png");

    string emptyText = "";

    //sfml window
    RenderWindow window (VideoMode(1000, 800), "Image Recovery");

    ScreenSetter displayer(interface);

    displayer.setBackground("appMedia/images/Background.png",Vector2f(1000,800));

    displayer.setDisplay(window);

    while (window.isOpen())
    {
        Event event;

        if (Keyboard::isKeyPressed(Keyboard::Return)) {
            displayer.setSelected(true);
        } else if (Keyboard::isKeyPressed(Keyboard::Escape)) {
            displayer.setSelected(false);
        }

        while(window.pollEvent(event))
        {
            switch (event.type) {

                case Event::Closed:
                    window.close();

                case Event::TextEntered:
                    displayer.typedOn(event);
                    break;

                case Event::MouseMoved:
                    if (displayer.isMouseOver(window)) {
                        if (interface == 1) {
                            displayer.setBtnImage("appMedia/images/Selected recovButton.jpeg");
                        } else if (interface == 2) {
                            displayer.setBtnImage("appMedia/images/selected choose.png");
                        }
                    } else {
                        if (interface == 1) {
                            displayer.setBtnImage("appMedia/images/RecovButton.png");
                        } else if (interface == 2) {
                            displayer.setBtnImage("appMedia/images/choose.png");
                        }
                    }
                    break;

                case Event::MouseButtonPressed:
                    if (displayer.isMouseOver(window)) {
                        if (displayer.getText().compare(emptyText) == 0) {
                            cout << "Gotta write a path, u dumb :v \n";
                        } else {
                            userEntry = displayer.getText();
                            if (interface == 1) {
                                displayer.setImage(userEntry);
                            }
                            interface += 1;
                            displayer.setScreen(interface);
                            displayer.setDisplay(window);

                        }
                    }
            }
        }
        window.clear(Color::Black);
        displayer.drawTo(window);
        window.display();
//        imageHandler.storeImageAsPixels();
    }
    return 0;
}
