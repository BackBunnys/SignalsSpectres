#ifndef VALIDATOR_H
#define VALIDATOR_H

#include "IValidator.h"

template <typename T>
class Validator: public IValidator<T>
{
    public:
        Validator(T& validatingField): validatingField(validatingField) { setErrorMessage("Неизвестная ошибка!"); }

        virtual ~Validator() {}

        virtual bool validate(std::string &errorString)
        {
            if(!condition()) errorString += errorMessage;
            else return true;

            return false;
        }

        virtual T& getValidatingField() { return this->validatingField; }

        virtual void setValidatingField(T& field) { this->validatingField = field; }

        std::string getErrorMessage() { return this->errorMessage; }
        void setErrorMessage(std::string message) { this->errorMessage = message;}

    protected:
        std::string errorMessage;
        T& validatingField;

        virtual bool condition() = 0;
};

#endif // VALIDATOR_H
