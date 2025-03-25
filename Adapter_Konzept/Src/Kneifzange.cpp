#include "../Inc/Kneifzange.hpp"
#include <string>
#include <sstream>
#include <iostream>

using namespace std;

// Constructor
Kneifzange::Kneifzange(int length, int width, string material,
    bool isolation_handle, int broadhead):
        Zange(length, width, material, isolation_handle){
            Kneifzange::broadhead = broadhead;
        }

Kneifzange::~Kneifzange(){}

Kneifzange::Kneifzange(const Kneifzange &other) : Zange(other){
    Kneifzange::broadhead = other.getBroadhead();
}

Kneifzange& Kneifzange::operator=(const Kneifzange &other){
    Zange::setLength(other.getLength());
    Zange::setWidth(other.getWidth());
    Zange::setMaterial(other.getMaterial());
    Zange::setIsolationHandle(other.hasIsolationHandle());
    Kneifzange::broadhead = other.getBroadhead();
    return ( *this );
}

int Kneifzange::getBroadhead() const{
    return broadhead;
}

void Kneifzange::setBroadhead(int broadhead){
    this->broadhead = broadhead;
}

string Kneifzange::to_string(){
    string help = Zange::to_string();
    int len = help.size();
    string str = help.substr(7, len-1);
    str = "Kneifzange:\n" + str;
    stringstream strstr;
    strstr << "Diameter Head: " << broadhead << "\n";
    str += strstr.str();
    return str;
}

void Kneifzange::doesJob() const{
    cout << "Eine Kneifzange kann auch haemmern!\n" << endl;
}

ostream & operator << (ostream &out, Kneifzange & z){
    out << z.to_string();
    return out;
}


