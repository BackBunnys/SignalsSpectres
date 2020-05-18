#ifndef GUIHANDLER_H
#define GUIHANDLER_H

#include <vector>

#include "InteractiveGUIElement.h"

class GUIHandler
{
    public:
        GUIHandler();

        virtual void update();
        virtual void draw(sf::RenderWindow& window);
        virtual bool processEvent(sf::Event &event);

        virtual void addInteractive(InteractiveGUIElement* elem);
        virtual void addStatic(sf::Drawable* elem);

        virtual ~GUIHandler();

    private:
        std::vector<InteractiveGUIElement*> interactivElems;
        std::vector<sf::Drawable*> staticElems;

        int activeElementIndex;

        void changeActive(int index);
};

#endif // GUIHANDLER_H
