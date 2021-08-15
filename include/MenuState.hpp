//-----------------------------------------------------------------------
//  Author      : Nikita Mashtalirov
//  Created     : 16.07.2021
//  Description : A class representing the main MenuState of the game
//-----------------------------------------------------------------------

#pragma once

#include <vector>

#include <SFML/Graphics/Text.hpp>

#include "Title.hpp"
#include "Button.hpp"

#include "State.hpp"
#include "Context.hpp"

#include "OptionState.hpp"

class MenuState : public Engine::State
{
private:
    std::shared_ptr<Context> context;

private:
    Title game_title;

    enum ButtonName
    {
        Single_Player,
        PVP,
        Option,
        Exit
    };

    std::vector<TextButton> buttons;
    std::vector<TextButton>::iterator selected_button;

    sf::Time elapsed_time{sf::Time::Zero};
    unsigned fps{0};

public:
    //  MenuState class onstructor
    //  @param  context
    MenuState(std::shared_ptr<Context> &context);
    ~MenuState() = default;

public:
    //  Overriding the method for initialization class data
    void init() override;

    //  Overriding the method for processing keystrokes and mouse clicks
    void processInput() override;

    //  Overriding the method for updating the position of sprites, texts
    //  @param  delta_time  time elapsed since the last function call
    void update(sf::Time delta_time) override;

    //  Overriding the method for drawing sprites and text
    void draw() override;

    void pause() override;

    void launch() override;
};