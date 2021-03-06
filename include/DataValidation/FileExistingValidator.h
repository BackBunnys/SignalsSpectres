#ifndef FILEEXISTINGVALIDATOR_H
#define FILEEXISTINGVALIDATOR_H

#include <fstream>

#include "Validator.h"
#include "DataWrapping/DataWrapper.h"

class FileExistingValidator: public Validator<std::string>
{
    public:
        FileExistingValidator(DataWrapper<std::string>* dataWrapper): Validator<std::string>(dataWrapper)
        {
            this->setErrorMessage("������: �� ������� ������� ����!");
        }

        virtual ~FileExistingValidator() {}

    protected:

        virtual bool condition()
        {
            return std::ifstream(this->dataWrapper->get().data());
        }
};

#endif // FILEEXISTINGVALIDATOR_H
