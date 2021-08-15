//-----------------------------------------------------------------------
//  Author      : Nikita Mashtalirov
//  Created     : 23.07.2021
//  Description : A class representing the main MenuState of the game
//-----------------------------------------------------------------------

#pragma once

#include <vector>

#include <SFML/Graphics/Text.hpp>

#include "Title.hpp"
#include "Button.hpp"
#include "State.hpp"
#include "Context.hpp"

class OptionState : public Engine::State
{
private:
    std::shared_ptr<Context> context;

private:
    std::vector<Title> titles;
    static Slider music_slider;
    static Slider sound_slider;
    static std::vector<Button> texture_buttons;
    TextButton save_button;
    //sf::Sprite textures;

    enum TitlesName
    {
        Option,
        MusicVolume,
        SoundVolume,
        Texture
    };

    sf::Time elapsed_time{sf::Time::Zero};
    unsigned fps{0};

public:
    //  OptionState class onstructor
    //  @param  context
    OptionState(std::shared_ptr<Context> &context);
    ~OptionState() = default;

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