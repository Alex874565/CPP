#ifndef LIBS
#define LIBS
#include <iostream>
#include <string>
#include <string.h>
#endif

#include <map>
#include <vector>
#include <sstream>
#include <fstream>
#include <cstdlib>
#include <algorithm>

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
std::string coscf = "../Shared/Files/cos_cumparaturi.txt";

bool is_number(char* c){
    int count = 0;
    for(int i = 0; i < strlen(c); i++){
        if(!isdigit(c[i])){
            if(c[i] != '.'){
                return 0;
            }else{
                count += 1;
                if(count > 1){
                    return 0;
                }
            }
        }
    }
    return 1;
}



/* void makeUnavailable(std::string filename, const std::string cod_de_bare){
    std::ifstream fin;
    std::ofstream fout;
    std::vector<std::string> lines;
    std::string line, code;
    char *clone, *token;
    lines.clear();
        fin.open(filename);
        std::getline(fin, line);
        lines.push_back(line);
        while(std::getline(fin, line)){
            clone = strdup(line.c_str());
            token = strtok(clone, ";");
            code = strdup(token);
            if(code != cod_de_bare){
                lines.push_back(line);
            }else{
                if(line.find("INDISPONIBIL") == std::string::npos){
                    line += ";INDISPONIBIL";
                }
                lines.push_back(line);
            }
        }
        fin.close();
        fout.open(filename);
        for(std::vector<std::string>::iterator a = lines.begin(); a != lines.end(); a++){
            fout << *a << '\n';
        }
        fout.close();
}*/

void afisare_produs(std::string produs, std::string categorie = ""){
    char *token, *clone;
    clone = strdup(produs.c_str());
    token = strtok(clone, ";");
    std::cout << "\n    Cod de bare: " << token;
    token = strtok(NULL, ";");
    std::cout << "\n    Denumire: " << token;
    token = strtok(NULL, ";");
    std::cout << "\n    Cantitate: " << token;
    token = strtok(NULL, ";");
    std::cout << "\n    Pret: " << token;
    if(categorie == ""){
        token = strtok(NULL, ";");
        std::cout << "\n    Categorie: " << token << '\n';
    }else{
        std::cout << "\n    Categorie: " << categorie << '\n';
    }
}

void vizualizare_stoc(){
    std::ifstream fin;
    fin.open(stocf);
    std::string line;
    char *clone, *token;
    Produs p;
    std::getline(fin, line);
    std::cout << "Numar produse distincte: " << line << '\n';
    if(line != "0"){
    std::cout << "Produse:\n";
        int index = 1;
        while(fin >> p){
            std::cout << "Produs " << index << ":\n";
            std::cout << p << '\n';
            index++;
        }
    }
    fin.close();
}

void vizualizare_categorie(std::string denumire){
    std::ifstream fin;
    std::string line;
    fin.open(categf);
    int exista = 0;
    while(std::getline(fin, line)){
        if(line == denumire){
            exista = 1;
            std::getline(fin, line);
            int nr_prod = strtol(line.c_str(), NULL, 10);
            std::cout << "Numar produse distincte: " << nr_prod << '\n';
            for(int i = 1; i <= nr_prod; i++){
                std::cout << "Produs " << i << ":";
                std::getline(fin, line);
                afisare_produs(line, denumire);
            }
        }
    }
    if(!exista){
        std::cout << "Nu exista categorii cu acest nume.\n";
    }
    fin.close();
}

void delProdCateg(std::string filename, const std::string cod_de_bare, const std::string categorie){
    std::ifstream fin;
    std::ofstream fout;
    std::vector<Categorie> lines;
    Categorie c;
    fin.open(filename);
    while(fin >> c){
        if(c.getDenumire() == categorie){
            c.delProdus(cod_de_bare);
        }
        if(c.getNrProduse() != 0){
            lines.push_back(c);
        }
        c = Categorie();
    }
    fout.open(filename);
    for(int i = 0; i < lines.size(); i++){
        fout << lines[i] << '\n';
    }
    fout.close();
}

