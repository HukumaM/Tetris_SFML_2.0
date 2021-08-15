#pragma once

#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

#include "Title.hpp"
#include "AssetManager.hpp"

class Button
{
private:
    sf::RectangleShape rectangle;

protected:
    bool selected{false};
    bool pressed{false};

    const float SCALE_SELECTED = 1.25f;
    const float SCALE_UNSELECTED = 0.8f;

public:
    Button(const sf::Vector2f &size);

public:
    void setRectangleFillColor(const sf::Color &color);
    void setRectangleOutlineColor(const sf::Color &color);
    void setRectangleOutlineThickness(float thickness);

    void setTexture(const sf::Texture *texture);

    virtual void setSize(const sf::Vector2f &size);
    virtual void setPosition(const sf::Vector2f &position);

    void setPressed(bool state);
    virtual void setSelected(bool state);

    bool onButton(const sf::Vector2i &mouse_position) const;

public:
    inline const sf::Vector2f &getSize() const
    {
        return rectangle.getSize();
    }
    inline const sf::Vector2f &getPosition() const
    {
        return rectangle.getPosition();
    }
    inline bool getSelected() const
    {
        return selected;
    }
    inline bool getPressed() const
    {
        return pressed;
    }

public:
    virtual void draw(sf::RenderWindow &window);
};

class TextButton final : public Button
{
private:
    Title text;

public:
    TextButton(const sf::Font &font, const sf::Vector2f &size = sf::Vector2f());

public:
    void setString(const sf::String &string, unsigned int size = 30U);
    void setCharacterSize(unsigned int size = 30U);

    void setTextFillColor(const sf::Color &color);
    void setTextOutlineColor(const sf::Color &color);
    void setTextOutlineThickness(float thickness);

    virtual void setSize(const sf::Vector2f &size) override;
    virtual void setPosition(const sf::Vector2f &position) override;

    virtual void setSelected(bool state) override;

public:
    virtual void draw(sf::RenderWindow &window) override;
};

class Slider final
{
private:
    std::vector<Button> slider;

public:
    Slider(unsigned size_slider, const sf::Vector2f &size_button);

public:
    void setPosition(const sf::Vector2f &position);
    void setPressed(bool state);
    void setSelected(const sf::Vector2i &mouse_position);
    bool onButton(const sf::Vector2i &mouse_position) const;

public:
    unsigned getAmountSelected() const;

public:
    void draw(sf::RenderWindow &window);
};

// class Button
// {
// private:
//     Title text;
//     sf::RectangleShape rectangle;

// private:
//     bool selected{false};
//     bool pressed{false};
//     void setStandartSettings();

// public:
//     Button();
//     Button(const sf::Font &font);
//     Button(const sf::Vector2f &size, bool select = false);
//     Button(const sf::Vector2f &size, const sf::Vector2f &position);

//     void setFont(const sf::Font &font);
//     void setString(const sf::String &string);
//     void setCharacterSize(uint16_t size);

//     void setSize(const sf::Vector2f &size);
//     void setPosition(const sf::Vector2f &position);

//     const sf::Vector2f &getSize() const;
//     const sf::Vector2f &getPosition() const;

//     bool isSelected() const;
//     void setSelected();
//     void setUnselected();

//     void setPressed(bool state);
//     bool isPressed() const;

//     [[maybe_unused]] const bool
//     onButton(const sf::Vector2i &mouse_position) const;

//     void setFillColor(const sf::Color &color);
//     void setOutlineColor(const sf::Color &color);
//     void setOutlineThickness(float thickness);

//     void Draw(sf::RenderWindow &window);
// };