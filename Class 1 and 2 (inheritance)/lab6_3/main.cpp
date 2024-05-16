//Со цел да се подобри системот Мој Термин, со воведување функционалност за пресметување плати за лекарите за еден месец, од Министерството за здравство на Република Македонија, ги добивате следните задачи:
//
//Да се креира класа Lekar во која што ќе се чуваат:
//
//факсимил на докторот (цел број)
//име (низа од максимум 10 знаци)
//презиме (низа од максимум 10 знаци)
//почетна плата (децимален број)
//За класата да се имплементираат методите:
//
//void pecati(): Печати информации за лекарот во формат Факсимил: име презиме
//
//double plata(): ја враќа платата на лекарот
//
//Да се креира класа MaticenLekar која што наследува од Lekar и во неа се чуваат дополнителни информации за:
//
//број на пациенти со којшто лекарот соработувал во текот на месецот (цел број)
//котизации наплатени од пациентите во текот на месецот (динамички алоцирана низа од децимални броеви)
//За класата да се препокријат методитe:
//
//void pecati() : ги печати основните информации за лекарот, а во нов ред го печати и просекот од наплатените котизации
//
//double plata(): ја враќа платата на матичниот лекар
//
//Платата на матичниот лекар се пресметува со зголемување на основната плата за 30% од просекот од наплатените котизации за месецот
#include <iostream>
#include <cstring>
using namespace std;

class Lekar{
protected:
    int faksimil;
    char ime[10];
    char prezime[10];
    double pocetna_plata;
public:
    Lekar(int faksimil = 0, char *ime ="", char *prezime = "", double pocetna_plata = 0){
        this->faksimil = faksimil;
        strcpy(this->ime, ime);
        strcpy(this->prezime, prezime);
        this->pocetna_plata = pocetna_plata;
    }

    Lekar(const Lekar & l){
        this->faksimil =l.faksimil;
        strcpy(this->ime, l.ime);
        strcpy(this->prezime, l.prezime);
        this->pocetna_plata = l.pocetna_plata;
    }

    void pecati(){
        cout << faksimil << ": " << ime << " " << prezime << endl;
    }

    double plata(){
        return pocetna_plata;
    }
};

class MaticenLekar : public Lekar{
    int broj_pacienti;
    double *kotizacija;

    void copy(const MaticenLekar & ml){
        this->broj_pacienti = ml.broj_pacienti;
        this->kotizacija = new double[ml.broj_pacienti];
        for(int i = 0; i < broj_pacienti; i++){
            this->kotizacija[i] = ml.kotizacija[i];
        }
        strcpy(ime, ml.ime);
        strcpy(prezime, ml.prezime);
        this->pocetna_plata = ml.pocetna_plata;
        this->faksimil = ml.faksimil;
    }

public:
    MaticenLekar() : Lekar(){
        broj_pacienti =  0;
        kotizacija = new double[0];
    }

    // ovoj konsturkor ne e potreben, poradi toa sto ne se kreira nikakov objekt vo mainot so ovie argumenti
//    MaticenLekar(int faksimil, char *ime, char *prezime, double pocetna_plata) : Lekar(faksimil, ime, prezime, pocetna_plata){
//        this->broj_pacienti = broj_pacienti;
//        this->kotizacija = new double[broj_pacienti];
//        for(int i = 0; i < broj_pacienti; i++){
//            this->kotizacija[i] = kotizacija[i];
//        }
//    }

    MaticenLekar(const Lekar & l, int broj_pacienti, double *kotizacija) : Lekar(l){
        this->broj_pacienti = broj_pacienti;
        this->kotizacija = new double[broj_pacienti];
        for(int i = 0; i < broj_pacienti; i++){
            this->kotizacija[i] = kotizacija[i];
        }
    }

    MaticenLekar(const MaticenLekar & ml){
        copy(ml);
    }

    MaticenLekar & operator=(const MaticenLekar & ml){
        if(this!=&ml){
            delete [] kotizacija;
            copy(ml);
        }
        return *this;
    }

    ~MaticenLekar(){
        delete [] kotizacija;
    }

    double prosek(){
        double vkupno = 0;
        for(int i = 0; i < broj_pacienti; i++){
            vkupno += kotizacija[i];
        }
        return (vkupno/broj_pacienti);
    }

    double plata(){
        return Lekar::plata() + (0.3 * prosek());
    }

    void pecati(){
        Lekar::pecati();
        cout << "Prosek na kotizacii: " << prosek() << endl;
    }
};
int main() {
    int n;
    cin>>n;
    int pacienti;
    double kotizacii[100];
    int faksimil;
    char ime [20];
    char prezime [20];
    double osnovnaPlata;

    Lekar * lekari = new Lekar [n];
    MaticenLekar * maticni = new MaticenLekar [n];

    for (int i=0;i<n;i++){
        cin >> faksimil >> ime >> prezime >> osnovnaPlata;
        lekari[i] = Lekar(faksimil,ime,prezime,osnovnaPlata);
    }

    for (int i=0;i<n;i++){
        cin >> pacienti;
        for (int j=0;j<pacienti;j++){
            cin >> kotizacii[j];
        }
        maticni[i]=MaticenLekar(lekari[i],pacienti,kotizacii);
    }

    int testCase;
    cin>>testCase;

    if (testCase==1){
        cout<<"===TESTIRANJE NA KLASATA LEKAR==="<<endl;
        for (int i=0;i<n;i++){
            lekari[i].pecati();
            cout<<"Osnovnata plata na gorenavedeniot lekar e: "<<lekari[i].plata()<<endl;
        }
    }
    else {
        cout<<"===TESTIRANJE NA KLASATA MATICENLEKAR==="<<endl;
        for (int i=0;i<n;i++){
            maticni[i].pecati();
            cout<<"Platata na gorenavedeniot maticen lekar e: "<<maticni[i].plata()<<endl;
        }
    }

    delete [] lekari;
    delete [] maticni;
    return 0;
}

