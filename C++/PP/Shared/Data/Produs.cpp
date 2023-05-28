#ifndef LIBS
#define LIBS
#include <iostream>
#include <string>
#include <string.h>
#endif

#ifndef PRODUSH
#define PRODUSH
#include "Produs.h"
#endif

void Produs::init(const std::string cod_de_bare, const std::string denumire, const int cantitate, const double pret, const Categorie& categorie){
    this -> cod_de_bare = cod_de_bare;
    this -> denumire = denumire;
    this -> cantitate = cantitate;
    this -> pret = pret;
    if(this -> categorie){
        delete this -> categorie;
    }
    this -> categorie = new Categorie(categorie);
}

Produs::Produs(const std::string cod_de_bare, const std::string denumire, const int cantitate, const double pret, const Categorie& categorie){
    this -> init(cod_de_bare, denumire, cantitate, pret, categorie);
}

Produs::Produs(const Produs& p){
    this -> init(p.cod_de_bare, p.denumire, p.cantitate, p.pret, *(p.categorie));
}

Produs::~Produs(){
    delete categorie;
}

Produs Produs::operator=(const Produs& p){
    this -> init(p.cod_de_bare, p.denumire, p.cantitate, p.pret, *(p.categorie));
    return *this;
}

std::ostream& operator<<(std::ostream& stream, const Produs& p){
    stream << p.denumire;
    return stream;
}

std::ifstream& operator>>(std::ifstream& stream, Produs *p){
    
    return stream; //tbc
}
