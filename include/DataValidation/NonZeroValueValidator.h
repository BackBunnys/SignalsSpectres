#ifndef NONZEROVALUEVALIDATOR_H
#define NONZEROVALUEVALIDATOR_H

#include "StringAsNumberValidator.h"

template <typename C, typename Number>
class NonZeroValueValidator: public StringAsNumberValidator<C, Number>
{
    public:
        NonZeroValueValidator(C &object, std::string (C::*accessor)() const, std::string fieldName)
            : StringAsNumberValidator<C, Number>(object, accessor, fieldName)
        {
            setErrorMessage("Ошибка: " + fieldName + " не может быть равной 0!");
        }

        virtual ~NonZeroValueValidator() {}

        virtual void setErrorMessage(std::string message) { this->errorMessage = message; }

    protected:

        virtual bool condition() override
        {
            return this->convertValidationFieldValue() != 0;
        }
};

#endif // NONZEROVALUEVALIDATOR_H
