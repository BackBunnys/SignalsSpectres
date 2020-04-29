#include "States/InputState.h"
#include <iostream>
#include <windows.h>

InputState::InputState(AppData &appData): State(appData)
{
    this->Init();
    this->inputBox = new InputBox(this->appData.GetAssets()->getFont("a SignboardCpsNr BoldItalic.ttf"),
                                  sf::Vector2u(800, 50), 2, 30,
                                  sf::Color(100, 100, 100), sf::Color(50, 50, 50),
                                  sf::Color::White, sf::Color(50, 50, 50));
    this->inputBox->setPosition(sf::Vector2f(this->appData.GetWindow()->getSize().x / 2,
                                             this->appData.GetWindow()->getSize().y / 2));
    this->inputBox->setHorizontalPadding(10);

    tip.setFont(this->appData.GetAssets()->getFont("Baltica Plain.001.001.ttf"));
    tip.setCharacterSize(30);
    tip.setString("¬ведите путь к файлу:");
    tip.setPosition(this->inputBox->getGlobalBounds().left, this->inputBox->getGlobalBounds().top - 1.5 * this->tip.getGlobalBounds().height);
}

InputState::~InputState()
{
    delete inputBox;
}

void InputState::Update()
{

}

void InputState::Render(sf::RenderWindow& window)
{
    window.clear(bgColor);

    window.draw(this->tip);
    this->inputBox->draw(window);
}

void InputState::Init()
{
    bgColor = sf::Color(100, 100, 100);
}

void InputState::ProccessEvent(sf::Event &event)
{
    if(event.type == sf::Event::TextEntered) {
        if(event.text.unicode >= 32)
            this->inputBox->addChar(event.text.unicode);
    }

    if(event.type == sf::Event::KeyPressed) {
        switch(event.key.code) {
            case sf::Keyboard::Left:
                this->inputBox->move(-1);
                break;

            case sf::Keyboard::Right:
                this->inputBox->move(1);

            case sf::Keyboard::A: //Ctrl + A combination
                if(event.key.control)
                    this->inputBox->selectAll();
                break;

            case sf::Keyboard::Backspace: //The Backspace button
                this->inputBox->removeChar();
                break;

            case sf::Keyboard::V: //Ctrl+V combination
                if(event.key.control)
                    this->inputBox->copyFromBuffer();    //Input from buffer
                break;

            case sf::Keyboard::Escape: //The Escape button
                this->appData.GetMachine()->Clear(); //Exit
                break;

            default:
                    break;
        }
    }
}
