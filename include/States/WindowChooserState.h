#ifndef WINDOWCHOOSERSTATE_H
#define WINDOWCHOOSERSTATE_H

#include "SFML/Graphics.hpp"
#include "Engine/State.h"
#include "GUI/Button.h"
#include "GUI/ChooseList.h"
#include "WindowFunction.h"

class WindowChooserState: public State
{
    public:
        WindowChooserState(AppData &appData);
        virtual ~WindowChooserState();

        virtual void Update();

        virtual void Render(sf::RenderWindow& window);

        virtual void Init();

        virtual void ProccessEvent(sf::Event &event);

    private:
        Button* backButton;             //TODO: CREATE THE GUI FACTORY
        Button* nextButton;
        ChooseList<WindowFunction>* clist;

        sf::Color bgColor;

        void initBackButton();
        void initNextButton();
        void initChooseList();
};

#endif // WINDOWCHOOSERSTATE_H
