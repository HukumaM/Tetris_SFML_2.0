//#include <iostream>

#include <iostream>
#include <cassert>

#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>

#include "MenuState.hpp"
//#include "OptionProcess.hpp"
//#include "PlayProcess.hpp"
//#include "PvP.hpp"

MenuState::MenuState(std::shared_ptr<Context> &context)
    : context(context),
      game_title(context->assets->getFont(Engine::FontID::Title_Font)),
      buttons(4, TextButton(context->assets->getFont(Engine::FontID::Title_Font))),
      selected_button(buttons.begin())
{
}

void MenuState::init()
{
    auto window_size = static_cast<sf::Vector2f>(context->window->getSize());

    context->assets->playMusic(Engine::MusicID::Title_Music);

    game_title.setString("TETRIS", 150U);
    game_title.setPosition(sf::Vector2f(window_size.x / 2.f, window_size.y / 6.f));
    game_title.setOutlineThickness(-5.f);

    buttons.at(ButtonName::Single_Player).setString("SINGLE PLAYER", 28U);
    buttons.at(ButtonName::Single_Player).setSize(sf::Vector2f(180.f, 60.f));
    buttons.at(ButtonName::Single_Player).setPosition(sf::Vector2f(window_size.x / 2.f, window_size.y / 2.f));
    buttons.at(ButtonName::Single_Player).setSelected(true);

    selected_button = buttons.begin();

    buttons.at(ButtonName::PVP).setString("PvP", 35U);
    buttons.at(ButtonName::PVP).setSize(sf::Vector2f(180.f, 60.f));
    buttons.at(ButtonName::PVP).setPosition(sf::Vector2f(window_size.x / 2.f, 3.f * window_size.y / 5.f));

    buttons.at(ButtonName::Option).setString("OPTION", 35U);
    buttons.at(ButtonName::Option).setSize(sf::Vector2f(180.f, 60.f));
    buttons.at(ButtonName::Option).setPosition(sf::Vector2f(window_size.x / 2.f, 7.f * window_size.y / 10.f));

    buttons.at(ButtonName::Exit).setString("EXIT", 32U);
    buttons.at(ButtonName::Exit).setSize(sf::Vector2f(180.f, 60.f));
    buttons.at(ButtonName::Exit).setPosition(sf::Vector2f(window_size.x / 2.f, 4.f * window_size.y / 5.f));
}

void MenuState::processInput()
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
                context->window->close();
                break;
            }
            case sf::Keyboard::Up:
            {
                context->assets->playSound(SoundID::Selection);
                if (std::make_reverse_iterator(selected_button) != buttons.rend())
                {
                    selected_button->setSelected(false);
                    (--selected_button)->setSelected(true);
                }
                break;
            }
            case sf::Keyboard::Down:
            {
                context->assets->playSound(SoundID::Selection);
                if (std::next(selected_button) != buttons.end())
                {
                    selected_button->setSelected(false);
                    (++selected_button)->setSelected(true);
                }
                break;
            }
            case sf::Keyboard::Return:
            {
                context->assets->playSound(SoundID::Selection);
                selected_button->setPressed(true);
                break;
            }
            default:
                break;
            }
        }
        else if (event.type == sf::Event::MouseMoved)
        {
            sf::Vector2i mouse_position(sf::Mouse::getPosition(*(context->window)));

            auto button = std::find_if(buttons.begin(), buttons.end(),
                                       [&mouse_position](auto const &button)
                                       { return button.onButton(mouse_position); });

            if (button != buttons.end())
            {
                if (!button->getSelected())
                {
                    button->setSelected(true);
                }
                if (button != selected_button)
                {
                    selected_button->setSelected(false);
                    selected_button = button;
                }
            }
        }
        else if (event.type == sf::Event::MouseButtonPressed &&
                 event.mouseButton.button == sf::Mouse::Left)
        {
            sf::Vector2i mouse_position(sf::Mouse::getPosition(*(context->window)));
            auto button = std::find_if(buttons.begin(), buttons.end(),
                                       [&mouse_position](auto const &button)
                                       { return button.onButton(mouse_position); });
            if (button != buttons.end())
            {
                button->setPressed(true);
            }
        }
    }
}

void MenuState::update(sf::Time delta_time)
{
    elapsed_time += delta_time;
    ++fps;
    if (elapsed_time.asSeconds() >= 1.0f)
    {
        //std::cout << "FPS: " << fps << std::endl;
        fps = 0;
        elapsed_time -= sf::Time(sf::seconds(1.f));
    }

    // if (button.at(ButtonType::Play).pressed)
    // {
    //     std::cout << "launch playing" << std::endl;
    //     Audio::GetMusic(Audio::MAIN_MUSIC).stop();
    //     context->states->PushState(
    //         std::make_unique<PlayProcess>(context), true);
    // }
    // else if (button.at(ButtonType::PlayerVsPlayer).pressed)
    // {
    //     std::cout << "launch pvp" << std::endl;
    //     Audio::GetMusic(Audio::MAIN_MUSIC).stop();
    //     context->states->PushState(
    //         std::make_unique<PvP>(context), true);
    // }

    if (buttons.at(ButtonName::Option).getPressed())
    {
        pause();
        selected_button->setPressed(false);
        context->states->pushState(
            std::make_unique<OptionState>(context));
    }
    else if (buttons.at(ButtonName::Exit).getPressed())
    {
        context->window->close();
    }
}

void MenuState::draw()
{
    context->window->clear(Engine::Colors::background);
    game_title.draw(*(context->window));

    for (auto &button : buttons)
    {
        button.draw(*(context->window));
    }
    context->window->display();
}

void MenuState::pause()
{
    context->assets->pauseMusic(Engine::MusicID::Title_Music);
}

void MenuState::launch()
{
    context->assets->playMusic(Engine::MusicID::Title_Music);
}
