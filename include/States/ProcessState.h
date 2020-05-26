#ifndef PROCESSSTATE_H
#define PROCESSSTATE_H

#include "Engine/State.h"
#include "GUI/DarkThemeGUIFactory.h"
#include "GUI/GUIHandler.h"

class ProcessState: public State
{
    public:
        ProcessState(AppData &appData);

        virtual ~ProcessState() override;

        virtual void Update();

        virtual void Render(sf::RenderWindow& window);

        virtual void Init();

        virtual void ProccessEvent(sf::Event &event);

        virtual void NextState();

    private:
        sf::Color bgColor;

        DarkThemeGUIFactory factory;
        GUIHandler guiHandler;

        void initGUI();
};


#endif // PROCESSSTATE_H
