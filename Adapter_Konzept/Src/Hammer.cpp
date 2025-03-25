#include "../Inc/Hammer.hpp"
#include <string>
#include <sstream>
#include <iostream>

using namespace std;
// Constructor
Hammer::Hammer(int length, int width, string material, string handle ) {
        this->length = length;
        this->width = width;
        this->material = material;
        this->handle = handle;
    }

Hammer::~Hammer(){}

Hammer::Hammer(const Hammer &other){
    Hammer::length = other.getLength();
    Hammer::width = other.getWidth();
    Hammer::material = other.getMaterial();
    Hammer::handle = other.getHandle();
}

Hammer& Hammer::operator=(const Hammer &other){
    Hammer::length = other.getLength();
    Hammer::width = other.getWidth();
    Hammer::material = other.getMaterial();
    Hammer::handle = other.getHandle();
    return ( *this );
}

int Hammer::getWidth() const {
    return length;
}

void Hammer::setWidth(int width){
    this->width = width;
}

int Hammer::getLength() const{
    return length;
}

void Hammer::setLength(int length){
    this->length = length;
}

const string& Hammer::getMaterial() const{
    return material;
}

void Hammer::setMaterial(const string &material){
    this->material = material;
}

const string& Hammer::getHandle() const{
    return material;
}

void Hammer::setHandle(const string &handle){
    this->handle = handle;
}

string Hammer::to_string(){
    stringstream strstr;
    strstr << "Hammer:\n" << "Length: " << length << " mm\n" 
    << "Width: " << width << " mm\n" 
    << "Material: " << material << "\n";

    string s = strstr.str();
    return s;
}

void Hammer::doesJob() const{
    cout << "Ein Hammer kann haemmern!\n" << endl;
}

void Hammer::doesNotWork() const{
    cout << "Ein Hammer ist keine Zange!\n" << endl;
}

ostream & operator << (ostream &out, Hammer & h){
    out << h.to_string();
    return out;
}








