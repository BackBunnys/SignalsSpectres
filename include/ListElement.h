#ifndef LISTELEMENT_H
#define LISTELEMENT_H

#include "cmath"

#include "SFML/Graphics.hpp"
#include "Engine/AppData.h"

template <typename T>
class ListElement
{
    public:
        ListElement(sf::Text text, T data, AppData &appData): appData(appData)
        {
            this->text = text;
            this->data = data;
            this->textSize = text.getCharacterSize();
            this->textHoverSize = this->textSize;
            setSize(sf::Vector2f(text.getGlobalBounds().width, text.getGlobalBounds().height * 2));
            setPosition(sf::Vector2f(0, 0));
            unselect();
        }

        void update()  //TODO: do something with code duplicate with button class (some new class maybe?)
        {
            if(isMouseOn(sf::Mouse::getPosition(*this->appData.GetWindow())))
                onHoverTransform();
            else if(!this->isSelected) {
                if(this->text.getFillColor() != this->textColor) {
                    sf::Color color = this->text.getFillColor();
                    this->text.setFillColor(sf::Color(color.r - std::ceil((color.r - textColor.r) / 10),
                                                      color.r - std::ceil((color.g - textColor.g) / 10),
                                                      color.r - std::ceil((color.b - textColor.b) / 10)));
                }
                if(this->field.getFillColor() != this->fieldColor) {
                    sf::Color color = this->field.getFillColor();
                    this->field.setFillColor(sf::Color(color.r - std::ceil((color.r - fieldColor.r) / 10),
                                                       color.r - std::ceil((color.g - fieldColor.g) / 10),
                                                       color.r - std::ceil((color.b - fieldColor.b) / 10)));
                }
                if(this->text.getCharacterSize() != this->textSize) {
                    unsigned size = text.getCharacterSize();
                    this->text.setCharacterSize(size - std::ceil((size - textSize) / 100));
                }
            }
        }

        void draw(sf::RenderWindow &window)
        {
            window.draw(this->field);
            window.draw(this->text);
        }

        void select() { this->isSelected = true; onHoverTransform(); }
        void unselect() { this->isSelected = false; }
        void onHoverTransform()
        {
            this->field.setFillColor(this->fieldHoverColor);
            this->text.setFillColor(this->textHoverColor);
            this->text.setCharacterSize(this->textHoverSize);
        }

        void setSize(sf::Vector2f size)
        {
            this->field.setSize(size);
        }

        void setPosition(sf::Vector2f position)
        {
            this->field.setPosition(position);
            this->text.setPosition(field.getPosition().x + (field.getSize().x - text.getGlobalBounds().width) / 2,
                                   field.getPosition().y + (field.getSize().y - text.getGlobalBounds().height) / 3);
        }

        void setTextSize(unsigned textSize, unsigned onHoverSize)
        {
            this->text.setCharacterSize(textSize);
            this->textSize = textSize;
            this->textHoverSize = onHoverSize;
        }

        void setTextColor(sf::Color color, sf::Color onHoverColor)
        {
            this->text.setFillColor(color);
            this->textColor = color;
            this->textHoverColor = onHoverColor;
        }

        void setFieldColor(sf::Color color, sf::Color onHoverColor)
        {
            this->field.setFillColor(color);
            this->fieldColor = color;
            this->fieldHoverColor = onHoverColor;
        }

        void setBorder(uint16_t weight, sf::Color color)
        {
            this->field.setOutlineThickness(weight);
            this->field.setOutlineColor(color);
        }

        template <typename t>
        bool isMouseOn(const sf::Vector2<t> mousePos)
        {
            return this->field.getGlobalBounds().contains(mousePos.x, mousePos.y);
        }

        T& getData() { return this->data; }

        bool isSelect() { return this->isSelected; }

    private:
        sf::Text text;
        sf::RectangleShape field;
        bool isSelected;

        unsigned textSize, textHoverSize;
        sf::Color textColor, textHoverColor,
                  fieldColor, fieldHoverColor;

        T data;
        AppData &appData;
};

#endif // LISTELEMENT_H
