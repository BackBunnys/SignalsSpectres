#ifndef VALIDATOR_H
#define VALIDATOR_H

#include "IValidator.h"
#include "DataWrapping/DataWrapper.h"

template <typename T>
class Validator: public IValidator
{
    public:

        Validator(DataWrapper<T>* dataWrapper): dataWrapper(dataWrapper) { }

        virtual ~Validator() { delete this->dataWrapper; }

        virtual bool validate(std::string &errorString)
        {
            if(!condition()) errorString += errorMessage;
            else return true;

            return false;
        }

        virtual void setValidatingData(DataWrapper<T>* dataWrapper)
        {
            this->dataWrapper = dataWrapper;
        }

        std::string getErrorMessage() { return this->errorMessage; }
        void setErrorMessage(std::string message) { this->errorMessage = message;}

    protected:
        DataWrapper<T>* dataWrapper;

        std::string errorMessage;

        virtual bool condition() = 0;
};

#endif // VALIDATOR_H