void addProdCateg(std::string filename, const std::string cod_de_bare, const std::string denumire, const int cantitate, const double pret, const std::string categorie){
    std::ifstream fin;
    std::vector<Categorie>lines;
    std::string line;
    Categorie c;
    fin.open(filename.c_str());
    while(fin >> c && c.getDenumire() != categorie){
        lines.push_back(Categorie(c));
        c = Categorie();
    }
    if(c.getDenumire() != categorie){
        c = Categorie(categorie);
        c.addProdus(new Produs(cod_de_bare, denumire, cantitate, pret, categorie));
        lines.push_back(Categorie(c));
    }else{
        c.addProdus(new Produs(cod_de_bare, denumire, cantitate, pret, categorie));
        lines.push_back(c);
    }
    while(fin >> c){
        lines.push_back(c);
        c = Categorie();
    }
    fin.close();
    std::ofstream fout;
    fout.open(filename.c_str());
    for(int i = 0; i < lines.size(); i++){
        fout << lines[i] << '\n';
    }
    fout.close();
} //pentru a adauga un produs unei categorii

void adaugare_produs(const std::string cod_de_bare, const std::string denumire, const int cantitate, const double pret, const std::string categorie){
    //adaugare in stoc.txt
    bool exista = 0;
    std::ifstream fin;
    fin.open(stocf);
    std::string line;
    std::vector<Produs> lines;
    std::getline(fin, line);
    int nr_prod = strtol(line.c_str(), NULL, 10);
    Produs p;
    while(fin >> p){
        lines.push_back(p);
        if(p.getCodDeBare() == cod_de_bare){
            exista = 1;
            break;
        }

    }
    fin.close();
    if(exista){
        std::cout << "Codul de bare a fost deja folosit.\n";
    }else{
        std::ofstream fout;
        fout.open(stocf);
        fout << std::to_string(nr_prod + 1).c_str() << '\n';
        for(int i = 0; i < lines.size(); i++){
            fout << lines[i] << "\n";
        }
        fout << Produs(cod_de_bare, denumire, cantitate, pret, Categorie(categorie));
        fout.close();
        //adaugare in categorii.txt
        addProdCateg(categf, cod_de_bare, denumire, cantitate, pret, categorie);
    }
};

void modificare_produs(const std::string cod_de_bare, const std::string camp, const std::string val_noua, const bool superficial = false){
    std::ifstream fin;
    std::ofstream fout;
    std::vector<Produs> lines;
    std::string line;
    char* clone;
    fin.open(stocf);
    std::string categorie;
    Produs p;
    int exista = 0;
    //modificare in stoc
    std::getline(fin, line);
    int nr_prod = strtol(line.c_str(), NULL, 10);
    while(fin >> p){
        if(p.getCodDeBare() != cod_de_bare){
            lines.push_back(p);
        }else{
            exista = 1;
            categorie = p.getCategorie()->getDenumire();
            if(camp == "categorie" && !superficial){
                delProdCateg(categf, cod_de_bare, categorie);
                p.setCategorie(Categorie(val_noua));
                addProdCateg(categf, cod_de_bare, p.getDenumire(), p.getCantitate(), p.getPret(), p.getCategorie() -> getDenumire());
            }
            if(camp == "denumire"){
                p.setDenumire(val_noua);
            }
            if(camp == "cantitate"){
                p.setCantitate(strtol(val_noua.c_str(), NULL, 10));
            }
            if(camp == "pret"){
                p.setPret(strtol(val_noua.c_str(), NULL, 10));
            }
            lines.push_back(p);
        }
    }
    fin.close();
    fout.open(stocf);
    fout << std::to_string(nr_prod).c_str() << '\n';
    for(int i = 0; i < lines.size(); i++){
        fout << lines[i] << '\n';
    }
    fout.close();
    //modificare in categorii
    if(!exista){
        std::cout << "Codul de bare este incorect.\n";
    }
    if(camp != "categorie" && exista){
        fin.open(categf);
        std::vector<Categorie> categs;
        Categorie c;
        while(fin >> c){
            if(c.getDenumire() == categorie){
                for(int i = 0; i < c.getNrProduse(); i++){
                    p = *c.getProdus(i);
                    if(p.getCodDeBare() == cod_de_bare){
                        if(camp == "denumire"){
                            p.setDenumire(val_noua);
                        }
                        if(camp == "cantitate"){
                            p.setCantitate(strtol(val_noua.c_str(), NULL, 10));
                        }
                        if(camp == "pret"){
                            p.setPret(strtol(val_noua.c_str(), NULL, 10));
                        }
                    }
                    c.setProdus(p, i);
                }
            }
            categs.push_back(c);
            c = Categorie();
        }
        fin.close();
        fout.open(categf);
        for(int i = 0; i < categs.size(); i++){
            fout << categs[i] << '\n';
        }
        fout.close();
    }
}

