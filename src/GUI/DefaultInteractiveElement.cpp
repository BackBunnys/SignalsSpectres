#include "GUI/DefaultInteractiveElement.h"
#include "cmath"

DefaultInteractiveElement::DefaultInteractiveElement(sf::Text text, AppData &appData): appData(&appData)
{
    this->activeBorderColor = sf::Color(150, 150, 150);
    this->isActive = false;
    this->text = text;
    this->textSize = text.getCharacterSize();
    this->textHoverSize = this->textSize;
    setSize(sf::Vector2f(this->text.getGlobalBounds().width, 2 * this->text.getGlobalBounds().height));
    setCenterPosition(sf::Vector2f(0, 0));
}

DefaultInteractiveElement::~DefaultInteractiveElement()
{
    //dtor
}

void DefaultInteractiveElement::update()
{
    sf::Vector2i mousePos = sf::Mouse::getPosition(*this->appData->GetWindow());
    if(isMouseOn(mousePos.x, mousePos.y))
        onHoverTransform();
    else onUnHoverTransform();
}

void DefaultInteractiveElement::draw(sf::RenderWindow &window)
{
    window.draw(this->field);
    window.draw(this->text);
}

void DefaultInteractiveElement::activate()
{
    this->isActive = true;

    this->field.setOutlineColor(this->activeBorderColor);
}

void DefaultInteractiveElement::deactivate()
{
    this->isActive = false;

    this->field.setOutlineColor(this->borderColor);
}

bool DefaultInteractiveElement::isMouseOn(float xPos, float yPos)
{
    return this->field.getGlobalBounds().contains(xPos, yPos);
}

void DefaultInteractiveElement::setPosition(sf::Vector2f position)
{
    this->field.setPosition(position);
    this->text.setPosition(field.getPosition().x + (field.getSize().x - text.getGlobalBounds().width) / 2,
                           field.getPosition().y + (field.getSize().y - text.getGlobalBounds().height) / 3);
}

void DefaultInteractiveElement::setCenterPosition(sf::Vector2f centerPosition)
{
    setPosition(sf::Vector2f(centerPosition.x - field.getSize().x / 2, centerPosition.y - field.getSize().y / 2));
}

void DefaultInteractiveElement::setSize(sf::Vector2f size)
{
    this->field.setSize(size);
}

void DefaultInteractiveElement::setTextSize(unsigned textSize, unsigned onHoverSize)
{
    this->text.setCharacterSize(textSize);
    this->textSize = textSize;
    this->textHoverSize = onHoverSize;
}

void DefaultInteractiveElement::setTextColor(sf::Color color, sf::Color onHoverColor)
{
    this->text.setFillColor(color);
    this->textColor = color;
    this->textHoverColor = onHoverColor;
}

void DefaultInteractiveElement::setFieldColor(sf::Color color, sf::Color onHoverColor)
{
    this->field.setFillColor(color);
    this->fieldColor = color;
    this->fieldHoverColor = onHoverColor;
}

void DefaultInteractiveElement::setBorder(uint16_t weight, sf::Color color)
{
    this->borderColor = color;
    this->field.setOutlineThickness(weight);
    this->field.setOutlineColor(borderColor);
}

void DefaultInteractiveElement::setActiveBorderColor(sf::Color color)
{
    this->activeBorderColor = color;
}

void DefaultInteractiveElement::onHoverTransform()
{
    this->field.setFillColor(this->fieldHoverColor);
    this->text.setFillColor(this->textHoverColor);
    this->text.setCharacterSize(this->textHoverSize);
}

#include <iostream>
void DefaultInteractiveElement::onUnHoverTransform()
{
    if(this->text.getFillColor() != this->textColor) {
        sf::Color color = this->text.getFillColor();
        this->text.setFillColor(sf::Color(color.r - (textHoverColor.r - textColor.r) / 20,
                                          color.r - (textHoverColor.g - textColor.g) / 20,
                                          color.r - (textHoverColor.b - textColor.b) / 20));
    }
    if(this->field.getFillColor() != this->fieldColor) {
        sf::Color color = this->field.getFillColor();
        this->field.setFillColor(sf::Color(color.r - (fieldHoverColor.r - fieldColor.r) / 20,
                                           color.r - (fieldHoverColor.g- fieldColor.g) / 20,
                                           color.r - (fieldHoverColor.b - fieldColor.b) / 20));
    }
    if(this->text.getCharacterSize() != this->textSize) {
       unsigned size = text.getCharacterSize();
       this->text.setCharacterSize(size - std::ceil((size - textSize) / 100));
    }
}
