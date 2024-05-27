//Сите елементи кои ги превезуваат камионите имаат одредена маса. Имплементирајте апстрактна класа ImaMasa од која што ќе наследуваат
// сите класи кои имаат маса. Во оваа класа треба да се дефинираат методите:
//
//double vratiMasa() враќа маса изразена во kg
//void pecati() печати информации за соодветниот објект
//        Нека еден камион превезува пијалоци и тоа: пакет сокови и пакет вина. Да се дефинираат класите PaketSok и PaketVino кои ги
//        имплементираат методите од апстрактната класа ImaMasa. При тоа да се земе предвид дека класите PaketSok и PaketVino се изведени
//        од класата PaketPijalok. Притоа да се земат дадените податоци:
//
//Класа PaketPijalok:
//
//членови:
//volumenEden double
//        kolicina int
//        методи:
//double vratiMasa()
//void pecati()
//int getKolicina()
//Класа PaketSok:
//
//членови:
//volumenEden double
//        kolicina int
//        daliGaziran bool
//        методи:
//double vratiMasa()
//void pecati()
//Класа PaketVino:
//
//членови:
//volumenEden double
//        kolicina int
//        procentAlkohol double
//        методи:
//double vratiMasa()
//double getProcentAlkohol()
//void pecati()
//Еден пијалок има маса пресметана како производ на волуменот и густината (0.8kg/dm3) и масата на амбалажата (0.2kg). Овие податоци за
//густината и за масата на амбалажата да се стават како статички податоци за класата PaketPijalok. Масата на пакетот е производ на масата на
//еден пијалок и количината на пијалоци која ја има во пакетот. Соковите кои не се газирани имаат дополнителна маса од 0.1kg по пијалок. За
//вината, масата се добива како производ од масата на пакетот пресметан по правилата за секој пијалок помножен со коефициентот: (0.9+procentAlkohol).
//
//Покрај овие класи, да се имплементира класата Kamion. За еден камион се чуваат информации за:
//
//регистрацијата char*
//        возачот char*
//        елементите кои ги превезува камионот (низа од покажувачи од ImaMasa)
//Во класата Kamion покрај методите set и get дефинирајте ги и следните методи:
//
//Kamion(char* ) конструктор со кој се генерира празен камион (без товар) и само возач
//void registriraj(char*) се додава регистрацијата на камионот
//void dodadiElement(ImaMasa) се додава нов елемент во камионот
//double vratiVkupnaMasa() се враќа вкупната маса на товарот кој го пренесува камионот
//void pecati() се печатат сите елементи во камионот заедно со регистрацијата и името на возачот
//        Kamion pretovar(char* , char* ) се врши претовар во нов камион, но во новиот покрај тоа што се менуваат регистрацијата и името на
//        возачот (аргументи), се отстранува пакетот со најголема маса.
//Со помош на правилата за справување со исклучоци да се модифицира програмата така што ќе се запазат следните правила: - Регистрацијата има
//8 карактери, така што првите два и последните два мора да бидат букви. Да се определи каде ќе се фрли соодветниот исклучок. Онаму каде што ќе
//се фати исклучокот, ќе се отпечати "Pogresno vnesena registracija!".
#include <iostream>
#include <cstring>

using namespace std;

class InvalidRegistrationException {
public:
    void printMessage() {
        cout << "Pogresno vnesena registracija" << endl;
    }
};

class ImaMasa {
public:
    virtual double vratiMasa() = 0;

    virtual void pecati() = 0;

    virtual double masaZaEden() = 0;

    virtual ~ImaMasa() {}
};

class PaketPijalok : public ImaMasa {
protected:
    double volumenEden;
    int kolicina;
    static double gustina;
    static double masaAmbalaza;

public:
    PaketPijalok(double v, int k) {
        this->volumenEden = v;
        this->kolicina = k;
    }

    double masaZaEden() override {
        return volumenEden * gustina * masaAmbalaza;
    }

    double vratiMasa() {
        return masaZaEden() * kolicina;
    }

    void pecati() override {
        cout << "kolicina " << kolicina << ", ";
    }
};

double PaketPijalok::gustina = 0.8;
double PaketPijalok::masaAmbalaza = 0.2;

class PaketSok : public PaketPijalok {
    bool daliGaziran;
public:
    PaketSok(double v, int k, bool g) : PaketPijalok(v, k) {
        this->daliGaziran = g;
    }

    double masaZaEden() override {
        return PaketPijalok::masaZaEden() + 0.1;
    }

