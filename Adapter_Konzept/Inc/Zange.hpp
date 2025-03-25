#ifndef __ZANGE_HPP
#define __ZANGE_HPP

#include <string>
#include <iostream>

using namespace std;

class Zange{
    private:
        int length;
        int width;
        string material;
        bool isolation_handle;

    public:
        Zange(int length=100, int width=20,
        string material="Industrial steel",
        bool isolation_handle=false);
        ~Zange();
        Zange(const Zange &other);
        Zange& operator=(const Zange &other);

        int getWidth() const;
        void setWidth(int witdh);
        bool hasIsolationHandle() const;
        void setIsolationHandle(bool isolation_handle);
        int getLength() const;
        void setLength(int length);
        const string& getMaterial() const;
        void setMaterial(const string &material);
        string to_string();
        virtual void doesJob() const;
        virtual void doesZangenJob() const;
};
ostream & operator << (ostream &out, Zange & z);

#endif