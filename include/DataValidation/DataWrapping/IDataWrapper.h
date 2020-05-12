#ifndef IDATAWRAPPER_H
#define IDATAWRAPPER_H

template <typename T>
class IDataWrapper
{
    public:
        virtual T get() const = 0;

        virtual ~IDataWrapper() {}
};

#endif // IDATAWRAPPER_H
