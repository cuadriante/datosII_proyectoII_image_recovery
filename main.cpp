#include <iostream>
#include<SFML/Graphics.hpp>
#include <valarray>
#include "ImageHandler.h"
#include "StrategyTest.h"

using namespace sf;


int main() {

    // Load test image
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

        // retrieves colors and starts genetic algorithm
        imageHandler.analyzeImage();
    }
    return 0;
}
