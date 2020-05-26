#ifndef GUI_H
#define GUI_H

#include "SFML/Graphics.hpp"

class GUI
{
    public:
        virtual void draw(sf::RenderWindow &window) = 0;
        virtual ~GUI() {}
};

#endif // GUI_H