    double vratiMasa() override {
        return !daliGaziran ? masaZaEden() * kolicina : PaketPijalok::vratiMasa();
    }

    void pecati() override {
        cout << "Paket sok" << endl;
        PaketPijalok::pecati();
        cout << "so po " << masaZaEden() << " l(dm3)" << endl;
    }
};


class PaketVino : public PaketPijalok {
    double procentAlkohol;

public:
    PaketVino(double v, int k, double p) : PaketPijalok(v, k) {
        this->procentAlkohol = p;
    }

    double masaZaEden() override {
        return PaketPijalok::masaZaEden() * (0.9 + procentAlkohol);
    }

    double vratiMasa() override {
        return masaZaEden() * kolicina;
    }

    void pecati() override {
        cout << "Paket vino" << endl;
        PaketPijalok::pecati();
        cout << procentAlkohol * 100 << "% alkohol od po " << masaZaEden() << " l(dm3)" << endl;
    }
};

class Kamion {
    char registracija[9];
    char vozac[20];
    ImaMasa **elementi;
    int brojElementi;

    bool validirajRegistracija(const char *reg) {
        if (strlen(reg) != 8)
            return false;
        if (!isalpha(reg[0]) || !isalpha(reg[1]) || !isalpha(reg[6]) || !isalpha(reg[7]))
            return false;
        return true;
    }

public:
    Kamion(char *vozac) {
        strcpy(this->vozac, vozac);
        strcpy(this->registracija, "");
        this->brojElementi = 0;
        this->elementi = new ImaMasa * [brojElementi];
    }

    void registriraj(const char *reg) {
        if (!validirajRegistracija(reg)) {
            throw InvalidRegistrationException();
        }
        strcpy(this->registracija, reg);
    }

    void dodadiElement(ImaMasa *element) {
        elementi[brojElementi++] = element;
    }

    double vratiVkupnaMasa() {
        double vkupnaMasa = 0;
        for (int i = 0; i < brojElementi; ++i) {
            vkupnaMasa += elementi[i]->vratiMasa();
        }
        return vkupnaMasa;
    }

    void pecati() {
        cout << "Kamion so registracija " << registracija << " i vozac " << vozac << " prenesuva:" << endl;
        for (int i = 0; i < brojElementi; ++i) {
            elementi[i]->pecati();
        }
    }

    Kamion pretovar(char *novaRegistracija, char *novVozac) {
        Kamion novKamion(novVozac);

        try {
            novKamion.registriraj(novaRegistracija);
        } catch (InvalidRegistrationException &ex) {
            ex.printMessage();
            throw;
        }

        int maxIdx = 0;
        double maxMasa = elementi[0]->vratiMasa();
        for (int i = 1; i < brojElementi; ++i) {
            if (elementi[i]->vratiMasa() > maxMasa) {
                maxMasa = elementi[i]->vratiMasa();
                maxIdx = i;
            }
        }

        for (int i = 0; i < brojElementi; ++i) {
            if (i != maxIdx) {
                novKamion.dodadiElement(elementi[i]);
            }
        }
        return novKamion;
    }


    ~Kamion() {
        delete[] elementi;
    }
};

int main() {
    char ime[20], reg[9];
    double vol;
    int kol;
    bool g;
    double proc;

    cin >> reg;
    cin >> ime;
    Kamion A(ime);

    try {
        A.registriraj(reg);
    } catch (InvalidRegistrationException &ex) {
        ex.printMessage();
        return 0;
    }

    ImaMasa **d = new ImaMasa *[5];
    cin >> vol >> kol >> g;
    d[0] = new PaketSok(vol, kol, g);
    cin >> vol >> kol >> proc;
    d[1] = new PaketVino(vol, kol, proc);
    cin >> vol >> kol >> proc;
    d[2] = new PaketVino(vol, kol, proc);
    cin >> vol >> kol >> g;
    d[3] = new PaketSok(vol, kol, g);
    cin >> vol >> kol >> proc;
    d[4] = new PaketVino(vol, kol, proc);

    A.dodadiElement(d[0]);
    A.dodadiElement(d[1]);
    A.dodadiElement(d[2]);
    A.dodadiElement(d[3]);
    A.dodadiElement(d[4]);
    A.pecati();
    cout << "Vkupna masa: " << A.vratiVkupnaMasa() << endl;

    cin >> reg;
    cin >> ime;

    Kamion B = A.pretovar(reg, ime);
    B.pecati();
    cout << "Vkupna masa: " << B.vratiVkupnaMasa() << endl;

}

