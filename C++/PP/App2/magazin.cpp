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

void delProdCateg(std::string filename, const std::string cod_de_bare, const std::string category){
    std::ifstream fin;
    std::ofstream fout;
    std::string line;
    std::vector<std::string> lines;
    char *clone, *token;
    std::string code;
    fin.open(filename);
    while(std::getline(fin, line)){
        if(line.find(";") != std::string::npos){
            clone = strdup(line.c_str());
            token = strtok(clone, ";");
            code = strdup(token);
            if(code != cod_de_bare){
                lines.push_back(line);
            }
        }else{
            if(line == category){
                lines.push_back(line);
                std::getline(fin, line);
                int nr_prod = std::strtol(line.c_str(), NULL, 10) - 1;
                if(!nr_prod){
                    lines.erase(lines.end());
                }
            }else{
                lines.push_back(line);
            }
        }
    }
    fout.open(filename);
    for(std::vector<std::string>::iterator a = lines.begin(); a != lines.end(); a++){
        fout << *a << '\n';
    }
    fout.close();
}

void addProdCateg(std::string filename, const std::string cod_de_bare, const std::string denumire, const int cantitate, const double pret, const std::string categorie){
    std::ifstream fin;
    fin.open(filename.c_str());
    std::vector<std::string>lines;
    std::string line;
    while(std::getline(fin, line) && line != categorie){
        lines.push_back(line);
    }
    if(line != categorie){
        lines.push_back(categorie);
        lines.push_back("1");
    }else{
        lines.push_back(line);
        std::getline(fin, line);
        lines.push_back(std::to_string(std::strtol(line.c_str(), NULL, 10) + 1));
    }
    std::stringstream ss;
    ss << cod_de_bare << ";" << denumire << ";" << cantitate << ";" << pret;
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
} //pentru a adauga un produs unei categorii

void adaugare_produs(const std::string cod_de_bare, const std::string denumire, const int cantitate, const double pret, const std::string categorie){
    //adaugare in stoc.txt
    bool exista = 0;
    std::ifstream fin;
    fin.open(stocf);
    std::string line;
    while(std::getline(fin, line)){
        if(strcmp(strtok(strdup(line.c_str()), ";"), cod_de_bare.c_str()) == 0){
            exista = 1;
        }
    }
    fin.close();
    if(exista){
        std::cout << "Codul de bare a fost deja folosit.\n";
    }else{
        std::ofstream fout;
        fout.open(stocf, std::ios_base::app);
        fout << cod_de_bare << ";" << denumire << ";" << cantitate << ";" << pret << ";" << categorie << '\n';
        fout.close();
        //adaugare in categorii.txt
        addProdCateg(categf, cod_de_bare, denumire, cantitate, pret, categorie);
    }
};

void modificare_produs(const std::string cod_de_bare, const std::string camp, const std::string val_noua){
    std::ifstream fin;
    std::ofstream fout;
    std::vector<std::string> lines;
    std::string line;
    char* clone;
    fin.open(stocf);
    std::map<std::string, std::string> campuri;
    std::stringstream ss;
    while(std::getline(fin, line)){
        clone = strdup(line.c_str());
        campuri["cod_de_bare"] = strtok(clone, ";");
        if(campuri["cod_de_bare"] != cod_de_bare){
            lines.push_back(line);
        }else{
            campuri["denumire"] = strtok(NULL, ";");
            campuri["cantitate"] = strtok(NULL, ";");
            campuri["pret"] = strtok(NULL, ";");
            campuri["categorie"] = strtok(NULL, ";");
            if(camp == "categorie"){
                delProdCateg(categf, cod_de_bare, campuri["categorie"]);
                addProdCateg(categf, cod_de_bare, campuri["denumire"], std::strtol(campuri["cantitate"].c_str(), NULL, 10), std::strtod(campuri["pret"].c_str(), NULL), val_noua);
            }
            campuri[camp] = val_noua;
            ss << cod_de_bare << ";"  << campuri["denumire"] << ";" << campuri["cantitate"] << ";" << campuri["pret"] << ";" << campuri["categorie"];
            lines.push_back(ss.str());
        }
    }
    fin.close();
    fout.open(stocf);
    for(int i = 0; i < lines.size(); i++){
        fout << lines[i] << '\n';
    }
    fout.close();
}

