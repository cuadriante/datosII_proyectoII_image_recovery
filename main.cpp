#include <iostream>
#include <SFML/Graphics.hpp>
#include <string.h>
#include "ImageHandler.h"
#include "Textbox.h"
#include "Button.h"

using namespace sf;

Texture backgroundTexture;
RectangleShape background, textbox;

int main() {

//    ImageHandler imageHandler("greenPattern.png");

    string emptyText = "";

    //sfml window
    RenderWindow window (VideoMode(1000, 800), "Image Recovery");

    backgroundTexture.loadFromFile("appMedia/images/Background.png");
    background.setSize(Vector2f(1000,800));
    background.setPosition(0,0);
    background.setTexture(&backgroundTexture);

    Font arial;
    arial.loadFromFile("arial.ttf");
    Textbox userEntry(15, Color::Black, false);
    userEntry.setFont(arial);
    userEntry.setPosition({100, 600});
    textbox.setSize({800,40});
    textbox.setFillColor(Color(189,195,199,175));
    textbox.setPosition(97,600);
    userEntry.setLimit(true, 10);

    Button btn1("Click me", {200, 50}, 20, Color(55,65,64,255), Color::White, "appMedia/images/RecovButton.png");
    btn1.setPosition({680, 135});
    btn1.setFont(arial);

    while (window.isOpen())
    {
        Event event;

        if (Keyboard::isKeyPressed(Keyboard::Return)) {
            userEntry.setSelected(true);
        } else if (Keyboard::isKeyPressed(Keyboard::Escape)) {
            userEntry.setSelected(false);
        }

        while(window.pollEvent(event))
        {
            switch (event.type) {

                case Event::Closed:
                    window.close();

                case Event::TextEntered:
                    userEntry.typedOn(event);
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
//                        const char *userEntry = userEntry.getText();
                        cout << userEntry.getText() << endl;
//                        cout << userEntry.getText() + " holi\n";
                    }
            }
        }
        window.clear();
        window.draw(background);
        window.draw(textbox);
        userEntry.drawTo(window);
        btn1.drawTo(window);
        window.display();
//        imageHandler.storeImageAsPixels();
    }
    return 0;
}
