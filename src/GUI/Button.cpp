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
