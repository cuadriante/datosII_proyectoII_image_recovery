#include <iostream>
#include<SFML/Graphics.hpp>
#include "ImageHandler.h"
#include "imageButton.h"

using namespace sf;

int main() {

    ImageHandler imageHandler("basicRedPattern.png");


    //sfml window
    RenderWindow window (VideoMode(1000, 800), "Image Recovery");

    imageButton btn1("Click me", {200, 50}, 20, Color::Green, Color::Black);
    btn1.setPosition({100, 300});

    while (window.isOpen())
    {
        Event event;
        while(window.pollEvent(event))
        {
            switch (event.type) {

                case Event::Closed:
                    window.close();

                case Event::MouseMoved:
                    if (btn1.isMouseOver(window)) {
                        btn1.setBackColor(Color::White);
                    } else {
                        btn1.setBackColor(Color::Green);
                    }

            }
        }
        window.clear(Color(23,57,84,255));
        btn1.drawTo(window);
        window.display();
//        imageHandler.storeImageAsPixels();
    }
    return 0;
}
