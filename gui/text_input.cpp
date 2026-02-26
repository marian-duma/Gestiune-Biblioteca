#include "text_input.h"

text_input::text_input(sf::Vector2f position, sf::Vector2f size, sf::Font& font, int characterSize, const std::string& labelText)
    : font(font) {
    inputBox.setPosition(position);
    inputBox.setSize(size);
    inputBox.setFillColor(sf::Color::White);
    inputBox.setOutlineThickness(1);
    inputBox.setOutlineColor(sf::Color::Black);

    inputText.setFont(font);
    inputText.setCharacterSize(characterSize);
    inputText.setFillColor(sf::Color::Black);
    inputText.setPosition(position.x + 5, position.y);
    cursor.setFillColor(sf::Color::Black);

     label.setFont(font);
     label.setString(labelText);
     label.setCharacterSize(characterSize);
     label.setFillColor(sf::Color::White);
     label.setStyle(sf::Text::Bold);
     label.setPosition(position.x, position.y - 30);
    isFocused = false;
}
void text_input::setLabel(const std::string& labelText) {
    label.setString(labelText);
}

void text_input::handleEvent(const sf::Event& event) {
    if(isFocused)
    {
    if (event.type == sf::Event::TextEntered) {
        if (event.text.unicode < 128) {
            if (event.text.unicode == 8 && !inputString.empty()) {
                inputString.pop_back();
            } else if (event.text.unicode != 13) {
                inputString += static_cast<char>(event.text.unicode);
            }
            }
        }
    }
}

void text_input::draw(sf::RenderWindow& window) {
    inputText.setString(inputString);

    if (cursorClock.getElapsedTime().asMilliseconds() > 500) {
        showCursor = !showCursor;
        cursorClock.restart();
    }

    cursor.setSize(sf::Vector2f(2, inputText.getGlobalBounds().height));
    cursor.setPosition(inputText.getPosition().x + inputText.getLocalBounds().width + 2, inputText.getPosition().y + 5);
    window.draw(inputBox);
    window.draw(inputText);
    if (isFocused && showCursor) {
        window.draw(cursor);
    }
    window.draw(label);
      
}

std::string text_input::getText() const {
    return inputString;
}

void text_input::setText(std::string str)
{
    inputString = str;
}

void text_input::setFocus(bool focus)
{
    isFocused = focus;
}

bool text_input::isMouseOver(sf::Vector2i mousePos) {
    return inputBox.getGlobalBounds().contains(sf::Vector2f(mousePos));
}