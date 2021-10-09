#include <iostream>
#include<SFML/Graphics.hpp>

using namespace sf;

int main() {
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
    }
    return 0;
}
