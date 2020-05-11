#ifndef VALIDATOR_H
#define VALIDATOR_H

#include "IValidator.h"

template <typename C, typename T>
class Validator: public IValidator<C, T>
{
    public:
        Validator(C &object, T (C::*accessor)() const)
        {
            setValidatingAccessor(object, accessor);
            setErrorMessage("Неизвестная ошибка!");
        }

        virtual ~Validator() {}

        virtual bool validate(std::string &errorString)
        {
            if(!condition()) errorString += errorMessage;
            else return true;

            return false;
        }

        virtual void setValidatingAccessor(const C &object, T (C::*accessor)() const)
        {
            this->validatingObject = &object;
            this->validatingFieldAccessor = accessor;
        }

        std::string getErrorMessage() { return this->errorMessage; }
        void setErrorMessage(std::string message) { this->errorMessage = message;}

    protected:
        std::string errorMessage;
        T (C::*validatingFieldAccessor)() const;
        const C* validatingObject;

        virtual bool condition() = 0;

        virtual T invoke()
        {
            return ((*this->validatingObject).*this->validatingFieldAccessor)();
        }

};

#endif // VALIDATOR_H
