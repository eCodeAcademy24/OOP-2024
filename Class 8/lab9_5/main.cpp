#include <iostream>
#include <cstring>

using namespace std;

class InvalidDateException {
    int day, month, year;
public:
    InvalidDateException(int day, int month, int year) : day(day), month(month), year(year) {}
    void showMessage() const {
        cout << "Invalid Date " << day << "/" << month << "/" << year << endl;
    }
};

class NotSupportedCurrencyException {
    char currency[4];
public:
    NotSupportedCurrencyException(const char* currency) {
        strncpy(this->currency, currency, 3);
        this->currency[3] = '\0';
    }
    void showMessage() const {
        cout << currency << " is not a supported currency" << endl;
    }
};

class Transakcija {
protected:
    int day, month, year;
    double amount;
    static double EUR;
    static double USD;
public:
    Transakcija(int day, int month, int year, double amount) {
        if (day < 1 || day > 31 || month < 1 || month > 12)
            throw InvalidDateException(day, month, year);
        this->day = day;
        this->month = month;
        this->year = year;
        this->amount = amount;
    }

    virtual double voDenari() const = 0;
    virtual void pecati() const = 0;

    static void setEUR(double newEUR) {
        EUR = newEUR;
    }

    static void setUSD(double newUSD) {
        USD = newUSD;
    }

    virtual ~Transakcija() {}
};

double Transakcija::EUR = 61;
double Transakcija::USD = 50;

class DenarskaTransakcija : public Transakcija {
public:
    DenarskaTransakcija(int day, int month, int year, double amount) : Transakcija(day, month, year, amount) {}

    double voDenari() const override {
        return amount;
    }

    void pecati() const override {
        cout << day << "/" << month << "/" << year << " " << amount << " MKD" << endl;
    }
};

class DeviznaTransakcija : public Transakcija {
    char currency[4];
public:
    DeviznaTransakcija(int day, int month, int year, double amount, const char* currency) : Transakcija(day, month, year, amount) {
        strncpy(this->currency, currency, 3);
        this->currency[3] = '\0';
        if (strcmp(currency, "USD") != 0 && strcmp(currency, "EUR") != 0)
            throw NotSupportedCurrencyException(currency);
    }

    double voDenari() const override {
        if (strcmp(currency, "USD") == 0) {
            return amount * USD;
        } else if (strcmp(currency, "EUR") == 0) {
            return amount * EUR;
        }
        return 0;
    }

    void pecati() const override {
        cout << day << "/" << month << "/" << year << " " << amount << " " << currency << endl;
    }
};

class Smetka {
    Transakcija** transakcii;
    int brojTransakcii;
    char brojSmetka[16];
    double saldo;
public:
    Smetka(const char* brojSmetka, double saldo) : brojTransakcii(0), saldo(saldo) {
        strncpy(this->brojSmetka, brojSmetka, 15);
        this->brojSmetka[15] = '\0';
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
        return *this;
    }

    void izvestajVoDenari() const {
        double momentalnoSaldo = saldo;
        for (int i = 0; i < brojTransakcii; ++i) {
            momentalnoSaldo += transakcii[i]->voDenari();
        }
        cout << "Korisnikot so smetka: " << brojSmetka << " ima momentalno saldo od " << momentalnoSaldo << " MKD" << endl;
    }

    void pecatiTransakcii() const {
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
    for (int i = 0; i < n; i++) {
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
            e.showMessage();
        } catch (NotSupportedCurrencyException& e) {
            e.showMessage();
        }
    }

    cout << "===PECHATENJE NA SITE TRANSAKCII===" << endl;
    s.pecatiTransakcii();
    cout << "===IZVESHTAJ ZA SOSTOJBATA NA SMETKATA VO DENARI===" << endl;
    s.izvestajVoDenari();

    cout << "\n===PROMENA NA KURSOT NA EVROTO I DOLAROT===\n" << endl;

    double newEUR, newUSD;
    cin >> newEUR >> newUSD;
    Transakcija::setEUR(newEUR);
    Transakcija::setUSD(newUSD);
    cout << "===IZVESHTAJ ZA SOSTOJBATA NA SMETKATA VO DENARI===" << endl;
    s.izvestajVoDenari();

    return 0;
}
