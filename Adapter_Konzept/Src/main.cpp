#include <iostream>
#include "../Inc/Zange.hpp"
#include "../Inc/Kneifzange.hpp"
#include "../Inc/Hammer.hpp"
#include "../libs/external/include/mylib.hpp"

using namespace std;

class Werkbank{
    public:
        void doesJob(Hammer* hammer){
            cout << "Werkzeug zum haemmern:" << endl;
            hammer->doesJob();
        }
        void doesZangenJob(Zange* zange){
            cout << "Werkzeug zum ziehen:" << endl;
            zange->doesZangenJob();
        }
};

class HammerAdapter : public Hammer{
    private:
        Zange* zange;

    public:
        HammerAdapter(Zange* z){ // : zange(z){}
            this->zange = z;
        }
        virtual void doesJob() const override {
            zange->doesJob();
        }
};

class ZangenAdapter : public Zange{
    private:
        Hammer* hammer;

    public:
        ZangenAdapter(Hammer* h){
            this->hammer = h;
        }
        virtual void doesZangenJob() const override {
            hammer->doesNotWork();
        }
};

int main() {
    cout.sync_with_stdio(false);
    Zange *zange = new Zange(200, 19, "Industriestahl", false);
    Kneifzange *zange2 = new Kneifzange(270, 17, "Industriestahl", true, 39);
    Hammer *hammer1 = new Hammer(150, 20, "Gusseisen", "Holz" );
    Werkbank werkbank;

    cout << zange->to_string() << endl;
    cout << zange2->to_string() << endl;
    cout << hammer1->to_string() << endl;
    
    werkbank.doesJob(hammer1);
    //werkzeuggebrauch.doesJob(zange);
    //werkbank.doesJob(zange2);
    //werkbank.doesZangenJob(hammer1)
    HammerAdapter* adapted_zange = new HammerAdapter(zange);
    werkbank.doesJob(adapted_zange);
    HammerAdapter* adapted_kneifzange = new HammerAdapter(zange2);
    werkbank.doesJob(adapted_kneifzange);

    werkbank.doesZangenJob(zange);
    werkbank.doesZangenJob(zange2);
    ZangenAdapter* adapated_hammer = new ZangenAdapter(hammer1);
    werkbank.doesZangenJob(adapated_hammer);

    int a = 1;
    int b = 2;
    int c = myAdd(a, b);
    int d = mySub(a, b);
    cout << "myAdd = " << a << " + " << b << " = " << c << endl;
    cout << "mySub = " << a << " - " << b << " = " << d << endl;
    firstLib();
/*
delete zange;
delete zange2;
delete hammer1;
delete adapted_zange;
delete adapted_kneifzange;
delete adapated_hammer;
*/
    cin .get();
    return 0;
}
