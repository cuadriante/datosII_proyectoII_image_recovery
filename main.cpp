#include <iostream>
#include<SFML/Graphics.hpp>
#include "ImageHandler.h"
#include "Textbox.h"
#include "imageButton.h"

using namespace sf;

int main() {

//    ImageHandler imageHandler("greenPattern.png");


    //sfml window
    RenderWindow window (VideoMode(1000, 800), "Image Recovery");

    Font arial;
    arial.loadFromFile("arial.ttf");
    Textbox textbox1(15, Color::White, true);
    textbox1.setFont(arial);
    textbox1.setPosition({100,100});
//    textbox1.setLimit(true, 10);

    while (window.isOpen())
    {
        Event event;

        if (Keyboard::isKeyPressed(Keyboard::Return)) {
            textbox1.setSelected(true);
        } else if (Keyboard::isKeyPressed(Keyboard::Escape)) {
            textbox1.setSelected(false);
        }

        while(window.pollEvent(event))
        {
            switch (event.type) {

                case Event::Closed:
                    window.close();

                case Event::TextEntered:
                    textbox1.typedOn(event);
            }
        }
        window.clear(Color(23,57,84,255));
        textbox1.drawTo(window);
        window.display();
//        imageHandler.storeImageAsPixels();
    }
    return 0;
}
