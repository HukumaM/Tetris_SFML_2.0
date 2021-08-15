#include "Button.hpp"
#include <algorithm>

Button::Button(const sf::Vector2f &size)
    : rectangle(size)
{
    rectangle.setFillColor(Engine::Colors::button);
    rectangle.setOutlineColor(sf::Color::Black);
    rectangle.setOutlineThickness(-2.f);
    setPosition(sf::Vector2f(0.f, 0.f));
}

void Button::setSize(const sf::Vector2f &size)
{
    rectangle.setSize(size);
}

void Button::setPosition(const sf::Vector2f &position)
{
    auto rect_origin = rectangle.getGlobalBounds();
    rectangle.setOrigin(rect_origin.width / 2, rect_origin.height / 2);
    rectangle.setPosition(position);
}

void Button::setRectangleFillColor(const sf::Color &color)
{
    rectangle.setFillColor(color);
}

void Button::setRectangleOutlineColor(const sf::Color &color)
{
    rectangle.setOutlineColor(color);
}

void Button::setRectangleOutlineThickness(float thickness)
{
    rectangle.setOutlineThickness(thickness);
}

void Button::setTexture(const sf::Texture *texture)
{
    rectangle.setTexture(texture);
}

void Button::setSelected(bool state)
{
    auto size = getSize();
    if (state && selected != state)
    {
        setRectangleFillColor(Engine::Colors::selected_button);
        setSize(sf::Vector2f(size.x * SCALE_SELECTED, size.y * SCALE_SELECTED));
    }
    else if (!state && selected != state)
    {
        setRectangleFillColor(Engine::Colors::button);
        setSize(sf::Vector2f(size.x * SCALE_UNSELECTED, size.y * SCALE_UNSELECTED));
    }
    
    selected = state;
}

void Button::setPressed(bool state)
{
    pressed = state;
}

bool Button::onButton(const sf::Vector2i &mouse_position) const
{
    sf::IntRect mouse(mouse_position, sf::Vector2i(1, 1));
    sf::IntRect button(
        getPosition().x - getSize().x / 2,
        getPosition().y - getSize().y / 2,
        getSize().x,
        getSize().y);

    return mouse.intersects(button);
}

void Button::draw(sf::RenderWindow &window)
{
    window.draw(rectangle);
}

////////////////////////////////////////////////////////////////

TextButton::TextButton(const sf::Font &font, const sf::Vector2f &size)
    : Button(size), text(font)
{
    setRectangleFillColor(Engine::Colors::button);
    setRectangleOutlineColor(sf::Color::Black);
    setRectangleOutlineThickness(-2.f);
}

void TextButton::setString(const sf::String &string, unsigned int size)
{
    text.setString(string, size);
}

void TextButton::setCharacterSize(unsigned int size)
{
    text.setCharacterSize(size);
}

void TextButton::setTextFillColor(const sf::Color &color)
{
    text.setFillColor(color);
}

void TextButton::setTextOutlineColor(const sf::Color &color)
{
    text.setOutlineColor(color);
}

void TextButton::setTextOutlineThickness(float thickness)
{
    text.setOutlineThickness(thickness);
}

void TextButton::setSize(const sf::Vector2f &size)
{
    auto position = getPosition();
    Button::setSize(size);
    setPosition(position);
}

void TextButton::setPosition(const sf::Vector2f &position)
{
    Button::setPosition(position);
    text.setPosition(position);
}

void TextButton::setSelected(bool state)
{
    Button::setSelected(state);
    auto character_size = text.getCharacterSize();
    if (state && getSelected() != state)
    {
        text.setCharacterSize(character_size + 2);
    }
    else if (!state && getSelected() != state)
    {
        text.setCharacterSize(character_size - 2);
    }
}

void TextButton::draw(sf::RenderWindow &window)
{
    Button::draw(window);
    text.draw(window);
}

////////////////////////////////////////////////////////////////

Slider::Slider(unsigned size_slider, const sf::Vector2f &size_button)
    : slider(size_slider, Button(size_button))
{
}

void Slider::setPosition(const sf::Vector2f &position)
{
    if (slider.size() < 1)
        return;
    if (slider.size() % 2)
    {
        auto middle = slider.size() / 2;
        auto offset{slider.at(0).getSize().x};

        slider.at(middle).setPosition(position);

        for (size_t i{1}; i < slider.size() / 2 + 1; ++i)
        {
            slider.at(middle - i).setPosition(sf::Vector2f(position.x - offset, position.y));
            slider.at(middle + i).setPosition(sf::Vector2f(position.x + offset, position.y));
            offset += slider.at(0).getSize().x;
        }

        // auto middle_ = std::next(slider.begin(), slider.size() / 2);
        // auto global_offset = middle_->getSize().x * (slider.size() / 2);
        // auto local_offset = middle_->getSize().x;
        // middle_->setPosition(position);
        // std::for_each(slider.begin(), middle_,
        //               [&global_offset, local_offset, position](auto &button) mutable
        //               {
        //                   button.setPosition(sf::Vector2f(position.x - global_offset, position.y));
        //                   global_offset -= local_offset;
        //               });
        // std::for_each(std::next(middle_), slider.end(),
        //               [&global_offset, local_offset, position](auto &button) mutable
        //               {
        //                   button.setPosition(sf::Vector2f(position.x + global_offset, position.y));
        //                   global_offset += local_offset;
        //               });
    }
    else
    {
        auto left = (slider.size() / 2) - 1;
        auto right = slider.size() / 2;
        auto offset{slider.at(0).getSize().x / 2};
        for (size_t i{0}; i < slider.size() / 2; ++i)
        {
            slider.at(left - i).setPosition(sf::Vector2f(position.x - offset, position.y));
            slider.at(right + i).setPosition(sf::Vector2f(position.x + offset, position.y));
            offset += slider.at(0).getSize().x;
        }

        // auto left = std::next(slider.begin(), slider.size() / 2 - 1);
        // auto right = std::next(slider.begin(), slider.size() / 2);
        // auto global_offset = left->getSize().x / 2;
        // auto local_offset = left->getSize().x / 2;
        // std::for_each(slider.begin(), left,
        //               [global_offset, local_offset, position](auto &button) mutable
        //               {
        //                   button.setPosition(sf::Vector2f(position.x - local_offset, position.y));
        //                   global_offset += local_offset;
        //               });
        // std::for_each(std::next(middle_), slider.end(),
        //               [&global_offset, local_offset, position](auto &button) mutable
        //               {
        //                   button.setPosition(sf::Vector2f(position.x + global_offset, position.y));
        //                   global_offset += local_offset;
        //               });
    }
}

