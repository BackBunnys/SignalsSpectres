#include "GUIHandler.h"

GUIHandler::GUIHandler()
{
    this->activeElementIndex = 0;
}

GUIHandler::~GUIHandler()
{
    for(size_t i = 0; i < interactivElems.size(); ++i) delete interactivElems[i];
    for(size_t i = 0; i < staticElems.size(); ++i) delete staticElems[i];
}

void GUIHandler::update()
{
    for(size_t i = 0; i < interactivElems.size(); ++i) interactivElems[i]->update();
}

void GUIHandler::draw(sf::RenderWindow &window)
{
    for(size_t i = 0; i < staticElems.size(); ++i) window.draw(*staticElems[i]);
    for(size_t i = 0; i < interactivElems.size(); ++i) interactivElems[i]->draw(window);
}

bool GUIHandler::processEvent(sf::Event &event)
{
    bool isProcessed = false;

    if(activeElementIndex < interactivElems.size())
        isProcessed = interactivElems[activeElementIndex]->processEvent(event);
    if(!isProcessed) {
        if(event.type == sf::Event::MouseButtonPressed) {
            bool isFind = false;
            size_t i;
            for(i = 0; !isFind && i < interactivElems.size(); ++i)
                if(interactivElems[i]->isMouseOn(event.mouseButton.x, event.mouseButton.y))
                    isFind = true;
            if(isFind) {
                changeActive(i - 1);
                isProcessed = true;
            }
        }
        else if(event.type == sf::Event::KeyPressed) {
            if(event.key.code == sf::Keyboard::Tab) {
                if(event.key.shift) changeActive(activeElementIndex - 1);
                else changeActive(activeElementIndex + 1);
                isProcessed = true;
            }
        }
    }

    return isProcessed;
}

void GUIHandler::addInteractive(InteractiveGUIElement* elem)
{
    interactivElems.push_back(elem);
    this->interactivElems[activeElementIndex]->activate();
}

void GUIHandler::addStatic(sf::Drawable* elem)
{
    staticElems.push_back(elem);
}

void GUIHandler::changeActive(int index)
{
    if(index < 0) index += interactivElems.size();
    index %= interactivElems.size();

    if(index != activeElementIndex) {
        if(this->activeElementIndex < interactivElems.size())
            this->interactivElems[activeElementIndex]->deactivate();
        this->activeElementIndex = index;
        this->interactivElems[activeElementIndex]->activate();
    }
}
