#ifndef __KNEIFZANGE_HPP
#define __KNEIFZANGE_HPP

#include "Zange.hpp"
#include <string>
#include <iostream>

using namespace std;

class Kneifzange : public Zange{
    private:
        int broadhead;

    public:
        Kneifzange(int length=100, int width=20,
        string material="Industrial steel",
        bool isolation_handle=false, int diameter_head = 50);
        ~Kneifzange();
        Kneifzange(const Kneifzange &other);
        Kneifzange& operator=(const Kneifzange &other);

        int getBroadhead() const;
        void setBroadhead(int broadhead);
        string to_string();
        virtual void doesJob() const override;
};
ostream & operator << (ostream &out, Kneifzange & z);

#endif