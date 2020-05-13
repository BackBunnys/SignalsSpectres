#ifndef CONVERTINGDATAWRAPPER_H
#define CONVERTINGDATAWRAPPER_H

#include <DataWrapper.h>

template <typename T, typename toType>
class ConvertingDataWrapper : public DataWrapper<toType>
{
    public:
        ConvertingDataWrapper(const DataWrapper<T>* dataWrapper)
        {
            this->dataWrapper = dataWrapper;
        }

        virtual ~ConvertingDataWrapper() { delete this->dataWrapper; }

        virtual toType get() const
        {
            return convert();
        }

        virtual std::string getDataDescription() const override
        {
            return this->dataWrapper->getDataDescription();
        }

    private:
        const DataWrapper<T>* dataWrapper;

    protected:
        virtual toType convert() const
        {
            T data = this->dataWrapper->get();
            toType result;

            std::stringstream sx;
            sx << data;
            sx >> result;

            return result;
        }
};

#endif // CONVERTINGDATAWRAPPER_H
