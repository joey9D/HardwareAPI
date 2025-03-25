#ifndef __HAMMER_HPP
#define __HAMMER_HPP

#include <string>
#include <iostream>

using namespace std;

class Hammer{
    private:
        int length;
        int width;
        string material;
        string handle;
    public:
        Hammer(int length=150, int width=20,
        string material="Industrial steel", string handle="Wood");
        ~Hammer();
        Hammer(const Hammer &other);
        Hammer& operator=(const Hammer &other);

        int getWidth() const;
        void setWidth(int width);
        int getLength() const;
        void setLength(int length);
        const string& getMaterial() const;
        void setMaterial(const string &material);
        const string& getHandle() const;
        void setHandle(const string &handel);
        string to_string();
        virtual void doesJob() const;
        virtual void doesNotWork() const;
};
ostream & operator << (ostream &out, Hammer & h);

#endif