#pragma once
#ifndef GAMEENGINE_H
#define GAMEENGINE_H

class StateMachine;

#include "SFML/Graphics.hpp"
#include "StateMachine.h"
#include "AssetManager.h"

class AppData
{
    public:
        AppData(sf::VideoMode VMode);
        ~AppData();

        void setFilePath(std::string filePath);
        void setSignalSize(int32_t signalSize) { this->signalSize = signalSize; }
        void setFFTSize(int32_t fftSize) { this->fftSize = fftSize; }

        StateMachine* const GetMachine() const { return machine; }
        AssetManager* const GetAssets() const { return assets; }
        sf::RenderWindow* const GetWindow() const { return window; }

        sf::Vector2i getMouseDelta(sf::Vector2i MousePos);
        sf::Vector2f getMouseDelta(sf::Vector2f MousePos);

    protected:

    private:

        StateMachine* machine;
        AssetManager* assets;
        sf::RenderWindow* window;

        sf::Vector2i mousePosition;
        sf::Vector2f f_mousePosition;
        std::string filePath;
        int32_t signalSize;
        int32_t fftSize;

        void initMachine();
        void initAssets();
        void initWindow(sf::VideoMode VMode);
};

#endif // GAMEENGINE_H
