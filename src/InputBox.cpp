#include "InputBox.h"
#include <string>
#include <iostream>

InputBox::InputBox(sf::Font &font,
                   sf::Vector2u fieldSize, unsigned borderSize, unsigned textSize,
                   sf::Color fieldColor, sf::Color borderColor, sf::Color textColor,
                   sf::Color delimiterColor)
{
    this->textColor = textColor;
    this->selectedMarker.setFillColor(sf::Color((fieldColor.r + 100) % 256,
                                                (fieldColor.g + 100) % 256,
                                                (fieldColor.b + 100) % 256));

    this->visibleText.setFont(font);
    this->visibleText.setCharacterSize(textSize);
    this->visibleText.setLetterSpacing(1);
    this->visibleText.setFillColor(textColor);

    this->field.setSize(sf::Vector2f(fieldSize.x, fieldSize.y));
    this->field.setFillColor(fieldColor);
    this->field.setOutlineThickness(borderSize);
    this->field.setOutlineColor(borderColor);

    this->isSelected = false;
    this->selectedTextColor = sf::Color((selectedMarker.getFillColor().r + 100) % 256,
                                        (selectedMarker.getFillColor().g + 100) % 256,
                                        (selectedMarker.getFillColor().b + 100) % 256);

    this->inputPtr.setSize(sf::Vector2f(2, textSize));
    this->inputPtr.setFillColor(delimiterColor);

    this->currentPosition = 0;
    this->leftVisibleCorner = 0;
    this->rightVisibleCorner = 0;
    this->inputtedText = L"";

    this->timer.restart();
    this->ptrTime = sf::seconds(1);

    this->setHorizontalPadding(4);
}

InputBox::~InputBox()
{
    //dtor
}

void InputBox::draw(sf::RenderWindow &window)
{
    window.draw(this->field);

    if(isSelected)
        window.draw(this->selectedMarker);

    window.draw(this->visibleText);

    if(this->timer.getElapsedTime() > this->ptrTime)
        timer.restart();
    else
        if(this->timer.getElapsedTime().asSeconds() > 0.5)
            window.draw(this->inputPtr);
}

void InputBox::addChar(uint32_t code)
{
    if(isSelected)
        removeChar();
    this->inputtedText.insert(currentPosition, 1, code);
    this->currentPosition++;
    this->rightVisibleCorner++;
    this->updateText();
}

void InputBox::removeChar()
{
    if(this->isSelected)
    {
        this->inputtedText.clear();
        this->currentPosition = 0;
        this->leftVisibleCorner = 0;
        this->rightVisibleCorner = 0;

        unselect();
        updateText();
    }
    else if(currentPosition != 0) {
        this->inputtedText.erase(inputtedText.begin() + currentPosition - 1);
        this->currentPosition--;
        if(this->leftVisibleCorner != 0)
            this->leftVisibleCorner--;

        this->updateText();
    }
}

void InputBox::selectAll()
{
    this->isSelected = true;
    this->visibleText.setFillColor(this->selectedTextColor);
    this->selectedMarker.setSize(sf::Vector2f(this->visibleText.getGlobalBounds().width, this->visibleText.getCharacterSize()));
}

void InputBox::unselect()
{
    this->isSelected = false;
    this->visibleText.setFillColor(this->textColor);
}

void InputBox::setPosition(sf::Vector2f position)
{
    this->field.setPosition(position.x - field.getSize().x / 2, position.y - field.getSize().y / 2);
    this->visibleText.setPosition(field.getPosition().x + field.getOutlineThickness() + horizontalPadding,
                                  field.getPosition().y + (field.getSize().y - visibleText.getCharacterSize()) / 2);
    this->selectedMarker.setPosition(visibleText.getPosition());

    updateText();
}

void InputBox::setHorizontalPadding(uint16_t px)
{
    this->horizontalPadding = px;

    setPosition(sf::Vector2f(field.getPosition().x + field.getSize().x / 2, field.getPosition().y + field.getSize().y / 2));
}

void InputBox::setSelectedTextColor(sf::Color color)
{
    this->selectedTextColor = color;
}

void InputBox::setSelectedFieldColor(sf::Color color)
{
    this->selectedMarker.setFillColor(color);
}

void InputBox::updateText()
{
    bool isMovedToLeft = false; //����� ��� "���������" �� ��������
    if(this->currentPosition < this->leftVisibleCorner) { //����� �� ���������� ��������� ����� ��� ������� �������
        isMovedToLeft = true;
        this->leftVisibleCorner = this->currentPosition; //������� ��������� �� �������, ������� �� �� ������
    }
    else if(this->currentPosition > this->rightVisibleCorner) //����� �� ��������� ������� ��� ���������� ��������� ������
        this->rightVisibleCorner = this->currentPosition; //������� ��������� �� �������, ������� �� �� ������

        std::wstring displayedString = inputtedText.substr(leftVisibleCorner, rightVisibleCorner - leftVisibleCorner);
        this->visibleText.setString(displayedString); //����� ���������� ��������, ������� �� ����� �������
        while(this->visibleText.getGlobalBounds().width + 2 * this->horizontalPadding >= this->field.getGlobalBounds().width - 2 * this->field.getOutlineThickness()) {
            if(isMovedToLeft) --rightVisibleCorner; //���������� ������ ����, ���� �� ����� �������
            else              ++leftVisibleCorner;  //���������� ����� ����, ���� �� ����� �������

            displayedString = inputtedText.substr(leftVisibleCorner, rightVisibleCorner - leftVisibleCorner);
            this->visibleText.setString(displayedString);
        }

    updatePtr();
}

void InputBox::updatePtr()
{
    this->inputPtr.setPosition(this->visibleText.findCharacterPos(currentPosition - leftVisibleCorner)); //������ ���������� ��������� � �������
}

void InputBox::move(int chars)
{
    if(this->isSelected) {
        unselect();
        if(chars > 0)
            this->currentPosition = this->inputtedText.size();
        else
            this->currentPosition = 0;
    }
    else {
        this->currentPosition += chars;
        if(this->currentPosition < 0)
            this->currentPosition = 0;
        if(this->currentPosition > this->inputtedText.size())
            this->currentPosition = this->inputtedText.size();
    }

    this->updateText();
}

sf::FloatRect InputBox::getGlobalBounds() const
{
    return this->field.getGlobalBounds();
}
