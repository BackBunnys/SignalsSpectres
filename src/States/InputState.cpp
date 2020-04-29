#include "States/InputState.h"
#include <iostream>
#include <windows.h>

InputState::InputState(AppData &appData): State(appData)
{
    this->Init();
}

InputState::~InputState()
{
    delete inputBox;
    delete nextButton;
}

void InputState::Update()
{

}

void InputState::Init()
{
    bgColor = sf::Color(100, 100, 100);

    initInputBox();
    initTip();
    initNextButton();
}

void InputState::initInputBox()
{
    this->inputBox = new InputBox(this->appData.GetAssets()->getFont("a SignboardCpsNr BoldItalic.ttf"),
                                  sf::Vector2u(800, 50), 2, 30,
                                  sf::Color(100, 100, 100), sf::Color(50, 50, 50),
                                  sf::Color::White, sf::Color(50, 50, 50));
    this->inputBox->setPosition(sf::Vector2f(this->appData.GetWindow()->getSize().x / 2,
                                             this->appData.GetWindow()->getSize().y / 2));
    this->inputBox->setHorizontalPadding(10);
}

void InputState::initTip()
{
    tip.setFont(this->appData.GetAssets()->getFont("Baltica Plain.001.001.ttf"));
    tip.setCharacterSize(30);
    tip.setString("Введите путь к файлу:");
    tip.setPosition(this->inputBox->getGlobalBounds().left, this->inputBox->getGlobalBounds().top - 1.5 * this->tip.getGlobalBounds().height);
}

void InputState::initNextButton()
{
    this->nextButton = new Button(sf::Text("Далее", this->appData.GetAssets()->getFont("Baltica Plain.001.001.ttf")),
                                  [](AppData &appData){std::cout << "HEllo";}, this->appData);
    this->nextButton->setBorder(2, sf::Color(50, 50, 50));
    this->nextButton->setFieldColor(sf::Color(100, 100, 100));
    this->nextButton->setSize(sf::Vector2f(200, 50));
    this->nextButton->setCenterPosition(sf::Vector2f(this->appData.GetWindow()->getSize().x / 2,
                                                     this->appData.GetWindow()->getSize().y / 5 * 4));
}

void InputState::Render(sf::RenderWindow& window)
{
    window.clear(bgColor);

    window.draw(this->tip);
    this->inputBox->draw(window);
    this->nextButton->draw(window);
}



void InputState::ProccessEvent(sf::Event &event)
{
    if(event.type == sf::Event::MouseButtonReleased)
        if(this->nextButton->isMouseOn(sf::Vector2f(event.mouseButton.x, event.mouseButton.y)))
            this->nextButton->runAction();
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
