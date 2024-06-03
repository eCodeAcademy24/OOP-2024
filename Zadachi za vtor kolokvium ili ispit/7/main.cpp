//
// Created by User on 3.6.2024.
//
#include<iostream>
#include<string.h>
using namespace std;
class OutOfBoundException {
public:
    void printMessage() {
        cout << "Brojot na pin kodovi ne moze da go nadmine dozvolenoto" << endl;
    }
};
class Karticka{
protected:
    char smetka[16];
    int pin;
    bool povekjePin;
public:
    Karticka(char* smetka,int pin){
        strcpy(this->smetka,smetka);
        this->pin=pin;
        this->povekjePin=false;
    }
    char *get_smetka(){
        return smetka;
    }
    // дополниете ја класата
    virtual int tezinaProbivanje() {
        int tezina = 0;
        int tempPin = pin;
        while (tempPin > 0) {
            tezina++;
            tempPin /= 10;
        }
        return tezina;
    }
    ~Karticka(){}

    virtual bool getDopolnitelenPin() const {
        return povekjePin;
    }

    friend ostream& operator<<(ostream& out,  Karticka& k) {
        out << k.smetka << ": " << k.tezinaProbivanje();
        return out;
    }
};
class SpecijalnaKarticka :public Karticka{
private:
    int *pinovi;
    int n;
    static const int MAX_PIN=4;
public:
    SpecijalnaKarticka(char *smetka, int pin): Karticka(smetka,pin){
        pinovi=new int[MAX_PIN];
        n=0;
        povekjePin=true;
    }
    ~SpecijalnaKarticka(){
        delete[]pinovi;
    }
    int tezinaProbivanje() {
        return Karticka::tezinaProbivanje() +n;
    }
    SpecijalnaKarticka& operator+=(int novPin) {
        if (n >= MAX_PIN) {
            throw OutOfBoundException();
        }
        pinovi[n++] = novPin;
        return *this;
    }
};
//вметнете го кодот за SpecijalnaKarticka

class Banka {
private:
    char naziv[30];
    Karticka *karticki[20];
    int broj;
    static int LIMIT;
public:
    Banka(char *naziv, Karticka** karticki,int broj ){
        strcpy(this->naziv,naziv);
        for (int i=0;i<broj;i++){
            //ako kartickata ima dopolnitelni pin kodovi
            if (karticki[i]->getDopolnitelenPin()){
                this->karticki[i]=new SpecijalnaKarticka(*dynamic_cast<SpecijalnaKarticka*>(karticki[i]));
            }
            else this->karticki[i]=new Karticka(*karticki[i]);
        }
        this->broj=broj;
    }

    static  void setLIMIT(int nova){
        LIMIT=nova;
    }
    void pecatiKarticki() {
        cout << "Vo bankata " << naziv << " moze da se probijat kartickite:" << endl;
        for (int i = 0; i < broj; i++) {
            if (karticki[i]->tezinaProbivanje() <= LIMIT) {
                cout << *karticki[i] << endl;
            }
        }
    }

    void dodadiDopolnitelenPin(char* smetka, int novPin) {
        for (int i = 0; i < broj; i++) {
            if (strcmp(karticki[i]->get_smetka(), smetka) == 0) {
                SpecijalnaKarticka* sk = dynamic_cast<SpecijalnaKarticka*>(karticki[i]);
                if (sk) {
                    try {
                        *sk += novPin;
                    } catch (OutOfBoundException &e) {
                        e.printMessage();
                    }
                }
            }
        }
    }
    //да се дополни класата

};
int Banka::LIMIT=7;

int main(){

    Karticka **niza;
    int n,m,pin;
    char smetka[16];
    bool daliDopolnitelniPin;
    cin>>n;
    niza=new Karticka*[n];
    for (int i=0;i<n;i++){
        cin>>smetka;
        cin>>pin;
        cin>>daliDopolnitelniPin;
        if (!daliDopolnitelniPin)
            niza[i]=new Karticka(smetka,pin);
        else
            niza[i]=new SpecijalnaKarticka(smetka,pin);
    }

    Banka komercijalna("Komercijalna",niza,n);
    for (int i=0;i<n;i++) delete niza[i];
    delete [] niza;
    cin>>m;
    for (int i=0;i<m;i++){
        cin>>smetka>>pin;

        komercijalna.dodadiDopolnitelenPin(smetka,pin);

    }

    Banka::setLIMIT(5);

    komercijalna.pecatiKarticki();

}
