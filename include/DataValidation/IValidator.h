#ifndef IVALIDATOR_H
#define IVALIDATOR_H

#include <string>

template <typename T>
class IValidator
{
    public:

        virtual bool validate(std::string &errorString) = 0;

        virtual T& getValidatingField() = 0;

        virtual void setValidatingField(T& field) = 0;

};

#endif // IVALIDATOR_H
