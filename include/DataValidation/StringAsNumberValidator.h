#ifndef STRINGASNUMBERVALIDATOR_H
#define STRINGASNUMBERVALIDATOR_H

#include <sstream>

#include "Validator.h"

template <typename T, typename Number>
class StringAsNumberValidator: public Validator<T>
{
public:
        StringAsNumberValidator(IDataWrapper<T>* dataWrapper, std::string fieldName): Validator<T>(dataWrapper)
        {
            this->fieldName = fieldName;
        }

        virtual ~StringAsNumberValidator() {}

    protected:
        std::string fieldName;

        Number convertValidationFieldValue()
        {
            std::string data = this->dataWrapper->get();
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
