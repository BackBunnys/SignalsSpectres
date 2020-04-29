#ifndef INPUTBOX_H
#define INPUTBOX_H

#include "SFML/Graphics.hpp"

class InputBox
{
    public:
        InputBox(sf::Font &font,
                   sf::Vector2u fieldSize, unsigned borderSize, unsigned textSize,
                   sf::Color fieldColor, sf::Color borderColor, sf::Color textColor,
                   sf::Color delimiterColor);
        virtual ~InputBox();

        void setPosition(sf::Vector2f position);
        void setHorizontalPadding(uint16_t px);
        void setSelectedTextColor(sf::Color color);
        void setSelectedFieldColor(sf::Color color);

        sf::FloatRect getGlobalBounds() const;
        std::string getInputtedText() const;

        void draw(sf::RenderWindow &window);

        void addChar(uint32_t code);
        void copyFromBuffer();
        void removeChar();

        void selectAll();
        void unselect();

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

        bool isSelected;

        int32_t currentPosition;
        int32_t leftVisibleCorner;
        int32_t rightVisibleCorner;

        uint16_t horizontalPadding;

        void updateText();
        void updatePtr();
};

#endif // INPUTBOX_H
