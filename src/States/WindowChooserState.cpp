#include "States/WindowChooserState.h"
#include "cmath"
#include <string>

#include "InRangeValueValidator.h"
#include "ConvertingDataWrapper.h"
#include "ConstantDataWrapper.h"
#include "AccessingDataWrapper.h"
#include "IsPowerOfValidator.h"

WindowChooserState::WindowChooserState(AppData &appData):
    State(appData), factory(appData) { }

WindowChooserState::~WindowChooserState() { }

void WindowChooserState::Init()
{
    bgColor = sf::Color(100, 100, 100);

    initGUI();
    initValidationHandler();
}

void WindowChooserState::initGUI()
{
    //////////////BUTTONS///////////////
    Button* backButton = factory.getButton("Назад", [](AppData &appData){ appData.GetMachine()->PopState(); },
                                           sf::Vector2f(this->appData.GetWindow()->getSize().x / 5, this->appData.GetWindow()->getSize().y / 5 * 4));
    Button* nextButton = factory.getButton("Далее", [](AppData &appData){ appData.GetMachine()->getCurrentState()->NextState(); },
                                           sf::Vector2f(this->appData.GetWindow()->getSize().x / 5 * 4, this->appData.GetWindow()->getSize().y / 5 * 4));
    ////////////INPUTBOXES//////////////
    InputBox* signalSize = factory.getInputBox(sf::Vector2u(220, 50), sf::Vector2f(this->appData.GetWindow()->getSize().x / 4 * 3,
                                                                                   this->appData.GetWindow()->getSize().y / 8 * 2));
    signalSize->setInputtedCharLimits(48, 57);
    InputBox* fftSize = factory.getInputBox(sf::Vector2u(220, 50), sf::Vector2f(this->appData.GetWindow()->getSize().x / 4 * 3,
                                                                                this->appData.GetWindow()->getSize().y / 8 * 4));
    fftSize->setInputtedCharLimits(48, 57);
    ////////////CHOOSELIST//////////////
    ChooseList<WindowFunction>* clist = new ChooseList<WindowFunction>(1);
    clist->setBorder(2, sf::Color(50, 50, 50), sf::Color(150, 150, 150));

    clist->addElement(this->factory.getListElement("Окно Ханна",
                      WindowFunction("Hann window", [](uint32_t n, uint32_t N)->double{ return 0.5 * (1 - cos(2 * M_PI * n / (N - 1))); })));
    clist->addElement(this->factory.getListElement("Окно Хэмминга",
                      WindowFunction("Hemming window", [](uint32_t n, uint32_t N)->double{ return 0.53836 - 0.46164 * cos(2 * M_PI * n / (N - 1)); })));
    clist->addElement(this->factory.getListElement("Синус окно",
                      WindowFunction("Sinus window", [](uint32_t n, uint32_t N)->double{ return sin(M_PI * n / (N - 1)); })));
    clist->addElement(this->factory.getListElement("Окно Ланцоша",
                      WindowFunction("Lanczos window", [](uint32_t n, uint32_t N)->double{ return sin(M_PI * (2 * n / (N - 1) - 1)) / M_PI * (2 * n / (N - 1) - 1); })));
    clist->addElement(this->factory.getListElement("Треугольное окно",
                      WindowFunction("Barlett window", [](uint32_t n, uint32_t N)->double{ return 1 - abs(n / ((N - 1) / 2) - 1) ; })));
    clist->setCenterPosition(sf::Vector2f(this->appData.GetWindow()->getSize().x / 3, this->appData.GetWindow()->getSize().y / 3));
    /////////////LABELS///////////////
    sf::Text* signalSizeTip = this->factory.getText("Длина сигнала", 30);
    signalSizeTip->setPosition(signalSize->getGlobalBounds().left, signalSize->getGlobalBounds().top - 1.5 * signalSizeTip->getGlobalBounds().height);

    sf::Text* fftSizeTip = this->factory.getText("Длина БПФ", 30);
    fftSizeTip->setPosition(fftSize->getGlobalBounds().left, fftSize->getGlobalBounds().top - 1.5 * fftSizeTip->getGlobalBounds().height);
    //////////GUI BINDINGS////////////
    this->guiHandler.addInteractive("signalSize", signalSize);
    this->guiHandler.addInteractive("fftSize", fftSize);
    this->guiHandler.addInteractive("next", nextButton);
    this->guiHandler.addInteractive("back", backButton);
    this->guiHandler.addInteractive("choose", clist);

    this->guiHandler.addStatic(signalSizeTip);
    this->guiHandler.addStatic(fftSizeTip);
}

void WindowChooserState::initValidationHandler()
{
    sf::Text errorText("", appData.GetAssets()->getFont("Baltica Plain.001.001.ttf"), 20);
    errorText.setFillColor(sf::Color::Red);
    errorText.setPosition(this->appData.GetWindow()->getSize().x / 2 - errorText.getGlobalBounds().width / 2,
                          this->appData.GetWindow()->getSize().y / 8 * 5 - errorText.getGlobalBounds().height / 2);
    errorHandler.setText(errorText);
    errorHandler.addValidator(
        (new InRangeValueValidator<long long>( //Need to be rewrited to shared pointers
            new ConvertingDataWrapper<std::string, long long>(
                new AccessingDataWrapper<InputBox, std::string>(*static_cast<InputBox*>(guiHandler.getInteractiveElement("signalSize")),
                                                                &InputBox::getInputtedText, "значение поля \"Длина сигнала\""))))->addBorder(
        new Border<long long>(new ConstantDataWrapper<long long>(0), LEFT, true)));
    errorHandler.addValidator(
        (new InRangeValueValidator<long long>(
            new ConvertingDataWrapper<std::string, long long>(
                new AccessingDataWrapper<InputBox, std::string>(*static_cast<InputBox*>(guiHandler.getInteractiveElement("fftSize")),
                                                                &InputBox::getInputtedText, "значение поля \"Длина БПФ\""))))->addBorder(
        new Border<long long>(
            new ConvertingDataWrapper<std::string, long long>(
                new AccessingDataWrapper<InputBox, std::string>(*static_cast<InputBox*>(guiHandler.getInteractiveElement("signalSize")),
                                                                &InputBox::getInputtedText, "значение поля \"Длина сигнала\"")), LEFT)));
    errorHandler.addValidator(
        new IsPowerOfValidator(
            new ConvertingDataWrapper<std::string, long long>(
                new AccessingDataWrapper<InputBox, std::string>(*static_cast<InputBox*>(guiHandler.getInteractiveElement("fftSize")),
                                                                &InputBox::getInputtedText, "значение поля \"Длина БПФ\"")),
            new ConstantDataWrapper<long long>(2)));
}

void WindowChooserState::Update()
{
    this->guiHandler.update();
}

void WindowChooserState::Render(sf::RenderWindow& window)
{
    window.clear(bgColor);

    this->guiHandler.draw(window);
    this->errorHandler.draw(window);
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
}

void WindowChooserState::NextState()
{
    if(this->errorHandler.fullValidate()) {
        this->appData.setSignalSize(std::atoi((static_cast<InputBox*>(guiHandler.getInteractiveElement("signalSize")))->getInputtedText().data()));
        this->appData.setFFTSize(std::atoi((static_cast<InputBox*>(guiHandler.getInteractiveElement("fftSize")))->getInputtedText().data()));

        //Push next state
    }
}
