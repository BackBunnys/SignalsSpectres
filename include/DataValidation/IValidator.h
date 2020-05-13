#ifndef IVALIDATOR_H
#define IVALIDATOR_H

class IValidator
{
    public:

        virtual bool validate(std::string &errorString) = 0;

        virtual ~IValidator() {}
};

#endif // IVALIDATOR_H
