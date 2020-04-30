#include "WindowFunction.h"

WindowFunction::WindowFunction(std::string name, double (*expression)(uint32_t, uint32_t))
{
    this->name = name;
    this->expression = expression;
}

double WindowFunction::getValue(uint32_t n, uint32_t N)
{
    return expression(n, N);
}

template <typename InputIterator>
void WindowFunction::applyTo(InputIterator first, InputIterator last)
{
    if(first < last) {
        int n = 0;
        int N = last - first;
        while(first != last) {
            *first = *first * expression(n, N);
            ++first;
            ++n;
        }
    }
}
