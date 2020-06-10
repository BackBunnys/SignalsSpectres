#include "Task.h"

Task::Task(bool run)
{
    progress = 0u;
    isAborted = false;
    this->thread = NULL;
    if(run) this->run();
}

Task::~Task()
{
    abort();
    if(thread) delete thread;
}

void Task::run()
{
    this->thread = new std::thread(&Task::task, this);
}

void Task::abort()
{
    this->isAborted = true;
}
