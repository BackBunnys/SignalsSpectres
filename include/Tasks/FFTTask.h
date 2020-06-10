#ifndef FFTTASK_H
#define FFTTASK_H

#include "Task.h"
#include "GUI/ProgressBar.h"

class FFTTask : public Task, public IProgressive
{
    public:
        FFTTask(const std::string& filePath, uint32_t signalSize, bool run = true);
        virtual ~FFTTask();

        virtual float getProgress() const { return this->progress; }
        virtual const std::string& getStageDescription() { return this->stageDescription; }

    private:
        virtual void actions() override;
        void readFromFile();

        float progress;
        std::string stageDescription;

        std::string filePath;
        uint32_t signalSize;

        std::vector<float> values;
};

#endif // FFTTASK_H
