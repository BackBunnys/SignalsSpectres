#ifndef TASK_H
#define TASK_H

#include <thread>
#include <string>

class Task
{
    public:
        Task(bool run = true);
        virtual ~Task();

        void run();
        void abort();

        inline uint8_t getProgress() const { return progress; }
        inline const std::string& getStageDescription() const { return stageDescription; }

        inline bool isDone() const { return progress >= 100; }


    private:
        bool isAborted;

        uint8_t progress;
        std::string stageDescription;

        std::thread* thread;

        virtual void task() = 0;
};

#endif // TASK_H
