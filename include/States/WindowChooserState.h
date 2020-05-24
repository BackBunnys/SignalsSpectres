#ifndef WINDOWCHOOSERSTATE_H
#define WINDOWCHOOSERSTATE_H

#include "SFML/Graphics.hpp"
#include "Engine/State.h"
#include "GUI/Button.h"
#include "GUI/ChooseList.h"
#include "WindowFunction.h"
#include "GUI/InputBox.h"
#include "GUI/DarkThemeGUIFactory.h"
#include "GUIHandler.h"
#include "ValidationHandler.h"

class WindowChooserState: public State
{
    public:
        WindowChooserState(AppData &appData);

        virtual ~WindowChooserState() override;

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

#endif // WINDOWCHOOSERSTATE_H
