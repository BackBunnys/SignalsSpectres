#ifndef GUIHANDLER_H
#define GUIHANDLER_H

#include <vector>
#include <map>

#include "InteractiveGUIElement.h"

class GUIHandler
{
    public:
        GUIHandler();

        virtual void update();
        virtual void draw(sf::RenderWindow& window);
        virtual bool processEvent(sf::Event &event);

        virtual void addInteractive(std::string key, InteractiveGUIElement* elem, bool Activate = false);
        virtual void addDynamic(DynamicGUI* elem);
        virtual void addStatic(sf::Drawable* elem);

        virtual InteractiveGUIElement* getInteractiveElement(std::string key);

        virtual ~GUIHandler();

    private:
        std::vector<std::pair<std::string, InteractiveGUIElement*> > interactivElems;
        std::vector<DynamicGUI*> dynamicElems;
        std::vector<sf::Drawable*> staticElems;

        int activeElementIndex;

        void changeActive(int index);
};

#endif // GUIHANDLER_H
