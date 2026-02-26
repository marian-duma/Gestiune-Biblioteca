#include "abonat.h"

abonat::abonat(int id, string nume, string prenume, string nr_telefon, string email, string cnp, Judet loc)
{
    this->id = id;
    this->nume = nume;
    this->prenume = prenume;
    this->numar_telefon = nr_telefon;
    this->email = email;
    this->cnp = cnp;
    this->locul_nasterii = loc;
}

abonat::abonat(vector<string> arr)
{
    id = (int)atoi(arr[0].c_str());
    nume = arr[1];
    prenume = arr[2];
    numar_telefon = arr[3];
    email = arr[4];
    cnp = arr[5];
    locul_nasterii = stringToJudet(arr[6]);
}

string abonat::abonat_to_file()
{
    return to_string(id) + sep + nume + sep + prenume + sep +
    numar_telefon + sep + email + sep + cnp + sep + judetToString(locul_nasterii) + sep + '\n';
}