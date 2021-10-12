#ifndef DATOSII_PROYECTOII_IMAGE_RECOVERY_IMAGEBUTTON_H
#define DATOSII_PROYECTOII_IMAGE_RECOVERY_IMAGEBUTTON_H

using namespace std;
using namespace sf;

class imageButton {
public:
    imageButton() {}

    imageButton(string t, Vector2f size, int charSize, Color bgColor, Color textColor) {
        text.setString(t);
        text.setColor(textColor);
        text.setCharacterSize(charSize);

        button.setSize(size);
        button.setFillColor(bgColor);

    }

    void setFont(Font &font) {
        text.setFont(font);
    }

    void setBackColor(Color color) {
        button.setFillColor(color);
    }

    void setTextColor(Color color) {
        text.setColor(color);
    }

    void setPosition(Vector2f pos) {
        button.setPosition(pos);

        float xPos = (pos.x + button.getGlobalBounds().width / 2) - (text.getGlobalBounds().width / 2);
        float yPos = (pos.y + button.getGlobalBounds().height / 2) - (text.getGlobalBounds().width / 2);
        text.setPosition({xPos, yPos});
    }

    void drawTo(RenderWindow &window) {
        window.draw(button);
        window.draw(text);
    }

    bool isMouseOver(RenderWindow &window) {
        float mouseX = Mouse::getPosition(window).x;
        float mouseY = Mouse::getPosition(window).y;

        float btnPosX = button.getPosition().x;
        float btnPosY = button.getPosition().y;

        float btnxPosWidth = button.getPosition().x + button.getLocalBounds().width;
        float btnyPosHeight = button.getPosition().y + button.getLocalBounds().height;

        if(mouseX < btnxPosWidth && mouseX > btnPosX && mouseY < btnyPosHeight && mouseY > btnPosY) {
            return true;
        }

        return false;
    }

private:
    RectangleShape button;
    Text text;
};

#endif