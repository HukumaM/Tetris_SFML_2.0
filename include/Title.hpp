#pragma once

#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include "AssetManager.hpp"

class Title
{
private:
    sf::Text text;
    
public:
    Title(const sf::Font &font);

    void setString(const sf::String &string, unsigned int size = 30U);
    void setCharacterSize(unsigned int size = 30U);
    void setScale(const sf::Vector2f &factors);

    void setPosition(const sf::Vector2f &position);

    void setFillColor(const sf::Color &color);
    void setOutlineColor(const sf::Color &color);
    void setOutlineThickness(float thickness);

    void draw(sf::RenderWindow &window);

public:
    const sf::Vector2f &getPosition() const;
    unsigned int getCharacterSize() const;
};