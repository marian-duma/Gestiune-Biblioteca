#include <SFML/Graphics.hpp>
#include <iostream>
#include "src/abonat.h"
#include "src/carte.h"
#include "src/exceptie.h"
#include "gui/button.h"
#include "gui/text_input.h"
#include "gui/meniu_abonati.h"
#include "gui/meniu_carti.h"
#include "gui/meniu_gestiune.h"

using namespace std;

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Main");
    sf::Font font; font.loadFromFile("gui/Arial.ttf");
    //sf::View view;

    // view.setCenter(400.f, 300.f);
    // view.setSize(800.f, 600.f);
    // window.setView(view); 
    
    Button abonati = Button(default_param(0), "Optiuni abonati");
    Button carti = Button(default_param(1), "Optiuni carti");
    Button gestiune = Button(default_param(2), "Imprumut/retur");
    Button exit = Button(default_param(3), "Exit");
    
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) 
            {
                    if(abonati.isClicked(sf::Mouse::getPosition(window)))
                    {
                        window.setActive(false);
                        open_meniu_abonati();
                    }
                    if(carti.isClicked(sf::Mouse::getPosition(window)))
                    {
                        window.setActive(false);
                        open_meniu_carti();
                    }
                    if(gestiune.isClicked(sf::Mouse::getPosition(window)))
                    {
                        window.setActive(false);
                        open_meniu_gestiune();
                    }
                    if(exit.isClicked(sf::Mouse::getPosition(window)))
                    {
                        window.close();
                    }
            }
            if (window.isOpen()) {
                window.clear(sf::Color(51, 51, 51));
                
                abonati.draw(window);
                carti.draw(window);
              
                gestiune.draw(window);
                exit.draw(window);
                
                window.display();
            }
        }
    }
    return 0;
}