#include <iostream>
#include<SFML/Graphics.hpp>
#include "ImageHandler.h"

using namespace sf;

int main() {

    ImageHandler imageHandler("brownPattern.png");


    //sfml window
    RenderWindow window (VideoMode(1000, 800), "Image Recovery");
    while (window.isOpen())
    {
        Event event;
        while(window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
        }
        window.clear(Color(23,57,84,255));
        window.display();
        imageHandler.storeImageAsPixels();
    }
    return 0;
}
