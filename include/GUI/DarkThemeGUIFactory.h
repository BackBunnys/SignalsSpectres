#ifndef DARKTHEMEGUIFACTORY_H
#define DARKTHEMEGUIFACTORY_H

#include "SFML/Graphics.hpp"
#include "Engine/AppData.h"
#include "GUI/Button.h"
#include "GUI/InputBox.h"
#include "GUI/ListElement.h"
#include "GUI/ProgressBar.h"

class DarkThemeGUIFactory
{
    public:
        DarkThemeGUIFactory(AppData &appData);
        virtual ~DarkThemeGUIFactory();

        Button* getButton(std::string text, void (*action)(AppData&), sf::Vector2f position);
        InputBox* getInputBox(sf::Vector2u size, sf::Vector2f position);

        ProgressBar* getProgressBar(sf::Vector2f position);

        sf::Text* getText(std::string str, int charSize);

        template <typename T>
        ListElement<T>* getListElement(std::string text, T data)
        {
            ListElement<T>* el = new ListElement<T>(sf::Text(text, this->appData.GetAssets()->getFont("Baltica Plain.001.001.ttf")),
                                                    data, this->appData);
            el->setTextColor(sf::Color::White, sf::Color(45, 45, 45));
            el->setFieldColor(sf::Color(100, 100, 100), sf::Color(200, 200, 200));
            el->setSize(sf::Vector2f(300, 50));
            el->setFieldSelectedColor(sf::Color::White);
            el->setTextSelectedColor(sf::Color(45, 45, 45));
            el->setBorder(2, sf::Color(45, 45, 45));
            el->setActiveBorderColor(sf::Color(150, 150, 150));

            return el;
        }

    protected:
        AppData &appData;
};

#endif // DARKTHEMEGUIFACTORY_H