void stergere_produs(const std::string cod_de_bare){
    std::ifstream fin;
    std::ofstream fout;
    std::vector<std::string> lines;
    std::string line, code, category;
    char *token, *clone;
    bool exista = 0;
    //stergere produs din stoc.txt
    fin.open(stocf);
    while(std::getline(fin, line)){
        clone = strdup(line.c_str());
        token = strtok(clone, ";");
        code = strdup(token);
        if(code != cod_de_bare){
            lines.push_back(line);
        }else{
            exista = 1;
            token = strtok(NULL, ";");
            token = strtok(NULL, ";");
            token = strtok(NULL, ";");
            token = strtok(NULL, ";");
            category = strdup(token);
        }
    }
    fin.close();
    fout.open(stocf);
    for(std::vector<std::string>::iterator a = lines.begin(); a != lines.end(); a++){
        fout << *a << '\n';
    }
    fout.close();
    if(exista){
        //stergere produs din cos_cumparaturi.txt
        lines.clear();
        exista = 0;
        fin.open(coscf);
        std::getline(fin, line);
        lines.push_back(line);
        while(std::getline(fin, line)){
            exista = 1;
            clone = strdup(line.c_str());
            token = strtok(clone, ";");
            code = strdup(token);
            if(code != cod_de_bare){
                lines.push_back(line);
            }
        }
        fin.close();
        fout.open(coscf);
        if(exista){
            lines[0] = std::to_string(std::strtol(lines[0].c_str(), NULL, 10)-1);
        }
        for(std::vector<std::string>::iterator a = lines.begin(); a != lines.end(); a++){
            fout << *a << '\n';
        }
        fout.close();
        //stergere produs din categorii.txt
        delProdCateg(categf, cod_de_bare, category);
    }else{
        std::cout << "Produsul nu exista.\n";
    }
}

void adaugare_categorie(int argc, char** argv){    
    std::ifstream fin;
    fin.open(categf);
    std::vector<std::string> lines;
    std::string line;
    std::stringstream ss;
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
            fin.open(stocf);
            while(std::getline(fin, line)){
                if(strcmp(strtok(strdup(line.c_str()), ";"), argv[4*i]) == 0){
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
    std::vector<std::string> lines;
    std::string line;
    bool exista = 0;
    fin.open(categf);
    while(std::getline(fin, line)){
        if(denumire == line){
            exista = 1;
            line = denumire_noua;
        }
        lines.push_back(line);
    }
    fin.close();
    fout.open(categf);
    for(std::vector<std::string>::iterator a = lines.begin(); a != lines.end(); a++){
        fout << *a << '\n';
    }
    if(!exista){
        std::cout << "Nu exista categorii cu aceasta denumire.\n";
    }
    fout.close();
}

void stergere_categorie(const std::string denumire){
    std::ifstream fin;
    std::ofstream fout;
    std::vector<std::string> lines;
    std::string line, code;
    bool exista = 0;
    char *copy, *token;
    fin.open(categf);
    while(std::getline(fin, line)){
        if(line != denumire){
            lines.push_back(line);
        }else{
            exista = 1;
            std::getline(fin, line);
            std::getline(fin, line);
            while(line.find(";") != std::string::npos){
                copy = strdup(line.c_str());
                token = strtok(copy, ";");
                code = token;
                std::getline(fin, line);
                stergere_produs(token);
            }
            if(line != "\n"){
                lines.push_back(line);
            }
        }
    }
    fin.close();
    fout.open(categf);
    for(std::vector<std::string>::iterator a = lines.begin(); a != lines.end(); a++){
        fout << *a << '\n';
    }
    fout.close();
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
        }
        if(strcmp(argv[1], "adaugare_categorie") == 0){
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
            if((argc >= 3) && ((argc - 4) % 4 == 0) && are_numbers){
                adaugare_categorie(argc, argv);
            }else{
                std::cout << "Sintaxa invalida! Sintaxa corecta: ./magazin.exe adaugare_categorie <denumire_categorie> <numar_produse> <cod_de_bare_produs_1> <denumire_produs_1> <cantitate_produs_1> <pret_produs_1> <cod_de_bare_produs_2> ...\n";
            }
        }
        if(strcmp(argv[1], "modificare_produs") == 0){
            if(argc == 5 && (!strcmp(argv[3], "denumire") || !strcmp(argv[3], "cantitate") || !strcmp(argv[3], "categorie") || !strcmp(argv[3], "pret"))){
                modificare_produs(argv[2], argv[3], argv[4]);
            }else{
                std::cout << "Sintaxa invalida! Sintaxa corecta: ./magazin.exe modificare_produs <cod_de_bare> <camp_de_modificat(denumire|pret|cantitate|categorie)> <valoare_noua>";
            }
        }
    }
    return 0;
}