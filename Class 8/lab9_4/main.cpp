#include <iostream>
#include <cstring>

using namespace std;

class InvalidDateException {
public:
    int day, month, year;
    InvalidDateException(int d, int m, int y) : day(d), month(m), year(y) {}
    void printMessage() const {
        cout << "Invalid Date " << day << "/" << month << "/" << year << endl;
    }
};

class NotSupportedCurrencyException {
public:
    char currency[4];
    NotSupportedCurrencyException(const char* cur) {
        strcpy(currency, cur);
    }
    void printMessage() const {
        cout << currency << " is not a supported currency" << endl;
    }
};

class Transakcija {
protected:
    int den, mesec, godina;
    double iznos;
    static double EUR;
    static double USD;

    void validateDate() {
        if (den < 1 || den > 31 || mesec < 1 || mesec > 12) {
            throw InvalidDateException(den, mesec, godina);
        }
    }

public:
    Transakcija(int d, int m, int y, double i) : den(d), mesec(m), godina(y), iznos(i) {
        validateDate();
    }

    virtual double voDenari() = 0;
    virtual double voEvra() = 0;
    virtual double voDolari() = 0;
    virtual void pecati() = 0;
    virtual ~Transakcija() {}

    static void setEUR(double value) {
        EUR = value;
    }

    static void setUSD(double value) {
        USD = value;
    }

    static double getEUR() {
        return EUR;
    }

    static double getUSD() {
        return USD;
    }
};

double Transakcija::EUR = 61.0;
double Transakcija::USD = 50.0;

class DenarskaTransakcija : public Transakcija {
public:
    DenarskaTransakcija(int d, int m, int y, double i) : Transakcija(d, m, y, i) {}

    double voDenari() override {
        return iznos;
    }

    double voEvra() override {
        return iznos / EUR;
    }

    double voDolari() override {
        return iznos / USD;
    }

    void pecati() override {
        cout << den << "/" << mesec << "/" << godina << " " << iznos << " MKD" << endl;
    }
};

class DeviznaTransakcija : public Transakcija {
    char valuta[4];

public:
    DeviznaTransakcija(int d, int m, int y, double i, const char* v) : Transakcija(d, m, y, i) {
        if (strcmp(v, "USD") != 0 && strcmp(v, "EUR") != 0) {
            throw NotSupportedCurrencyException(v);
        }
        strcpy(valuta, v);
    }

    double voDenari() override {
        if (strcmp(valuta, "EUR") == 0) {
            return iznos * EUR;
        } else if (strcmp(valuta, "USD") == 0) {
            return iznos * USD;
        }
        return 0;
    }

    double voEvra() override {
        if (strcmp(valuta, "EUR") == 0) {
            return iznos;
        } else if (strcmp(valuta, "USD") == 0) {
            return (iznos * USD) / EUR;
        }
        return 0;
    }

    double voDolari() override {
        if (strcmp(valuta, "USD") == 0) {
            return iznos;
        } else if (strcmp(valuta, "EUR") == 0) {
            return (iznos * EUR) / USD;
        }
        return 0;
    }

    void pecati() override {
        cout << den << "/" << mesec << "/" << godina << " " << iznos << " " << valuta << endl;
    }
};

class Smetka {
    Transakcija** transakcii;
    int brojTransakcii;
    char brojSmetka[15];
    double saldo;

public:
    Smetka(const char* brSmetka, double pocetnoSaldo) : brojTransakcii(0), saldo(pocetnoSaldo) {
        strcpy(brojSmetka, brSmetka);
        transakcii = new Transakcija*[100];
    }

    ~Smetka() {
        for (int i = 0; i < brojTransakcii; ++i) {
            delete transakcii[i];
        }
        delete[] transakcii;
    }

    Smetka& operator+=(Transakcija* t) {
        transakcii[brojTransakcii++] = t;
        saldo += t->voDenari();
        return *this;
    }

    void izvestajVoDenari()  {
        cout << "Korisnikot so smetka: " << brojSmetka << " ima momentalno saldo od " << saldo << " MKD" << endl;
    }

    void izvestajVoEvra()  {
        cout << "Korisnikot so smetka: " << brojSmetka << " ima momentalno saldo od " << saldo / Transakcija::getEUR() << " EUR" << endl;
    }

    void izvestajVoDolari()  {
        cout << "Korisnikot so smetka: " << brojSmetka << " ima momentalno saldo od " << saldo / Transakcija::getUSD() << " USD" << endl;
    }

    void pecatiTransakcii()  {
        for (int i = 0; i < brojTransakcii; ++i) {
            transakcii[i]->pecati();
        }
    }
};

int main() {
    Smetka s("300047024112789", 1500);

    int n, den, mesec, godina, tip;
    double iznos;
    char valuta[4];

    cin >> n;
    cout << "===VNESUVANJE NA TRANSAKCIITE I SPRAVUVANJE SO ISKLUCOCI===" << endl;
    for (int i = 0; i < n; ++i) {
        cin >> tip >> den >> mesec >> godina >> iznos;
        try {
            if (tip == 2) {
                cin >> valuta;
                Transakcija* t = new DeviznaTransakcija(den, mesec, godina, iznos, valuta);
                s += t;
            } else {
                Transakcija* t = new DenarskaTransakcija(den, mesec, godina, iznos);
                s += t;
            }
        } catch (InvalidDateException& e) {
            e.printMessage();
        } catch (NotSupportedCurrencyException& e) {
            e.printMessage();
        }
    }

    cout << "===PECHATENJE NA SITE TRANSAKCII===" << endl;
    s.pecatiTransakcii();

    cout << "===IZVESHTAJ ZA SOSTOJBATA NA SMETKATA VO DENARI===" << endl;
    s.izvestajVoDenari();

    cout << "===IZVESHTAJ ZA SOSTOJBATA NA SMETKATA VO EVRA===" << endl;
    s.izvestajVoEvra();

    cout << "===IZVESHTAJ ZA SOSTOJBATA NA SMETKATA VO DOLARI===" << endl;
    s.izvestajVoDolari();

    cout << "\n===PROMENA NA KURSOT NA EVROTO I DOLAROT===\n" << endl;

    double newEUR, newUSD;
    cin >> newEUR >> newUSD;
    Transakcija::setEUR(newEUR);
    Transakcija::setUSD(newUSD);

    cout << "===IZVESHTAJ ZA SOSTOJBATA NA SMETKATA VO DENARI===" << endl;
    s.izvestajVoDenari();

    cout << "===IZVESHTAJ ZA SOSTOJBATA NA SMETKATA VO EVRA===" << endl;
    s.izvestajVoEvra();

    cout << "===IZVESHTAJ ZA SOSTOJBATA NA SMETKATA VO DOLARI===" << endl;
    s.izvestajVoDolari();

    return 0;
}
