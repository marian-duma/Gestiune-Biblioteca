#include "functii.h"
void afisare_abonat(sf::RenderWindow& window, sf::Font& font, abonat& a) {
    sf::Text textNume, textPrenume, textCNP, textLocNastere, textTelefon, textEmail;
    
    textNume.setFont(font);
    textPrenume.setFont(font);
    textCNP.setFont(font);
    textLocNastere.setFont(font);
    textTelefon.setFont(font);
    textEmail.setFont(font);

    textNume.setCharacterSize(24);
    textPrenume.setCharacterSize(24);
    textCNP.setCharacterSize(24);
    textLocNastere.setCharacterSize(24);
    textTelefon.setCharacterSize(24);
    textEmail.setCharacterSize(24);

    textNume.setFillColor(sf::Color::White);
    textPrenume.setFillColor(sf::Color::White);
    textCNP.setFillColor(sf::Color::White);
    textLocNastere.setFillColor(sf::Color::White);
    textTelefon.setFillColor(sf::Color::White);
    textEmail.setFillColor(sf::Color::White);

    textNume.setString("Nume: " + a.get_nume());
    textPrenume.setString("Prenume: " + a.get_prenume());
    textCNP.setString("CNP: " + a.get_cnp());
    textLocNastere.setString("Locul Nasterii: " + judetToString(a.get_loc_nastere()));
    textTelefon.setString("Telefon: " + a.get_numar_telefon());
    textEmail.setString("Email: " + a.get_email());

    textNume.setPosition(300, 50);
    textPrenume.setPosition(300, 100);
    textCNP.setPosition(300, 150);
    textLocNastere.setPosition(300, 200);
    textTelefon.setPosition(300, 250);
    textEmail.setPosition(300, 300);

    window.draw(textNume);
    window.draw(textPrenume);
    window.draw(textCNP);
    window.draw(textLocNastere);
    window.draw(textTelefon);
    window.draw(textEmail);
}

void afisare_carte(sf::RenderWindow& window, sf::Font& font, carte& c) {
    sf::Text textTitlu, textAutor, textEditura, textPret, textPagini, textISBN;
    textTitlu.setFont(font);
    textAutor.setFont(font);
    textEditura.setFont(font);
    textPret.setFont(font);
    textPagini.setFont(font);
    textISBN.setFont(font);

    textTitlu.setCharacterSize(24);
    textAutor.setCharacterSize(24);
    textEditura.setCharacterSize(24);
    textPret.setCharacterSize(24);
    textPagini.setCharacterSize(24);
    textISBN.setCharacterSize(24);

    textTitlu.setFillColor(sf::Color::White);
    textAutor.setFillColor(sf::Color::White);
    textEditura.setFillColor(sf::Color::White);
    textPret.setFillColor(sf::Color::White);
    textPagini.setFillColor(sf::Color::White);
    textISBN.setFillColor(sf::Color::White);

    textTitlu.setString("Titlu: " + c.get_titlu());
    textAutor.setString("Autor: " + c.get_autor());
    textEditura.setString("Editura: " + c.get_editura());
    
    textPagini.setString("Numar pagini: " + std::to_string(c.get_numar_pagini()));
    textISBN.setString("ISBN: " + c.get_isbn());

    textTitlu.setPosition(300, 50);
    textAutor.setPosition(300, 100);
    textEditura.setPosition(300, 150);
    textPret.setPosition(300, 200);
    textPagini.setPosition(300, 250);
    textISBN.setPosition(300, 300);

    window.draw(textTitlu);
    window.draw(textAutor);
    window.draw(textEditura);
    window.draw(textPret);
    window.draw(textPagini);
    window.draw(textISBN);
}

void afisare_mesaj(sf::RenderWindow& window, sf::Font& font, string mesaj)
{
    sf::Text sfMesaj;
    sfMesaj.setFont(font);
    sfMesaj.setCharacterSize(24);
    sfMesaj.setFillColor(sf::Color::White);
    sfMesaj.setString(mesaj);
    sfMesaj.setPosition(300, 50);
    window.draw(sfMesaj);
}


