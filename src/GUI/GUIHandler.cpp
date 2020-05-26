#include "GUIHandler.h"

GUIHandler::GUIHandler()
{
    this->activeElementIndex = 0;
}

GUIHandler::~GUIHandler()
{
    for(size_t i = 0; i < interactivElems.size(); ++i) delete interactivElems[i].second;
    for(size_t i = 0; i < dynamicElems.size(); ++i) delete dynamicElems[i];
    for(size_t i = 0; i < staticElems.size(); ++i) delete staticElems[i];
}

void GUIHandler::update()
{
    for(size_t i = 0; i < interactivElems.size(); ++i) interactivElems[i].second->update();
    for(size_t i = 0; i < dynamicElems.size(); ++i) dynamicElems[i]->update();
}

void GUIHandler::draw(sf::RenderWindow &window)
{
    for(size_t i = 0; i < staticElems.size(); ++i) window.draw(*staticElems[i]);
    for(size_t i = 0; i < dynamicElems.size(); ++i) dynamicElems[i]->draw(window);
    for(size_t i = 0; i < interactivElems.size(); ++i) interactivElems[i].second->draw(window);
}

bool GUIHandler::processEvent(sf::Event &event)
{
    bool isProcessed = false;

    if(event.type == sf::Event::MouseButtonPressed) {
        bool isFind = false;
        size_t i;
        for(i = 0; !isFind && i < interactivElems.size(); ++i)
            if(interactivElems[i].second->isMouseOn(event.mouseButton.x, event.mouseButton.y))
                isFind = true;
        if(isFind) {
            changeActive(i - 1);
        }
    }
    else if(event.type == sf::Event::KeyPressed) {
        if(event.key.code == sf::Keyboard::Tab) {
            if(event.key.shift) changeActive(activeElementIndex - 1);
            else changeActive(activeElementIndex + 1);
        }
    }

    if(activeElementIndex < interactivElems.size())
        isProcessed = interactivElems[activeElementIndex].second->processEvent(event);


    return isProcessed;
}

void GUIHandler::addInteractive(std::string key, InteractiveGUIElement* elem, bool Activate)
{
    interactivElems.push_back(std::make_pair(key, elem));
    if(!Activate)
        this->interactivElems[activeElementIndex].second->activate();
    else
        changeActive(interactivElems.size() - 1);
}

void GUIHandler::addStatic(sf::Drawable* elem)
{
    staticElems.push_back(elem);
}

void GUIHandler::addDynamic(DynamicGUI* elem)
{
    dynamicElems.push_back(elem);
}

InteractiveGUIElement* GUIHandler::getInteractiveElement(std::string key)
{
    for(size_t i = 0; i < interactivElems.size(); ++i)
        if(interactivElems[i].first == key)
            return interactivElems[i].second;
    return NULL;
}

void GUIHandler::changeActive(int index)
{
    if(index < 0) index += interactivElems.size();
    index %= interactivElems.size();

    if(index != activeElementIndex) {
        if(this->activeElementIndex < interactivElems.size())
            this->interactivElems[activeElementIndex].second->deactivate();
        this->activeElementIndex = index;
        this->interactivElems[activeElementIndex].second->activate();
    }
}
