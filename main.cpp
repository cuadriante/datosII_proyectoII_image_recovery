#include <iostream>
#include <SFML/Graphics.hpp>
#include <string.h>

#include "ScreenSetter.h"

using namespace sf;

string emptyText = "";
int interface = 1;
string imagepath = "";
string stringImgGenerations = "";
int imageGenerations = 0;
int generationIndex = 0;

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
                        if (displayer.getText().compare(emptyText) == 0 && interface < 3) {
                            cout << "Gotta write a path, u dumb :v \n";
                        } else {
                            if (interface == 1) {
                                imagepath = displayer.getText();
                                displayer.setImage(imagepath);
                            } else if (interface == 2) {
                                stringImgGenerations = displayer.getText();
                                imageGenerations = stoi(stringImgGenerations);
                                displayer.setImagePosition({245,165});
                                displayer.setImageSize({500,500});
                                displayer.setImage("out" + to_string(imageGenerations) + ".png");
                                generationIndex = imageGenerations;
                                displayer.setIndex(generationIndex);
                            }
                            interface += 1;
                            displayer.setScreen(interface);
                            displayer.setDisplay(window);

                        }
                    }

            }


            if (Keyboard::isKeyPressed(Keyboard::Left)) {
                if (interface == 3) {
                    if (generationIndex == 0) {
                        generationIndex = imageGenerations;
                    } else {
                        generationIndex -= 1;
                    }
                    displayer.setIndex(generationIndex);

                    cout << generationIndex << endl;
                    displayer.setImage("out" + to_string(generationIndex) + ".png");
                }
            }
            if (Keyboard::isKeyPressed(Keyboard::Right)) {
                if (interface == 3) {
                    if (generationIndex == imageGenerations) {
                        generationIndex = 0;
                    } else {
                        generationIndex += 1;
                    }
                    displayer.setIndex(generationIndex);

                    cout << generationIndex << endl;
                    displayer.setImage("out" + to_string(generationIndex) + ".png");

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
