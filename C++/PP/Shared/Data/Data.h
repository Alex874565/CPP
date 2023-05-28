#ifndef LIBS
#define LIBS
#include <iostream>
#include <string>
#include <string.h>
#endif

class Data{
        int zi;
        int luna;
        int an;
    public:
        Data(const int, const int, const int);
        Data(const Data&);
        
        int getZi() const{return this->zi;};
        int getLuna() const{return this->luna;};
        int getAn() const{return this->an;};

        void setZi(const int zi){this->zi = zi;};
        void setLuna(const int luna){this->luna = luna;};
        void setAn(const int an){this->an = an;};

        Data operator=(const Data&);
        friend std::ostream& operator<<(std::ostream& stream, const Data&);
        friend int operator>>(std::istream& stream, Data*);
        
    private:
        void init(const int, const int, const int);
};