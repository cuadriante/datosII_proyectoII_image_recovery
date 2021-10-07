#include <iostream>
#include<SFML/Graphics.hpp>

int main() {
    sf::RenderWindow window (sf::VideoMode(1000, 800), "Image Recovery");
    while (window.isOpen())
    {
        sf::Event event;
        while(window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.clear(sf::Color(23,57,84,255));
        window.display();
    }
    return 0;
}