void Slider::setPressed(bool state)
{
    state = false;
}

void Slider::setSelected(const sf::Vector2i &mouse_position)
{
    auto border = std::find_if(slider.begin(), slider.end(),
                               [mouse_position](auto &button)
                               { return button.onButton(mouse_position); });
    if (border != slider.end())
    {
        std::for_each(slider.begin(), std::next(border),
                      [](auto &button)
                      {
                          if (!button.getSelected())
                          {
                              button.setSelected(true);
                              button.setPressed(true);
                          }
                      });

        std::for_each(std::next(border), slider.end(),
                      [](auto &button)
                      {
                          if (button.getSelected())
                          {
                              button.setSelected(false);
                              button.setPressed(false);
                          }
                      });
    }

    // auto selection_position{slider.begin()};
    // for (auto button{slider.begin()}; button != slider.end(); ++button)
    // {
    //     if (button->onButton(mouse_position))
    //     {
    //         selection_position = button;
    //         while (selection_position != slider.end())
    //         {
    //             selection_position->setSelected(true);
    //             selection_position->setPressed(true);
    //             ++selection_position;
    //         }
    //         while (button != slider.end())
    //         {
    //             button->setSelected(false);
    //             button->setPressed(true);
    //             ++button;
    //         }
    //         break;
    //     }
    // }
}

bool Slider::onButton(const sf::Vector2i &mouse_position) const
{
    return std::any_of(slider.begin(), slider.end(),
                       [&mouse_position](auto const &button)
                       { return button.onButton(mouse_position); });
    // for (auto &button : slider)
    // {
    //     if (button.onButton(mouse_position))
    //         return true;
    // }
    // return false;
}

unsigned Slider::getAmountSelected() const
{
    // unsigned amount{0};
    // for (auto &button : slider)
    // {
    //     if (button.getSelected())
    //         ++amount;
    // }
    return std::count_if(slider.begin(), slider.end(), [](auto const &button)
                         { return button.getSelected(); });
    //return amount;
}

void Slider::draw(sf::RenderWindow &window)
{
    std::for_each(slider.begin(), slider.end(), [&window](auto &button)
                  { button.draw(window); });
    // for (auto &button : slider)
    // {
    //     button.draw(window);
    // }
}

// void Button::setStandartSettings()
// {
//     text.setStyle(sf::Text::Style::Bold);
//     text.setFillColor(Engine::Colors::letter);
//     text.setOutlineColor(sf::Color::Black);
//     text.setOutlineThickness(-1.f);
//     rectangle.setFillColor(Engine::Colors::button);
//     rectangle.setOutlineColor(sf::Color::Black);
//     rectangle.setOutlineThickness(-2.f);
// }

// void Button::setSize(const sf::Vector2f &size)
// {
//     auto position = rectangle.getPosition();
//     rectangle.setSize(size);
//     setPosition(position);
// }
// void Button::setPosition(const sf::Vector2f &position)
// {
//     auto rect_origin = rectangle.getGlobalBounds();
//     auto text_origin = text.getGlobalBounds();

//     rectangle.setOrigin(rect_origin.width / 2, rect_origin.height / 2);
//     text.setOrigin(text_origin.width / 2, text_origin.height / 1.5f);

//     rectangle.setPosition(position);
//     text.setPosition(position);
// }

// void Button::setSelected()
// {
//     selected = true;

//     setCharacterSize(text.getCharacterSize() + 2U);
//     setFillColor(Engine::Colors::selected_button);

//     auto size = getSize();
//     setSize(sf::Vector2f(1.05f * size.x, 1.05f * size.y));
// }
// void Button::setUnselected()
// {
//     selected = false;

//     setCharacterSize(text.getCharacterSize() - 2U);
//     setFillColor(Engine::Colors::button);

//     auto size = getSize();
//     setSize(sf::Vector2f(0.95f * size.x, 0.95f * size.y));
// }

// void Button::setPressed(bool state)
// {
//     pressed = state;
// }
// bool Button::isPressed() const
// {
//     return pressed;
// }

// [[maybe_unused]] const bool
// Button::onButton(const sf::Vector2i &mouse_position) const
// {
//     sf::IntRect mouse(mouse_position, sf::Vector2i(1, 1));
//     sf::IntRect button(
//         getPosition().x - getSize().x / 2,
//         getPosition().y - getSize().y / 2,
//         getSize().x,
//         getSize().y);

//     return mouse.intersects(button);
// }

// void Button::setFillColor(const sf::Color &color)
// {
//     rectangle.setFillColor(color);
// }
// void Button::setOutlineColor(const sf::Color &color)
// {
//     rectangle.setOutlineColor(color);
// }
// void Button::setOutlineThickness(float thickness)
// {
//     rectangle.setOutlineThickness(thickness);
// }
