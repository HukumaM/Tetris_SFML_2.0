//-----------------------------------------------------------------------
//  Author      : Nikita Mashtalirov
//  Created     : 16.07.2021
//  Description : The main class of the game
//-----------------------------------------------------------------------

#pragma once

#include <iostream>
#include "Context.hpp"

//  An enumeration that stores the game window resolution values
enum WINDOW_SIZE
{
    WIDTH = 540,
    HEIGHT = 720,
};

class Tetris
{
private:
    //  A common pointer for all states
    std::shared_ptr<Context> context;

    //  A variable that stores a time value equal to one frame
    const sf::Time TIME_PER_FRAME = sf::seconds(1.f / 60.f);

public:
    Tetris();
    Tetris(const Tetris &) = delete;
    Tetris &operator=(const Tetris &) = delete;
    ~Tetris() = default;

public:
    //  Game launch function
    void Run();
private:
    void load_assets();
};
