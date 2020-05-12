#ifndef IVALIDATOR_H
#define IVALIDATOR_H

#include <string>

template <typename T>
class IValidator
{
    public:

        virtual bool validate(std::string &errorString) = 0;

        virtual ~IValidator() {}

};

#endif // IVALIDATOR_H
