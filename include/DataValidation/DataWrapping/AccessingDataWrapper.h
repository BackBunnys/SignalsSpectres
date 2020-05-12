#ifndef ACCESSINGDATAWRAPPER_H
#define ACCESSINGDATAWRAPPER_H

#include "IDataWrapper.h"

template <typename C, typename T>
class AccessingDataWrapper : public IDataWrapper<T>
{
    public:
        AccessingDataWrapper(const C &object, T (C::*accessor)() const)
        {
            this->object = &object;
            this->accessor = accessor;
        }

        virtual ~AccessingDataWrapper() {}

        virtual T get() const
        {
            return ((*this->object).*this->accessor)();
        }

        private:
            T (C::*accessor)() const;
            const C*  object;
};

#endif // ACCESSINGDATAWRAPPER_H
