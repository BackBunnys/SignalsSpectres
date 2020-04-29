#pragma once
#ifndef STATEMACHINE_H
#define STATEMACHINE_H

class State;

#include "State.h"
#include "stack"

class StateMachine
{
    public:
        StateMachine();
        StateMachine(State* state);
        virtual ~StateMachine();

        State* getCurrentState();

        void PopState();

        void PushState(State* state);

        void Clear();

        bool isEmpty();

    private:

        std::stack<State*> states;
};

#endif // STATEMACHINE_H
