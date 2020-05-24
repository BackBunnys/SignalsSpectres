#ifndef CHOOSELIST_H
#define CHOOSELIST_H

#include <vector>

#include "SFML/Graphics.hpp"
#include "ListElement.h"

template <typename T>
class ChooseList: public InteractiveGUIElement
{
    public:
        ChooseList(uint32_t selectionLimit)
        {
            this->isActive = false;
            this->activeElementIndex = 0;
            this->numOfSelected = 0;
            this->selectionLimit = selectionLimit;
            this->field.setFillColor(sf::Color::Transparent);
        }

        ChooseList(std::vector<ListElement<T>* > elements, uint32_t selectionLimit): ChooseList(selectionLimit)
        {
            this->isActive = false;
            addElement(elements);
        }

        virtual ~ChooseList() {
            clear();
        }

        void clear()
        {
            for(size_t i = 0; i < elements.size(); ++i)
                delete elements[i];
            elements.clear();
            onResized();
        }

        void setBorder(uint16_t weight, sf::Color borderColor, sf::Color activeBorderColor)
        {
            this->borderColor = borderColor;
            this->activeBorderColor = activeBorderColor;
            this->field.setOutlineThickness(weight);
            this->field.setOutlineColor(borderColor);
        }

        void setPosition(sf::Vector2f position)
        {
            this->field.setPosition(position);

            for(size_t i = 0; i < elements.size(); ++i)
            {
                elements[i]->setPosition(position);
                position.y += elements[i]->getSize().y + elements[i]->getBorderWidth();
            }
        }

        void setCenterPosition(sf::Vector2f position)
        {
            setPosition(sf::Vector2f(position.x - this->field.getSize().x / 2, position.y - this->field.getSize().y / 2));
        }

        void addElement(ListElement<T>* element) {
            this->elements.push_back(element);
            onResized();
        }

        void insertElement(ListElement<T>* element, uint32_t index) {
            this->elements.insert(elements.begin() + index, element);
            onResized();
        }

        void addElements(std::vector<ListElement<T>* > elements)
        {
            this->elements.insert(this->elements.end(), elements.begin(), elements.end());
            onResized();
        }

        void removeElement(uint32_t index)
        {
            delete this->elements[index];
            this->elements.erase(this->elements.begin() + index);
            onResized();
        }

        void draw(sf::RenderWindow &window)
        {
            for(size_t i = 0; i < elements.size(); ++i)
                if(i != activeElementIndex)
                    elements[i]->draw(window);
            window.draw(this->field);
            elements[activeElementIndex]->draw(window);
        }

        void update()
        {
            for(size_t i = 0; i < elements.size(); ++i)
                elements[i]->update();
        }

        bool processEvent(sf::Event &event)
        {
            if(event.type == sf::Event::MouseButtonPressed)
            {
                if(event.mouseButton.button == sf::Mouse::Left)
                    if(isMouseOn(event.mouseButton.x, event.mouseButton.y)) {
                        changeActive(findElem(event.mouseButton.x, event.mouseButton.y));
                        return true;
                    }
            }
            if(event.type == sf::Event::MouseButtonReleased) {
                if(event.mouseButton.button == sf::Mouse::Left)
                    if(isMouseOn(event.mouseButton.x, event.mouseButton.y)) {
                        changeSelection();
                        return true;
                    }
            }
            else if(event.type == sf::Event::KeyPressed) {
                if(event.key.code == sf::Keyboard::Up) {
                    changeActive(this->activeElementIndex - 1);
                    return true;
                }
                else if(event.key.code == sf::Keyboard::Down) {
                    changeActive(this->activeElementIndex + 1);
                    return true;
                }
                else if(event.key.code == sf::Keyboard::Enter) {
                    if(activeElementIndex >= 0 && activeElementIndex < elements.size())
                    {
                        changeSelection();
                        return true;
                    }
                }
            }
            return false;
        }

        void activate()
        {
            this->isActive = true;
            if(activeElementIndex >= 0 && activeElementIndex < elements.size())
                elements[activeElementIndex]->activate();

            this->field.setOutlineColor(this->activeBorderColor);
        }
        void deactivate()
        {
            this->isActive = false;
            if(activeElementIndex >= 0 && activeElementIndex < elements.size())
                this->elements[activeElementIndex]->deactivate();

            this->field.setOutlineColor(this->borderColor);
        }

        bool isMouseOn(float xPos, float yPos)
        {
            return this->field.getGlobalBounds().contains(xPos, yPos);
        }

        void changeSelection()
        {
            if(!elements[activeElementIndex]->isSelect()) {
                if(numOfSelected < selectionLimit)
                {
                    elements[activeElementIndex]->select();
                    ++numOfSelected;
                }
            }
            else {
                elements[activeElementIndex]->unselect();
                --numOfSelected;
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
        int activeElementIndex;

        sf::RectangleShape field;

        sf::Color borderColor, activeBorderColor;

        bool isActive;

        uint32_t selectionLimit;
        uint32_t numOfSelected;

        void onResized()
        {
            updateFieldSize();
            setPosition(field.getPosition());
        }

        void updateFieldSize()
        {
            sf::Vector2f maxSize = findMaxWidthHeight();
            float totalHeight = 0;
            float borderWidth = 0;

            for(size_t i = 0; i < elements.size(); ++i)
            {
                borderWidth = elements[i]->getBorderWidth();
                elements[i]->setSize(maxSize);
                totalHeight += maxSize.y + borderWidth;
            }
            field.setSize(sf::Vector2f(maxSize.x, totalHeight - borderWidth));
        }

        sf::Vector2f findMaxWidthHeight()
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
            return sf::Vector2f(maxWidth, maxHeight);
        }

        void changeActive(int index)
        {
            if(index < 0) index += elements.size();
            index %= elements.size();

            if(index != activeElementIndex) {
                if(this->activeElementIndex < elements.size())
                    this->elements[activeElementIndex]->deactivate();
                this->activeElementIndex = index;
                this->elements[activeElementIndex]->activate();
            }
        }

        size_t findElem(float xPos, float yPos)
        {
            for(size_t i = 0; i < elements.size(); ++i)
                if(elements[i]->isMouseOn(xPos, yPos))
                    return i;
            return elements.size();
        }
};

#endif // CHOOSELIST_H