void stergere_produs(const std::string cod_de_bare, const bool superficial = false){
    std::ifstream fin;
    std::ofstream fout;
    std::vector<Produs> lines;
    std::string line, code, categorie;
    bool exista = 0;
    //stergere produs din stoc.txt
    fin.open(stocf);
    std::getline(fin, line);
    int nr_prod = std::strtol(line.c_str(), NULL, 10);
    Produs p;
    while(fin >> p){
        if(p.getCodDeBare() != cod_de_bare){
            lines.push_back(p);
        }else{
            exista = 1;
            categorie = p.getCategorie()->getDenumire();
        }
    }
    fin.close();
    if(exista){
        nr_prod -= 1;
    }
    fout.open(stocf);
    fout << nr_prod << '\n';
    for(int i = 0; i < lines.size(); i++){
        fout << lines[i] << '\n';
    }
    fout.close();
    if(exista){
        //stergere produs din cos_cumparaturi.txt
        std::vector<std::string>clines;
        char *clone, *token;
        exista = 0;
        fin.open(coscf);
        std::getline(fin, line);
        clines.push_back(line);
        while(std::getline(fin, line)){
            clone = strdup(line.c_str());
            token = strtok(clone, ";");
            code = strdup(token);
            if(code != cod_de_bare){
                clines.push_back(line);
            }else{
                exista = 1;
            }
        }
        fin.close();
        fout.open(coscf);
        if(exista){
            clines[0] = std::to_string(std::strtol(clines[0].c_str(), NULL, 10)-1);
        }
        for(int i = 0; i < clines.size(); i++){
            fout << clines[i].c_str() << '\n';
        }
        fout.close();
        //stergere produs din categorii.txt
        if(!superficial){
            delProdCateg(categf, cod_de_bare, categorie);
        }
    }else{
        std::cout << "Produsul nu exista.\n";
    }
}

void adaugare_categorie(int argc, char** argv){    
    std::ifstream fin;
    fin.open(categf);
    std::string line;
    bool exista = 0;
    while(std::getline(fin, line)){
        if(line == argv[2]){
            exista = 1;
            break;
        }
    }
    fin.close();
    if(exista){
        std::cout << "O categorie cu aceasta denumire exista deja.\n";
    }else{
        for(int i = 1; i <= std::strtol(argv[3], NULL, 10); i++){
            std::ifstream fin;
            Produs p;
            fin.open(stocf);
            std::getline(fin, line);
            while(fin >> p){
                if(p.getCodDeBare() == argv[4*i]){
                    std::cout << "Codul de bare: " << argv[4*i] << " a fost deja folosit.\n";
                    fin.close();
                    return ;
                }
            }
            fin.close();
        }
        for(int i = 1; i <= std::strtol(argv[3], NULL, 10); i++){
            adaugare_produs(argv[4 * i], argv[4 * i + 1], std::strtol(argv[4 * i + 2], NULL, 10), std::strtod(argv[4 * i] + 3, NULL), argv[2]);
        }
    }
}

void modificare_categorie(const std::string denumire, const std::string denumire_noua){
    std::ifstream fin;
    std::ofstream fout;
    Categorie c;
    bool exista = 0, exista2 = 0;
    fin.open(categf);
    while(fin >> c){
        if(c.getDenumire() == denumire){
            exista = 1;
            while(c.getNrProduse()){
                modificare_produs(c.getProdus(c.getNrProduse() - 1)->getCodDeBare(), "categorie", denumire_noua);
                c.delProdus(c.getProdus(c.getNrProduse() - 1)->getCodDeBare());
            }
        }else if (c.getDenumire() == denumire_noua){
            std::cout << "O categorie cu noul nume exista deja.\n";
            return;
        }
        c = Categorie();
    }
    fin.close();
    if(!exista){
        std::cout << "Nu exista categorii cu aceasta denumire.\n";
    }
}

