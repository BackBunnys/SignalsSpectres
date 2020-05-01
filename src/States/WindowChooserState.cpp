#include "States/WindowChooserState.h"
#include "cmath"
#include <sstream>

WindowChooserState::WindowChooserState(AppData &appData):
    State(appData)
{

}

WindowChooserState::~WindowChooserState()
{
    delete this->backButton;
    delete this->nextButton;
    delete this->signalSize;
    delete this->fftSize;
    delete this->clist;
}

void WindowChooserState::Init()
{
    bgColor = sf::Color(100, 100, 100);

    initBackButton();
    initNextButton();
    initChooseList();
    initInputBoxes();
    initTips();
    this->errorMessage.setFont(this->appData.GetAssets()->getFont("Baltica Plain.001.001.ttf"));
    this->errorMessage.setFillColor(sf::Color::Red);
    this->errorMessage.setString("");
}

void WindowChooserState::initBackButton()
{
    this->backButton = new Button(sf::Text("Назад", this->appData.GetAssets()->getFont("Baltica Plain.001.001.ttf")),
                                  [](AppData &appData){appData.GetMachine()->PopState();}, this->appData);
    this->backButton->setBorder(2, sf::Color(50, 50, 50));
    this->backButton->setTextColor(sf::Color::White, sf::Color(45, 45, 45));
    this->backButton->setFieldColor(sf::Color(100, 100, 100), sf::Color(200, 200, 200));
    this->backButton->setSize(sf::Vector2f(200, 50));
    this->backButton->setCenterPosition(sf::Vector2f(this->appData.GetWindow()->getSize().x / 5,
                                                     this->appData.GetWindow()->getSize().y / 5 * 4));
}

void WindowChooserState::initNextButton()
{
    this->nextButton = new Button(sf::Text("Далее", this->appData.GetAssets()->getFont("Baltica Plain.001.001.ttf")),
                                  [](AppData &appData){;}, this->appData);
    this->nextButton->setBorder(2, sf::Color(50, 50, 50));
    this->nextButton->setTextColor(sf::Color::White, sf::Color(45, 45, 45));
    this->nextButton->setFieldColor(sf::Color(100, 100, 100), sf::Color(200, 200, 200));
    this->nextButton->setSize(sf::Vector2f(200, 50));
    this->nextButton->setCenterPosition(sf::Vector2f(this->appData.GetWindow()->getSize().x / 5 * 4,
                                                     this->appData.GetWindow()->getSize().y / 5 * 4));
}

void WindowChooserState::initChooseList()
{
    this->clist = new ChooseList<WindowFunction>(1);
    this->clist->setBorder(2, sf::Color(50, 50, 50));

    ListElement<WindowFunction> el(ListElement<WindowFunction>(sf::Text("Окно Ханна", this->appData.GetAssets()->getFont("Baltica Plain.001.001.ttf")),
                WindowFunction("Hann window", [](uint32_t n, uint32_t N)->double{ return 0.5 * (1 - cos(2 * M_PI * n / (N - 1))); }), &this->appData));
    el.setTextColor(sf::Color::White, sf::Color(45, 45, 45));
    el.setFieldColor(sf::Color(100, 100, 100), sf::Color(200, 200, 200));
    el.setSize(sf::Vector2f(300, 50));
    this->clist->addElement(el);
    el = ListElement<WindowFunction>(ListElement<WindowFunction>(sf::Text("Окно Хэмминга", this->appData.GetAssets()->getFont("Baltica Plain.001.001.ttf")),
                     WindowFunction("Hemming window", [](uint32_t n, uint32_t N)->double{ return 0.53836 - 0.46164 * cos(2 * M_PI * n / (N - 1)); }), &this->appData));
    el.setTextColor(sf::Color::White, sf::Color(45, 45, 45));
    el.setFieldColor(sf::Color(100, 100, 100), sf::Color(200, 200, 200));
    this->clist->addElement(el);
    el = ListElement<WindowFunction>(ListElement<WindowFunction>(sf::Text("Синус окно", this->appData.GetAssets()->getFont("Baltica Plain.001.001.ttf")),
                     WindowFunction("Sinus window", [](uint32_t n, uint32_t N)->double{ return sin(M_PI * n / (N - 1)); }), &this->appData));
    el.setTextColor(sf::Color::White, sf::Color(45, 45, 45));
    el.setFieldColor(sf::Color(100, 100, 100), sf::Color(200, 200, 200));
    this->clist->addElement(el);
    el = ListElement<WindowFunction>(ListElement<WindowFunction>(sf::Text("Окно Ланцоша", this->appData.GetAssets()->getFont("Baltica Plain.001.001.ttf")),
                     WindowFunction("Lanczos window", [](uint32_t n, uint32_t N)->double{ return sin(M_PI * (2 * n / (N - 1) - 1)) / M_PI * (2 * n / (N - 1) - 1); }), &this->appData));
    el.setTextColor(sf::Color::White, sf::Color(45, 45, 45));
    el.setFieldColor(sf::Color(100, 100, 100), sf::Color(200, 200, 200));
    this->clist->addElement(el);
    el = ListElement<WindowFunction>(ListElement<WindowFunction>(sf::Text("Треугольное окно", this->appData.GetAssets()->getFont("Baltica Plain.001.001.ttf")),
                     WindowFunction("Barlett window", [](uint32_t n, uint32_t N)->double{ return 1 - abs(n / ((N - 1) / 2) - 1) ; }), &this->appData));
    el.setTextColor(sf::Color::White, sf::Color(45, 45, 45));
    el.setFieldColor(sf::Color(100, 100, 100), sf::Color(200, 200, 200));
    this->clist->addElement(el);
    this->clist->setCenterPosition(sf::Vector2f(this->appData.GetWindow()->getSize().x / 3, this->appData.GetWindow()->getSize().y / 3));
}

