#ifndef LIBS
#define LIBS
#include <iostream>
#include <string>
#include <string.h>
#endif

#ifndef COMANDACPP
#define COMANDACPP
#include "../Shared/Data/Comanda.cpp"
#endif

#ifndef PRODUSCPP
#define PRODUSCPP
#include "../Shared/Data/Produs.cpp"
#endif

#ifndef CATEGORIECPP
#define CATEGORIECPP
#include "../Shared/Data/Categorie.cpp"
#endif

void modificare_produs(const std::string cod_de_bare, const std::string camp, const std::string val_noua){
    return ; //tbc
}

void stergere_produs(const std::string cod_de_bare){
    return ; //tbc
}

void adaugare_categorie(int argc, char** argv){ //tbc
    return ; //tbc
}

void modificare_categorie(const std::string, const std::string, const std::string){
    return ; //tbc
}

void stergere_categorie(const std::string){
    return ; //tbc
}

int main(int argc, char **argv){
    Categorie c("a");
    Produs p("1", "1", 2, 2.0, c);
    if(argv[1]){
        if(strcmp(argv[1], "getCodDeBare") == 0){
            std::cout << p.getCodDeBare() << '/n';
        }
    }
}