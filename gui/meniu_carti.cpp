#include "meniu_carti.h"
#include "button.h"
#include "text_input.h"
#include "../src/carte.h"
#include "../src/admin_fisier.h"
#include "../src/functii.h"
#include <SFML/Graphics.hpp>
#include <iostream>

enum show {
    DEFAULT,
    ADD,
    SEARCH,
    EDIT,
    REMOVE,
    SHOW,
    MESAJ,
};

void open_meniu_carti() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Optiuni carti");
    sf::Font font;
    if (!font.loadFromFile("gui/Arial.ttf")) {
        std::cerr << "Eroare la incarcarea fontului.\n";
        window.close();
        return;
    }
    // Butoane
    Button add_book(default_param(0), "Adauga carte");
    Button find_book(default_param(1), "Cauta carte");
    Button modify_book(default_param(2), "Modifica carte");
    Button delete_book(default_param(3), "Elimina carte");
    Button exit(default_param(4), "Exit");

    // Campuri input
    std::vector<text_input> prompt;
    prompt.push_back(text_input(sf::Vector2f(300, 50), sf::Vector2f(200, 30), font, 20, "Titlu"));
    prompt.push_back(text_input(sf::Vector2f(300, 120), sf::Vector2f(200, 30), font, 20, "Autor"));
    prompt.push_back(text_input(sf::Vector2f(300, 190), sf::Vector2f(200, 30), font, 20, "Editura"));
    prompt.push_back(text_input(sf::Vector2f(300, 260), sf::Vector2f(200, 30), font, 20, "Nr. pagini"));

    Button submitButton(sf::Vector2f(300, 500), sf::Vector2f(200, 50), sf::Color(0, 168, 107), "Submit");

    admin_fisier admin("info/abonati.txt", "info/carti.txt");
    admin.read_all_books();
    vector<carte> carti;
    carte Carte("", "", "", 0);
    Carte.set_isbn("");
    string info;
    string mesaj;
    show stare = DEFAULT;
    for (auto& input : prompt)
        input.setFocus(false);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                if (add_book.isClicked(sf::Mouse::getPosition(window))) {
                    stare = ADD;
                    for(auto& tx: prompt) tx.setText("");
                    submitButton.setText("ADAUGA");
                }
                if (find_book.isClicked(sf::Mouse::getPosition(window))) {
                    stare = SEARCH;
                    for(auto& tx: prompt) tx.setText("");
                    submitButton.setText("CAUTA");
                }
                if (modify_book.isClicked(sf::Mouse::getPosition(window))) {
                    if(Carte.get_isbn() == "" || Carte.get_isbn() == "NECUNOSCUT")
                    {
                        mesaj = "Nu ati selectat o carte.\nUtilizati optiunea de cautare!";
                        stare = MESAJ;
                        break;
                    }
                    prompt[0].setText(Carte.get_titlu());
                    prompt[1].setText(Carte.get_autor());
                    prompt[2].setText(Carte.get_editura());
                    prompt[3].setText(to_string(Carte.get_numar_pagini()));
                    stare = EDIT;
                    submitButton.setText("SALVEAZA");
                }
                if (delete_book.isClicked(sf::Mouse::getPosition(window))) {
                    if(Carte.get_isbn() == "" || Carte.get_isbn() == "NECUNOSCUT")
                    {
                        mesaj = "Nu ati selectat o carte.\nUtilizati optiunea de cautare!";
                        stare = MESAJ;
                        break;
                    }
                    stare = REMOVE;
                    submitButton.setText("STERGE");
                }
                if (exit.isClicked(sf::Mouse::getPosition(window))) {
                    window.close();
                }

                if (submitButton.isClicked(sf::Mouse::getPosition(window))) {
                    switch (stare) {
                        case ADD:
                            for(auto& tx: prompt)
                            {
                                if(tx.getText() == "")
                                {
                                    mesaj = "Toate campurile sunt obligatorii!";
                                    stare = MESAJ;
                                    break;
                                }
                            }
                            if(stare == MESAJ){break;}    
                            Carte = admin.find_book(prompt[0].getText() + ' ' + prompt[1].getText());
                            if(Carte.get_isbn() != "NECUNOSCUT")
                            {
                                mesaj = "Nu pot exista 2 carti cu acelasi titlu si autor";
                                stare = MESAJ;
                                break;
                            }
                            Carte.set_titlu(prompt[0].getText());
                            Carte.set_autor(prompt[1].getText());
                            Carte.set_editura(prompt[2].getText());
                            if(isNumber(prompt[3].getText()))
                            {
                                Carte.set_numar_pagini(std::stoi(prompt[3].getText()));
                            }else{
                                Carte.set_numar_pagini(-1);
                            }
                            Carte.set_isbn(carte::genereazaISBN());
                            for (auto& tx : prompt) tx.setText("");
                            admin.add(Carte);
                            admin.write(Carte);
                            mesaj = "Carte adaugata cu succes!";
                            stare = MESAJ;
                            break;

                        case SEARCH:
                            Carte = admin.find_book(prompt[0].getText() + ' ' + prompt[1].getText());
                            for(auto& tx: prompt) tx.setText("");
                            if(Carte.get_isbn() == "NECUNOSCUT")
                            {
                                mesaj = "Cartea nu a fost gasita!";
                                stare = MESAJ;
                                break;
                            }
                            prompt[0].setText(Carte.get_titlu());
                            prompt[1].setText(Carte.get_autor());
                            prompt[2].setText(Carte.get_editura());
                            prompt[3].setText(to_string(Carte.get_numar_pagini()));
                            stare = SHOW;
                            break;

                        case EDIT:
                            carti = admin.get_books();
                            for(size_t i = 0; i < carti.size(); i++)
                            {
                                if(carti[i] == Carte)
                                {
                                    update(prompt, Carte);
                                    update(prompt, carti[i]);
                                    admin.set_books(carti);
                                }
                            }
                            admin.write_all_books();
                            mesaj = "Cartea a fost modificata";
                            stare = MESAJ;
                            break;

                        case REMOVE:
                            admin.remove_book(Carte.get_isbn());
                            for (auto& tx : prompt) tx.setText("");
                            admin.write_all_books();
                            mesaj = "Cartea a fost stearsa!";
                            stare = MESAJ;
                            break;

                        default:
                            stare = DEFAULT;
                            break;
                    }
                }

                bool anyInputFocused = false;
                for (auto& input : prompt) {
                    if (input.isMouseOver(sf::Mouse::getPosition(window))) {
                        input.setFocus(true);
                        anyInputFocused = true;
                    } else {
                        input.setFocus(false);
                    }
                }

                if (!anyInputFocused) {
                    for (auto& input : prompt)
                        input.setFocus(false);
                }
            }

            for (auto& input : prompt)
                input.handleEvent(event);
        }

        window.clear(sf::Color(51, 51, 51));
        add_book.draw(window);
        find_book.draw(window);
        modify_book.draw(window);
        delete_book.draw(window);
        exit.draw(window);

        
        if (stare == ADD || stare == EDIT) {
            for (text_input& tx : prompt)
                tx.draw(window);
            submitButton.draw(window);
        }
        if(stare == SEARCH)
        {
            prompt[0].draw(window);
            prompt[1].draw(window);
            submitButton.draw(window);
        }
        if (stare == SHOW) {
            afisare_carte(window, font, Carte);
        }
        if(stare == REMOVE)
        {
            afisare_carte(window, font, Carte);
            submitButton.draw(window);
        }
        if(stare == MESAJ)
        {
            afisare_mesaj(window, font, mesaj);
        }

        window.display();
    }
}
