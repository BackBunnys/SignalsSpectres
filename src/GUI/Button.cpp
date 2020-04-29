#include "GUI/Button.h"
#include "cmath"

Button::Button(sf::Text buttonText,
               void action(AppData&), AppData &appData)
: appData(appData)
{
    this->buttonText = buttonText;
    this->textSize = buttonText.getCharacterSize();
    this->textHoverSize = this->textSize;
    this->action = action;
    this->field.setSize(sf::Vector2f(this->buttonText.getGlobalBounds().width, 2 * this->buttonText.getGlobalBounds().height));
    setCenterPosition(sf::Vector2f(field.getSize().x / 2, field.getSize().y / 2));
}

Button::~Button()
{

}

void Button::update()
{
    if(isMouseOn(sf::Mouse::getPosition(*this->appData.GetWindow())))
        onHoverTransform();
    else {
        if(this->buttonText.getFillColor() != this->textColor) {
            sf::Color color = this->buttonText.getFillColor();
            this->buttonText.setFillColor(sf::Color(color.r - std::ceil((color.r - textColor.r) / 10),
                                                    color.r - std::ceil((color.g - textColor.g) / 10),
                                                    color.r - std::ceil((color.b - textColor.b) / 10)));
        }
        if(this->field.getFillColor() != this->fieldColor) {
            sf::Color color = this->field.getFillColor();
            this->field.setFillColor(sf::Color(color.r - std::ceil((color.r - fieldColor.r) / 10),
                                               color.r - std::ceil((color.g - fieldColor.g) / 10),
                                               color.r - std::ceil((color.b - fieldColor.b) / 10)));
        }
        if(this->buttonText.getCharacterSize() != this->textSize) {
            unsigned size = buttonText.getCharacterSize();
            this->buttonText.setCharacterSize(size - std::ceil((size - textSize) / 100));
        }
    }
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

void Button::onHoverTransform()
{
    this->field.setFillColor(this->fieldHoverColor);
    this->buttonText.setFillColor(this->textHoverColor);
    this->buttonText.setCharacterSize(this->textHoverSize);
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

void Button::setTextSize(unsigned textSize, unsigned onHoverSize)
{
    this->buttonText.setCharacterSize(textSize);
    this->textSize = textSize;
    this->textHoverSize = onHoverSize;
}

void Button::setTextColor(sf::Color color, sf::Color onHoverColor)
{
    this->buttonText.setFillColor(color);
    this->textColor = color;
    this->textHoverColor = onHoverColor;
}

void Button::setFieldColor(sf::Color color, sf::Color onHoverColor)
{
    this->field.setFillColor(color);
    this->fieldColor = color;
    this->fieldHoverColor = onHoverColor;
}

void Button::setBorder(uint16_t weight, sf::Color color)
{
    this->field.setOutlineThickness(weight);
    this->field.setOutlineColor(color);
}

