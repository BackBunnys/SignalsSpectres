#include "States/WindowChooserState.h"
#include "cmath"
#include <string>

#include "InRangeValueValidator.h"
#include "ConvertingDataWrapper.h"
#include "ConstantDataWrapper.h"
#include "AccessingDataWrapper.h"
#include "IsPowerOfValidator.h"

WindowChooserState::WindowChooserState(AppData &appData):
    State(appData), factory(appData)
{

}

WindowChooserState::~WindowChooserState()
{
    //delete this->backButton;
    //delete this->nextButton;
    //delete this->signalSize;
    //delete this->fftSize;
    //delete this->clist;
    delete this->errorHandler;
}

void WindowChooserState::Init()
{
    bgColor = sf::Color(100, 100, 100);

    initButtons();
    initChooseList();
    initInputBoxes();
    initTips();
    initValidationHandler();
    guiHandler.addInteractive(signalSize);
    guiHandler.addInteractive(fftSize);
    guiHandler.addInteractive(nextButton);
    guiHandler.addInteractive(backButton);
    guiHandler.addInteractive(clist);
    guiHandler.addStatic(&signalSizeTip);
    guiHandler.addStatic(&fftSizeTip);
}

void WindowChooserState::initButtons()
{
    this->backButton = factory.getButton("Назад", [](AppData &appData){ appData.GetMachine()->PopState(); },
                                         sf::Vector2f(this->appData.GetWindow()->getSize().x / 5, this->appData.GetWindow()->getSize().y / 5 * 4));
    this->nextButton = factory.getButton("Далее", [](AppData &appData){ appData.GetMachine()->getCurrentState()->NextState(); },
                                         sf::Vector2f(this->appData.GetWindow()->getSize().x / 5 * 4, this->appData.GetWindow()->getSize().y / 5 * 4));
}

void WindowChooserState::initChooseList()
{
    this->clist = new ChooseList<WindowFunction>(1);
    this->clist->setBorder(2, sf::Color(50, 50, 50));

    this->clist->addElement(this->factory.getListElement("Окно Ханна",
                            WindowFunction("Hann window", [](uint32_t n, uint32_t N)->double{ return 0.5 * (1 - cos(2 * M_PI * n / (N - 1))); })));
    this->clist->addElement(this->factory.getListElement("Окно Хэмминга",
                            WindowFunction("Hemming window", [](uint32_t n, uint32_t N)->double{ return 0.53836 - 0.46164 * cos(2 * M_PI * n / (N - 1)); })));
    this->clist->addElement(this->factory.getListElement("Синус окно",
                            WindowFunction("Sinus window", [](uint32_t n, uint32_t N)->double{ return sin(M_PI * n / (N - 1)); })));
    this->clist->addElement(this->factory.getListElement("Окно Ланцоша",
                            WindowFunction("Lanczos window", [](uint32_t n, uint32_t N)->double{ return sin(M_PI * (2 * n / (N - 1) - 1)) / M_PI * (2 * n / (N - 1) - 1); })));
    this->clist->addElement(this->factory.getListElement("Треугольное окно",
                            WindowFunction("Barlett window", [](uint32_t n, uint32_t N)->double{ return 1 - abs(n / ((N - 1) / 2) - 1) ; })));

    this->clist->setCenterPosition(sf::Vector2f(this->appData.GetWindow()->getSize().x / 3, this->appData.GetWindow()->getSize().y / 3));
}

void WindowChooserState::initInputBoxes()
{
    this->signalSize = factory.getInputBox(sf::Vector2u(220, 50), sf::Vector2f(this->appData.GetWindow()->getSize().x / 4 * 3,
                                                                               this->appData.GetWindow()->getSize().y / 8 * 2));
    this->fftSize = factory.getInputBox(sf::Vector2u(220, 50), sf::Vector2f(this->appData.GetWindow()->getSize().x / 4 * 3,
                                                                            this->appData.GetWindow()->getSize().y / 8 * 4));

    //this->signalSize->activate();
}

void WindowChooserState::initTips()
{
    this->signalSizeTip.setFont(this->appData.GetAssets()->getFont("Baltica Plain.001.001.ttf"));
    this->signalSizeTip.setCharacterSize(30);
    this->signalSizeTip.setString("Длина сигнала");
    this->signalSizeTip.setPosition(this->signalSize->getGlobalBounds().left, this->signalSize->getGlobalBounds().top - 1.5 * this->signalSizeTip.getGlobalBounds().height);

    this->fftSizeTip = this->signalSizeTip;
    this->fftSizeTip.setString("Длина БПФ");
    this->fftSizeTip.setPosition(this->fftSize->getGlobalBounds().left, this->fftSize->getGlobalBounds().top - 1.5 * this->fftSizeTip.getGlobalBounds().height);
}

void WindowChooserState::initValidationHandler()
{
    sf::Text errorText("", appData.GetAssets()->getFont("Baltica Plain.001.001.ttf"), 20);
    errorText.setFillColor(sf::Color::Red);
    errorText.setPosition(this->appData.GetWindow()->getSize().x / 2 - errorText.getGlobalBounds().width / 2,
                          this->appData.GetWindow()->getSize().y / 8 * 5 - errorText.getGlobalBounds().height / 2);
    errorHandler = new ValidationHandler(errorText);
    errorHandler->addValidator(
        (new InRangeValueValidator<long long>( //Need to be rewrited to shared pointers
            new ConvertingDataWrapper<std::string, long long>(
                new AccessingDataWrapper<InputBox, std::string>(*this->signalSize, &InputBox::getInputtedText, "значение поля \"Длина сигнала\""))))->addBorder(
        new Border<long long>(new ConstantDataWrapper<long long>(0), LEFT, true)));
    errorHandler->addValidator(
        (new InRangeValueValidator<long long>(
            new ConvertingDataWrapper<std::string, long long>(
                new AccessingDataWrapper<InputBox, std::string>(*this->fftSize, &InputBox::getInputtedText, "значение поля \"Длина БПФ\""))))->addBorder(
        new Border<long long>(
            new ConvertingDataWrapper<std::string, long long>(
                new AccessingDataWrapper<InputBox, std::string>(*this->signalSize, &InputBox::getInputtedText, "значение поля \"Длина сигнала\"")), LEFT)));
    errorHandler->addValidator(
        new IsPowerOfValidator(
            new ConvertingDataWrapper<std::string, long long>(
                new AccessingDataWrapper<InputBox, std::string>(*this->fftSize, &InputBox::getInputtedText, "значение поля \"Длина БПФ\"")),
            new ConstantDataWrapper<long long>(2)));
}

