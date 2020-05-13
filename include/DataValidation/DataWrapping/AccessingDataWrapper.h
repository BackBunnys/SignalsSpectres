#ifndef ACCESSINGDATAWRAPPER_H
#define ACCESSINGDATAWRAPPER_H

#include "DataWrapper.h"

template <typename C, typename T>
class AccessingDataWrapper : public DataWrapper<T>
{
    public:
        AccessingDataWrapper(const C &object, T (C::*accessor)() const, std::string dataDescription)
            : DataWrapper<T>(dataDescription)
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
