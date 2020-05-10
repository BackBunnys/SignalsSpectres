#ifndef FILEEXISTINGVALIDATOR_H
#define FILEEXISTINGVALIDATOR_H

#include "DataValidation/Validator.h"

class FileExistingValidator: public Validator<std::string>
{
    public:
        FileExistingValidator(std::string& validationField);

        virtual ~FileExistingValidator() {}

    protected:

        virtual bool condition();
};

#endif // FILEEXISTINGVALIDATOR_H
