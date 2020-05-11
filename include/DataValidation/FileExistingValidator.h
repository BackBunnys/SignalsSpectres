#ifndef FILEEXISTINGVALIDATOR_H
#define FILEEXISTINGVALIDATOR_H

#include <fstream>

#include "DataValidation/Validator.h"

template <typename C>
class FileExistingValidator: public Validator<C, std::string>
{
    public:
        FileExistingValidator(C &object, std::string (C::*accessor)() const): Validator<C, std::string>(object, accessor)
        {
            this->setErrorMessage("Ошибка: не удалось открыть файл!");
        }

        virtual ~FileExistingValidator() {}

    protected:

        virtual bool condition()
        {
            return std::ifstream(this->invoke().data());
        }
};

#endif // FILEEXISTINGVALIDATOR_H
