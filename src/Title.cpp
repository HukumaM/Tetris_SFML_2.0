#include "Title.hpp"

Title::Title(const sf::Font &font)
    : text()
{
    text.setFont(font);
    text.setStyle(sf::Text::Style::Bold);
    text.setFillColor(Engine::Colors::letter);
    text.setOutlineColor(sf::Color::Black);
    text.setOutlineThickness(-2.f);
}

void Title::setString(const sf::String &string, unsigned int size)
{
    text.setString(string);
    text.setCharacterSize(size);
}

void Title::setCharacterSize(unsigned int size)
{
    text.setCharacterSize(size);
}

void Title::setScale(const sf::Vector2f &factors)
{
    text.setScale(factors);
    //text.scale(factors);
}

void Title::setPosition(const sf::Vector2f &position)
{
    auto text_origin = text.getGlobalBounds();
    text.setOrigin(text_origin.width / 2, text_origin.height / 1.5f);
    text.setPosition(position);
}

const sf::Vector2f &Title::getPosition() const
{
    return text.getPosition();
}

unsigned int Title::getCharacterSize() const
{
    return text.getCharacterSize();
}

void Title::setFillColor(const sf::Color &color)
{
    text.setFillColor(color);
}
void Title::setOutlineColor(const sf::Color &color)
{
    text.setOutlineColor(color);
}
void Title::setOutlineThickness(float thickness)
{
    text.setOutlineThickness(thickness);
}

void Title::draw(sf::RenderWindow &window)
{
    window.draw(text);
}
