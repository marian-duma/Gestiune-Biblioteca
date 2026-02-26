#ifndef FUNCTII_H
#define FUNCTII_H
#include <SFML/Graphics.hpp>
#include "../gui/text_input.h"
#include "abonat.h"
#include "carte.h"
#include "admin.h"
#include "exceptie.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

void update(vector<text_input> prompt, abonat& Abonat);
void update(vector<text_input> prompt, carte& Carte);

void get_info(vector<text_input> prompt, string& info);
void get_info_carte(vector<text_input> prompt, string& info);
vector<string> split(string str);
string str_to_upper(string str);
bool isNumber(string s);
//Functii pentru interfata grafica
void afisare_mesaj(sf::RenderWindow& window, sf::Font& font, string mesaj);
string get_lista_carti(abonat Abonat, admin Admin);

void afisare_abonat(sf::RenderWindow& window, sf::Font& font, abonat& a);
void afisare_carte(sf::RenderWindow& window, sf::Font& font, carte& c);

void imprumuta_carte(abonat Abonat, carte Carte);
void returneaza_carte(abonat Abonat, carte Carte);
#endif //FUNCTII_H