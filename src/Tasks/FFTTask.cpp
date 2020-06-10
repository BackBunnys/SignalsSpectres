#include "FFTTask.h"
#include <sstream>
#include <fstream>

FFTTask::FFTTask(const std::string& filePath, uint32_t signalSize, bool run): Task(run)
{
    this->filePath = filePath;
    this->signalSize = signalSize;
    this->progress = 0.f;
}

FFTTask::~FFTTask()
{
    //dtor
}

void FFTTask::actions()
{
    readFromFile();
}

void FFTTask::readFromFile()
{
    std::ifstream input(filePath);
    values.clear();
    values.reserve(signalSize);
    if(input.is_open()) {
        while(values.size() < signalSize && !input.eof()) {
            float val;
            input >> val;
            values.push_back(val);
            progress = 20.f * values.size() / signalSize;
        }
    }
}
