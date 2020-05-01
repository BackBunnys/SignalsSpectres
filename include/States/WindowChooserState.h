#ifndef WINDOWCHOOSERSTATE_H
#define WINDOWCHOOSERSTATE_H

#include "SFML/Graphics.hpp"
#include "Engine/State.h"
#include "GUI/Button.h"
#include "GUI/ChooseList.h"
#include "WindowFunction.h"
#include "GUI/InputBox.h"

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
        InputBox* signalSize;
        InputBox* fftSize;
        sf::Text signalSizeTip;
        sf::Text fftSizeTip;
        ChooseList<WindowFunction>* clist;

        sf::Text errorMessage;
        sf::Color bgColor;


        void initBackButton();
        void initNextButton();
        void initChooseList();
        void initInputBoxes();
        void initTips();

        bool fullValidate();

        bool intValueValidate(const std::string &str, std::string fieldName);
};

#endif // WINDOWCHOOSERSTATE_H
