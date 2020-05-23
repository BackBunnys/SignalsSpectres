#ifndef ISPOWEROFVALIDATOR_H
#define ISPOWEROFVALIDATOR_H

#include <cmath>

#include "Validator.h"
#include "DataWrapping/DataWrapper.h"

class IsPowerOfValidator: public Validator<long long>
{
    public:
        IsPowerOfValidator(DataWrapper<long long>* valueWrapper, DataWrapper<long long>* baseWrapper): Validator<long long>(valueWrapper)
        {
            this->valueWrapper = valueWrapper;
            this->baseWrapper = baseWrapper;
            this->setErrorMessage("Ошибка: " + valueWrapper->getDataDescription() + " не является степенью " + baseWrapper->getDataDescription() + "!");
        }

        virtual ~IsPowerOfValidator()
        {
            //delete this->valueWrapper; I dont know why it is already deleted
            delete this->baseWrapper;
        }

    protected:

        virtual bool condition()
        {
            long long number = this->valueWrapper->get();
            long long base = this->baseWrapper->get();
            bool isPower = number != 0;

            while(isPower && number != 0) {
                if(number % base != 0 && abs(number) != 1)
                    isPower = false;
                number /= base;
            }
            return isPower;
        }

    private:
        DataWrapper<long long>* valueWrapper;
        DataWrapper<long long>* baseWrapper;
};


#endif // ISPOWEROFVALIDATOR_H
