//-----------------------------------------------------------------------
//  Author      : Nikita Mashtalirov
//  Created     : 16.07.2021
//  Description : Abstract base class for the state stack.
//-----------------------------------------------------------------------
#pragma once

#include <SFML/System/Time.hpp>

namespace Engine
{
    class State
    {
    protected:
        enum ControlMethod
        {
            Keyboard,
            Mouse
        };

    public:
        State() = default;
        virtual ~State() = default;

    public:
        /** @brief  Virtual method for initializing class data
         */
        virtual void init() = 0;

        /** @brief  Virtual method for processing keystrokes and mouse clicks
         */
        virtual void processInput() = 0;

        /** @brief  Virtual method for updating the position of sprites, texts
         *  @param  delta_time - time elapsed since the last function call
         */
        virtual void update(sf::Time delta_time) = 0;

        /** @brief  Virtual method for drawing sprites and text
         */
        virtual void draw() = 0;

        /** @brief  Virtual method for pausing the state
         */
        virtual void pause(){};

        /** @brief  Virtual method for launching the state
         */
        virtual void launch(){};
    };

} // namespace Engine
