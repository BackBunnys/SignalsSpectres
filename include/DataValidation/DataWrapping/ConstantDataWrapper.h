#ifndef CONSTANTDATAWRAPPER_H
#define CONSTANTDATAWRAPPER_H

#include "IDataWrapper.h"

template <typename T>
class ConstantDataWrapper : public IDataWrapper<T>
{
    public:
        ConstantDataWrapper(T data): data(data) {}

        virtual ~ConstantDataWrapper() {}

        virtual T get() const { return this->data; }

    private:
        const T data;
};

#endif // CONSTANTDATAWRAPPER_H
