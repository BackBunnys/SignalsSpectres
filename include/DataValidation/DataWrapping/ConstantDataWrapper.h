#ifndef CONSTANTDATAWRAPPER_H
#define CONSTANTDATAWRAPPER_H

#include "DataWrapper.h"

template <typename T>
class ConstantDataWrapper : public DataWrapper<T>
{
    public:
        ConstantDataWrapper(T data)
            : DataWrapper(dataDescription), data(data) {}

        virtual ~ConstantDataWrapper() {}

        virtual T get() const { return this->data; }

        virtual std::string getDataDescription() const override
        {
            return std::toString(data);
        }

    private:
        const T data;
};

#endif // CONSTANTDATAWRAPPER_H
