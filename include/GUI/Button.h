#ifndef BUTTON_H
#define BUTTON_H

#include "SFML/Graphics.hpp"
#include "Engine/AppData.h"

class Button
{
    public:
        Button(sf::Text buttonText,
               void action(AppData&), AppData &appData);
        virtual ~Button();

        void setCenterPosition(sf::Vector2f position);
        void setSize(sf::Vector2f size);
        void setTextSize(unsigned textSize);
        void setTextColor(sf::Color color);
        void setFieldColor(sf::Color color);
        void setBorder(uint16_t weight, sf::Color color);

        void draw(sf::RenderWindow &window);

        bool isMouseOn(sf::Vector2f mousePos);

        void runAction();

    private:
        sf::Text buttonText;
        sf::RectangleShape field;

        AppData &appData;

        void (*action) (AppData&);
};

#endif // BUTTON_H
