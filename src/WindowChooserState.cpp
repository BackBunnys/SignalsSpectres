#include "WindowChooserState.h"

WindowChooserState::WindowChooserState(AppData &appData):
    State(appData)
{

}

WindowChooserState::~WindowChooserState()
{
    //dtor
}

void WindowChooserState::Init()
{
    bgColor = sf::Color(100, 100, 100);

    initBackButton();
    initNextButton();
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

void WindowChooserState::Update()
{
    this->backButton->update();
    this->nextButton->update();
}

void WindowChooserState::Render(sf::RenderWindow& window)
{
    window.clear(bgColor);
    this->backButton->draw(window);
    this->nextButton->draw(window);
}


void WindowChooserState::ProccessEvent(sf::Event &event)
{
    if(event.type == sf::Event::MouseButtonReleased)
        if(this->backButton->isMouseOn(sf::Vector2i(event.mouseButton.x, event.mouseButton.y)))
            this->backButton->runAction();
        else if(this->nextButton->isMouseOn(sf::Vector2i(event.mouseButton.x, event.mouseButton.y)))
            this->nextButton->runAction();

    if(event.type == sf::Event::KeyPressed) {
        switch(event.key.code) {
            case sf::Keyboard::Escape:
                this->appData.GetMachine()->PopState();
                break;
            case sf::Keyboard::Enter:
                this->nextButton->runAction();
                break;
            default:
                break;
        }
    }


}
