#ifndef VALIDATIONHANDLER_H
#define VALIDATIONHANDLER_H

#include <vector>

#include "SFML/Graphics.hpp"

#include "IValidator.h"

class ValidationHandler
{
    public:
        ValidationHandler() { }
        ValidationHandler(sf::Text errorText) { this->errorText = errorText; }

        virtual ~ValidationHandler()
        {
            for(size_t i = 0; i < validators.size(); ++i) delete validators[i];
        }

        void setText(sf::Text errorText) { this->errorText = errorText; }

        void draw(sf::RenderWindow &window)
        {
            window.draw(errorText);
        }

        void addValidator(IValidator* validator) { this->validators.push_back(validator); }

        bool fullValidate()
        {
            std::string errors = "";
            for(size_t i = 0; i < validators.size(); ++i)
                if(!validators[i]->validate(errors)) errors += "\n";
            if(errors.size() != 0)
                    errors.erase(errors.end() - 1);

            updateText(errors);

            return errors.size() == 0;
        }

    private:
        std::vector<IValidator*> validators;

        sf::Text errorText;

        void updateText(std::string &errors)
        {
            sf::Vector2f position(errorText.getPosition().x + errorText.getGlobalBounds().width / 2,
                                  errorText.getPosition().y + errorText.getGlobalBounds().height / 2);
            errorText.setString(errors);
            errorText.setPosition(position.x - errorText.getGlobalBounds().width / 2, position.y - errorText.getGlobalBounds().height / 2);
        }
};

#endif // VALIDATIONHANDLER_H
