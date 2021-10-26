#include <iostream>
#include <SFML/Graphics.hpp>
#include <string.h>
#include "ImageHandler.h"
#include "Textbox.h"
#include "Button.h"
#include "ScreenSetter.h"

using namespace sf;

Texture backgroundTexture;
RectangleShape background, textbox;
string emptyText = "";
int interface = 1;
string chosenImage = "";

int main() {

//    ImageHandler imageHandler("greenPattern.png");

    string emptyText = "";

    //sfml window
    RenderWindow window (VideoMode(1000, 800), "Image Recovery");

    ScreenSetter displayer(interface);

    displayer.setBackground("appMedia/images/Background.png",Vector2f(1000,800));

//    backgroundTexture.loadFromFile("appMedia/images/Background.png");
//    background.setSize(Vector2f(1000,800));
//    background.setPosition(0,0);
//    background.setTexture(&backgroundTexture);

//    Font arial;
    displayer.setDisplay(window);
//    arial.loadFromFile("GistLight.otf");
//    Textbox userEntry(15, Color::Black, false);
//    userEntry.setFont(arial);
//    userEntry.setPosition({110, 600});
//    textbox.setSize({800,40});
//    textbox.setFillColor(Color(189,195,199,100));
//    textbox.setPosition(97,600);
//    userEntry.setLimit(true, 99999);

//    Button btn1("Click me", {200, 50}, 20, Color(55,65,64,255), Color::White, "appMedia/images/RecovButton.png");
//    btn1.setPosition({680, 135});
//    btn1.setFont(arial);

    while (window.isOpen())
    {
        Event event;

        if (Keyboard::isKeyPressed(Keyboard::Return)) {
            displayer.setSelected(true);
//            userEntry.setSelected(true);
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
//                        const char *userEntry = userEntry.getText();
//                        cout << "Jeje" << endl;
//                        cout << displayer.getText() + "\n";
                        if (displayer.getText().compare(emptyText) == 0) {
                            cout << "Gotta write a path, u dumb :v \n";
                        } else {
                            chosenImage = displayer.getText();
                            interface += 1;
                            displayer.setScreen(interface);
                            displayer.setDisplay(window);
                        }
                    }
            }
        }
        window.clear(Color::Black);
        displayer.drawTo(window);
//        window.draw(background);
//        window.draw(textbox);
//        userEntry.drawTo(window);
//        btn1.drawTo(window);
        window.display();
//        imageHandler.storeImageAsPixels();
    }
    return 0;
}
