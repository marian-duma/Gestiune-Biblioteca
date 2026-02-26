#ifndef CARTE_H
#define CARTE_H

#include <string>
#include <vector>
#include <random>
using namespace std;

class carte
{
    private:
        char sep = ';';
        string titlu;
        string autor;
        string isbn;
        string editura;
        int numar_pagini;
    public:    
        carte(){}
        carte(string titlu, string autor, string editura, int numar_pagini);
        carte(vector<string> linieFisier);
        
        string get_titlu() {return this->titlu;}
        string get_autor() {return this->autor;}
        string get_editura() {return this->editura;}
        int get_numar_pagini() {return this->numar_pagini;}
        string get_isbn() {return this->isbn;}

        void set_titlu(string nume);
        void set_autor(string autor) {this->autor = autor;}
        void set_numar_pagini(const int numar_pagini);
        void set_editura(string editura) {this->editura = editura;}
        void set_isbn(string isbn) {this->isbn = isbn;}
        string carte_to_file();
        
        static string genereazaISBN();
        static int calculeazaCifraControl(string isbn);
        ~carte(){}
        
        bool operator==(const carte& other) const {
            return titlu == other.titlu && autor == other.autor;
        }
};

#endif //CARTE_H