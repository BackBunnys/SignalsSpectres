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

        const std::string& getFilePath() const { return this->filePath; };
        int32_t getSignalSize() { return this->signalSize; }
        int32_t getFFTSize() { return this->fftSize; }

        StateMachine* const GetMachine() const { return machine; }
        AssetManager* const GetAssets() const { return assets; }
        sf::RenderWindow* const GetWindow() const { return window; }

        template <typename T>
        sf::Vector2<T> getMouseDelta(sf::Vector2<T> mousePos);

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
