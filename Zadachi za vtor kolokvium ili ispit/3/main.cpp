//
// Created by User on 2.6.2024.
//
#include<iostream>
#include<string.h>

using namespace std;


class Kurs {
private:
    char ime[20];
    int krediti;
public:
    Kurs(char *ime, int krediti) {
        strcpy(this->ime, ime);
        this->krediti = krediti;
    }

    Kurs() {
        strcpy(this->ime, "");
        krediti = 0;
    }

    bool operator==(const char *ime) const {
        return strcmp(this->ime, ime) == 0;
    }

    char const *getIme() const {
        return ime;
    }

    void pecati() const { cout << ime << " " << krediti << "ECTS"; }
};

class Student {
private:
    int *ocenki;
    int brojOcenki;

protected:
    int indeks;

public:
    Student(int indeks, int *ocenki, int brojOcenki) {
        this->indeks = indeks;
        this->brojOcenki = brojOcenki;
        this->ocenki = new int[brojOcenki];
        for (int i = 0; i < brojOcenki; i++) this->ocenki[i] = ocenki[i];
    }

    Student(const Student &k) {
        this->indeks = k.indeks;
        this->brojOcenki = k.brojOcenki;
        this->ocenki = new int[k.brojOcenki];
        for (int i = 0; i < k.brojOcenki; i++) this->ocenki[i] = k.ocenki[i];
    }

    Student operator=(const Student &k) {
        if (&k == this) return *this;
        this->indeks = k.indeks;
        this->brojOcenki = k.brojOcenki;
        delete[] ocenki;
        this->ocenki = new int[k.brojOcenki];
        for (int i = 0; i < k.brojOcenki; i++) this->ocenki[i] = k.ocenki[i];
        return *this;
    }

    ~Student() { delete[] ocenki; }

    //dopolni ja klasata
    virtual int getBodovi() {
        int brojac = 0;
        for (int i = 0; i < brojOcenki; ++i) {
            if (ocenki[i] > 5) {
                brojac++;
            }
        }
        return (brojac * 100) / brojOcenki;
    }

    virtual void pecati() {
        cout << indeks;
    }
};

class Predavach {
private:
    Kurs kursevi[10];
    int brojKursevi;

protected:
    char *imeIPrezime;

public:
    Predavach(char *imeIPrezime, Kurs *kursevi, int brojKursevi) {
        this->brojKursevi = brojKursevi;
        for (int i = 0; i < brojKursevi; i++) this->kursevi[i] = kursevi[i];
        this->imeIPrezime = new char[strlen(imeIPrezime) + 1];
        strcpy(this->imeIPrezime, imeIPrezime);
    }

    Predavach(const Predavach &p) {
        this->brojKursevi = p.brojKursevi;
        for (int i = 0; i < p.brojKursevi; i++) this->kursevi[i] = p.kursevi[i];
        this->imeIPrezime = new char[strlen(p.imeIPrezime) + 1];
        strcpy(this->imeIPrezime, p.imeIPrezime);
    }

    Predavach operator=(const Predavach &p) {
        if (this == &p) return *this;
        this->brojKursevi = p.brojKursevi;
        for (int i = 0; i < p.brojKursevi; i++) this->kursevi[i] = p.kursevi[i];
        this->imeIPrezime = new char[strlen(p.imeIPrezime) + 1];
        delete[] imeIPrezime;
        strcpy(this->imeIPrezime, p.imeIPrezime);
        return *this;
    }

    ~Predavach() { delete[] imeIPrezime; }

    int getBrojKursevi() const { return brojKursevi; }

    char *const getImeIPrezime() const { return imeIPrezime; }

    Kurs operator[](int i) const {
        if (i < brojKursevi && i >= 0)
            return kursevi[i];
        else return Kurs();
    }

    void pecati() const {
        cout << imeIPrezime << " (";
        for (int i = 0; i < brojKursevi; i++) {
            kursevi[i].pecati();
            if (i < brojKursevi - 1) cout << ", "; else cout << ")";
        }
    }
};


//mesto za vashiot kod
class NoCourseException {
private:
    int indeks;
public:
    NoCourseException(int indeks) {
        this->indeks = indeks;
    }

    void print() {
        cout << "Demonstratorot so indeks " << indeks << " ne drzi laboratoriski vezbi" << endl;
    }

};

