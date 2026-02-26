#ifndef ABONAT_H
#define ABONAT_H

#include <string>
#include <vector>
#include "enumerari.h"
#include "exceptie.h"
using namespace std;

class abonat
{
    private:
        char sep = ';';
        int id;

        string nume;
        string prenume;
        string cnp;
        Judet locul_nasterii;
        
        string numar_telefon;
        string email;
    public:
        abonat(){}
        abonat(int id, string nume, string prenume, string nr_telefon, string email, string cnp, Judet loc);
        abonat(vector<string> linieFisier);
        
        int get_id() const { return id; }
        string get_nume() const { return nume; }
        string get_prenume() const { return prenume; }
        string get_cnp() const { return cnp; }
        Judet get_loc_nastere() const { return locul_nasterii; }
        string get_numar_telefon() const { return numar_telefon; }
        string get_email() const { return email; }

        void set_nume(string nume) { this->nume = nume; }
        void set_prenume(string prenume) { this->prenume = prenume; }
        void set_id(int id) { this->id = id; }
        void set_email(string email) { this->email = email; }
        void set_telefon(string nr_telefon) { this->numar_telefon = nr_telefon; }
        void set_cnp(string cnp) { this->cnp = cnp; }
        void set_loc_nastere(Judet loc_nastere) { this->locul_nasterii = loc_nastere; }
        string abonat_to_file();
        bool operator==(const abonat& other) const {
            return id == other.id;
        }
        ~abonat(){}
};

#endif //ABONAT_H