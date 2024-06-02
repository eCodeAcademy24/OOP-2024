#include <iostream>
#include <cstring>

using namespace std;

class Oglas {
private:
    char naslov[51];
    char kategorija[31];
    char opis[101];
    float cena;

public:
    Oglas(char *naslov = "", char *kategorija = "", const char *opis = "", float cena = 0.0) {
        strncpy(this->naslov, naslov, 50);
        this->naslov[50] = '\0';
        strncpy(this->kategorija, kategorija, 30);
        this->kategorija[30] = '\0';
        strncpy(this->opis, opis, 100);
        this->opis[100] = '\0';
        this->cena = cena;
    }

    friend bool operator>(const Oglas &o1, const Oglas &o2) {
        return o1.cena > o2.cena;
    }

    friend ostream &operator<<(ostream &os, const Oglas &o) {
        os << o.naslov << endl;
        os << o.opis << endl;
        os << o.cena << " evra" << endl;
        return os;
    }

    char* getKategorija() {
        return kategorija;
    }

    float getCena() {
        return cena;
    }

    char *getNaslov() {
        return naslov;
    }

    char *getOpis() {
        return opis;
    }

};

class NegativnaVrednost {
public:
    void print() {
        cout << "Oglasot ima nevalidna vrednost za cenata i nema da bide evidentiran!" << endl;
    }
};

class Oglasnik {
private:
    char ime[21];
    Oglas *oglasi;
    int brojOglasi;
    int kapacitet;

    void kopiraj(const Oglasnik &other) {
        strncpy(ime, other.ime, 20);
        ime[20] = '\0';
        brojOglasi = other.brojOglasi;
        kapacitet = other.kapacitet;
        oglasi = new Oglas[kapacitet];
        for (int i = 0; i < brojOglasi; ++i) {
            oglasi[i] = other.oglasi[i];
        }
    }

    void brisi() {
        delete[] oglasi;
    }

public:
    Oglasnik(const char *ime = "") {
        strncpy(this->ime, ime, 20);
        this->ime[20] = '\0';
        kapacitet = 10;
        brojOglasi = 0;
        oglasi = new Oglas[kapacitet];
    }

    Oglasnik(const Oglasnik &other) {
        kopiraj(other);
    }

    Oglasnik& operator=(const Oglasnik &other) {
        if (this != &other) {
            brisi();
            kopiraj(other);
        }
        return *this;
    }

    ~Oglasnik() {
        brisi();
    }

    Oglasnik& operator+=(Oglas &oglas) {
        if (oglas.getCena() < 0) {
            NegativnaVrednost ex;
            ex.print();
            return *this;
        }

        if (brojOglasi == kapacitet) {
            kapacitet *= 2;
            Oglas *temp = new Oglas[kapacitet];
            for (int i = 0; i < brojOglasi; ++i) {
                temp[i] = oglasi[i];
            }
            delete[] oglasi;
            oglasi = temp;
        }

        oglasi[brojOglasi++] = oglas;
        return *this;
    }

    friend ostream& operator<<(ostream &os, Oglasnik &o) {
        os << o.ime << endl;
        for (int i = 0; i < o.brojOglasi; ++i) {
            os << o.oglasi[i].getNaslov() << endl;
            os << o.oglasi[i].getOpis() << endl;
            os << o.oglasi[i].getCena() << " evra" << endl;
            os << endl;
        }
        return os;
    }

    void oglasiOdKategorija(char *k) {
        for (int i = 0; i < brojOglasi; ++i) {
            if (strcmp(oglasi[i].getKategorija(), k) == 0) {
                cout << oglasi[i];
                cout << endl;
            }
        }
    }

    void najniskaCena() {
        if (brojOglasi == 0) return;

        int minIndex = 0;
        for (int i = 1; i < brojOglasi; ++i) {
            if (oglasi[i].getCena() < oglasi[minIndex].getCena()) {
                minIndex = i;
            }
        }
        cout << oglasi[minIndex];
        cout << endl;
    }
};

