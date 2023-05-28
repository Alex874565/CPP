#ifndef LIBS
#define LIBS
#include <iostream>
#include <string>
#include <string.h>
#endif

#include <vector>
#include <sstream>
#include <fstream>
#include <cstdlib>

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

std::string stocf = "../Shared/Files/stoc.txt";
std::string categf = "../Shared/Files/categorii.txt";

void addProdCateg(std::string filename, const std::string cod_de_bare, const std::string denumire, const int cantitate, const double pret, const std::string categorie){
    std::ifstream fin;
    fin.open(filename.c_str());
    std::vector<std::string>lines;
    std::string line;
    while(std::getline(fin, line) && line != categorie){
        lines.push_back(line);
    }
    lines.push_back(line);
    std::getline(fin, line);
    lines.push_back(std::to_string(std::strtol(line.c_str(), NULL, 10) + 1));
    std::stringstream ss;
    ss << cod_de_bare << " " << denumire << " " << cantitate << " " << pret;
    line = ss.str();
    lines.push_back(line);
    while(std::getline(fin, line)){
        lines.push_back(line);
    }
    fin.close();
    std::ofstream fout;
    fout.open(filename.c_str());
    for(std::vector<std::string>::iterator a = lines.begin(); a != lines.end(); a++){
        fout << *a << '\n';
    }
    fout.close();
}

void adaugare_produs(const std::string cod_de_bare, const std::string denumire, const int cantitate, const double pret, const std::string categorie){
    std::ofstream fout;
    fout.open(stocf.c_str(), std::ios_base::app);
    fout << cod_de_bare << " " << denumire << " " << cantitate << " " << pret << " " << categorie << '\n';
    fout.close();
    addProdCateg(categf, cod_de_bare, denumire, cantitate, pret, categorie);
};

void modificare_produs(const std::string cod_de_bare, const std::string camp, const std::string val_noua){
    return ; //tbc
}

void stergere_produs(const std::string cod_de_bare){
    return ; //tbc
}

void adaugare_categorie(int argc, char** argv){    
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
        if(strcmp(argv[1], "adaugare_produs") == 0){
            adaugare_produs(argv[2], argv[3], (int)strtol(argv[4], NULL, 0), (double)strtol(argv[5], NULL, 10), argv[6]);
        }
    }
    return 0;
}