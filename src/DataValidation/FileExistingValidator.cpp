#include "DataValidation/FileExistingValidator.h"
#include <fstream>

FileExistingValidator::FileExistingValidator(std::string &validationField): Validator(validationField)
{
    setErrorMessage("������: �� ������� ������� ����!");
}

bool FileExistingValidator::condition()
{
    return std::ifstream(this->validatingField.data());
}


