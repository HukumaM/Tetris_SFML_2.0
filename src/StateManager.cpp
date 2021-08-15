#include "StateManager.hpp"

namespace Engine
{
    StateManager::StateManager()
    {
    }

    void
    StateManager::pushState(std::unique_ptr<State> to_add, bool replace)
    {
        push = true;

        next_state = std::move(to_add);

        replace = replace;
    }

    void
    StateManager::popState()
    {
        remove = true;
    }

    void
    StateManager::processStateChange()
    {
        //  Checks if the extract flag is true and the state stack is not empty,
        //  then retrieves the state and runs the next one
        //  if the state stack is not empty
        if (remove && !state_stack.empty())
        {
            state_stack.pop();
            if (!state_stack.empty())
            {
                state_stack.top()->launch();
            }
            remove = false;
        }

        //  Checks whether the add flag is true. If the replace flag is set 
        //  and the state stack is not empty, the element is removed from it 
        //  and the flag is reset. Then the state object at the top of the stack 
        //  is stopped and a new one is added
        if (push)
        {
            if (replace && !state_stack.empty())
            {
                state_stack.pop();
                replace = false;
            }

            if (!state_stack.empty())
            {
                state_stack.top()->pause();
            }

            state_stack.push(std::move(next_state));
            state_stack.top()->init();
            state_stack.top()->launch();
            push = false;
        }
    }

    std::unique_ptr<State> &
    StateManager::getState()
    {
        return state_stack.top();
    }

} //namespace Engine