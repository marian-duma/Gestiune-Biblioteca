#include "carte.h"

carte::carte(string titlu, string autor, string editura, int numar_pagini)
{
    this->isbn = genereazaISBN();
    this->titlu = titlu;
    this->autor = autor;
    this->editura = editura;
    this->numar_pagini = numar_pagini;
}

carte::carte(vector<string> arr)
{
    isbn = arr[0];
    titlu = arr[1];
    autor = arr[2];
    editura = arr[3];
    numar_pagini = (int)atoi(arr[4].c_str());
}

string carte::carte_to_file()
{
    return isbn + sep + titlu + sep + autor + sep + editura +
           sep + to_string(numar_pagini) + sep + '\n';

}

void carte::set_titlu(string titlu)
{
    if(titlu.empty()) return;
    this->titlu = titlu;
}

void carte::set_numar_pagini(int numar_pagini)
{
    this->numar_pagini = numar_pagini;
}

// Functie pentru calcularea cifrei de control ISBN-13
int carte::calculeazaCifraControl(string isbn) {
    int suma = 0;

    // ISBN-13 trebuie sa aiba 12 cifre inainte de cifra de control
    for (int i = 0; i < 12; i++) {
        int cifra = isbn[i] - '0';
        if (i % 2 == 0)
            suma += cifra;       // pozitie impara (0, 2, 4...): adaugam la suma
        else
            suma += cifra * 3;   // pozitie para (1, 3, 5...): inmultim cu 3 si adaugam la suma
    }

    int rest = suma % 10;
    int cifraControl = (10 - rest) % 10;

    return cifraControl;
}

// Functie pentru generarea unui ISBN-13 valid
string carte::genereazaISBN() {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distrib(0, 9);

    string isbn = "978"; // Prefixul standard pentru ISBN-13

    // Adaugam 9 cifre random pentru a completa 12 cifre in total
    for (int i = 0; i < 9; i++) {
        isbn += to_string(distrib(gen));
    }

    // Calculeaza cifra de control pe baza primelor 12 cifre
    int cifraControl = calculeazaCifraControl(isbn);
    isbn += to_string(cifraControl); // Adauga cifra de control la final

    return isbn;
}