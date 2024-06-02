#include <iostream>
#include <cstring>

using namespace std;

class Exception {

public:
    Exception() {}

    void print() {
        cout << "Ne moze da se vnese dadeniot trud" << endl;
    }
};


class Student {
private:
    char ime[30];
    int indeks;
    int godina_na_upis;
    int *polozeni;
    int n;
public:
    Student() {
        this->n = 0;
        this->polozeni = new int[0];
    }

    Student(char *ime, int indeks, int godina_na_upis, int *polozeni, int n) {
        strcpy(this->ime, ime);
        this->indeks = indeks;
        this->godina_na_upis = godina_na_upis;
        this->n = n;
        this->polozeni = new int[n];
        for (int i = 0; i < n; ++i) {
            this->polozeni[i] = polozeni[i];
        }
    }

    Student(const Student &s) {
        strcpy(this->ime, s.ime);
        this->indeks = s.indeks;
        this->godina_na_upis = s.godina_na_upis;
        this->n = s.n;
        this->polozeni = new int[n];
        for (int i = 0; i < n; ++i) {
            this->polozeni[i] = s.polozeni[i];
        }
    }

    Student &operator=(const Student &s) {
        if (this != &s) {
            delete[]polozeni;
            strcpy(this->ime, s.ime);
            this->indeks = s.indeks;
            this->godina_na_upis = s.godina_na_upis;
            this->n = s.n;
            this->polozeni = new int[n];
            for (int i = 0; i < n; ++i) {
                this->polozeni[i] = s.polozeni[i];
            }
        }
        return *this;
    }

    ~Student() {
        delete[]polozeni;
    }

    int get_godina_upis() {
        return godina_na_upis;
    }

    virtual double rang() {
        double prosek = 0.0;
        for (int i = 0; i < n; ++i) {
            prosek += polozeni[i];
        }
        return prosek / n;
    }

    friend ostream &operator<<(ostream &o, Student &s) {
        o << s.indeks << " " << s.ime << " " << s.godina_na_upis << " " << s.rang() << endl;
        return o;
    }

    int getIDX() {
        return indeks;
    }

    int getUpis() {
        return godina_na_upis;
    }
};

class Trud {
private:
    char znak;
    int godina_na_izdavanje;
public:
    Trud() {
        this->godina_na_izdavanje = 0;
    }

    Trud(char znak, int godina_na_izdavanje) {
        this->znak = znak;

        this->godina_na_izdavanje = godina_na_izdavanje;
    }

    ~Trud() {}

    char get_znak() {
        return znak;
    }

    int get_godina() {
        return godina_na_izdavanje;
    }

    friend istream &operator>>(istream &i, Trud &t) {
        i >> t.znak >> t.godina_na_izdavanje;
        return i;
    }
};

class PhDStudent : public Student {
private:
    Trud *trudovi;
    int n;
    static int SPISANIE;
    static int KONFERENCISKI;

    void copy(const PhDStudent &p) {
        this->n = p.n;
        this->trudovi = new Trud[n];
        for (int i = 0; i < n; ++i) {
            this->trudovi[i] = p.trudovi[i];
        }
    }

public:
    PhDStudent() {
        this->n = 0;
        this->trudovi = new Trud[n];
    }

    PhDStudent(char *ime, int indeks, int godina_na_upis, int polozeni[50], int n, Trud trudovi[], int ntr) : Student(
            ime, indeks, godina_na_upis, polozeni, n) {
        this->n = ntr;
        this->trudovi = new Trud[ntr];
        int j = 0;
        for (int i = 0; i < ntr; ++i) {
            if (trudovi[i].get_godina() < godina_na_upis) {
                throw Exception();
            } else {
                this->trudovi[j++] = trudovi[i];
            }
        }
        this->n = j;
    }

    PhDStudent(const PhDStudent &p) : Student(p) {
        copy(p);
    }

    static void setJ(int spisanie) {
        SPISANIE = spisanie;
    }

    static void setK(int konferenciski) {
        KONFERENCISKI = konferenciski;
    }

    double rang() {
        int suma = 0;
        for (int i = 0; i < n; ++i) {
            if (trudovi[i].get_znak() == 'c' || trudovi[i].get_znak() == 'C') {
                suma += KONFERENCISKI;
            } else if (trudovi[i].get_znak() == 'j' || trudovi[i].get_znak() == 'J') {
                suma += SPISANIE;
            }
        }
        return Student::rang() + suma;
    }

