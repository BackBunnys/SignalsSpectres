#ifndef INTERACTIVEGUIELEMENT_H
#define INTERACTIVEGUIELEMENT_H

#include "SFML/Graphics.hpp"

class InteractiveGUIElement
{
    public:

        virtual void update() = 0;
        virtual void draw(sf::RenderWindow &window) = 0;

        virtual bool isMouseOn(int xPos, int yPos) = 0;
};

#endif // INTERACTIVEGUIELEMENT_H
