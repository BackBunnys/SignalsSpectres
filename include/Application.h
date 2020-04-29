#pragma once
#ifndef APPLICATION_H
#define APPLICATION_H

#include "Engine/AppData.h"
#include <SFML/Graphics.hpp>

class Application
{
    public:
        Application(sf::VideoMode VMode);

        ~Application();

        void Run();

    private:
        sf::RenderWindow* window;
        sf::Event EventSFML;

        AppData Engine;

        void update();

        void render();

        void updateSFMLEvents();
};

#endif // GAME_H
