#include "Application.h"
#include "InputState.h"

Application::Application(sf::VideoMode VMode):
    Engine(VMode)
{
    this->Engine.GetMachine()->PushState(new InputState(this->Engine));
}

Application::~Application()
{

}

void Application::updateSFMLEvents()
{
    while(this->Engine.GetWindow()->pollEvent(this->EventSFML)) {
        if(EventSFML.type == sf::Event::Closed)
            this->Engine.GetWindow()->close();
        else
            if(!this->Engine.GetMachine()->isEmpty())
                this->Engine.GetMachine()->getCurrentState()->ProccessEvent(EventSFML);
    }
}

void Application::update()
{
    updateSFMLEvents();

    if(!this->Engine.GetMachine()->isEmpty())
        this->Engine.GetMachine()->getCurrentState()->Update();
}

void Application::render()
{
    if(this->Engine.GetWindow()->isOpen()) {
        this->Engine.GetWindow()->clear(sf::Color::White);

        if(!this->Engine.GetMachine()->isEmpty())
            this->Engine.GetMachine()->getCurrentState()->Render(*this->Engine.GetWindow());

        this->Engine.GetWindow()->display();
    }
}

void Application::Run()
{
    while(!this->Engine.GetMachine()->isEmpty()) {
        update();
        render();
    }
}


