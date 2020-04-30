#ifndef WINDOWFUNCTION_H
#define WINDOWFUNCTION_H

#include <string>

class WindowFunction
{
    public:

        WindowFunction(std::string name, double expression(uint32_t));

        double getValue(uint32_t i);

        template <typename InputIterator>
        void applyTo(InputIterator first, InputIterator last);

    private:
        std::string name;

        double (*expression)(uint32_t);
};

#endif // WINDOWFUNCTION_H
