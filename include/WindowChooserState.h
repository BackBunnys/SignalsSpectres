#ifndef WINDOWCHOOSERSTATE_H
#define WINDOWCHOOSERSTATE_H

#include "SFML/Graphics.hpp"
#include "Engine/State.h"
#include "GUI/Button.h"

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

        void initBackButton();
        void initNextButton();
};

#endif // WINDOWCHOOSERSTATE_H
