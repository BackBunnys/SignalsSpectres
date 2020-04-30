#include "WindowFunction.h"

WindowFunction::WindowFunction(std::string name, double (*expression)(uint32_t))
{
    this->name = name;
    this->expression = expression;
}

double WindowFunction::getValue(uint32_t i)
{
    return expression(i);
}

template <typename InputIterator>
void WindowFunction::applyTo(InputIterator first, InputIterator last)
{
    if(first < last) {
        int i = 0;
        while(first != last) {
            *first = *first * expression(i);
            ++first;
            ++i;
        }
    }
}
