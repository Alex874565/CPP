#ifndef LIBS
#define LIBS
#include <iostream>
#include <string>
#include <string.h>
#include <fstream>

#endif

#include <cstdlib>

#ifndef PRODUSH
#define PRODUSH
#include "Produs.h"
#endif

void Produs::init(const std::string cod_de_bare, const std::string denumire, const int cantitate, const double pret, const Categorie& categorie){
    this -> setCodDeBare(cod_de_bare);
    this -> denumire = denumire;
    this -> setCantitate(cantitate);
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
    this -> init(p.getCodDeBare(), p.denumire, p.getCantitate(), p.pret, *(p.categorie));
}

Produs::~Produs(){
    delete categorie;
}

Produs Produs::operator=(const Produs& p){
    this -> init(p.getCodDeBare(), p.denumire, p.getCantitate(), p.pret, *(p.categorie));
    return *this;
}

std::ostream& operator<<(std::ostream& stream, const Produs& p){
    stream << "{ "<<  p.getDenumire() << ", " << p.getPret() << "lei" << ", cantitate in stoc: " << p.getCantitate() << " }";
    return stream;
}

std::ifstream& operator>>(std::ifstream& stream, Produs &p){
    //asta o implementase-si tu Carpi doar ca ai uitat sa incluzie
    //relatia de friend si in prototipul clasei :))
    char *str = new char[100];
    if(stream.getline(str, 100)){
        p.setCodDeBare(strtok(str, ";"));
        p.setDenumire(strtok(NULL, ";"));
        p.setCantitate((int)std::strtol(strtok(NULL, ";"), NULL, 10));
        p.setPret(std::strtod(strtok(NULL, ";"), NULL));
        p.setCategorie(Categorie(strtok(NULL, ";")));
        return stream;
    }else{

        return stream;
    }
}

std::ofstream& operator<<(std::ofstream& stream, const Produs &p){
    stream << p.getCodDeBare() <<";" <<p.getDenumire() <<";"<<p.getCantitate()<<";"<<p.getPret()<<";"<<p.getCategorie()->getDenumire();
    return stream;
}
