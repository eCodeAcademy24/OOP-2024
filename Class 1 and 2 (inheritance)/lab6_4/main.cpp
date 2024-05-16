//Да се развие класа Nediviznina за коjа се чуваат следниве информации:
//
//адреса (динамички алоцирана низа од знаци)
//квадратура (цел боj)
//цена за квадрат (цел боj)
//За оваа класа да се имплементираат соодветните конструктори и следните методи:
//
//cena() коj ќе jа враќа цената на недвижнината (квадратура * цена-за-квадрат)
//pecati() коj ќе ги испечати сите информации за истата
//danokNaImot() коj го ваќа данокот што се плаќа за недвижнината, а истиот се пресметува како 5% од цената на недвижнината.
//Од оваа класа да се изведе класа Vila за коjа дополнително се чува данок на луксуз (цел боj, пр. 10%). За оваа класа да се преоптоварат методите:
//
//pecati()
//danokNaImot() со тоа што пресметаниот данок се зголемува процентуално за данокот на луксуз.
//И за двете класи треба да се преоптовари operator >>.
#include <iostream>
#include <cstring>
using namespace std;
class Nedviznina{
protected:
    char *adresa;
    int kvadratura;
    int cena;

    void copy(const Nedviznina & n){
        this->adresa = new char[strlen(n.adresa) + 1];
        strcpy(this->adresa, n.adresa);
        this->kvadratura = n.kvadratura;
        this->cena = n.cena;
    }
public:
    Nedviznina(){
        adresa = new char[0];
        kvadratura = 0;
        cena = 0;
    }

    Nedviznina(char * adresa, int kvadratura, int cena){
        this->adresa = new char[strlen(adresa) + 1];
        strcpy(this->adresa, adresa);
        this->kvadratura = kvadratura;
        this->cena = cena;
    }

    Nedviznina(const Nedviznina & n){
        copy(n);
    }

    Nedviznina & operator=(const Nedviznina & n){
        if(this!=&n){
            delete [] adresa;
            copy(n);
        }
        return *this;
    }

    ~Nedviznina(){
        delete [] adresa;
    }

    int vrati_cena(){
        return kvadratura * cena;
    }

    double danokNaImot(){
        return vrati_cena() * 0.05;
    }

    void pecati(){
        cout << adresa << ", Kvadratura: " << kvadratura << ", Cena po Kvadrat: " << cena;
    }

    friend istream & operator >>(istream & in, Nedviznina & n){
        in>>n.adresa>>n.kvadratura>>n.cena;
        return in;
    }

    char *getAdresa()
    {
        return adresa;
    }
};

class Vila : public Nedviznina{
    double danok;
public:
    void pecati(){
        Nedviznina :: pecati();
        cout << ", Danok na luksuz: " << danok << endl;
    }

    double danokNaImot()
    {
        return (Nedviznina::vrati_cena() * ((danok+5)/100.0));
    }
    char *getAdresa()
    {
        return adresa;
    }
    friend istream &operator>>(istream &in,Vila &v)
    {
        in>>v.adresa>>v.kvadratura>>v.cena>>v.danok;
        return in;
    }
};

int main() {
    Nedviznina n;
    Vila v;
    cin>>n;
    cin>>v;
    n.pecati();
    cout << endl;
    cout<<"Danok za: "<<n.getAdresa()<<", e: "<<n.danokNaImot()<<endl;
    v.pecati();
    cout<<"Danok za: "<<v.getAdresa()<<", e: "<<v.danokNaImot()<<endl;
    return 0;
}

