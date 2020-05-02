#include "Engine/StateMachine.h"

StateMachine::StateMachine()
{

}

StateMachine::StateMachine(State* state)
{
    PushState(state);
}

StateMachine::~StateMachine()
{
    Clear();
}

void StateMachine::Clear()
{
    while(!states.empty())
    {
        delete states.top();
        states.pop();
    }
}

bool StateMachine::isEmpty()
{
    return states.empty();
}

void StateMachine::PopState()
{
    if(!states.empty()) {
        delete states.top();
        states.pop();
    }
}

void StateMachine::PushState(State* state)
{

    state->Init();
    states.push(state);
}

State* StateMachine::getCurrentState()
{
    if(!states.empty())
        return states.top();
    else
        return NULL;
}