void update(vector<text_input> prompt, abonat& Abonat)
{
    for (size_t i = 0; i < prompt.size(); ++i) {
        if (prompt[i].getText() != "") {
            switch (i) {
                case 0:
                    Abonat.set_nume(prompt[i].getText());
                    break;
                case 1:
                    Abonat.set_prenume(prompt[i].getText());
                    break;
                case 2:
                    Abonat.set_cnp(prompt[i].getText());
                    break;
                case 3:
                    Abonat.set_loc_nastere(stringToJudet(prompt[i].getText()));
                    break;
                case 4:
                    Abonat.set_telefon(prompt[i].getText());
                    break;
                case 5:
                    Abonat.set_email(prompt[i].getText());
                    break;
                default:
                    break;
            }

        }
    }
}

void update(vector<text_input> prompt, carte& Carte)
{
    for (size_t i = 0; i < prompt.size(); ++i) {
        if (!prompt[i].getText().empty()) {
            switch (i) {
                case 0:
                    Carte.set_titlu(prompt[i].getText());
                    break;
                case 1:
                    Carte.set_autor(prompt[i].getText());
                    break;
                case 2:
                    Carte.set_editura(prompt[i].getText());
                    break;
                case 3:
                    Carte.set_numar_pagini(static_cast<int>(std::stoi(prompt[i].getText())));
                    break;
                default:
                    break;
            }
        }
    }
}

void get_info(vector<text_input> prompt, string& info)
{
    string nume, prenume, data, cnp;
    nume = prompt[0].getText();
    prenume = prompt[1].getText();
    if(nume != "" && prenume != "") {
        info = nume + ' ' + prenume;
    } else{
        info = "";
    }
}

void get_info_carte(vector<text_input> prompt, string& info)
{
    for(const auto& tx: prompt)
    {
        if(tx.getText() != "") info = tx.getText();
    }
}

void imprumuta_carte(abonat Abonat, carte Carte)
{
    string nume_fisier = "info/";
    nume_fisier += Abonat.get_nume() + to_string(Abonat.get_id());
    nume_fisier += ".txt";
    ofstream fisier(nume_fisier, ios::app);
    fisier << Carte.get_isbn() << '\n'; 
    fisier.close();
}

void returneaza_carte(abonat Abonat, carte Carte)
{
    string nume_fisier = "info/";
    vector<string> carti;
    string linie;
    nume_fisier += Abonat.get_nume() + to_string(Abonat.get_id());
    nume_fisier += ".txt";
    ifstream citire(nume_fisier, ios::in);
    while(getline(citire, linie)) carti.push_back(linie);

    for(size_t i = 0; i < carti.size();)
    {
        if(carti[i] == Carte.get_isbn()) carti.erase(carti.begin() + i);
        else{
            i++;
        }
    }
    citire.close();

    ofstream scriere(nume_fisier, ios::out );

    for(string& str: carti) scriere << str + '\n';
}

string get_lista_carti(abonat Abonat, admin Admin)
{
    string mesaj = "";
    string nume_fisier = "info/";
    vector<string> carti; //vector care stocheaza isbn-ul fiecarei carti
    string linie; //o linie de fisier = 1 isbn.
    nume_fisier += Abonat.get_nume() + to_string(Abonat.get_id());
    nume_fisier += ".txt";
    carte Carte;
    ifstream citire(nume_fisier, ios::in);
    while(getline(citire, linie)) carti.push_back(linie);

    for(auto& carte: carti)
    {
        Carte = Admin.find_book(carte);
        mesaj += Carte.get_titlu() + ": " + Carte.get_autor() + '\n';
    }
    citire.close();  
    return mesaj;
}

vector<string> split(string str)
{
    vector<string> arr;
    string word = "";
    for(char ch: str)
    {
        if(ch == ';')
        {
            arr.push_back(word);
            word = "";
        }
        else
        {
            word += ch;
        }
    }
    return arr;
}

string str_to_upper(string str)
{
    string out = "";
    for(char ch: str)
    {
        out += toupper(ch);
    }
    return out;
}


bool isNumber(std::string s) {
    if (s.empty()) return false;
    for (char c : s) {
        if (!std::isdigit(static_cast<unsigned char>(c)))
            return false;
    }
    return true;
}