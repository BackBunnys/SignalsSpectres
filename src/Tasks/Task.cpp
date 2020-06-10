#include "Task.h"

Task::Task(bool run)
{
    done = false;
    isAborted = false;
    this->thread = NULL;
    if(run) this->run();
}

Task::~Task()
{
    abort();
    if(thread) {
        thread->join();
        delete thread;
    }
}

void Task::run()
{
    this->thread = new std::thread(&Task::task, this);
}

void Task::abort()
{
    this->isAborted = true;
}

void Task::task()
{
    actions();
    this->done = true;
}
