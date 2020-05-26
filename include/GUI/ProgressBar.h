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
        ProgressBar();

        void update();
        void draw(sf::RenderWindow &window);

        void addProgress(float percent);
        void setProgress(float persent);
        void associateWithSource(const IProgressive* source);

        void setSize(sf::Vector2f size);
        void setBorder(float weight);
        void setPadding(float padding, PaddingType type);
        void setPosition(sf::Vector2f position);
        void setCenterPosition(sf::Vector2f position);

        void setFieldColor(sf::Color color);
        void setBorderColor(sf::Color color);
        void setBarColor(sf::Color color);

        const IProgressive* getAssociatedSource() const { return this->associatedSource; }

        const sf::Vector2f& getSize() const { return this->field.getSize(); }
        float getBorderWeight() const { return this->field.getOutlineThickness(); }
        float getHorizontalPadding() const { return this->horizontalPadding; }
        float getVerticalPadding() const { return this->verticalPadding; }

        const sf::Vector2f& getPosition() const { return this->field.getPosition(); }

        const sf::Color& getFieldColor() const { return this->field.getFillColor(); }
        const sf::Color& getBorderColor() const { return this->field.getOutlineColor(); }
        const sf::Color& getBarColor() const { return this->bar.getFillColor(); }

        virtual ~ProgressBar();

    private:
        const IProgressive* associatedSource;

        sf::RectangleShape field;
        sf::RectangleShape bar;

        float horizontalPadding,
              verticalPadding;
        float barWidth;

        float progress;
};

#endif // PROGRESSBAR_H
