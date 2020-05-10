#ifndef VALIDATOR_H
#define VALIDATOR_H

#include "IValidator.h"

template <typename T>
class Validator: public IValidator<T>
{
    public:
        Validator(T& validatingField) { setValidatingField(validatingField); }

        virtual ~Validator();

        virtual bool validate(std::string &errorString) = 0;

        virtual T& getValidatingField() { return this->validatingField; }

        virtual T& setValidatingField(T& field) { this->validatingField = validatingField; }

    protected:
        T& validatingField;
};

#endif // VALIDATOR_H