class Demonstrator : public Student, public Predavach {
private:
    int broj_na_casovi;
public:
    Demonstrator(int indeks, int *ocenki, int brojOcenki, char *imeIPrezime, Kurs *kursevi, int brojKursevi,
                 int brojNaChasovi) :
            Student(indeks, ocenki, brojOcenki), Predavach(imeIPrezime, kursevi, brojKursevi) {
        this->broj_na_casovi = brojNaChasovi;
    }

    int getBodovi() {
        double osnovniBodovi = Student::getBodovi();
        if (getBrojKursevi() == 0) {
            throw NoCourseException(indeks);
        }
        return osnovniBodovi + (20 * broj_na_casovi) / getBrojKursevi();
    }

    void pecati() {
        Student::pecati();
        cout << ": " << getImeIPrezime() << " (";
        for (int i = 0; i < getBrojKursevi(); i++) {
            operator[](i).pecati();
            if (i < getBrojKursevi() - 1) cout << ", ";
            else cout << ")";
        }
    }
};

Student &vratiNajdobroRangiran(Student **studenti, int n) {
    int maxBodovi = -1;
    Student *najdobarStudent = studenti[0];
    int indeks = 0;
    for (int i = 1; i < n; i++) {
        int bodovi = 0;
        try {
            bodovi = studenti[i]->getBodovi();
        } catch (NoCourseException &e) {
            e.print();
        }
        if (bodovi > maxBodovi) {
            maxBodovi = bodovi;
            najdobarStudent = studenti[i];
        }
    }
    return *najdobarStudent;
}

void pecatiDemonstratoriKurs(char *kurs, Student **studenti, int n) {
    for (int i = 0; i < n; i++) {
        Demonstrator *d = dynamic_cast<Demonstrator *>(studenti[i]);
        if (d != nullptr) {
            for (int j = 0; j < d->getBrojKursevi(); j++) {
                if (d->operator[](j) == kurs) {
                    d->pecati();
                    cout << endl;
                    break;
                }
            }
        }
    }
}

