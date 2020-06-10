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

        inline bool isDone() const { return this->done; }


    protected:
        bool isAborted;
        bool done;

        std::thread* thread;

        void task();

        virtual void actions() = 0;
};

#endif // TASK_H
