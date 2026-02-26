#include "button.h"
#include <iostream>

Button::Button(sf::Vector2f position_, sf::Vector2f size_, sf::Color color_, std::string text_)
    : position(position_), size(size_), color(color_) {
    shape.setPosition(position);
    shape.setSize(size);
    shape.setFillColor(color);

    if (!font.loadFromFile("gui/Arial.ttf")) {
        std::cerr << "Error loading font!" << std::endl;
    }
    text.setFont(font);
    text.setCharacterSize(18);
    text.setFillColor(sf::Color::Black);
    text.setString(text_);
    text.setStyle(sf::Text::Bold);
    text.setPosition(position.x + size.x / 2 - text.getLocalBounds().width / 2,
                        position.y + size.y / 2 - text.getLocalBounds().height / 2);
}

void Button::setText(std::string txt)
{
    text.setString(txt);
}

void Button::draw(sf::RenderWindow& window) {
    window.draw(shape);
    window.draw(text);
}

bool Button::isClicked(sf::Vector2i mousePos) {
    sf::FloatRect bounds = shape.getGlobalBounds();
    return bounds.contains(static_cast<sf::Vector2f>(mousePos));
}

void Button::OffsetText()
{
    text.setPosition(position.x  + 50,
                        position.y + size.y / 2 - text.getLocalBounds().height / 2);
}