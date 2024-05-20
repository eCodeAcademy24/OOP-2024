//Да се дефинира класа Vozilo која ќе содржи информација за неговата маса (децимален број), ширина и висина (цели броеви).
//
//Од оваа класа да се изведе класата Автомобил во која како дополнителна информација се чува информацијата за бројот на врати (цел број).
//
//Од класата возило да се изведе и класата Автобус во која се чуваат информации и за бројот на патници кои може да ги пренесува.
//
//Од класата возило да се изведе класата Камион во која се чуваат информации и за максималната маса која може да се товари на него (децимална вредност).
//
//За сите класи да се креираат погодни контруктори, како и set и get функции.
//
//Да се дефинира класа ParkingPlac за која се чува динамичко алоцирано поле од покажувачи кон Vozilo, како и бројот на елементи во полето. Во оваа класа да се дефинираат:
//
//конструктор
//деструктор
//операторот += за додавање на ново возило (аргументот е покажувач кон Vozilo)
//функција float presmetajVkupnaMasa() со која се пресметува вкупната маса на сите возила во паркинг плацот
//функција int brojVozilaPoshirokiOd(int l) со која се пресметува бројот на возила кои се пошироки од дадената вредност
//функција void pecati() со која се печати: Brojot na avtomobili e X, brojot na avtobusi e Y i brojot na kamioni e Z.
//функција int pogolemaNosivostOd(Vozilo& v) во која се враќа бројот на сите камиони кои имаат носивост поголема од масата на возилото предадено како аргумент.
//Да се дефинира виртуелна функција int vratiDnevnaCena() во класата Vozilo и истата да се преоптовари во сите изведени класи. За секој автомобил со помалку од 5
//врати дневната цена е 100, а инаку е 130 денари. За секој камион цената се пресметува со формулата: (masa+nosivost)*0.02. За секој автобус цената е 5 денари по
//лице кое може да се пренесува.
//
//Во класата ParkingPlac да се додаде следната функција: - функција int vratiDnevnaZarabotka() со која се враќа дневната заработка од сите возила на паркингот.
//вашиот код треба да биде тука

#include <iostream>
using namespace std;

class Vozilo {
protected:
    float masa;
    int shirina;
    int visina;
public:
    Vozilo(float masa, int shirina, int visina) {
        this->masa = masa;
        this->shirina = shirina;
        this->visina = visina;
    }

    float getMasa() { return masa; }
    int getShirina() { return shirina; }
    int getVisina() { return visina; }

    virtual int vratiDnevnaCena() = 0;
};

class Avtomobil : public Vozilo {
private:
    int brojVrati;
public:
    Avtomobil(float masa, int shirina, int visina, int brojVrati) : Vozilo(masa, shirina, visina) {
        this->brojVrati = brojVrati;
    }

    int getBrojVrati() { return brojVrati; }

    int vratiDnevnaCena() override {
        if (brojVrati < 5)
            return 100;
        else
            return 130;
    }
};

class Avtobus : public Vozilo {
private:
    int brojPatnici;
public:
    Avtobus(float masa, int shirina, int visina, int brojPatnici) : Vozilo(masa, shirina, visina) {
        this->brojPatnici = brojPatnici;
    }

    int getBrojPatnici() { return brojPatnici; }

    int vratiDnevnaCena() override {
        return brojPatnici * 5;
    }
};

class Kamion : public Vozilo {
private:
    float nosivost;
public:
    Kamion(float masa, int shirina, int visina, float nosivost) : Vozilo(masa, shirina, visina) {
        this->nosivost = nosivost;
    }

    float getNosivost() { return nosivost; }

    int vratiDnevnaCena() override {
        return (masa + nosivost) * 0.02;
    }
};

class ParkingPlac {
private:
    Vozilo** vozila;
    int brojVozila;
public:
    ParkingPlac(){
        this->vozila = nullptr;
        this->brojVozila = 0;
    }

    ~ParkingPlac() {
        delete[] vozila;
    }

    void operator+=(Vozilo* v) {
        Vozilo** temp = new Vozilo*[brojVozila + 1];
        for (int i = 0; i < brojVozila; i++) {
            temp[i] = vozila[i];
        }
        temp[brojVozila] = v;
        delete[] vozila;
        vozila = temp;
        brojVozila++;
    }

    // Пресметување на вкупната маса на сите возила
    float presmetajVkupnaMasa() {
        float vkupnaMasa = 0;
        for (int i = 0; i < brojVozila; i++) {
            vkupnaMasa += vozila[i]->getMasa();
        }
        return vkupnaMasa;
    }

    // Пресметување на бројот на возила пошироки од дадената вредност
    int brojVozilaPoshirokiOd(int l) {
        int brojPoshiroki = 0;
        for (int i = 0; i < brojVozila; i++) {
            if (vozila[i]->getShirina() > l)
                brojPoshiroki++;
        }
        return brojPoshiroki;
    }

    // Печатење на информации за бројот на автомобили, автобуси и камиони
    void pecati() {
        int brojAvtomobili = 0, brojAvtobusi = 0, brojKamioni = 0;
        for (int i = 0; i < brojVozila; i++) {
            if (dynamic_cast<Avtomobil*>(vozila[i]))
                brojAvtomobili++;
            else if (dynamic_cast<Avtobus*>(vozila[i]))
                brojAvtobusi++;
            else if (dynamic_cast<Kamion*>(vozila[i]))
                brojKamioni++;
        }
        cout << "Brojot na avtomobili e " << brojAvtomobili << ", brojot na avtobusi e " << brojAvtobusi << " i brojot na kamioni e " << brojKamioni << "." << endl;
    }

    // Пресметување на бројот на камиони со носивост поголема од масата на предаденото возило
    int pogolemaNosivostOd(Vozilo& v) {
        int brojKamioni = 0;
        for (int i = 0; i < brojVozila; i++) {
            Kamion* kamion = dynamic_cast<Kamion*>(vozila[i]);
            if (kamion && kamion->getNosivost() > v.getMasa())
                brojKamioni++;
        }
        return brojKamioni;
    }

    // Пресметување на дневната заработка од сите возила на паркингот
    int vratiDnevnaZarabotka() {
        int zarabotka = 0;
        for (int i = 0; i < brojVozila; i++)
            zarabotka += vozila[i]->vratiDnevnaCena();
        return zarabotka;
    }
};

int main(){
ParkingPlac p;

int n;
cin>>n;
int shirina,visina, broj;
float masa,nosivost;
for (int i=0;i<n;i++){
    int type;
    cin>>type;
    if(type==1){
        cin>>masa>>shirina>>visina>>broj;
        Avtomobil *a=new Avtomobil(masa,shirina,visina,broj);
        p+=a;
    }
    if(type==2){
        cin>>masa>>shirina>>visina>>broj;
        p+=new Avtobus(masa,shirina,visina,broj);
    }
    if(type==3){
        cin>>masa>>shirina>>visina>>nosivost;
        p+=new Kamion(masa,shirina,visina,nosivost);
    }
}

p.pecati();

cout<<"\nZarabotkata e "<<p.vratiDnevnaZarabotka()<<endl;
cout<<"Vkupnata masa e "<<p.presmetajVkupnaMasa()<<endl;
cout<<"Brojot poshiroki od 5 e "<<p.brojVozilaPoshirokiOd(5)<<endl;
Avtomobil a(1200,4,3,5);
cout<<"Brojot na kamioni so nosivost pogolema od avtomobilot e "<<p.pogolemaNosivostOd(a)<<endl;


}
