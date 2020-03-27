// Sofia (Sofia_aleph)
//
// Sofia, my way for developing knowledge
//
// (c) 2004 Ludovic LIEVRE aka Ludorg

//
// 0.0.1 2004/06/15 : file creation

#if !defined(S_AUTOMATA_H)
#define S_AUTOMATA_H 1

#include <map>

#include "sofia.h"

SOFIA_NS_BEGIN

template <typename TState, typename TEvent, typename TActions>
class Automata
{

    std::map<TState, std::map<TEvent, std::pair<TState, void (TActions::*)(void)>>> transitions_;

    TState currentState_;

public:
    bool init(const TState &initialState);
    bool handleEvent(const TEvent &event, TActions &actions);
    void addTransition(const TState &from, const TState &to, const TEvent &evt, void (TActions::*action)(void));

    const TState &getCurrentState() const;
};

template <typename TState, typename TEvent, typename TActions>
bool Automata<TState, TEvent, TActions>::init(const TState &initialState)
{
    bool ret = false;

    if (transitions_.find(initialState) != transitions_.end())
    {
        currentState_ = initialState;
        ret = true;
    }

    return ret;
}

template <typename TState, typename TEvent, typename TActions>
bool Automata<TState, TEvent, TActions>::handleEvent(const TEvent &event, TActions &actions)
{
    bool ret = false;

    if (transitions_[currentState_].find(event) !=
        transitions_[currentState_].end())
    {
        std::pair<TState, void (TActions::*)(void)> transition =
            transitions_[currentState_][event];

        if (transition.second != 0)
        {
            (actions.*transition.second)();
        }
        currentState_ = transition.first;

        ret = true;
    }

    return ret;
}

template <typename TState, typename TEvent, typename TActions>
void Automata<TState, TEvent, TActions>::addTransition(const TState &from, const TState &to, const TEvent &evt, void (TActions::*action)(void))
{
    transitions_[from][evt] =
        // 2020-03-27: below line is valid in c++11, but not c++14
        // std::make_pair<TState, void ( TActions::* ) ( void )>( to, action );
        std::make_pair(to, action);
}

template <typename TState, typename TEvent, typename TActions>
const TState &Automata<TState, TEvent, TActions>::getCurrentState() const
{
    return currentState_;
}

SOFIA_NS_END

#endif // S_AUTOMATA_H