void stergere_categorie(const std::string denumire){
    std::ifstream fin;
    bool exista = 0;
    fin.open(categf);
    Categorie c;
    while(fin >> c){
        if(c.getDenumire() == denumire){
            exista = 1;
            while(c.getNrProduse()){
                stergere_produs(c.getProdus(c.getNrProduse() - 1)->getCodDeBare());
                c.delProdus(c.getProdus(c.getNrProduse() - 1)->getCodDeBare());
            }
            break;
        }
        c = Categorie();
    }
    fin.close();
    if(!exista){
        std::cout << "Nu exista categorii cu aceasta denumire.\n";
    }
}

int main(int argc, char **argv){
    if(argv[1]){
        if(strcmp(argv[1], "adaugare_produs") == 0){
            if(argc == 7 && is_number(argv[4]) && is_number(argv[5])){
                adaugare_produs(argv[2], argv[3], (int)strtol(argv[4], NULL, 0), (double)strtod(argv[5], NULL), argv[6]);
            }else{
                std::cout << "Sintaxa invalida! Sintaxa corecta: ./magazin.exe adaugare_produs <cod_de_bare> <denumire_produs> <cantitate> <pret> <denumire_categorie>\n";
            }
        }else if(strcmp(argv[1], "stergere_produs") == 0){
            if(argc == 3){
                stergere_produs(argv[2]);
            }else{
                std::cout << "Sintaxa invalida! Sintaxa corecta: ./magazin.exe stergere_produs <cod_de_bare>\n";
            }
        }else if(strcmp(argv[1], "modificare_categorie") == 0){
            if(argc == 4){
                modificare_categorie(argv[2], argv[3]);
            }else{
                std::cout << "Sintaxa invalida! Sintaxa corecta: ./magazin.exe modificare_categorie <denumire_categorie> <valoare_noua_denumire>\n";
            }
        }else if(strcmp(argv[1], "stergere_categorie") == 0){
            if(argc == 3){
                stergere_categorie(argv[2]);
            }else{
                std::cout << "Sintaxa invalida! Sintaxa corecta: ./magazin.exe stergere_categorie <denumire_categorie>\n";
            }
        }else if(strcmp(argv[1], "adaugare_categorie") == 0){
            int are_numbers = 1;
            if(!is_number(argv[3])){
                are_numbers = 0;
            }else{
                for(int i = 6; i < argc - 4; i+= 4){
                    if(!is_number(argv[i]) || !is_number(argv[i + 1])){
                        are_numbers = 0;
                    } 
                }
            }
            if((argc >= 4) && (argc == ((int)strtol(argv[3], NULL, 10) + 1) * 4) && are_numbers){
                adaugare_categorie(argc, argv);
            }else{
                std::cout << "Sintaxa invalida! Sintaxa corecta: ./magazin.exe adaugare_categorie <denumire_categorie> <numar_produse> <cod_de_bare_produs_1> <denumire_produs_1> <cantitate_produs_1> <pret_produs_1> <cod_de_bare_produs_2> ...\n";
            }
        }else if(strcmp(argv[1], "modificare_produs") == 0){
            if(argc == 5 && (!strcmp(argv[3], "denumire") || !strcmp(argv[3], "cantitate") || !strcmp(argv[3], "categorie") || !strcmp(argv[3], "pret"))){
                modificare_produs(argv[2], argv[3], argv[4]);
            }else{
                std::cout << "Sintaxa invalida! Sintaxa corecta: ./magazin.exe modificare_produs <cod_de_bare> <camp_de_modificat(denumire|pret|cantitate|categorie)> <valoare_noua>\n";
            }
        }else if(strcmp(argv[1], "vizualizare_stoc") == 0){
            if(argc == 2){
                vizualizare_stoc();
            }else{
                std::cout << "Sintaxa invalida! Sintaxa corecta: ./magazin.exe vizualizare_stoc\n";
            }
        }else if(strcmp(argv[1], "vizualizare_categorie") == 0){
            if(argc == 3){
                vizualizare_categorie(argv[2]);
            }else{
                std::cout << "Sintaxa invalida! Sintaxa corecta: ./magazin.exe vizualizare_categorie <denumire_categorie>\n";
            }
        }else{
            std::cout << "Aceasta comanda nu exista.\n";
        }
    }
    return 0;
}