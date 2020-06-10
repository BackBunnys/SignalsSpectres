#include "States/ProcessState.h"

ProcessState::ProcessState(AppData &appData):
    State(appData), factory(appData), task(appData.getFilePath(), appData.getSignalSize()) { }

ProcessState::~ProcessState() { }


void ProcessState::Init()
{
    bgColor = sf::Color(100, 100, 100);

    initGUI();
}

void ProcessState::initGUI()
{
    ProgressBar* bar = this->factory.getProgressBar(sf::Vector2f(this->appData.GetWindow()->getSize().x / 2,
                                                                 this->appData.GetWindow()->getSize().y / 2));
    bar->associateWithSource(&task);
    guiHandler.addDynamic(bar);
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
    this->guiHandler.processEvent(event);
}

void ProcessState::NextState()
{
    //Push a state
}
