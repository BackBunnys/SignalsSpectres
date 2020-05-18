#ifndef INPUTBOX_H
#define INPUTBOX_H

#include "SFML/Graphics.hpp"
#include "GUI/InteractiveGUIElement.h"

class InputBox: public InteractiveGUIElement
{
    public:
        InputBox(sf::Font &font,
                   sf::Vector2u fieldSize, unsigned borderSize, unsigned textSize,
                   sf::Color fieldColor, sf::Color borderColor, sf::Color textColor,
                   sf::Color delimiterColor);
        virtual ~InputBox();

        void update();
        void draw(sf::RenderWindow &window);
        bool processEvent(sf::Event &event);

        void setInputtedCharLimits(uint32_t left, uint32_t right = 0);
        void setPosition(sf::Vector2f position);
        void setHorizontalPadding(uint16_t px);
        void setSelectedTextColor(sf::Color color);
        void setSelectedFieldColor(sf::Color color);

        sf::FloatRect getGlobalBounds() const;
        std::string getInputtedText() const;

        void addChar(uint32_t code);
        void copyFromBuffer();
        void removeChar();

        void selectAllText();
        void unselectAllText();
        void activate();
        void deactivate();

        bool isMouseOn(float xPos, float yPos)
        {
            return this->field.getGlobalBounds().contains(xPos, yPos);
        }

        bool isActivated();

        void move(int chars);

    private:
        std::wstring inputtedText;
        sf::Text visibleText;

        sf::RectangleShape field;
        sf::RectangleShape inputPtr;
        sf::RectangleShape selectedMarker;

        sf::Color textColor;
        sf::Color selectedTextColor;

        sf::Clock timer;
        sf::Time ptrTime;

        uint32_t leftLimit;
        uint32_t rightLimit;

        bool isTextSelected;
        bool isActive;
        bool isPtrVisible;

        int32_t currentPosition;
        int32_t leftVisibleCorner;
        int32_t rightVisibleCorner;

        uint16_t horizontalPadding;

        void updateText();
        void updatePtr();
};

#endif // INPUTBOX_H
