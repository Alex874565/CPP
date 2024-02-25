#ifndef LIBS
#define LIBS
#include <iostream>
#include <string>
#include <string.h>
#include <fstream>
#include <assert.h>
#include <stdlib.h>

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

/*std::ostream& operator<<(std::ostream& stream, const Produs& p){
    stream << "{ "<<  p.getDenumire() << ", " << p.getPret() << " lei" << ", cantitate in stoc: " << p.getCantitate() << " }";
    return stream;
}*/

template <typename T> T& operator>>(T& stream, Produs& p){
    //asta o implementase-si tu Carpi doar ca ai uitat sa incluzie
    //relatia de friend si in prototipul clasei :))
    char *str = new char[100];
    if(stream.getline(str, 100) && strcmp(str, "") != 0){
        char *token = strtok(str, ";");
        p.setCodDeBare(token);
        token = strtok(NULL, ";");
        p.denumire = token;
        token = strtok(NULL, ";");
        p.cantitate = (int)std::strtol(token, NULL, 10);
        token = strtok(NULL, ";");
        p.pret = std::strtod(token, NULL);
        token = strtok(NULL, ";");
        p.categorie = new Categorie(token);
        return stream;
    }else{

        return stream;
    }
}

std::string& operator>>(std::string& stream, Produs& p){
    //asta o implementase-si tu Carpi doar ca ai uitat sa incluzie
    //relatia de friend si in prototipul clasei :))
    if(stream != ""){
        char *token;
        strcpy(token, stream.c_str());
        token = strtok(token, ";");
        p.cod_de_bare = token;
        token = strtok(NULL, ";");
        p.denumire = token;
        token = strtok(NULL, ";");
        p.cantitate = (int)std::strtol(token, NULL, 10);
        token = strtok(NULL, ";");
        p.pret = std::strtod(token, NULL);
        token = strtok(NULL, ";");
        p.categorie = new Categorie(token);
        return stream;
    }else{

        return stream;
    }
}

/*std::ofstream& operator<<(std::ofstream& stream, const Produs &p){
    stream << p.getCodDeBare() <<";" <<p.getDenumire() <<";"<<p.getCantitate()<<";"<<p.getPret()<<";"<<p.getCategorie()->getDenumire();
    return stream;
}*/

template <typename T> T& operator<<(T& stream, const Produs& p){
    stream << p.getCodDeBare().c_str() << ";" << p.denumire << ";" << p.cantitate << ";" << p.pret << ";" << p.categorie->getDenumire();
    return stream;
}

template <typename T> T& operator>>(T& is, Produs_Simplu& p) {
    char *str = new char[100];
    if(is.getline(str, 100) && strcmp(str, "") != 0){
        char *token = strtok(str, ";");
        p.setCodDeBare(token);
        token = strtok(NULL, ";");
        p.cantitate = (int)std::strtol(token, NULL, 10);
        return is;
    }else{

        return is;
    }
}

template <typename T> T& operator<<(T& os, const Produs_Simplu& p) {
    os << p.getCodDeBare().c_str() << ";" << p.getCantitate();
    return os;
}

