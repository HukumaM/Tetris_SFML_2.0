//-----------------------------------------------------------------------
//  Author      : Nikita Mashtalirov
//  Created     : 16.07.2021
//  Description : A class that controls application state management.
//-----------------------------------------------------------------------

#pragma once

#include <stack>
#include <memory>

#include "State.hpp"

namespace Engine
{
    class StateManager
    {
    private:
        /** @brief  Next state to put on the stack
         */
        std::unique_ptr<State> next_state;

        /** @brief  Stack that stores states
         */
        std::stack<std::unique_ptr<State>> state_stack;

    private:
        //  A flag variable that stores the need to insert a state
        bool push{false};
        //  A flag variable that stores the need to replace a state
        bool replace{false};
        //  A flag variable that stores the need to remove a state
        bool remove{false};

    public:
        StateManager();
        ~StateManager() = default;

    public:
        /** @brief  Adding a new state to the top of the state stack
         *  @param  to_add   the state to be added to the state stack
         *  @param  replace  a flag indicating whether we just want to add a new value - false,
         *          or replace the current one with it - true
         */
        void
        pushState(std::unique_ptr<State> to_add, bool replace = false);

        /** @brief  Popping the current state from the top of the state stack
         */
        void
        popState();

        /** @brief  Actual process state change
         */
        void
        processStateChange();

        /** @brief  Returns a pointer to the current state object by reference
        *   @return a pointer to the current state object by reference
        */
        std::unique_ptr<State> &
        getState();
    };

} // namespace Engine