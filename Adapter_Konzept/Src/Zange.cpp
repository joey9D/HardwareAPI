#include "../Inc/Zange.hpp"
#include <string>
#include <sstream>
#include <iostream>

using namespace std;
// Constructor
Zange::Zange(int length, int width, string material, 
    bool isolation_handle) :
    length(length), width(width), material(material), isolation_handle(isolation_handle){}

Zange::~Zange(){}

Zange::Zange(const Zange &other){
    Zange::width = other.getWidth();
    Zange::length = other.getLength();
    Zange::material = other.getMaterial();
    Zange::isolation_handle = other.hasIsolationHandle();
}

Zange& Zange::operator=(const Zange &other){
    Zange::width = other.getWidth();
    Zange::length = other.getLength();
    Zange::material = other.getMaterial();
    Zange::isolation_handle = other.hasIsolationHandle();
    return ( *this );
}

int Zange::getWidth() const {
    return width;
}

void Zange::setWidth(int width){
    this->width = width;
}

bool Zange::hasIsolationHandle() const{
    return isolation_handle;
}

void Zange::setIsolationHandle(bool isolation_handle) {
    this->isolation_handle = isolation_handle;
}

int Zange::getLength() const {
    return length;
}

void Zange::setLength(int length){
    this->length = length;
}

const string& Zange::getMaterial() const{
    return material;
}

void Zange::setMaterial(const string &material){
    this->material = material;
}


string Zange::to_string(){
    stringstream strstr;
    strstr << "Zange:\n" << "Length: " << length << " mm\n" 
    << "Width: " << width << " mm\n" 
    << "Material: " << material << "\n";
    
    string s = strstr.str();
    return s;
}

void Zange::doesJob() const {
    cout << "Eine Zange kann auch haemmern!\n" << endl;
}

void Zange::doesZangenJob() const {
    cout << "Eine Zange macht Zangensachen!\n" << endl;
}

ostream & operator << (ostream &out, Zange & z){
    out << z.to_string();
    return out;
}