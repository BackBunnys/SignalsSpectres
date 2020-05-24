#ifndef CONSTANTDATAWRAPPER_H
#define CONSTANTDATAWRAPPER_H

#include <sstream>

#include "DataWrapper.h"

template <typename T>
class ConstantDataWrapper : public DataWrapper<T>
{
    public:
        ConstantDataWrapper(T data)
            : data(data) {}

        virtual ~ConstantDataWrapper() {}

        virtual T get() const { return this->data; }

        virtual std::string getDataDescription() const override
        {
            std::stringstream sx;
            sx << data;

            return sx.str();
        }

    private:
        const T data;
};

#endif // CONSTANTDATAWRAPPER_H
