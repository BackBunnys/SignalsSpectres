#ifndef CHOOSELIST_H
#define CHOOSELIST_H

#include <vector>

#include "SFML/Graphics.hpp"
#include "ListElement.h"

template <typename T>
class ChooseList
{
    public:
        ChooseList(uint32_t selectionLimit)
        {
            this->numOfSelected = 0;
            this->selectionLimit = selectionLimit;
            this->field.setFillColor(sf::Color::Transparent);
        }

        ChooseList(std::vector<ListElement<T> > elements, uint32_t selectionLimit): ChooseList(selectionLimit)
        {
            this->elements = elements;
            updateFieldSize();
            setPosition(field.getPosition());
        }

        virtual ~ChooseList() {}

        void setBorder(uint16_t weight, sf::Color color)
        {
            this->field.setOutlineThickness(weight);
            this->field.setOutlineColor(color);
        }

        void setPosition(sf::Vector2f position)
        {
            this->field.setPosition(position);
            int32_t yPos = position.y;
            for(size_t i = 0; i < elements.size(); ++i)
            {
                elements[i].setPosition(sf::Vector2f(position.x, yPos));
                yPos += elements[i].getSize().y;
            }
        }

        void setCenterPosition(sf::Vector2f position)
        {
            setPosition(sf::Vector2f(position.x - this->field.getSize().x / 2, position.y - this->field.getSize().y / 2));
        }

        void addElement(ListElement<T> element) {
            this->elements.push_back(element);
            updateFieldSize();
            setPosition(field.getPosition());
        }

        void insertElement(ListElement<T> element, uint32_t index) {
            this->elements.insert(elements.begin() + index, element);
            updateFieldSize();
            setPosition(field.getPosition());
        }

        void addElements(std::vector<ListElement<T> > elements)
        {
            this->elements.insert(this->elements.end(), elements.begin(), elements.end());
            updateFieldSize();
            setPosition(field.getPosition());
        }

        void removeElement(uint32_t index)
        {
            this->elements.erase(this->elements.begin() + index);
            updateFieldSize();
            setPosition(field.getPosition());
        }

        void draw(sf::RenderWindow &window)
        {
            window.draw(this->field);
            for(size_t i = 0; i < elements.size(); ++i)
                elements[i].draw(window);
        }

        void update()
        {
            for(size_t i = 0; i < elements.size(); ++i)
                elements[i].update();
        }

        template <typename t>
        bool isMouseOn(sf::Vector2<t> mousePos)
        {
            return this->field.getGlobalBounds().contains(mousePos.x, mousePos.y);
        }

        template <typename t>
        void changeSelection(sf::Vector2<t> mousePos)
        {
            if(isMouseOn(mousePos))
                for(size_t i = 0; i < elements.size(); ++i)
                    if(elements[i].isMouseOn(mousePos)) {
                        if(!elements[i].isSelect()) {
                            if(numOfSelected < selectionLimit)
                            {
                                elements[i].select();
                                ++numOfSelected;
                            }
                        }
                        else {
                            elements[i].unselect();
                            --numOfSelected;
                        }
                    }
        }

        std::vector<ListElement<T> > getSelectedElements()
        {
            std::vector<ListElement<T> > selectedElements;
            for(size_t i = 0; i < elements.size(); ++i)
                if(elements[i].isSelect())
                    selectedElements.push_back(elements[i]);
            return selectedElements;
        }

        std::vector<T> getSelectedElementsData()
        {
            std::vector<T> data;
            for(size_t i = 0; i < elements.size(); ++i)
                if(elements[i].isSelect())
                    data.push_back(elements[i].getData());
            return data;
        }

        uint32_t getNumOfSelected() { return this->numOfSelected; }

    private:
        std::vector<ListElement<T> > elements;

        sf::RectangleShape field;

        uint32_t selectionLimit;
        uint32_t numOfSelected;

        void updateFieldSize()
        {
            int32_t maxWidth = elements[0].getSize().x,
                    maxHeight = elements[0].getSize().y;
            for(size_t i = 0; i < elements.size(); ++i)
            {
                sf::Vector2f size = elements[i].getSize();
                if(size.x > maxWidth)
                    maxWidth = size.x;
                if(size.y > maxHeight)
                    maxHeight = size.y;
            }
            for(size_t i = 0; i < elements.size(); ++i)
            {
                elements[i].setSize(sf::Vector2f(maxWidth, maxHeight));
            }
            field.setSize(sf::Vector2f(maxWidth, maxHeight * elements.size()));
        }
};

#endif // CHOOSELIST_H
