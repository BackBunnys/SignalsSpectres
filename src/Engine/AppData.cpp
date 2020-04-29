#include "Engine/AppData.h"

AppData::AppData(sf::VideoMode VMode)
{
    initAssets();

    initWindow(VMode);

    initMachine();
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

sf::Vector2i AppData::getMouseDelta(sf::Vector2i MousePos)
{
    sf::Vector2i Delta = MousePos - this->mousePosition;
    this->mousePosition = MousePos;
    return Delta;
}

sf::Vector2f AppData::getMouseDelta(sf::Vector2f MousePos)
{
    sf::Vector2f Delta = MousePos - this->f_mousePosition;
    this->f_mousePosition = MousePos;
    return Delta;
}