void WindowChooserState::Update()
{
    //this->backButton->update();
    //this->nextButton->update();
    //this->clist->update();
    //this->signalSize->update();
    //this->fftSize->update();
    this->guiHandler.update();
}

void WindowChooserState::Render(sf::RenderWindow& window)
{
    window.clear(bgColor);
    //this->backButton->draw(window);
    //this->nextButton->draw(window);
    //this->signalSize->draw(window);
    //this->fftSize->draw(window);
    //window.draw(this->signalSizeTip);
    //window.draw(this->fftSizeTip);
    //this->clist->draw(window);
    this->guiHandler.draw(window);
    this->errorHandler->draw(window);
}

void WindowChooserState::ProccessEvent(sf::Event &event)
{
    if(!this->guiHandler.processEvent(event))
        if(event.type == sf::Event::KeyPressed) {
            if(event.key.code == sf::Keyboard::Enter)
                NextState();
            else if(event.key.code == sf::Keyboard::Escape)
                this->appData.GetMachine()->PopState();
        }
    /*if(event.type == sf::Event::MouseButtonReleased)
        if(event.mouseButton.button == sf::Mouse::Left)
            if(this->backButton->isMouseOn(event.mouseButton.x, event.mouseButton.y))
                    this->backButton->runAction();
            else if(this->nextButton->isMouseOn(event.mouseButton.x, event.mouseButton.y)) {
                if(this->errorHandler->fullValidate()) {
                    this->appData.setSignalSize(std::atoi(this->signalSize->getInputtedText().data()));
                    this->appData.setFFTSize(std::atoi(this->fftSize->getInputtedText().data()));
                    this->nextButton->runAction();
                }
            }
            else if(this->clist->isMouseOn(event.mouseButton.x, event.mouseButton.y))
                this->clist->changeSelection(event.mouseButton.x, event.mouseButton.y);
            else if(this->signalSize->isMouseOn(event.mouseButton.x, event.mouseButton.y))
            {
                this->signalSize->activate();
                this->fftSize->deactivate();
            }
            else if(this->fftSize->isMouseOn(event.mouseButton.x, event.mouseButton.y))
            {
                this->signalSize->deactivate();
                this->fftSize->activate();
            }

    if(event.type == sf::Event::TextEntered) {
        if(event.text.unicode >= 48 && event.text.unicode <= 57) //if a digit was inputted
            if(this->signalSize->isActivated())
                this->signalSize->addChar(event.text.unicode);
            else if(this->fftSize->isActivated())
                this->fftSize->addChar(event.text.unicode);
    }

    if(event.type == sf::Event::KeyPressed) {
        switch(event.key.code) {
            case sf::Keyboard::Escape:
                this->backButton->runAction();
                break;
            case sf::Keyboard::Enter:
                if(this->errorHandler->fullValidate()) {
                    this->appData.setSignalSize(std::atoi(this->signalSize->getInputtedText().data()));
                    this->appData.setFFTSize(std::atoi(this->fftSize->getInputtedText().data()));
                    this->nextButton->runAction();
                }
                break;
            case sf::Keyboard::Left:
                if(this->signalSize->isActivated())
                    this->signalSize->move(-1);
                else if(this->fftSize->isActivated())
                    this->fftSize->move(-1);
                break;
            case sf::Keyboard::Right:
                if(this->signalSize->isActivated())
                    this->signalSize->move(1);
                else if(this->fftSize->isActivated())
                    this->fftSize->move(1);
                break;

            case sf::Keyboard::A: //Ctrl + A combination
                if(event.key.control)
                    if(this->signalSize->isActivated())
                        this->signalSize->selectAllText();
                    else if(this->fftSize->isActivated())
                        this->fftSize->selectAllText();
                break;

            case sf::Keyboard::Backspace: //The Backspace button
                if(this->signalSize->isActivated())
                    this->signalSize->removeChar();
                else if(this->fftSize->isActivated())
                    this->fftSize->removeChar();
                break;

            case sf::Keyboard::V: //Ctrl+V combination
                if(event.key.control)
                    if(this->signalSize->isActivated())
                        this->signalSize->copyFromBuffer();
                    else if(this->fftSize->isActivated())
                        this->fftSize->copyFromBuffer();    //Input from buffer
                break;

            case sf::Keyboard::Tab:
                if(event.key.shift) {
                    this->signalSize->activate();
                    this->fftSize->deactivate();
                }
                else {
                    this->signalSize->deactivate();
                    this->fftSize->activate();
                }
                break;

            default:
                break;
        }
    }*/
}

void WindowChooserState::NextState()
{
    if(this->errorHandler->fullValidate()) {
        this->appData.setSignalSize(std::atoi(this->signalSize->getInputtedText().data()));
        this->appData.setFFTSize(std::atoi(this->fftSize->getInputtedText().data()));

        //Push next state
    }
}
