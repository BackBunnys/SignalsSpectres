#include "ProgressBar.h"
#include <sstream>

ProgressBar::ProgressBar(sf::Font &font, uint16_t charSize)
{
    progressText.setFont(font);
    setProgress(0);
    setPosition(sf::Vector2f(0, 0));
    setSize(sf::Vector2f(400, 50));
    setTextSize(charSize);
    setPadding(4, Both);
    setBorder(4);

    setTextColor(sf::Color::Black);
    setFieldColor(sf::Color::White);
    setBorderColor(sf::Color::Black);
    setBarColor(sf::Color::Green);

    associateWithSource(NULL);

    updateText();
}

ProgressBar::~ProgressBar()
{
    //dtor
}

void ProgressBar::update()
{
    if(associatedSource)
        setProgress(associatedSource->getProgress());
}

void ProgressBar::draw(sf::RenderWindow &window)
{
    window.draw(this->field);
    window.draw(this->bar);
    window.draw(this->progressText);
}

void ProgressBar::addProgress(float percent)
{
    setProgress(this->progress + percent);
}

void ProgressBar::setProgress(float persent)
{
    unsigned progressBefore = static_cast<unsigned>(progress);
    if(persent < 0)
        persent = 0;
    else if(persent > 100)
        persent = 100;
    this->progress = persent;

    this->bar.setSize(sf::Vector2f(barWidth * progress / 100, bar.getSize().y));
    if(static_cast<unsigned>(progress) != progressBefore)
        updateText();
}

void ProgressBar::associateWithSource(const IProgressive* source)
{
    this->associatedSource = source;
}

void ProgressBar::setSize(sf::Vector2f size)
{
    this->field.setSize(size);
    this->barWidth = size.x - 2 * horizontalPadding;
    this->bar.setSize(sf::Vector2f(barWidth, size.y - 2 * verticalPadding));
    setProgress(this->progress);
}

void ProgressBar::setTextSize(uint16_t charSize)
{
    this->progressText.setCharacterSize(charSize);
    this->setPosition(field.getPosition());
}

void ProgressBar::setBorder(float weight)
{
    this->field.setOutlineThickness(weight);
}

void ProgressBar::setPadding(float padding, PaddingType type)
{
    switch(type) {
    case Horizontal:
        this->horizontalPadding = padding;
        break;
    case Vertical:
        this->verticalPadding = padding;
    case Both:
        this->horizontalPadding = this->verticalPadding = padding;
    default: break;
    }
    setSize(field.getSize());
}

void ProgressBar::setPosition(sf::Vector2f position)
{
    this->field.setPosition(position);
    this->bar.setPosition(position.x + horizontalPadding, position.y + verticalPadding);
    this->progressText.setPosition(position.x + field.getSize().x - progressText.getGlobalBounds().width,
                                   position.y - 1.5 * progressText.getGlobalBounds().height - getBorderWeight());
}

void ProgressBar::setCenterPosition(sf::Vector2f position)
{
    setPosition(sf::Vector2f(position.x - field.getSize().x / 2,
                             position.y - field.getSize().y / 2));
}

void ProgressBar::setTextColor(sf::Color color) { this->progressText.setFillColor(color); }

void ProgressBar::setFieldColor(sf::Color color) { this->field.setFillColor(color); }

void ProgressBar::setBorderColor(sf::Color color) { this->field.setOutlineColor(color); }

void ProgressBar::setBarColor(sf::Color color) { this->bar.setFillColor(color); }

void ProgressBar::updateText()
{
    std::stringstream sx;
    sx << static_cast<unsigned>(progress);

    progressText.setString("Выполнено: " + sx.str() + "%");

    this->progressText.setPosition(field.getPosition().x + field.getSize().x - progressText.getGlobalBounds().width,
                                   progressText.getPosition().y);
}
