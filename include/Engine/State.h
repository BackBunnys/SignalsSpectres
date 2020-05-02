#pragma once
#ifndef STATE_H
#define STATE_H

class AppData;

#include <SFML/Graphics.hpp>
#include "AppData.h"

class State
{
    public:

        State(AppData &appData);

        virtual ~State();

        virtual void Update() = 0;

        virtual void Render(sf::RenderWindow& window) = 0;

        virtual void Init() = 0;

        virtual void ProccessEvent(sf::Event &event) = 0;

        virtual const std::string getDescription() const;

    protected:

        AppData &appData;
        std::string Description;
};

#endif // STATE_H
