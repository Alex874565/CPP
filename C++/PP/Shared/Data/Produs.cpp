#ifndef LIBS
#define LIBS
#include <iostream>
#include <string>
#include <string.h>
#endif

#include <fstream>
#include <cstdlib>

#ifndef PRODUSH
#define PRODUSH
#include "Produs.h"
#endif

void Produs::init(const std::string cod_de_bare, const std::string denumire, const int cantitate, const double pret, const Categorie& categorie){
    this -> cod_de_bare = cod_de_bare;
    this -> denumire = denumire;
    this -> cantitate = cantitate;
    this -> pret = pret;
    if(this -> categorie != NULL){
        delete this -> categorie;
    }
    this -> categorie = new Categorie(categorie);
}

Produs::Produs(const std::string cod_de_bare, const std::string denumire, const int cantitate, const double pret, const Categorie& categorie){
    this -> categorie = NULL;
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

int operator>>(std::ifstream& stream, Produs &p){
    char *str = new char[50];
    if(stream.getline(str, 50)){
        p.setCodDeBare(strtok(str, " "));
        p.setDenumire(strtok(NULL, " "));
        p.setCantitate((int)std::strtol(strtok(NULL, " "), NULL, 10));
        p.setPret(std::strtod(strtok(NULL, " "), NULL));
        p.setCategorie(Categorie(strtok(NULL, " ")));
        return 1;
    }else{
        return 0;
    }
}
