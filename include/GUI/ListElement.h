#ifndef LISTELEMENT_H
#define LISTELEMENT_H

#include "cmath"

#include "SFML/Graphics.hpp"
#include "Engine/AppData.h"
#include "DefaultInteractiveElement.h"

template <typename T>
class ListElement: public DefaultInteractiveElement
{
    public:
        ListElement(sf::Text text, T data, AppData &appData): DefaultInteractiveElement(text, appData)
        {
            this->data = data;
            unselect();
        }

        void update() override
        {
            if(!this->isSelected)
                DefaultInteractiveElement::update();
        }

        bool processEvent(sf::Event &event)
        {
            return false;
        }

        void select() { this->isSelected = true; onSelectTransform(); }
        void unselect() { this->isSelected = false; }

        void setText(std::string text) { this->text.setString(text); }

        T getData() { return this->data; }
        sf::Vector2f getSize() { return this->field.getSize(); }

        bool isSelect() { return this->isSelected; }

        void setFieldSelectedColor(sf::Color color) { this->fieldSelectedColor = color; }
        void setTextSelectedColor(sf::Color color) { this-> textSelectedColor = color; }

        void onSelectTransform()
        {
            this->field.setFillColor(fieldSelectedColor);
            this->text.setFillColor(textSelectedColor);
        }

    private:
        bool isSelected;

        sf::Color fieldSelectedColor,
                  textSelectedColor;

        T data;
};

#endif // LISTELEMENT_H
