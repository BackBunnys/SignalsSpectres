#ifndef PROGRESSBAR_H
#define PROGRESSBAR_H

#include "DynamicGUI.h"

class IProgressive
{
    public:
        virtual float getProgress() const = 0;
};

enum PaddingType { Horizontal, Vertical, Both};

class ProgressBar: public DynamicGUI
{
    public:
        ProgressBar(sf::Font &font, uint16_t charSize = 30);

        void update();
        void draw(sf::RenderWindow &window);

        void addProgress(float percent);
        void setProgress(float persent);
        void associateWithSource(const IProgressive* source);

        void setSize(sf::Vector2f size);
        void setTextSize(uint16_t charSize);
        void setBorder(float weight);
        void setPadding(float padding, PaddingType type);
        void setPosition(sf::Vector2f position);
        void setCenterPosition(sf::Vector2f position);

        void setTextColor(sf::Color color);
        void setFieldColor(sf::Color color);
        void setBorderColor(sf::Color color);
        void setBarColor(sf::Color color);

        const IProgressive* getAssociatedSource() const { return this->associatedSource; }

        const sf::Vector2f& getSize() const { return this->field.getSize(); }
        float getBorderWeight() const { return this->field.getOutlineThickness(); }
        float getHorizontalPadding() const { return this->horizontalPadding; }
        float getVerticalPadding() const { return this->verticalPadding; }

        const sf::Vector2f& getPosition() const { return this->field.getPosition(); }

        const sf::Color& getTextColor() const { return this->progressText.getFillColor(); }
        const sf::Color& getFieldColor() const { return this->field.getFillColor(); }
        const sf::Color& getBorderColor() const { return this->field.getOutlineColor(); }
        const sf::Color& getBarColor() const { return this->bar.getFillColor(); }

        virtual ~ProgressBar();

    private:
        const IProgressive* associatedSource;

        sf::Text progressText;
        sf::RectangleShape field;
        sf::RectangleShape bar;

        float horizontalPadding,
              verticalPadding;
        float barWidth;

        float progress;

        void updateText();
};

#endif // PROGRESSBAR_H
