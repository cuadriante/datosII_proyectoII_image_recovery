#include <iostream>
#include<SFML/Graphics.hpp>
#include <valarray>
#include "ImageHandler.h"
#include <string.h>
#include "ScreenSetter.h"

using namespace sf;

string emptyText = "";
int interface = 1;
string imagepath = "";
string stringImgGenerations = "";
int imageGenerations = 0;
int generationIndex = 0;
ImageHandler imageHandler;

int startUI() {

    // Load test image
    //ImageHandler imageHandler("verticalStripesPattern.png");
    string emptyText = "";

    //sfml window
    RenderWindow window (VideoMode(1000, 800), "Image Recovery");

    ScreenSetter displayer(interface);

    displayer.setBackground("/home/dimi/CLionProjects/datosII_proyectoII_image_recovery/appMedia/images/Background.png",Vector2f(1000,800));

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
                            displayer.setBtnImage("/home/dimi/CLionProjects/datosII_proyectoII_image_recovery/appMedia/images/Selected recovButton.jpeg");
                        } else if (interface == 2) {
                            displayer.setBtnImage("/home/dimi/CLionProjects/datosII_proyectoII_image_recovery/appMedia/images/elected choose.png");
                        }
                    } else {
                        if (interface == 1) {
                            displayer.setBtnImage("/home/dimi/CLionProjects/datosII_proyectoII_image_recovery/appMedia/images/RecovButton.png");
                        } else if (interface == 2) {
                            displayer.setBtnImage("/home/dimi/CLionProjects/datosII_proyectoII_image_recovery/appMedia/images/choose.png");
                        }
                    }
                    break;

                case Event::MouseButtonPressed:
                    if (displayer.isMouseOver(window)) {
                        if (displayer.getText().compare(emptyText) == 0 && interface < 3) {
                            cout << "Input string cannot be empty!!\n";
                        } else {
                            if (interface == 1) {
                                imagepath = displayer.getText();
                                displayer.setImage(imagepath);
                                imageHandler.analyzeImage(imagepath);
                                // #####################################################################################

                                // La variable image path tiene la ubicación de la imagen que ingresó el usuario
                                // Elimine estos comentarios y cargue aquí la la imagen para su programa

                                // #####################################################################################

                            } else if (interface == 2) {
                                stringImgGenerations = displayer.getText();
                                imageGenerations = stoi(stringImgGenerations);
                                imageHandler.startGeneticAlgorithm(imageGenerations);


                                // #####################################################################################

                                // la variable imageGenerations es un int de la cantidad de generaciones que quiere el usuario
                                // Indique aquí la cantidad de generaciones de su programa con esa variable

                                // #####################################################################################
                                displayer.setImagePosition({245,165});
                                displayer.setImageSize({500,500});

                                // Coloque el procesamiento de la imagen aquí, porque la siguiente línea ya necesita una
                                // "imagen resultado" para mostrarla en pantalla

                                // A este setImage hay que configurarle bien el path de las imagenes de salida
                                displayer.setImage("output/out" + to_string(imageGenerations - 2) + ".png");
                                generationIndex = imageGenerations - 2;
                                displayer.setIndex(generationIndex + 1);
                            }
                            interface += 1;
                            displayer.setScreen(interface);
                            displayer.setDisplay(window);

                        }
                    }

            }


            if (Keyboard::isKeyPressed(Keyboard::Left)) {
                if (interface == 3) {
                    if (generationIndex == -1) {
                        generationIndex = imageGenerations - 2;
                    } else {
                        generationIndex -= 1;
                    }
                    displayer.setIndex(generationIndex + 1);

                    //Aquí también tiene que cambiar el path
                    displayer.setImage("output/out" + to_string(generationIndex) + ".png");
                }
            }
            if (Keyboard::isKeyPressed(Keyboard::Right)) {
                if (interface == 3) {
                    if (generationIndex == imageGenerations - 2) {
                        generationIndex = -1;
                    } else {
                        generationIndex += 1;
                    }
                    displayer.setIndex(generationIndex + 1);

                    // Aquí también tiene que cambiar el path
                    displayer.setImage("output/out" + to_string(generationIndex) + ".png");

                }
            }
        }
        window.clear(Color::Black);
        displayer.drawTo(window);
        window.display();

        // retrieves colors and starts genetic algorithm
        //imageHandler.analyzeImage();
    }
    return 0;
}

int test(){
    //imageHandler.analyzeImage("horizontalStripesPattern.png");
    //imageHandler.startGeneticAlgorithm(10);
}


int main(){
    startUI();
    //test();
}