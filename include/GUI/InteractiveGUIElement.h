#ifndef INTERACTIVEGUIELEMENT_H
#define INTERACTIVEGUIELEMENT_H

#include "DynamicGUI.h"

class InteractiveGUIElement: public DynamicGUI
{
    public:
        virtual bool processEvent(sf::Event &event) = 0;

        virtual void activate() = 0;
        virtual void deactivate() = 0;

        virtual bool isMouseOn(float xPos, float yPos) = 0;

        virtual ~InteractiveGUIElement() {}
};

#endif // INTERACTIVEGUIELEMENT_H
