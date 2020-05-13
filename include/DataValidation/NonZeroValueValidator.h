#ifndef NONZEROVALUEVALIDATOR_H
#define NONZEROVALUEVALIDATOR_H

#include "StringAsNumberValidator.h"

template <typename Number>
class NonZeroValueValidator: public StringAsNumberValidator<Number>
{
    public:
        NonZeroValueValidator(DataWrapper<std::string>* dataWrapper)
            : StringAsNumberValidator<Number>(dataWrapper, fieldName)
        {
            setErrorMessage("Ошибка: " + dataWrapper.getDataDescription() + " не может быть равной 0!");
        }

        virtual ~NonZeroValueValidator() {}

    protected:

        virtual bool condition() override
        {
            return this->convertDataValue(this->dataWrapper) != 0;
        }
};

#endif // NONZEROVALUEVALIDATOR_H
