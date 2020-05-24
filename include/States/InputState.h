#ifndef INPUTSTATE_H
#define INPUTSTATE_H

#include "Engine/State.h"
#include "GUI/InputBox.h"
#include "GUI/Button.h"
#include "GUI/DarkThemeGUIFactory.h"
#include "GUIHandler.h"
#include "ValidationHandler.h"

class InputState : public State
{
    public:
        InputState(AppData &appData);
        virtual ~InputState();

        virtual void Update();

        virtual void Render(sf::RenderWindow& window);

        virtual void Init();

        virtual void ProccessEvent(sf::Event &event);

        virtual void NextState();

    private:
        sf::Color bgColor;

        DarkThemeGUIFactory factory;
        ValidationHandler errorHandler;
        GUIHandler guiHandler;

        void initGUI();
        void initValidationHandler();
};

#endif // INPUTSTATE_H
