#include "Engine/AppData.h"

AppData::AppData(sf::VideoMode VMode)
{
    initAssets();

    initWindow(VMode);

    initMachine();

    this->filePath = "";
    this->signalSize = this->fftSize = -1;
}

AppData::~AppData()
{
    delete this->assets;

    delete this->machine;

    delete this->window;
}

void AppData::initMachine()
{
    this->machine = new StateMachine();
}

void AppData::initAssets()
{
    this->assets = new AssetManager();
}

void AppData::initWindow(sf::VideoMode VMode)
{
    this->window = new sf::RenderWindow(VMode, "SignalsSpectres");
    this->window->setFramerateLimit(60);
}

void AppData::setFilePath(std::string filePath)
{
    this->filePath = filePath;
}

template <typename T>
sf::Vector2<T> AppData::getMouseDelta(sf::Vector2<T> mousePos)
{
    sf::Vector2<T> delta = mousePos - this->mousePosition;
    this->mousePosition = mousePos;
    return delta;
}