void WindowChooserState::initInputBoxes()
{
    this->signalSize = new InputBox(this->appData.GetAssets()->getFont("a SignboardCpsNr BoldItalic.ttf"),
                                  sf::Vector2u(100, 50), 2, 30,
                                  sf::Color(100, 100, 100), sf::Color(50, 50, 50),
                                  sf::Color::White, sf::Color(50, 50, 50));
    this->signalSize->setPosition(sf::Vector2f(this->appData.GetWindow()->getSize().x / 4 * 3,
                                               this->appData.GetWindow()->getSize().y / 8 * 2));
    this->signalSize->setHorizontalPadding(10);
    this->fftSize = new InputBox(this->appData.GetAssets()->getFont("a SignboardCpsNr BoldItalic.ttf"),
                                  sf::Vector2u(100, 50), 2, 30,
                                  sf::Color(100, 100, 100), sf::Color(50, 50, 50),
                                  sf::Color::White, sf::Color(50, 50, 50));
    this->fftSize->setPosition(sf::Vector2f(this->appData.GetWindow()->getSize().x / 4 * 3,
                                            this->appData.GetWindow()->getSize().y / 8 * 4));
    this->fftSize->setHorizontalPadding(10);
    this->signalSize->activate();
}

void WindowChooserState::initTips()
{
    this->signalSizeTip.setFont(this->appData.GetAssets()->getFont("Baltica Plain.001.001.ttf"));
    this->signalSizeTip.setCharacterSize(30);
    this->signalSizeTip.setString("Длина сигнала");
    this->signalSizeTip.setPosition(this->signalSize->getGlobalBounds().left, this->signalSize->getGlobalBounds().top - 1.5 * this->signalSizeTip.getGlobalBounds().height);

    this->fftSizeTip.setFont(this->appData.GetAssets()->getFont("Baltica Plain.001.001.ttf"));
    this->fftSizeTip.setCharacterSize(30);
    this->fftSizeTip.setString("Длина БПФ");
    this->fftSizeTip.setPosition(this->fftSize->getGlobalBounds().left, this->fftSize->getGlobalBounds().top - 1.5 * this->fftSizeTip.getGlobalBounds().height);
}

void WindowChooserState::Update()
{
    this->backButton->update();
    this->nextButton->update();
    this->clist->update();
}

void WindowChooserState::Render(sf::RenderWindow& window)
{
    window.clear(bgColor);
    this->backButton->draw(window);
    this->nextButton->draw(window);
    this->signalSize->draw(window);
    this->fftSize->draw(window);
    window.draw(this->signalSizeTip);
    window.draw(this->fftSizeTip);
    this->clist->draw(window);
    window.draw(this->errorMessage);
}

void WindowChooserState::ProccessEvent(sf::Event &event)
{
    if(event.type == sf::Event::MouseButtonReleased)
        if(this->backButton->isMouseOn(sf::Vector2i(event.mouseButton.x, event.mouseButton.y)))
            this->backButton->runAction();
        else if(this->nextButton->isMouseOn(sf::Vector2i(event.mouseButton.x, event.mouseButton.y))) {
            if(fullValidate())
                this->nextButton->runAction();
        }
        else if(this->clist->isMouseOn(sf::Vector2i(event.mouseButton.x, event.mouseButton.y)))
            this->clist->changeSelection(sf::Vector2i(event.mouseButton.x, event.mouseButton.y));
        else if(this->signalSize->isMouseOn(sf::Vector2i(event.mouseButton.x, event.mouseButton.y)))
        {
            this->signalSize->activate();
            this->fftSize->deactivate();
        }
        else if(this->fftSize->isMouseOn(sf::Vector2i(event.mouseButton.x, event.mouseButton.y)))
        {
            this->signalSize->deactivate();
            this->fftSize->activate();
        }

    if(event.type == sf::Event::TextEntered) {
        if(event.text.unicode >= 32)
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
                if(fullValidate())
                    this->nextButton->runAction();
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
    }
}

bool WindowChooserState::fullValidate()
{
    this->errorMessage.setString("");
    return intValueValidate(this->signalSize->getInputtedText(), "Длина сигнала") &
           intValueValidate(this->fftSize->getInputtedText(), "Размер БФП");
}

bool WindowChooserState::intValueValidate(const std::string &str, std::string fieldName)
{
    std::stringstream ss;
    ss << str;
    int n;
    ss >> n;
    if(n == 0)
    {
        this->errorMessage.setString(this->errorMessage.getString() + "\nОшибка: некорректное значение в поле " + fieldName + "!");
        this->errorMessage.setPosition(this->appData.GetWindow()->getSize().x / 2 - this->errorMessage.getGlobalBounds().width / 2,
                                       this->appData.GetWindow()->getSize().y / 5 * 3 - this->errorMessage.getGlobalBounds().height / 2);
        return false;
    }
    return true;
}
