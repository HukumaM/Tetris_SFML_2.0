//-----------------------------------------------------------------------
//  Author      : Nikita Mashtalirov
//  Created     : 16.07.2021
//  Description : The main class of the game
//-----------------------------------------------------------------------

#pragma once

#include <memory>

#include <SFML/Graphics/RenderWindow.hpp>

#include "AssetManager.hpp"
#include "StateManager.hpp"

//  A structure that stores smart pointers to assets, states, and a window
struct Context
{
    //  Pointer to context assets
    std::unique_ptr<Engine::AssetManager> assets;
    //  Pointer to context states
    std::unique_ptr<Engine::StateManager> states;
    //  Pointer to render window
    std::unique_ptr<sf::RenderWindow> window;

    Context()
    {
        assets = std::make_unique<Engine::AssetManager>();
        states = std::make_unique<Engine::StateManager>();
        window = std::make_unique<sf::RenderWindow>();
    }
};