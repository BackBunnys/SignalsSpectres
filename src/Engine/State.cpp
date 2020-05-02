#include "Engine/State.h"

State::State(AppData &appData):
     appData(appData)
{

}

State::~State() {}

const std::string State::getDescription() const
{
    return this->Description;
}
