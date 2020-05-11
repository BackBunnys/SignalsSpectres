#ifndef IVALIDATOR_H
#define IVALIDATOR_H

#include <string>

template <typename C, typename T>
class IValidator
{
    public:

        virtual bool validate(std::string &errorString) = 0;

        virtual void setValidatingAccessor(const C &object, T (C::*accessor)() const) = 0;

};

#endif // IVALIDATOR_H
