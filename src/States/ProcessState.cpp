#include "ProcessState.h"

ProcessState::ProcessState(AppData &appData):
    State(appData), factory(appData) { }

ProcessState::~ProcessState() { }


void ProcessState::Init()
{
    bgColor = sf::Color(100, 100, 100);

    initGUI();
}

void ProcessState::initGUI()
{

}

void ProcessState::Update()
{
    this->guiHandler.update();
}

void ProcessState::Render(sf::RenderWindow& window)
{
    window.clear(bgColor);

    this->guiHandler.draw(window);
}

void ProcessState::ProccessEvent(sf::Event &event)
{

}

void ProcessState::NextState()
{

}
