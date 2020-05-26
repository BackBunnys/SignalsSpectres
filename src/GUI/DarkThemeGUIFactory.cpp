#include "GUI/DarkThemeGUIFactory.h"

DarkThemeGUIFactory::DarkThemeGUIFactory(AppData &appData): appData(appData)
{
    //ctor
}

DarkThemeGUIFactory::~DarkThemeGUIFactory()
{
    //dtor
}

Button* DarkThemeGUIFactory::getButton(std::string text, void (*action)(AppData&), sf::Vector2f position)
{
    Button* button = new Button(sf::Text(text, this->appData.GetAssets()->getFont("Baltica Plain.001.001.ttf")),
                                 action, this->appData);
    button->setBorder(2, sf::Color(50, 50, 50));
    button->setTextColor(sf::Color::White, sf::Color(45, 45, 45));
    button->setFieldColor(sf::Color(100, 100, 100), sf::Color(200, 200, 200));
    button->setSize(sf::Vector2f(200, 50));
    button->setCenterPosition(position);

    return button;
}

InputBox* DarkThemeGUIFactory::getInputBox(sf::Vector2u size, sf::Vector2f position)
{
    InputBox* box = new InputBox(this->appData.GetAssets()->getFont("a SignboardCpsNr BoldItalic.ttf"),
                                 size, 2, 30,
                                 sf::Color(100, 100, 100), sf::Color(50, 50, 50),
                                 sf::Color::White, sf::Color(50, 50, 50));
    box->setPosition(position);
    box->setHorizontalPadding(10);

    return box;
}

ProgressBar* DarkThemeGUIFactory::getProgressBar(sf::Vector2f position)
{
    ProgressBar* pBar = new ProgressBar();
    pBar->setFieldColor(sf::Color(45, 45, 45));
    pBar->setBarColor(sf::Color(200, 200, 200));
    pBar->setCenterPosition(position);

    return pBar;
}

sf::Text* DarkThemeGUIFactory::getText(std::string str, int charSize)
{
    sf::Text* text = new sf::Text();
    text->setFont(this->appData.GetAssets()->getFont("Baltica Plain.001.001.ttf"));
    text->setCharacterSize(charSize);
    text->setString(str);

    return text;
}
