#include "meniu_abonati.h"
#include "button.h"
#include "text_input.h"
#include "../src/abonat.h"
#include "../src/functii.h"
#include "../src/admin_fisier.h"
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

void open_meniu_abonati() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Optiuni abonati");
    sf::Font font; 
    font.loadFromFile("gui/Arial.ttf");
    // Butoane
    Button add_abonat = Button(default_param(0), "Adauga abonat");
    Button find_abonat = Button(default_param(1), "Cauta abonat");
    Button modify_abonat = Button(default_param(2), "Modifica abonat");
    Button delete_abonat = Button(default_param(3), "Elimina abonat");
    Button exit = Button(default_param(4), "Exit");
    
    // Câmpuri de text pentru adaugare
    std::vector<text_input> prompt;
    prompt.push_back(text_input(sf::Vector2f(300, 50), sf::Vector2f(200, 30), font, 20, "Nume"));
    prompt.push_back(text_input(sf::Vector2f(300, 120), sf::Vector2f(200, 30), font, 20, "Prenume"));
    prompt.push_back(text_input(sf::Vector2f(300, 190), sf::Vector2f(200, 30), font, 20, "CNP"));
    prompt.push_back(text_input(sf::Vector2f(300, 260), sf::Vector2f(200, 30), font, 20, "Loc Nastere"));
    prompt.push_back(text_input(sf::Vector2f(300, 330), sf::Vector2f(200, 30), font, 20, "Telefon"));
    prompt.push_back(text_input(sf::Vector2f(300, 400), sf::Vector2f(200, 30), font, 20, "Email"));

    text_input id = text_input(sf::Vector2f(300, 400), sf::Vector2f(200, 30), font, 20, "ID");
    Button submitButton(sf::Vector2f(300, 500), sf::Vector2f(200, 50), sf::Color(0, 168, 107), "Submit");
    
    
    admin_fisier admin("info/abonati.txt", "info/carti.txt");
    static int nextId = 0;
    
    admin.read_all_readers();
    for(auto& a: admin.get_abonati()) nextId = a.get_id() + 1; //Obtine ultimul ID salvat + 1.
    
    vector<abonat> v;
    abonat Abonat; 
    string info;
    string mesaj;
    show stare = DEFAULT;
    // Resetăm focusul pentru câmpurile de text
    for (auto& input : prompt) {
        input.setFocus(false);
    }
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            // Tratarea click-urilor pe butoane
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                if (add_abonat.isClicked(sf::Mouse::getPosition(window))) {
                    stare = ADD;
                    for(auto& tx: prompt) tx.setText("");
                    submitButton.setText("ADAUGA");
                }
                if(find_abonat.isClicked(sf::Mouse::getPosition(window))){
                    stare = SEARCH;
                    for(auto& tx: prompt) tx.setText("");
                    submitButton.setText("CAUTA");
                }
                if(modify_abonat.isClicked(sf::Mouse::getPosition(window))){
                    if(Abonat.get_cnp() == "" || Abonat.get_cnp() == "NECUNOSCUT")
                    {
                        mesaj = "Nu ati selectat un abonat.\nUtilizati optiunea de cautare!";
                        stare = MESAJ;
                        break;
                    }
                    prompt[0].setText(Abonat.get_nume());
                    prompt[1].setText(Abonat.get_prenume());
                    prompt[2].setText(Abonat.get_cnp());
                    prompt[3].setText(judetToString(Abonat.get_loc_nastere()));
                    prompt[4].setText(Abonat.get_numar_telefon());
                    prompt[5].setText(Abonat.get_email());
                    stare = EDIT;
                    submitButton.setText("SALVEAZA");
                }
                if(delete_abonat.isClicked(sf::Mouse::getPosition(window))){
                    if(Abonat.get_cnp() == "" || Abonat.get_cnp() == "NECUNOSCUT")
                    {
                        mesaj = "Nu ati selectat un abonat.\nUtilizati optiunea de cautare!";
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
                    switch(stare) {
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
                            Abonat = admin.find_abonat(prompt[2].getText()); //cautare dupa CNP.
                            if(Abonat.get_cnp() != "NECUNOSCUT")
                            {
                                mesaj = "Nu pot exista 2 abonati cu acelasi CNP!";
                                stare = MESAJ;
                                break;
                            }
                            update(prompt, Abonat);
                            Abonat.set_id(nextId++);

                            for(auto& tx: prompt) tx.setText("");
                            admin.add(Abonat);
                            admin.write(Abonat);
                            mesaj = "Abonat adaugat cu succes!";
                            stare = MESAJ;
                            break;
                    
                        case SEARCH:
                            get_info(prompt, info);
                            for(auto& tx: prompt) tx.setText("");
                            Abonat = admin.find_abonat(info);
                            if(Abonat.get_cnp() == "NECUNOSCUT")
                            {
                                mesaj = "Abonatul nu a fost gasit!";
                                stare = MESAJ;
                                break;
                            }
                            prompt[0].setText(Abonat.get_nume());
                            prompt[1].setText(Abonat.get_prenume());
                            prompt[2].setText(Abonat.get_cnp());
                            prompt[3].setText(judetToString(Abonat.get_loc_nastere()));
                            prompt[4].setText(Abonat.get_numar_telefon());
                            prompt[5].setText(Abonat.get_email());
                            stare = SHOW;
                            break;
                        case EDIT:
                            v = admin.get_abonati();
                            for(size_t i = 0; i < v.size(); i++)
                            {
                                if(v[i] == Abonat)
                                {
                                    update(prompt, Abonat);
                                    update(prompt, v[1]);
                                    admin.set_abonati(v);
                                }
                            }
                            admin.write_all_readers();
                            mesaj = "Abonatul a fost modificat!";
                            stare = MESAJ;
                            break;
                        case REMOVE:
                            admin.remove_abonat(Abonat.get_cnp());
                            for(auto& tx: prompt) tx.setText("");
                            admin.write_all_readers();
                            mesaj = "Abonatul a fost sters!";
                            stare = MESAJ;
                            break;
                        default:
                            stare = DEFAULT;
                            break;
                    }
                }
                //Verifica daca am selectat un text_input pentru a introduce textul.
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
                    for (auto& input : prompt) {
                        input.setFocus(false);
                    }
                }
            }

            for (auto& input : prompt) {
                input.handleEvent(event);
            }
        }

        window.clear(sf::Color(51, 51, 51));

        add_abonat.draw(window);
        find_abonat.draw(window);
        modify_abonat.draw(window);
        delete_abonat.draw(window);
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
        if(stare == SHOW)
        {
            afisare_abonat(window, font, Abonat);
        }
        if(stare == REMOVE)
        {
            afisare_abonat(window, font, Abonat);
            submitButton.draw(window);
        }
        if(stare == MESAJ)
        {
            afisare_mesaj(window, font, mesaj);
        }
        window.display();
    }
}