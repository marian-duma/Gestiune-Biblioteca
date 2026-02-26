#include "meniu_gestiune.h"
#include <SFML/Graphics.hpp>
#include "../src/admin_fisier.h"
#include "../src/functii.h"
#include "button.h"
#include "text_input.h"

enum show {
    DEFAULT,
    LEND,
    RETURN,
    STATUS,
    SHOW,
};

void open_meniu_gestiune()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Optiuni gestiune");
    sf::Font font; 
    font.loadFromFile("gui/Arial.ttf");
    
    Button imprumut_carti = Button(default_param(0), "Imprumuta");
    Button retur_carti = Button(default_param(1), "Returneaza");
    Button situatie_abonat = Button(default_param(2), "Situatie");
    Button exit = Button(default_param(3), "Exit");

    text_input txId(sf::Vector2f(300, 50), sf::Vector2f(200, 30), font, 20, "Id abonat");
    text_input txCarte(sf::Vector2f(300, 120), sf::Vector2f(200, 30), font, 20, "Titlu sau ISBN carte");
    Button submitButton(sf::Vector2f(300, 170), sf::Vector2f(200, 50), sf::Color(0, 168, 107), "Submit");
    
    submitButton.OffsetText();
    sf::Text Nume;
    
    vector<sf::Text> txCarti;
    sf::Text tempCarte;

    admin_fisier admin("info/abonati.txt", "info/carti.txt");
    admin.read_all_readers();
    admin.read_all_books();
    string nume_fisier_imprumut;
    string info_abonat, info_carte;
    show stare = DEFAULT;

    string mesaj;
    abonat Abonat;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
            {
                if(imprumut_carti.isClicked(sf::Mouse::getPosition(window)))
                {
                    stare= LEND;
                    submitButton.setText("IMPRUMUTA");
                }
                if(retur_carti.isClicked(sf::Mouse::getPosition(window)))
                {
                    stare = RETURN;
                    submitButton.setText("RETURNEAZA");
                }
                if(situatie_abonat.isClicked(sf::Mouse::getPosition(window)))
                {
                    stare = STATUS;
                    submitButton.setText("AFISEAZA");
                }
                if(exit.isClicked(sf::Mouse::getPosition(window))) window.close();
            
                if (submitButton.isClicked(sf::Mouse::getPosition(window)))
                {
                    switch(stare) {
                    case LEND:
                        if(txId.getText() == "" || txCarte.getText() == "")
                        {
                            mesaj = "Toate campurile sunt obligatorii!";
                            stare = SHOW;
                            break;
                        }
                        info_abonat = txId.getText();
                        info_carte = txCarte.getText();

                        if(admin.find_abonat(info_abonat).get_nume() == "NECUNOSCUT")
                        {
                            mesaj = "Acest abonat nu este inregistrat!";
                            stare = SHOW;
                            break;
                        }

                        if(admin.find_book(info_carte).get_isbn() == "NECUNOSCUT")
                        {
                            mesaj = "Acesta carte nu este inregistrata!";
                            stare = SHOW;
                            break;
                        }
                        imprumuta_carte(admin.find_abonat(info_abonat), admin.find_book(info_carte));
                        txId.setText("");
                        txCarte.setText("");
                        mesaj = "Imprumut realizat cu succes!";
                        stare = SHOW;
                        break;
                    case RETURN:
                    if(txId.getText() == "" || txCarte.getText() == "")
                        {
                            mesaj = "Toate campurile sunt obligatorii!";
                            stare = SHOW;
                            break;
                        }
                        info_abonat = txId.getText();
                        info_carte = txCarte.getText();
                        
                        if(admin.find_abonat(info_abonat).get_nume() == "NECUNOSCUT")
                        {
                            stare = SHOW;
                            mesaj = "Acest abonat nu este inregistrat!";
                            break;
                        }
                        
                        if(admin.find_book(info_carte).get_titlu() == "NECUNOSCUT")
                        {
                            stare = SHOW;
                            mesaj = "Aceasta carte nu este inregistrata!";
                            break;
                        }

                        returneaza_carte(admin.find_abonat(info_abonat), admin.find_book(info_carte));
                        
                        txId.setText("");
                        txCarte.setText("");

                        mesaj = "Returnarea cartii a fost efectuata cu succes";
                        stare = SHOW;
                        
                        break;
                    case STATUS:
                        stare = SHOW;    
                        Abonat = admin.find_abonat(txId.getText());
                        if(Abonat.get_cnp() == "NECUNOSCUT")
                        {
                            mesaj = "Acest abonat nu este inregistrat!";
                            break;
                        }
                        if(txId.getText() == "")
                        {
                            mesaj = "Introduceti un ID!";
                            break;
                        }
                        mesaj = "Cartile imprumutate de " + Abonat.get_nume() + ' ' + Abonat.get_prenume() + " sunt:\n";
                        mesaj += get_lista_carti(Abonat, admin);
                        break;
                    default:
                        break;
                    }
            
                }
            
        }
            if (txId.isMouseOver(sf::Mouse::getPosition(window)) && 
            event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
            {
                txId.setFocus(true);
                txCarte.setFocus(false);
            }
            if (txCarte.isMouseOver(sf::Mouse::getPosition(window)) && 
            event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
            {
                txId.setFocus(false);
                txCarte.setFocus(true);
            }

            txId.handleEvent(event);
            txCarte.handleEvent(event);

        window.clear(sf::Color(51, 51, 51));



        if(stare == LEND || stare == RETURN)
        {
            txId.draw(window);
            submitButton.draw(window);
            txCarte.draw(window);
        }

        if(stare == STATUS)
        {
            txId.draw(window);
            submitButton.draw(window);
        }

        if(stare == SHOW)
        {
            txId.setText("");
            txCarte.setText("");
            afisare_mesaj(window, font, mesaj);
        }

        imprumut_carti.draw(window);
        retur_carti.draw(window);
        situatie_abonat.draw(window);
        exit.draw(window);

        window.display();
        }
    }
}