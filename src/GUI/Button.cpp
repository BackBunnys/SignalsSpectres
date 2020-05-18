#include "GUI/Button.h"
#include "cmath"

Button::Button(sf::Text buttonText,
               void action(AppData&), AppData &appData)
: DefaultInteractiveElement(buttonText, appData)
{
    this->action = action;
}

void Button::runAction()
{
    this->action(*this->appData);
}

bool Button::processEvent(sf::Event& event)
{
    if(event.type == sf::Event::MouseButtonReleased) {
        if(event.mouseButton.button == sf::Mouse::Left)
            if(isMouseOn(event.mouseButton.x, event.mouseButton.y)) {
                runAction();
                return true;
            }
        return false;
    }
    else if(event.type == sf::Event::KeyPressed) {
        if(event.key.code == sf::Keyboard::Enter)
            runAction();
        else return false;
    } else return false;

    return true;
}
