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

        void select() { this->isSelected = true; onSelectTransform(); }
        void unselect() { this->isSelected = false; }

        void setText(std::string text) { this->text.setString(text); }

        T getData() { return this->data; }
        sf::Vector2f getSize() { return this->field.getSize(); }

        bool isSelect() { return this->isSelected; }

        void setFieldSelectedColor(sf::Color color) { this->fieldSelectedColor = color; }

        void onSelectTransform() { this->field.setFillColor(fieldSelectedColor); }

    private:
        bool isSelected;

        sf::Color fieldSelectedColor;

        T data;
};

#endif // LISTELEMENT_H
