#ifndef INRANGEVALUEVALIDATOR_H
#define INRANGEVALUEVALIDATOR_H

#include <vector>

#include "Validator.h"

enum Side {LEFT, RIGHT};

template <typename T>
class Border
{
    public:
        Border(const DataWrapper<T>* dataWrapper, Side side, bool isStrong = false)
        {
            this->border = dataWrapper;
            this->side = side;
            this->isStrong = isStrong;
        }

        bool check(DataWrapper<T>* comparingWrapper)
        {
            if(side == LEFT) {
                if(isStrong)
                    return this->border->get() < comparingWrapper->get();
                else return this->border->get() <= comparingWrapper->get();
            }
            else if(isStrong)
                return comparingWrapper->get() < this->border->get();
            else return comparingWrapper->get() <= this->border->get();
        }

        std::string getDataDescription() const
        {
            return this->border->getDataDescription();
        }

        std::string getBorderDescription() const
        {
            return (side == LEFT)? "больше": "меньше";
        }

    private:
        const DataWrapper<T>* border;
        Side side;
        bool isStrong = isStrong;
};


template <typename T>
class InRangeValueValidator: public Validator<T>
{
    public:
        InRangeValueValidator(DataWrapper<T>* validatingData,
                              Border<T>* leftBorder,
                              Border<T>* rightBorder)
            : Validator<T>(validatingData)
        {
            addBorder(leftBorder);
            addBorder(rightBorder);
        }

        InRangeValueValidator(DataWrapper<T>* validatingData)
            : Validator<T>(validatingData)
        {
        }

        virtual void addBorder(Border<T>* border)
        {
            this->borders.push_back(border);
        }

        virtual ~InRangeValueValidator()
        {
            for(size_t i = 0; i < borders.size(); ++i) delete borders[i];
        }

    protected:

        virtual bool condition() override
        {
            bool isInRange = true;
            size_t i = 0;

            while(isInRange && i < borders.size()) {
                isInRange = this->borders[i]->check(this->dataWrapper);
                ++i;
            }

            if(!isInRange)
                this->setErrorMessage("Ошибка: " + this->dataWrapper->getDataDescription() +
                                      " должно быть " + this->borders[i - 1]->getBorderDescription() +
                                      " , чем " + this->borders[i - 1]->getDataDescription() + "!\n");
            return isInRange;
        }

    private:
        std::vector<Border<T>*> borders;
};

#endif // INRANGEVALUEVALIDATOR_H
