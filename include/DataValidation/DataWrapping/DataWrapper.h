#ifndef IDATAWRAPPER_H
#define IDATAWRAPPER_H

#include <string>

template <typename T>
class DataWrapper
{
    public:
        DataWrapper() {}

        DataWrapper(std::string dataDescription)
        {
            this->dataDescription = dataDescription;
        }

        virtual T get() const = 0;

        virtual std::string getDataDescription() const
        {
            return this->dataDescription;
        }

        virtual ~DataWrapper() {}

    private:
        std::string dataDescription;
};

#endif // IDATAWRAPPER_H
