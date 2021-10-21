#include <iostream>
#include <SFML/Graphics.hpp>
#include <string.h>
#include "ImageHandler.h"
#include "Textbox.h"
#include "Button.h"

using namespace sf;

int main() {

//    ImageHandler imageHandler("greenPattern.png");

    string emptyText = "";

    //sfml window
    RenderWindow window (VideoMode(1000, 800), "Image Recovery");

    Font arial;
    arial.loadFromFile("arial.ttf");
    Textbox textbox1(15, Color::Black, true);
    textbox1.setFont(arial);
    textbox1.setPosition({100,100});
//    textbox1.setLimit(true, 10);

    Button btn1("Click me", {200, 50}, 20, Color(55,65,64,255), Color::White);
    btn1.setPosition({680, 135});
    btn1.setFont(arial);

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
                    break;

                case Event::MouseMoved:
                    if (btn1.isMouseOver(window)) {
                        btn1.setTextColor(Color::Black);
                        btn1.setBackColor(Color(217, 203, 158, 255));
                    } else {
                        btn1.setTextColor(Color::White);
                        btn1.setBackColor(Color(55,65,64,255));
                    }
                    break;

                case Event::MouseButtonPressed:
                    if (btn1.isMouseOver(window)) {
//                        const char *userEntry = textbox1.getText();
                        cout << textbox1.getText().compare(emptyText) << endl;
//                        cout << textbox1.getText() + " holi\n";
                    }
            }
        }
        window.clear(Color(23,57,84,255));
        textbox1.drawTo(window);
        btn1.drawTo(window);
        window.display();
//        imageHandler.storeImageAsPixels();
    }
    return 0;
}
