#ifndef STRINGASNUMBERVALIDATOR_H
#define STRINGASNUMBERVALIDATOR_H

#include <sstream>

#include "Validator.h"

template <typename C, typename Number>
class StringAsNumberValidator: public Validator<C, std::string>
{
public:
        StringAsNumberValidator(C &object, std::string (C::*accessor)() const, std::string fieldName): Validator<C, std::string>(object, accessor)
        {
            this->fieldName = fieldName;
        }

        virtual ~StringAsNumberValidator() {}

    protected:
        std::string fieldName;

        Number convertValidationFieldValue()
        {
            std::string data = this->invoke();
            if(data.size() == 0)
                return -1;
            else {
                Number result;
                std::stringstream sx;
                sx << data;
                sx >> result;
                return result;
            }
        }

        virtual bool condition() = 0;
};

#endif // STRINGASNUMBERVALIDATOR_H
