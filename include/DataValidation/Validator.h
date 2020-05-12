#ifndef VALIDATOR_H
#define VALIDATOR_H

#include "IValidator.h"
#include "DataWrapping/IDataWrapper.h"

template <typename T>
class Validator: public IValidator<T>
{
    public:

        Validator(IDataWrapper<T>* dataWrapper): dataWrapper(dataWrapper) { }

        virtual ~Validator() { delete this->dataWrapper; }

        virtual bool validate(std::string &errorString)
        {
            if(!condition()) errorString += errorMessage;
            else return true;

            return false;
        }

        virtual void setValidatingData(IDataWrapper<T>* dataWrapper)
        {
            this->dataWrapper = dataWrapper;
        }

        std::string getErrorMessage() { return this->errorMessage; }
        void setErrorMessage(std::string message) { this->errorMessage = message;}

    protected:
        IDataWrapper<T>* dataWrapper;

        std::string errorMessage;

        virtual bool condition() = 0;
};

#endif // VALIDATOR_H
