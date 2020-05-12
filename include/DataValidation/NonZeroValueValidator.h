#ifndef NONZEROVALUEVALIDATOR_H
#define NONZEROVALUEVALIDATOR_H

#include "StringAsNumberValidator.h"

template <typename T, typename Number>
class NonZeroValueValidator: public StringAsNumberValidator<T, Number>
{
    public:
        NonZeroValueValidator(IDataWrapper<T>* dataWrapper, std::string fieldName)
            : StringAsNumberValidator<T, Number>(dataWrapper, fieldName)
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
