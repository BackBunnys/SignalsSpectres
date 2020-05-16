#include "States/InputState.h"
#include "States/WindowChooserState.h"

#include "FileExistingValidator.h"
#include "AccessingDataWrapper.h"

InputState::InputState(AppData &appData):
    State(appData), factory(appData)
{

}

InputState::~InputState()
{
    delete inputBox;
    delete nextButton;
    delete errorHandler;
}

void InputState::Update()
{
    this->nextButton->update();
}

void InputState::Init()
{
    bgColor = sf::Color(100, 100, 100);

    initInputBox();
    initTip();
    initNextButton();
    initValidationHandler();
}

void InputState::initInputBox()
{
    this->inputBox = factory.getInputBox(sf::Vector2u(800, 50), sf::Vector2f(this->appData.GetWindow()->getSize().x / 2,
                                                                             this->appData.GetWindow()->getSize().y / 2));
    this->inputBox->activate();
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
    this->nextButton = factory.getButton("Далее", [](AppData &appData){ appData.GetMachine()->getCurrentState()->NextState(); },
                                         sf::Vector2f(this->appData.GetWindow()->getSize().x / 5 * 4, this->appData.GetWindow()->getSize().y / 5 * 4));
}

void InputState::initValidationHandler()
{
    sf::Text errorText("", appData.GetAssets()->getFont("Baltica Plain.001.001.ttf"), 30);
    errorText.setFillColor(sf::Color::Red);
    errorText.setPosition(this->appData.GetWindow()->getSize().x / 2 - errorText.getGlobalBounds().width / 2,
                          this->appData.GetWindow()->getSize().y / 8 * 5 - errorText.getGlobalBounds().height / 2);
    errorHandler = new ValidationHandler(errorText);
    errorHandler->addValidator(
        new FileExistingValidator(
            new AccessingDataWrapper<InputBox, std::string>(*this->inputBox, &InputBox::getInputtedText, "путь к файлу")));
}

void InputState::Render(sf::RenderWindow& window)
{
    window.clear(bgColor);

    window.draw(this->tip);
    this->inputBox->draw(window);
    this->nextButton->draw(window);
    this->errorHandler->draw(window);
}

void InputState::ProccessEvent(sf::Event &event)
{
    if(event.type == sf::Event::MouseButtonReleased)
        if(event.mouseButton.button == sf::Mouse::Left)
            if(this->nextButton->isMouseOn(event.mouseButton.x, event.mouseButton.y))
                NextState();
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
                break;

            case sf::Keyboard::A: //Ctrl + A combination
                if(event.key.control)
                    this->inputBox->selectAllText();
                break;

            case sf::Keyboard::Backspace: //The Backspace button
                this->inputBox->removeChar();
                break;

            case sf::Keyboard::V: //Ctrl+V combination
                if(event.key.control)
                    this->inputBox->copyFromBuffer();    //Input from buffer
                break;

            case sf::Keyboard::Escape: //The Escape button
                this->appData.GetMachine()->PopState(); //Exit
                break;

            case sf::Keyboard::Enter:
                NextState();
                break;
            default:
                break;
        }
    }
}

void InputState::NextState()
{
    if(this->errorHandler->fullValidate()) {
        this->appData.setFilePath(this->inputBox->getInputtedText());

        this->appData.GetMachine()->PushState(new WindowChooserState(this->appData));
    }
}
