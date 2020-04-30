#ifndef WINDOWFUNCTION_H
#define WINDOWFUNCTION_H

#include <string>

class WindowFunction
{
    public:
        WindowFunction() {}

        WindowFunction(std::string name, double (*expression)(uint32_t, uint32_t));

        const std::string& getName() { return this->name; }

        double getValue(uint32_t n, uint32_t N);

        template <typename InputIterator>
        void applyTo(InputIterator first, InputIterator last);

    private:
        std::string name;

        double (*expression)(uint32_t, uint32_t);
};

#endif // WINDOWFUNCTION_H
