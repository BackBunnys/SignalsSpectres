#ifndef INTERACTIVEGUIELEMENT_H
#define INTERACTIVEGUIELEMENT_H

#include "SFML/Graphics.hpp"

class InteractiveGUIElement
{
    public:

        virtual void update() = 0;
        virtual void draw(sf::RenderWindow &window) = 0;
        virtual bool processEvent(sf::Event &event) = 0;

        virtual void activate() = 0;
        virtual void deactivate() = 0;

        virtual bool isMouseOn(float xPos, float yPos) = 0;

        virtual ~InteractiveGUIElement() {}
};

#endif // INTERACTIVEGUIELEMENT_H
