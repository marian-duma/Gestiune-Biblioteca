#ifndef BUTTON_H
#define BUTTON_H

#include <SFML/Graphics.hpp>
#include <string>
#define default_param(y_offset) sf::Vector2f(10, 10 + (y_offset)*70), sf::Vector2f(150, 60), sf::Color(255, 140, 0)

class Button {
    private:
        sf::RectangleShape shape;
        sf::Vector2f position;
        sf::Vector2f size;
        sf::Color color;
        sf::Font font;
        sf::Text text;
    public:
        Button(){}
        ~Button(){}
        Button(sf::Vector2f position, sf::Vector2f size, sf::Color color, std::string text);

        void setText(std::string txt);
        void draw(sf::RenderWindow& window);
        bool isClicked(sf::Vector2i mousePos);
        void OffsetText();
        
};

#endif // BUTTON_H