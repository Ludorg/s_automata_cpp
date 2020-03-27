// Sofia (Sofia_aleph)
//
// Sofia, my way for developing knowledge
//
// (c) 2004 Ludovic LIEVRE aka Ludorg

//
// 0.0.1 2004/06/15 : file creation

#if !defined(S_AUTOMATA_H)
#define S_AUTOMATA_H 1

/**
 * @file s_automata.h
 * @author Ludorg - ludorg@ludorg.net -
 * @brief 
 * @version 0.1 Add documentation
 * @date 2020-03-27
 * 
 * @copyright Copyright (c) 2004-2020
 * 
 */

#include <map>

#include "sofia.h"

SOFIA_NS_BEGIN

/**
 * @brief Template class for an automata
 * 
 * @tparam TState Type for automata states
 * @tparam TEvent Type for automata events
 * @tparam TActions Class for automata actions. These are methods with signature void method_name(void). Actions are executed when firing a transition.
 */
template <typename TState, typename TEvent, typename TActions>
class Automata
{

    std::map<TState, std::map<TEvent, std::pair<TState, void (TActions::*)(void)>>> transitions_;

    TState currentState_;

public:
    /**
     * @brief Set initial state of automata
     * 
     * @param initialState 
     * @return true if initial state correctly initialized
     * @return false when initial state does not exist
     */
    bool init(const TState &initialState);

    /**
     * @brief Handle event and fire corresponding transition. Action is executed before changing state.
     * 
     * @param event The event to handle
     * @param actions Class containing the methods for actions with signature void method(void)
     * @return true if handeld
     * @return false if event was not handled in current state
     */
    bool handleEvent(const TEvent &event, TActions &actions);

    /**
     * @brief Add a transition to automata
     * 
     * @param from state
     * @param to state
     * @param evt event
     * @param action (void method(void)) to be run on event firing
     */
    void addTransition(const TState &from, const TState &to, const TEvent &evt, void (TActions::*action)(void));

    /**
     * @brief Get the current state of automata
     * 
     * @return const TState& 
     */
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