int main() {
    char naslov[50];
    char kategorija[30];
    char opis[100];
    float cena;
    char naziv[50];
    char k[30];
    int n;

    int tip;
    cin >> tip;

    if (tip == 1) {
        cout << "-----Test Oglas & operator <<-----" << endl;
        cin.get();
        cin.getline(naslov, 49);
        cin.getline(kategorija, 29);
        cin.getline(opis, 99);
        cin >> cena;
        Oglas o(naslov, kategorija, opis, cena);
        cout << o;
    } else if (tip == 2) {
        cout << "-----Test Oglas & operator > -----" << endl;
        cin.get();
        cin.getline(naslov, 49);
        cin.getline(kategorija, 29);
        cin.getline(opis, 99);
        cin >> cena;
        Oglas o1(naslov, kategorija, opis, cena);
        cin.get();
        cin.getline(naslov, 49);
        cin.getline(kategorija, 29);
        cin.getline(opis, 99);
        cin >> cena;
        Oglas o2(naslov, kategorija, opis, cena);
        if (o1 > o2) cout << "Prviot oglas e poskap." << endl;
        else cout << "Prviot oglas ne e poskap." << endl;
    } else if (tip == 3) {
        cout << "-----Test Oglasnik, operator +=, operator << -----" << endl;
        cin.get();
        cin.getline(naziv, 49);
        cin >> n;
        Oglasnik ogl(naziv);
        for (int i = 0; i < n; i++) {
            cin.get();
            cin.getline(naslov, 49);
            cin.getline(kategorija, 29);
            cin.getline(opis, 99);
            cin >> cena;
            Oglas o(naslov, kategorija, opis, cena);
            ogl += o;
        }
        cout << ogl;
    } else if (tip == 4) {
        cout << "-----Test oglasOdKategorija -----" << endl;
        cin.get();
        cin.getline(naziv, 49);
        cin >> n;
        Oglasnik ogl(naziv);
        for (int i = 0; i < n; i++) {
            cin.get();
            cin.getline(naslov, 49);
            cin.getline(kategorija, 29);
            cin.getline(opis, 99);
            cin >> cena;
            Oglas o(naslov, kategorija, opis, cena);
            ogl += o;
        }
        cin.get();
        cin.getline(k, 29);
        cout << "Oglasi od kategorijata: " << k << endl;
        ogl.oglasiOdKategorija(k);
    } else if (tip == 5) {
        cout << "-----Test Exception -----" << endl;
        cin.get();
        cin.getline(naziv, 49);
        cin >> n;
        Oglasnik ogl(naziv);
        for (int i = 0; i < n; i++) {
            cin.get();
            cin.getline(naslov, 49);
            cin.getline(kategorija, 29);
            cin.getline(opis, 99);
            cin >> cena;
            Oglas o(naslov, kategorija, opis, cena);
            ogl += o;
        }
        cout << ogl;
    } else if (tip == 6) {
        cout << "-----Test najniskaCena -----" << endl;
        cin.get();
        cin.getline(naziv, 49);
        cin >> n;
        Oglasnik ogl(naziv);
        for (int i = 0; i < n; i++) {
            cin.get();
            cin.getline(naslov, 49);
            cin.getline(kategorija, 29);
            cin.getline(opis, 99);
            cin >> cena;
            Oglas o(naslov, kategorija, opis, cena);
            ogl += o;
        }
        cout << "Oglas so najniska cena:" << endl;
        ogl.najniskaCena();
    } else if (tip == 7) {
        cout << "-----Test All -----" << endl;
        cin.get();
        cin.getline(naziv, 49);
        cin >> n;
        Oglasnik ogl(naziv);
        for (int i = 0; i < n; i++) {
            cin.get();
            cin.getline(naslov, 49);
            cin.getline(kategorija, 29);
            cin.getline(opis, 99);
            cin >> cena;
            Oglas o(naslov, kategorija, opis, cena);
            ogl += o;
        }
        cout << ogl;

        cin.get();
        cin.get();
        cin.getline(k, 29);
        cout << "Oglasi od kategorijata: " << k << endl;
        ogl.oglasiOdKategorija(k);

        cout << "Oglas so najniska cena:" << endl;
        ogl.najniskaCena();
    }

    return 0;
}
