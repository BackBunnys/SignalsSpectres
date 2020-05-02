#ifndef WINDOWCHOOSERSTATE_H
#define WINDOWCHOOSERSTATE_H

#include "SFML/Graphics.hpp"
#include "Engine/State.h"
#include "GUI/Button.h"
#include "GUI/ChooseList.h"
#include "WindowFunction.h"
#include "GUI/InputBox.h"
#include "GUI/DarkThemeGUIFactory.h"

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

        sf::Text errorMessage;
        sf::Color bgColor;

        DarkThemeGUIFactory factory;

        void initButtons();
        void initChooseList();
        void initInputBoxes();
        void initTips();

        void appendErrors(const std::string error);

        bool fullValidate();

        bool notZeroValueValidate(const std::string &str, std::string fieldName);

        bool fftSizeValidate();

        int parseToInt(const std::string &str);
};

#endif // WINDOWCHOOSERSTATE_H
