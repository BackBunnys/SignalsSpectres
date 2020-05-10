#ifndef IVALIDATOR_H
#define IVALIDATOR_H

template <typename T>
class IValidator
{
    public:

        virtual bool validate(string &errorString);

        virtual T& getValidatingField() = 0;

        virtual void setValidatingField(T& field) = 0;

};

#endif // IVALIDATOR_H
