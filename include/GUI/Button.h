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
        void setTextSize(unsigned textSize, unsigned onHoverSize);
        void setTextColor(sf::Color color, sf::Color onHoverColor);
        void setFieldColor(sf::Color color, sf::Color onHoverColor);
        void setBorder(uint16_t weight, sf::Color color);

        void update();

        void draw(sf::RenderWindow &window);

        template <typename T>
        bool isMouseOn(const sf::Vector2<T> mousePos)
        {
            return this->field.getGlobalBounds().contains(mousePos.x, mousePos.y);
        }

        void runAction();

    private:
        sf::Text buttonText;
        sf::RectangleShape field;

        unsigned textSize, textHoverSize;
        sf::Color textColor, textHoverColor,
                  fieldColor, fieldHoverColor;

        AppData &appData;

        void (*action) (AppData&);

        void onHoverTransform();
};

#endif // BUTTON_H
