#include <iostream>
#include <cstring>

using namespace std;
enum tip {
    smartfon, kompjuter
};

class Device {
private:
    char model[100];
    tip t;
    static double potrebni_casovi;
    int godina;
public:
    Device() {}

    Device(char *model, tip t, int godina) {
        strcpy(this->model, model);
        this->t = t;
        this->godina = godina;
    }

    double promena() {
        double casovi = potrebni_casovi;
        if (godina > 2015) {
            casovi += 2.0;
        }
        if (t == kompjuter) {
            casovi += 2.0;
        }

        return casovi;
    }

    int get_godina() {
        return godina;
    }

    static void setPocetniCasovi(double novi) {
        potrebni_casovi = novi;
    }

    friend ostream &operator<<(ostream &o, Device &d) {
        o << d.model << endl;
        if (d.t == kompjuter) {
            o << "Laptop " << d.promena() << endl;
        } else {
            o << "Mobilen " << d.promena() << endl;
        }
        return o;
    }
};

class InvalidProductionDate {
private:
    string poraka;
public:
    InvalidProductionDate(string poraka) {
        this->poraka = poraka;
    }

    void print() {
        cout << poraka << endl;
    }
};

class MobileServis {
private:
    char adresa[100];
    Device *uredi;
    int n;
public:
    MobileServis() {
        this->n = 0;
        this->uredi = new Device[n];
    }

    MobileServis(char *adresa) {
        strcpy(this->adresa, adresa);
        this->n = 0;
        this->uredi = new Device[n];
    }

    ~MobileServis() {
        delete[]uredi;
    }

    MobileServis &operator+=(Device &d) {
        if (d.get_godina() > 2019 || d.get_godina() < 2000) {
            throw InvalidProductionDate("Невалидна година на производство");
        } else {
            Device *tmp = new Device[n + 1];
            for (int i = 0; i < n; ++i) {
                tmp[i] = uredi[i];
            }
            tmp[n++] = d;
            delete[]uredi;
            uredi = tmp;
        }
        return *this;
    }

    void pecatiCasovi() {
        cout << "Ime: " << adresa << endl;
        for (int i = 0; i < n; ++i) {
            cout << uredi[i];
        }
    }

};

double Device::potrebni_casovi = 1;

int main() {
    int testCase;
    cin >> testCase;
    char ime[100];
    int tipDevice;
    int godina;
    int n;
    Device devices[50];
    if (testCase == 1) {
        cout << "===== Testiranje na klasite ======" << endl;
        cin >> ime;
        cin >> tipDevice;
        cin >> godina;
        Device ig(ime, (tip) tipDevice, godina);
        cin >> ime;
        MobileServis t(ime);
        cout << ig;
    }
    if (testCase == 2) {
        cout << "===== Testiranje na operatorot += ======" << endl;
        cin >> ime;
        cin >> n;
        MobileServis t(ime);
        for (int i = 0; i < n; i++) {
            cin >> ime;
            cin >> tipDevice;
            cin >> godina;
            Device tmp(ime, (tip) tipDevice, godina);
            try {
                t += tmp;
            }
            catch (InvalidProductionDate &i) {
                i.print();
            }
        }
        t.pecatiCasovi();
    }
    if (testCase == 3) {
        cout << "===== Testiranje na isklucoci ======" << endl;
        cin >> ime;
        cin >> n;
        MobileServis t(ime);
        for (int i = 0; i < n; i++) {
            cin >> ime;
            cin >> tipDevice;
            cin >> godina;
            Device tmp(ime, (tip) tipDevice, godina);
            try {
                t += tmp;
            } catch (InvalidProductionDate &i) {
                i.print();
            }
        }
        t.pecatiCasovi();
    }
    if (testCase == 4) {
        cout << "===== Testiranje na konstruktori ======" << endl;
        cin >> ime;
        cin >> n;
        MobileServis t(ime);
        for (int i = 0; i < n; i++) {
            cin >> ime;
            cin >> tipDevice;
            cin >> godina;
            Device tmp(ime, (tip) tipDevice, godina);
            try {
                t += tmp;
            } catch (InvalidProductionDate &i) {
                i.print();
            }
        }
        MobileServis t2 = t;
        t2.pecatiCasovi();
    }
    if (testCase == 5) {
        cout << "===== Testiranje na static clenovi ======" << endl;
        cin >> ime;
        cin >> n;
        MobileServis t(ime);
        for (int i = 0; i < n; i++) {
            cin >> ime;
            cin >> tipDevice;
            cin >> godina;
            Device tmp(ime, (tip) tipDevice, godina);
            try {
                t += tmp;
            }
            catch (InvalidProductionDate &i) {
                i.print();
            }
        }
        t.pecatiCasovi();
        cout << "===== Promena na static clenovi ======" << endl;
        Device::setPocetniCasovi(2);
        t.pecatiCasovi();
    }

    if (testCase == 6) {
        cout << "===== Testiranje na kompletna funkcionalnost ======" << endl;
        cin >> ime;
        cin >> n;
        MobileServis t(ime);
        for (int i = 0; i < n; i++) {
            cin >> ime;
            cin >> tipDevice;
            cin >> godina;
            Device tmp(ime, (tip) tipDevice, godina);
            try {
                t += tmp;
            } catch (InvalidProductionDate &i) {
                i.print();
            }
        }
        Device::setPocetniCasovi(3);
        MobileServis t2 = t;
        t2.pecatiCasovi();
    }

    return 0;

}

