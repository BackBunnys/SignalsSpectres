#ifndef BUTTON_H
#define BUTTON_H

#include "SFML/Graphics.hpp"
#include "Engine/AppData.h"
#include "DefaultInteractiveElement.h"

class Button: public DefaultInteractiveElement
{
    public:
        Button(sf::Text buttonText,
               void action(AppData&), AppData &appData);

        bool processEvent(sf::Event& event);

        void runAction();

    private:

        void (*action) (AppData&);

};

#endif // BUTTON_H
