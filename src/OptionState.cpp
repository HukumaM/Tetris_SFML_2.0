#include <iostream>
#include <cassert>

#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>

#include "OptionState.hpp"
//#include "PlayProcess.hpp"
//#include "PvP.hpp"

Slider OptionState::music_slider(10, sf::Vector2f(20.f, 40.f));
Slider OptionState::sound_slider(10, sf::Vector2f(20.f, 40.f));

std::vector<Button> OptionState::texture_buttons(3, Button(sf::Vector2f(40.f, 40.f)));

OptionState::OptionState(std::shared_ptr<Context> &context)
    : context(context),
      titles(4, Title(context->assets->getFont(Engine::FontID::Title_Font))),
      save_button(context->assets->getFont(Engine::FontID::Title_Font), sf::Vector2f(160.f, 60.f))
{
}

void OptionState::init()
{
    context->assets->playMusic(Engine::MusicID::Title_Music);

    titles[TitlesName::Option].setString("OPTION", 75U);
    titles[TitlesName::MusicVolume].setString("MUSIC VOLUME", 35U);
    titles[TitlesName::SoundVolume].setString("SOUND VOLUME", 35U);
    titles[TitlesName::Texture].setString("TEXTURE", 35U);

    titles[TitlesName::Option].setPosition(sf::Vector2f(260.f, 110.f));
    titles[TitlesName::MusicVolume].setPosition(sf::Vector2f(150.f, 200.f));
    titles[TitlesName::SoundVolume].setPosition(sf::Vector2f(150.f, 280.f));
    titles[TitlesName::Texture].setPosition(sf::Vector2f(260.f, 360.f));

    music_slider.setPosition(sf::Vector2f(390.f, 200.f));
    sound_slider.setPosition(sf::Vector2f(390.f, 280.f));

    auto offset_y{440.f};
    for (auto &button : texture_buttons)
    {
        button.setPosition(sf::Vector2f(60.f, offset_y));
        offset_y += 60.f;
    }
    texture_buttons.at(0).setSelected(true);

    save_button.setString("SAVE", 35U);
    save_button.setPosition(sf::Vector2f(260.f, 630.f));
}

void OptionState::processInput()
{
    sf::Event event;
    using namespace Engine;

    while (context->window->pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            context->window->close();
        }
        else if (event.type == sf::Event::KeyPressed)
        {
            switch (event.key.code)
            {
            case sf::Keyboard::Escape:
            {
                pause();
                context->states->popState();
                break;
            }
            default:
                break;
            }
        }
        else if (event.type == sf::Event::MouseMoved)
        {
            sf::Vector2i mouse_position(sf::Mouse::getPosition(*(context->window)));

            save_button.setSelected(save_button.onButton(mouse_position));

            for (auto &button : texture_buttons)
            {
                auto flag = button.onButton(mouse_position);
                button.setSelected(flag);
            }
        }
        else if (event.type == sf::Event::MouseButtonPressed)
        {
            sf::Vector2i mouse_position(sf::Mouse::getPosition(*(context->window)));

            music_slider.setSelected(mouse_position);
            sound_slider.setSelected(mouse_position);

            for (auto button{texture_buttons.begin()};
                 button != texture_buttons.end(); ++button)
            {
                if (!button->getPressed() && button->onButton(mouse_position))
                {
                    button->setPressed(true);
                    button->setSelected(true);

                    for (auto off_button{texture_buttons.begin()};
                         off_button != texture_buttons.end(); ++off_button)
                    {
                        if (off_button != button && off_button->getSelected())
                        {
                            off_button->setPressed(false);
                            off_button->setSelected(false);
                        }
                    }
                    break;
                }
            }

            if (save_button.onButton(mouse_position))
            {
                save_button.setPressed(true);
            }
        }
    }
}

void OptionState::update(sf::Time delta_time)
{
    elapsed_time += delta_time;
    ++fps;
    if (elapsed_time.asSeconds() >= 1.0f)
    {
        //std::cout << "FPS: " << fps << std::endl;
        fps = 0;
        elapsed_time -= sf::Time(sf::seconds(1.f));
    }

    if (save_button.getPressed())
    {
        save_button.setPressed(false);
        context->assets->changeMusicVolume(music_slider.getAmountSelected() * 10);
        context->assets->changeSoundVolume(sound_slider.getAmountSelected() * 10);
        pause();
        context->states->popState();
    }
}

void OptionState::draw()
{
    context->window->clear(Engine::Colors::background);
    for (auto &title : titles)
    {
        title.draw(*(context->window));
    }
    music_slider.draw(*(context->window));
    sound_slider.draw(*(context->window));
    for (auto &button : texture_buttons)
    {
        button.draw(*(context->window));
    }
    save_button.draw(*(context->window));
    context->window->display();
}

void OptionState::pause()
{
    context->assets->pauseMusic(Engine::MusicID::Title_Music);
}

void OptionState::launch()
{
    context->assets->playMusic(Engine::MusicID::Title_Music);
}