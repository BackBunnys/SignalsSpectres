#ifndef DEFAULTINTERACTIVEELEMENT_H
#define DEFAULTINTERACTIVEELEMENT_H

#include "InteractiveGUIElement.h"
#include "Engine/AppData.h"

class DefaultInteractiveElement: public InteractiveGUIElement
{
    public:
        DefaultInteractiveElement(sf::Text text, AppData &appData);
        virtual ~DefaultInteractiveElement();

        virtual void update() override;
        virtual void draw(sf::RenderWindow &window) override;
        virtual bool processEvent(sf::Event &event) = 0;

        virtual void activate() override;
        virtual void deactivate() override;

        void setPosition(sf::Vector2f position);
        void setCenterPosition(sf::Vector2f centerPosition);
        void setSize(sf::Vector2f size);
        void setTextSize(unsigned textSize, unsigned onHoverSize);
        void setTextColor(sf::Color color, sf::Color onHoverColor);
        void setFieldColor(sf::Color color, sf::Color onHoverColor);
        void setBorder(uint16_t weight, sf::Color color);

        virtual bool isMouseOn(float xPos, float yPos) override;

        void onHoverTransform();
        void onUnHoverTransform();

    protected:
        sf::Text text;
        sf::RectangleShape field;
        sf::RectangleShape activeBorder;

        unsigned textSize, textHoverSize;
        sf::Color textColor, textHoverColor,
                  fieldColor, fieldHoverColor;

        bool isActive;

        AppData* appData;
};

#endif // DEFAULTINTERACTIVEELEMENT_H
