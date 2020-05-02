#include "DefaultInteractiveElement.h"
#include "cmath"

DefaultInteractiveElement::DefaultInteractiveElement(sf::Text text, AppData &appData): appData(appData)
{
    this->text = text;
    this->textSize = text.getCharacterSize();
    this->textHoverSize = this->textSize;
    setSize(sf::Vector2f(this->text.getGlobalBounds().width, 2 * this->text.getGlobalBounds().height));
    setCenterPosition(sf::Vector2f(field.getSize().x / 2, field.getSize().y / 2));
}

DefaultInteractiveElement::~DefaultInteractiveElement()
{
    //dtor
}

void DefaultInteractiveElement::update()
{
    sf::Vector2i mousePos = sf::Mouse::getPosition(*this->appData.GetWindow());
    if(isMouseOn(mousePos.x, mousePos.y))
        onHoverTransform();
    else onUnHoverTransform();
}

void DefaultInteractiveElement::draw(sf::RenderWindow &window)
{
    window.draw(this->field);
    window.draw(this->text);
}

bool DefaultInteractiveElement::isMouseOn(float xPos, float yPos)
{
    return this->field.getGlobalBounds().contains(xPos, yPos);
}

void DefaultInteractiveElement::setCenterPosition(sf::Vector2f position)
{
    this->field.setPosition(position.x - field.getSize().x / 2, position.y - field.getSize().y / 2);
    this->text.setPosition(field.getPosition().x + (field.getSize().x - text.getGlobalBounds().width) / 2,
                           field.getPosition().y + (field.getSize().y - text.getGlobalBounds().height) / 3);
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
    this->field.setOutlineThickness(weight);
    this->field.setOutlineColor(color);
}

void DefaultInteractiveElement::onHoverTransform()
{
    this->field.setFillColor(this->fieldHoverColor);
    this->text.setFillColor(this->textHoverColor);
    this->text.setCharacterSize(this->textHoverSize);
}

void DefaultInteractiveElement::onUnHoverTransform()
{
    if(this->text.getFillColor() != this->textColor) {
        sf::Color color = this->text.getFillColor();
        this->text.setFillColor(sf::Color(color.r - std::ceil((color.r - textColor.r) / 10),
                                          color.r - std::ceil((color.g - textColor.g) / 10),
                                          color.r - std::ceil((color.b - textColor.b) / 10)));
    }
    if(this->field.getFillColor() != this->fieldColor) {
        sf::Color color = this->field.getFillColor();
        this->field.setFillColor(sf::Color(color.r - std::ceil((color.r - fieldColor.r) / 10),
                                           color.r - std::ceil((color.g - fieldColor.g) / 10),
                                           color.r - std::ceil((color.b - fieldColor.b) / 10)));
    }
    if(this->text.getCharacterSize() != this->textSize) {
       unsigned size = text.getCharacterSize();
       this->text.setCharacterSize(size - std::ceil((size - textSize) / 100));
    }
}
