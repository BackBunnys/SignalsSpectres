#include "ProgressBar.h"

ProgressBar::ProgressBar()
{
    setProgress(0);
    setPosition(sf::Vector2f(0, 0));
    setSize(sf::Vector2f(400, 50));
    setPadding(4, Both);
    setBorder(4);

    setFieldColor(sf::Color::White);
    setBorderColor(sf::Color::Black);
    setBarColor(sf::Color::Green);

    associateWithSource(NULL);
    setPollPauseTime(sf::Time(sf::milliseconds(50)));
}

ProgressBar::~ProgressBar()
{
    //dtor
}

void ProgressBar::update()
{
    if(associatedSource)
        if(timer.getElapsedTime() >= pollPauseTime) {
            timer.restart();
            setProgress(associatedSource->getProgress());
    }
}

void ProgressBar::draw(sf::RenderWindow &window)
{
    window.draw(this->field);
    window.draw(this->bar);
}

void ProgressBar::addProgress(float percent)
{
    setProgress(this->progress + percent);
}

void ProgressBar::setProgress(float persent)
{
    if(persent < 0)
        persent = 0;
    else if(persent > 100)
        persent = 100;
    this->progress = persent;

    this->bar.setSize(sf::Vector2f(barWidth * progress / 100, bar.getSize().y));
}

void ProgressBar::associateWithSource(const IProgressive* source)
{
    this->associatedSource = source;
}

void ProgressBar::setPollPauseTime(sf::Time time)
{
    this->pollPauseTime = time;
}

void ProgressBar::setSize(sf::Vector2f size)
{
    this->field.setSize(size);
    this->barWidth = size.x - 2 * horizontalPadding;
    this->bar.setSize(sf::Vector2f(barWidth, size.y - 2 * verticalPadding));
    setProgress(this->progress);
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
}

void ProgressBar::setCenterPosition(sf::Vector2f position)
{
    setPosition(sf::Vector2f(position.x - field.getSize().x / 2,
                             position.y - field.getSize().y / 2));
}

void ProgressBar::setFieldColor(sf::Color color) { this->field.setFillColor(color); }

void ProgressBar::setBorderColor(sf::Color color) { this->field.setOutlineColor(color); }

void ProgressBar::setBarColor(sf::Color color) { this->bar.setFillColor(color); }
