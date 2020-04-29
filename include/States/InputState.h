#ifndef INPUTSTATE_H
#define INPUTSTATE_H

#include "Engine/State.h"
#include "GUI/InputBox.h"

class InputState : public State
{
    public:
        InputState(AppData &appData);
        virtual ~InputState();

        virtual void Update();

        virtual void Render(sf::RenderWindow& window);

        virtual void Init();

        virtual void ProccessEvent(sf::Event &event);

    private:
        sf::Color bgColor;
        sf::Text tip;
        InputBox *inputBox;

        void fileNameFromBuffer();

        wchar_t* fileChoose();

};

#endif // INPUTSTATE_H
