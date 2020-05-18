#ifndef CHOOSELIST_H
#define CHOOSELIST_H

#include <vector>

#include "SFML/Graphics.hpp"
#include "ListElement.h"

template <typename T>
class ChooseList: InteractiveGUIElement
{
    public:
        ChooseList(uint32_t selectionLimit)
        {
            this->isActive = false;
            this->numOfSelected = 0;
            this->selectionLimit = selectionLimit;
            this->field.setFillColor(sf::Color::Transparent);
        }

        ChooseList(std::vector<ListElement<T>* > elements, uint32_t selectionLimit): ChooseList(selectionLimit)
        {
            this->isActive = false;
            this->elements = elements;
            updateFieldSize();
            setPosition(field.getPosition());
        }

        virtual ~ChooseList() {
            clear();
        }

        void clear()
        {
            for(size_t i = 0; i < elements.size(); ++i)
                delete elements[i];
            elements.clear();
        }

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
                elements[i]->setPosition(sf::Vector2f(position.x, yPos));
                yPos += elements[i]->getSize().y;
            }
        }

        void setCenterPosition(sf::Vector2f position)
        {
            setPosition(sf::Vector2f(position.x - this->field.getSize().x / 2, position.y - this->field.getSize().y / 2));
        }

        void addElement(ListElement<T>* element) {
            this->elements.push_back(element);
            updateFieldSize();
            setPosition(field.getPosition());
        }

        void insertElement(ListElement<T>* element, uint32_t index) {
            this->elements.insert(elements.begin() + index, element);
            updateFieldSize();
            setPosition(field.getPosition());
        }

        void addElements(std::vector<ListElement<T>* > elements)
        {
            this->elements.insert(this->elements.end(), elements.begin(), elements.end());
            updateFieldSize();
            setPosition(field.getPosition());
        }

        void removeElement(uint32_t index)
        {
            delete this->elements[index];
            this->elements.erase(this->elements.begin() + index);
            updateFieldSize();
            setPosition(field.getPosition());
        }

        void draw(sf::RenderWindow &window)
        {
            window.draw(this->field);
            for(size_t i = 0; i < elements.size(); ++i)
                elements[i]->draw(window);
        }

        void update()
        {
            for(size_t i = 0; i < elements.size(); ++i)
                elements[i]->update();
        }

        bool processEvent(sf::Event &event)
        {
            if(event.type == sf::Event::MouseButtonReleased)
                if(event.mouseButton.button == sf::Mouse::Left)
                    if(isMouseOn(event.mouseButton.x, event.mouseButton.y)) {
                        changeSelection(event.mouseButton.x, event.mouseButton.y);
                        return true;
                    }
            return false;
        }

        void activate() { this->isActive = true; }
        void deactivate() { this->isActive = false; }

        bool isMouseOn(float xPos, float yPos)
        {
            return this->field.getGlobalBounds().contains(xPos, yPos);
        }

        void changeSelection(float xPos, float yPos)
        {
            for(size_t i = 0; i < elements.size(); ++i)
                if(elements[i]->isMouseOn(xPos, yPos)) {
                    if(!elements[i]->isSelect()) {
                        if(numOfSelected < selectionLimit)
                        {
                            elements[i]->select();
                            ++numOfSelected;
                        }
                    }
                    else {
                        elements[i]->unselect();
                        --numOfSelected;
                    }
                }
        }

        std::vector<ListElement<T>* > getSelectedElements()
        {
            std::vector<ListElement<T>* > selectedElements;
            for(size_t i = 0; i < elements.size(); ++i)
                if(elements[i]->isSelect())
                    selectedElements.push_back(elements[i]);
            return selectedElements;
        }

        std::vector<T> getSelectedElementsData()
        {
            std::vector<T> data;
            for(size_t i = 0; i < elements.size(); ++i)
                if(elements[i]->isSelect())
                    data.push_back(elements[i]->getData());
            return data;
        }

        uint32_t getNumOfSelected() { return this->numOfSelected; }

    private:
        std::vector<ListElement<T>* > elements;

        sf::RectangleShape field;

        bool isActive;

        uint32_t selectionLimit;
        uint32_t numOfSelected;

        void updateFieldSize()
        {
            int32_t maxWidth = elements[0]->getSize().x,
                    maxHeight = elements[0]->getSize().y;
            for(size_t i = 0; i < elements.size(); ++i)
            {
                sf::Vector2f size = elements[i]->getSize();
                if(size.x > maxWidth)
                    maxWidth = size.x;
                if(size.y > maxHeight)
                    maxHeight = size.y;
            }
            for(size_t i = 0; i < elements.size(); ++i)
            {
                elements[i]->setSize(sf::Vector2f(maxWidth, maxHeight));
            }
            field.setSize(sf::Vector2f(maxWidth, maxHeight * elements.size()));
        }
};

#endif // CHOOSELIST_H
