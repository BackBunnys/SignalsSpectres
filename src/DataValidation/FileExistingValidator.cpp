#include "DataValidation/FileExistingValidator.h"
#include <fstream>

FileExistingValidator::FileExistingValidator(std::string &validationField): Validator(validationField)
{
    setErrorMessage("Ошибка: не удалось открыть файл!");
}

bool FileExistingValidator::condition()
{
    return std::ifstream(this->validatingField.data());
}


