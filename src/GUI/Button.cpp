#include "GUI/Button.h"

Button::Button(sf::Text buttonText,
               void action(AppData&), AppData &appData)
: appData(appData)
{
    this->buttonText = buttonText;
    this->action = action;
    this->field.setSize(sf::Vector2f(this->buttonText.getGlobalBounds().width, 2 * this->buttonText.getGlobalBounds().height));
    setCenterPosition(sf::Vector2f(field.getSize().x / 2, field.getSize().y / 2));
}

Button::~Button()
{

}

void Button::draw(sf::RenderWindow &window)
{
    window.draw(this->field);
    window.draw(this->buttonText);
}

void Button::runAction()
{
    this->action(this->appData);
}

bool Button::isMouseOn(sf::Vector2f mousePos)
{
    return this->field.getGlobalBounds().contains(mousePos);
}

void Button::setCenterPosition(sf::Vector2f position)
{
    this->field.setPosition(position.x - field.getSize().x / 2, position.y - field.getSize().y / 2);
    this->buttonText.setPosition(field.getPosition().x + (field.getSize().x - buttonText.getGlobalBounds().width) / 2,
                                 field.getPosition().y + (field.getSize().y - buttonText.getGlobalBounds().height) / 3);
}

void Button::setSize(sf::Vector2f size)
{
    this->field.setSize(size);
}

void Button::setTextSize(unsigned textSize)
{
    this->buttonText.setCharacterSize(textSize);
}

void Button::setTextColor(sf::Color color)
{
    this->buttonText.setFillColor(color);
}

void Button::setFieldColor(sf::Color color)
{
    this->field.setFillColor(color);
}

void Button::setBorder(uint16_t weight, sf::Color color)
{
    this->field.setOutlineThickness(weight);
    this->field.setOutlineColor(color);
}

