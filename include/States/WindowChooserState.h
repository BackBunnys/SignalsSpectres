#ifndef WINDOWCHOOSERSTATE_H
#define WINDOWCHOOSERSTATE_H

#include "SFML/Graphics.hpp"
#include "Engine/State.h"
#include "GUI/Button.h"
#include "GUI/ChooseList.h"
#include "WindowFunction.h"
#include "GUI/InputBox.h"
#include "GUI/DarkThemeGUIFactory.h"
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

    private:
        Button* backButton;
        Button* nextButton;
        InputBox* signalSize;
        InputBox* fftSize;
        ChooseList<WindowFunction>* clist;
        sf::Text signalSizeTip;
        sf::Text fftSizeTip;

        sf::Color bgColor;

        DarkThemeGUIFactory factory;
        ValidationHandler<long long>* errorHandler;

        void initButtons();
        void initChooseList();
        void initInputBoxes();
        void initTips();
};

#endif // WINDOWCHOOSERSTATE_H