    PhDStudent &operator+=(Trud &t) {
        if (t.get_godina() < getUpis()) {
            throw Exception();
        } else {
            Trud *tmp = new Trud[n + 1];
            for (int i = 0; i < n; ++i) {
                tmp[i] = trudovi[i];
            }
            tmp[n++] = t;
            delete[]trudovi;
            trudovi = tmp;
        }
        return *this;
    }
};

int PhDStudent::KONFERENCISKI = 1;
int PhDStudent::SPISANIE = 3;

int main() {
    int testCase;
    cin >> testCase;

    int god, indeks, n, god_tr, m, n_tr;
    int izbor; //0 za Student, 1 za PhDStudent
    char ime[30];
    int oceni[50];
    char tip;
    Trud trud[50];

    if (testCase == 1) {
        cout << "===== Testiranje na klasite ======" << endl;
        cin >> ime;
        cin >> indeks;
        cin >> god;
        cin >> n;
        for (int j = 0; j < n; j++)
            cin >> oceni[j];
        Student s(ime, indeks, god, oceni, n);
        cout << s;

        cin >> ime;
        cin >> indeks;
        cin >> god;
        cin >> n;
        for (int j = 0; j < n; j++)
            cin >> oceni[j];
        cin >> n_tr;
        for (int j = 0; j < n_tr; j++) {
            cin >> tip;
            cin >> god_tr;
            Trud t(tip, god_tr);
            trud[j] = t;
        }
        try {
            PhDStudent phd(ime, indeks, god, oceni, n, trud, n_tr);
            cout << phd;
        } catch (Exception &e) {
            e.print();
        }
    }
    if (testCase == 2) {
        cout << "===== Testiranje na operatorot += ======" << endl;
        Student **niza;
        cin >> m;
        niza = new Student *[m];
        for (int i = 0; i < m; i++) {
            cin >> izbor;
            cin >> ime;
            cin >> indeks;
            cin >> god;
            cin >> n;
            for (int j = 0; j < n; j++)
                cin >> oceni[j];

            if (izbor == 0) {
                niza[i] = new Student(ime, indeks, god, oceni, n);
            } else {
                cin >> n_tr;
                for (int j = 0; j < n_tr; j++) {
                    cin >> tip;
                    cin >> god_tr;
                    Trud t(tip, god_tr);
                    trud[j] = t;
                }
                try {
                    niza[i] = new PhDStudent(ime, indeks, god, oceni, n, trud, n_tr);
                } catch (Exception &e) {
                    e.print();
                }
            }
        }

        // pecatenje na site studenti
        cout << "\nLista na site studenti:\n";
        for (int i = 0; i < m; i++)
            cout << *niza[i];

        int flag = 0;
        Trud t;
        cin >> indeks;
        cin >> t;
        for (int i = 0; i < m; ++i) {
            if (indeks == niza[i]->getIDX()) {
                PhDStudent *tmp = dynamic_cast<PhDStudent *>(niza[i]);
                if (tmp != nullptr) {
                    flag++;
                    try {
                        *tmp += t;
                    }
                    catch (Exception &e) {
                        e.print();
                    }
                }
            }
        }
        if (!flag) {
            cout << "Ne postoi PhD student so indeks " << indeks << endl;
        }
        // pecatenje na site studenti
        cout << "\nLista na site studenti:\n";
        for (int i = 0; i < m; i++)
            cout << *niza[i];
    }
    if (testCase == 3) {
        cout << "===== Testiranje na operatorot += ======" << endl;
        Student **niza;
        cin >> m;
        niza = new Student *[m];
        for (int i = 0; i < m; i++) {
            cin >> izbor;
            cin >> ime;
            cin >> indeks;
            cin >> god;
            cin >> n;
            for (int j = 0; j < n; j++)
                cin >> oceni[j];

            if (izbor == 0) {
                niza[i] = new Student(ime, indeks, god, oceni, n);
            } else {
                cin >> n_tr;
                for (int j = 0; j < n_tr; j++) {
                    cin >> tip;
                    cin >> god_tr;
                    Trud t(tip, god_tr);
                    trud[j] = t;
                }
                niza[i] = new PhDStudent(ime, indeks, god, oceni, n, trud, n_tr);
            }
        }
        // pecatenje na site studenti
        cout << "\nLista na site studenti:\n";
        for (int i = 0; i < m; i++)
            cout << *niza[i];

        int flag = 0;
        Trud t;
        cin >> indeks;
        cin >> t;
        for (int i = 0; i < m; ++i) {
            if (indeks == niza[i]->getIDX()) {
                PhDStudent *tmp = dynamic_cast<PhDStudent *>(niza[i]);
                if (tmp != nullptr) {
                    flag++;
                    try {
                        *tmp += t;
                    }
                    catch (Exception &e) {
                        e.print();
                    }
                }
            }
        }
        if (!flag) {
            cout << "Ne postoi PhD student so indeks " << indeks << endl;
        }

        // pecatenje na site studenti
        cout << "\nLista na site studenti:\n";
        for (int i = 0; i < m; i++)
            cout << *niza[i];
    }
    if (testCase == 4) {
        cout << "===== Testiranje na isklucoci ======" << endl;

        cin >> ime;
        cin >> indeks;
        cin >> god;
        cin >> n;
        for (int j = 0; j < n; j++)
            cin >> oceni[j];
        cin >> n_tr;
        for (int j = 0; j < n_tr; j++) {
            cin >> tip;
            cin >> god_tr;
            Trud t(tip, god_tr);
            trud[j] = t;
        }
        // Attempt to create a PhDStudent object
        try {
            PhDStudent phd(ime, indeks, god, oceni, n, trud, n_tr);
            cout << phd;
        }
        catch (Exception &e) {
            e.print();
        }

    }
    if (testCase == 5) {
        cout << "===== Testiranje na isklucoci ======" << endl;
        Student **niza;
        cin >> m;
        niza = new Student *[m];
        for (int i = 0; i < m; i++) {
            cin >> izbor;
            cin >> ime;
            cin >> indeks;
            cin >> god;
            cin >> n;
            for (int j = 0; j < n; j++)
                cin >> oceni[j];

            if (izbor == 0) {
                niza[i] = new Student(ime, indeks, god, oceni, n);
            } else {
                cin >> n_tr;
                for (int j = 0; j < n_tr; j++) {
                    cin >> tip;
                    cin >> god_tr;
                    Trud t(tip, god_tr);
                    trud[j] = t;
                }
                niza[i] = new PhDStudent(ime, indeks, god, oceni, n, trud, n_tr);
            }
        }
        // pecatenje na site studenti
        cout << "\nLista na site studenti:\n";
        for (int i = 0; i < m; i++)
            cout << *niza[i];

        int flag = 0;
        Trud t;
        cin >> indeks;
        cin >> t;
        for (int i = 0; i < m; ++i) {
            if (indeks == niza[i]->getIDX()) {
                PhDStudent *tmp = dynamic_cast<PhDStudent *>(niza[i]);
                if (tmp != nullptr) {
                    flag++;
                    try {
                        *tmp += t;
                    }
                    catch (Exception &e) {
                        e.print();
                    }
                }
            }
        }
        if (!flag) {
            cout << "Ne postoi PhD student so indeks " << indeks << endl;
        }
        // pecatenje na site studenti
        cout << "\nLista na site studenti:\n";
        for (int i = 0; i < m; i++)
            cout << *niza[i];
    }
    if (testCase == 6) {
        cout << "===== Testiranje na static clenovi ======" << endl;
        Student **niza;
        cin >> m;
        niza = new Student *[m];
        for (int i = 0; i < m; i++) {
            cin >> izbor;
            cin >> ime;
            cin >> indeks;
            cin >> god;
            cin >> n;
            for (int j = 0; j < n; j++)
                cin >> oceni[j];

            if (izbor == 0) {
                niza[i] = new Student(ime, indeks, god, oceni, n);
            } else {
                cin >> n_tr;
                for (int j = 0; j < n_tr; j++) {
                    cin >> tip;
                    cin >> god_tr;
                    Trud t(tip, god_tr);
                    trud[j] = t;
                }
                niza[i] = new PhDStudent(ime, indeks, god, oceni, n, trud, n_tr);
            }
        }
        // pecatenje na site studenti
        cout << "\nLista na site studenti:\n";
        for (int i = 0; i < m; i++)
            cout << *niza[i];

        int conf, journal;
        cin >> conf;
        cin >> journal;

        PhDStudent::setK(conf);
        PhDStudent::setJ(journal);

        // pecatenje na site studenti
        cout << "\nLista na site studenti:\n";
        for (int i = 0; i < m; i++)
            cout << *niza[i];
    }

    return 0;
}