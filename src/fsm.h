#pragma once

#include <iostream>
#include <vector>
#include <functional>

template <typename State, typename Event>
class FSM
{
    using Index = uint32_t;
    using Mask = uint32_t;
    using ActionCallback = std::function<void(void)>;

    struct Transition
    {
        Event TriggerEvent;
        State DstState;
        ActionCallback Action;
    };

public:
    FSM(size_t NumStates, State DefaultState) :
        StateTransitions(NumStates),
        CurrentState(DefaultState)
    {
        ;
    }

    void AddTransition(State SrcState, State DstState,
                       Event TriggerEvent, const ActionCallback& Action)
    {
        StateTransitions[(Index)SrcState].push_back({TriggerEvent, DstState, Action});
    }

    void AddWildcardTransition(Mask SrcStateMask, State DstState,
                               Event TriggerEvent, const ActionCallback& Action)
    {
        Transition Transition = {TriggerEvent, DstState, Action};
        for (size_t i = 0; i < StateTransitions.size(); i++)
        {
            if (SrcStateMask & (1 << i))
            {
                StateTransitions[i].push_back(Transition);
            }
        }
    }

    void Input(Event EventIn)
    {
        for (auto&& Transition : StateTransitions[(Index)CurrentState])
        {
            if (EventIn == Transition.TriggerEvent)
            {
                CurrentState = Transition.DstState;
                Transition.Action();
                break;
            }
        }
    }

protected:
    std::vector<std::vector<Transition>> StateTransitions;
    State CurrentState;
};