int main() {

    Kurs kursevi[10];
    int indeks, brojKursevi, ocenki[20], ocenka, brojOcenki, tip, brojCasovi, krediti;
    char ime[20], imeIPrezime[50];

    cin >> tip;

    if (tip == 1) //test class Demonstrator
    {
        cout << "-----TEST Demonstrator-----" << endl;
        cin >> indeks >> brojOcenki;
        for (int i = 0; i < brojOcenki; i++) {
            cin >> ocenka;
            ocenki[i] = ocenka;
        }
        cin >> imeIPrezime >> brojKursevi;
        for (int i = 0; i < brojKursevi; i++) {
            cin >> ime >> krediti;
            kursevi[i] = Kurs(ime, krediti);
        }
        cin >> brojCasovi;

        Demonstrator d(indeks, ocenki, brojOcenki, imeIPrezime, kursevi, brojKursevi, brojCasovi);
        cout << "Objekt od klasata Demonstrator e kreiran";

    } else if (tip == 2) //funkcija pecati vo Student
    {
        cout << "-----TEST pecati-----" << endl;
        cin >> indeks >> brojOcenki;
        for (int i = 0; i < brojOcenki; i++) {
            cin >> ocenka;
            ocenki[i] = ocenka;
        }

        Student s(indeks, ocenki, brojOcenki);
        s.pecati();

    } else if (tip == 3) //funkcija getVkupnaOcenka vo Student
    {
        cout << "-----TEST getVkupnaOcenka-----" << endl;
        cin >> indeks >> brojOcenki;
        for (int i = 0; i < brojOcenki; i++) {
            cin >> ocenka;
            ocenki[i] = ocenka;
        }
        Student s(indeks, ocenki, brojOcenki);
        cout << "Broj na bodovi: " << s.getBodovi() << endl;

    } else if (tip == 4) //funkcija getVkupnaOcenka vo Demonstrator
    {
        cout << "-----TEST getVkupnaOcenka-----" << endl;
        cin >> indeks >> brojOcenki;
        for (int i = 0; i < brojOcenki; i++) {
            cin >> ocenka;
            ocenki[i] = ocenka;
        }
        cin >> imeIPrezime >> brojKursevi;
        for (int i = 0; i < brojKursevi; i++) {
            cin >> ime >> krediti;
            kursevi[i] = Kurs(ime, krediti);
        }
        cin >> brojCasovi;

        Demonstrator d(indeks, ocenki, brojOcenki, imeIPrezime, kursevi, brojKursevi, brojCasovi);
        cout << "Broj na bodovi: " << d.getBodovi() << endl;


    } else if (tip == 5) //funkcija pecati vo Demonstrator
    {
        cout << "-----TEST pecati -----" << endl;
        cin >> indeks >> brojOcenki;
        for (int i = 0; i < brojOcenki; i++) {
            cin >> ocenka;
            ocenki[i] = ocenka;
        }
        cin >> imeIPrezime >> brojKursevi;
        for (int i = 0; i < brojKursevi; i++) {
            cin >> ime >> krediti;
            kursevi[i] = Kurs(ime, krediti);
        }
        cin >> brojCasovi;

        Demonstrator d(indeks, ocenki, brojOcenki, imeIPrezime, kursevi, brojKursevi, brojCasovi);
        d.pecati();

    } else if (tip == 6) //site klasi
    {
        cout << "-----TEST Student i Demonstrator-----" << endl;
        cin >> indeks >> brojOcenki;
        for (int i = 0; i < brojOcenki; i++) {
            cin >> ocenka;
            ocenki[i] = ocenka;
        }
        cin >> imeIPrezime >> brojKursevi;
        for (int i = 0; i < brojKursevi; i++) {
            cin >> ime >> krediti;
            kursevi[i] = Kurs(ime, krediti);
        }
        cin >> brojCasovi;

        Student *s = new Demonstrator(indeks, ocenki, brojOcenki, imeIPrezime, kursevi, brojKursevi, brojCasovi);
        s->pecati();
        cout << "\nBroj na bodovi: " << s->getBodovi() << endl;
        delete s;


    } else if (tip == 7) //funkcija vratiNajdobroRangiran
    {
        cout << "-----TEST vratiNajdobroRangiran-----" << endl;
        int k, opt;
        cin >> k;
        Student **studenti = new Student *[k];
        for (int j = 0; j < k; j++) {
            cin >> opt; //1 Student 2 Demonstrator
            cin >> indeks >> brojOcenki;
            for (int i = 0; i < brojOcenki; i++) {
                cin >> ocenka;
                ocenki[i] = ocenka;
            }
            if (opt == 1) {
                studenti[j] = new Student(indeks, ocenki, brojOcenki);
            } else {
                cin >> imeIPrezime >> brojKursevi;
                for (int i = 0; i < brojKursevi; i++) {
                    cin >> ime >> krediti;
                    kursevi[i] = Kurs(ime, krediti);
                }
                cin >> brojCasovi;
                studenti[j] = new Demonstrator(indeks, ocenki, brojOcenki, imeIPrezime, kursevi, brojKursevi,
                                               brojCasovi);
            }
        }
        Student &najdobar = vratiNajdobroRangiran(studenti, k);
        cout << "Maksimalniot broj na bodovi e:" << najdobar.getBodovi();
        cout << "\nNajdobro rangiran:";
        najdobar.pecati();

        for (int j = 0; j < k; j++) delete studenti[j];
        delete[] studenti;
    } else if (tip == 8) //funkcija pecatiDemonstratoriKurs
    {
        cout << "-----TEST pecatiDemonstratoriKurs-----" << endl;
        int k, opt;
        cin >> k;
        Student **studenti = new Student *[k];
        for (int j = 0; j < k; j++) {
            cin >> opt; //1 Student 2 Demonstrator
            cin >> indeks >> brojOcenki;
            for (int i = 0; i < brojOcenki; i++) {
                cin >> ocenka;
                ocenki[i] = ocenka;
            }
            if (opt == 1) {
                studenti[j] = new Student(indeks, ocenki, brojOcenki);
            } else {
                cin >> imeIPrezime >> brojKursevi;
                for (int i = 0; i < brojKursevi; i++) {
                    cin >> ime >> krediti;
                    kursevi[i] = Kurs(ime, krediti);
                }
                cin >> brojCasovi;
                studenti[j] = new Demonstrator(indeks, ocenki, brojOcenki, imeIPrezime, kursevi, brojKursevi,
                                               brojCasovi);
            }
        }
        char kurs[20];
        cin >> kurs;
        cout << "Demonstratori na " << kurs << " se:" << endl;
        pecatiDemonstratoriKurs(kurs, studenti, k);
        for (int j = 0; j < k; j++) delete studenti[j];
        delete[] studenti;

    }


    return 0;
}

