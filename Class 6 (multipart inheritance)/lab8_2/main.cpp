
//Во една игротека има 2 типа играчки: топки и коцки. Коцките и топките се опишани со параметри како што се:
//
//боја (char *)
//густина (int).
//Дополнително за топките се знае и радиусот (int), додека за коцките целосните димензии (висина, ширина и длабочина – int).
//
//За секоја од класите треба да се дефинираат методи getMasa() и getVolumen(). Масата на играчката се пресметува како производ од волуменот и
//густината на играчката. За PI користете ја вредноста 3.14.
//
//Во функцијата main да се декларира променлива kupche што претставува динамички алоцирана низа кон Igrachka. Во зависност од првиот влезен
//параметар се внесуваат објекти од класите Topka или Kocka (1 - се внесува топка, 2 - се внесува коцка).
//
//Од тастатура да се внесат податоци за коцката на Петра Kocka petra. Во главната функција во да се отпечатат:
//
//Да се отпечати DA ако вкупната маса на сите играчки е поголема од масата на играчката на Петра, а NE во спротивно.
//Разликата по апсолутна вредност на волуменот на играчката со максимален волумен во купчето и волуменот на коцката на Петра. Форматот е:
//
//Razlikata e: {razlika}
//Задачата да се реши со тоа што класите Kocka и Topka ќе наследуваат од класите Forma и Igrachka.
//
//Дополнителни барања:
//
//Во класата Igrachka да се додаде уште една чисто виртуелна функција float getPlostina(). Истата да се имплементира во класите Kocka и Topka
//        Во главната функција, дополнително да се испечати и: Разликата по апсолутна вредност на плоштината на играчката со минимална плоштина
//        во купчето и плоштината на коцката на Петра во истиот формат како и второто барање погоре.


//Input
//3
//1
//crvena
//23
//3
//2
//zelena
//50
//2
//3
//3
//1
//sina
//30
//5
//crvena
//60
//12
//3
//7

//Result
//DA
//Razlikata e: 271.333
//Razlikata e: 240

#include <iostream>
#include <cmath>
#include <cstring>

using namespace std;

const float PI = 3.14;

class Igrachka {
public:
    virtual float getVolumen() = 0;
    virtual float getMasa() = 0;
    virtual float getPlostina() = 0;
};

class Forma {
protected:
    char boja[100];
    int gustina;
public:
    Forma(const char* _boja, int _gustina) {
        strcpy(boja, _boja);
        gustina = _gustina;
    }
};

class Topka : public Forma, public Igrachka {
private:
    int radius;
public:
    Topka(const char* _boja, int _gustina, int _radius) : Forma(_boja, _gustina) {
        this->radius = _radius;
    }

    float getVolumen() override {
        return (4.0 / 3.0) * PI * pow(radius, 3);
    }

    float getMasa() override {
        return getVolumen() * gustina;
    }

    float getPlostina() override {
        return 4 * PI * pow(radius, 2);
    }
};

class Kocka : public Forma, public Igrachka {
private:
    int visina, sirina, dlabocina;
public:
    Kocka(const char* _boja, int _gustina, int _visina, int _sirina, int _dlabocina) : Forma(_boja, _gustina) {
        this->visina = _visina;
        this->sirina = _sirina;
        this->dlabocina = _dlabocina;
    }

    float getVolumen() override {
        return visina * sirina * dlabocina;
    }

    float getMasa() override {
        return getVolumen() * gustina;
    }

    float getPlostina() override {
        return 2 * (visina * sirina + visina * dlabocina + sirina * dlabocina);
    }
};

int main() {
    int n;
    cin >> n;

    Igrachka** kupche = new Igrachka*[n];

    for (int i = 0; i < n; i++) {
        int tip;
        cin >> tip;

        char boja[100];
        int gustina;
        cin >> boja;
        cin >> gustina;

        if (tip == 1) {
            int radius;
            cin >> radius;
            kupche[i] = new Topka(boja, gustina, radius);
        } else if (tip == 2) {
            int visina, sirina, dlabocina;
            cin >> visina;
            cin >> sirina;
            cin >> dlabocina;
            kupche[i] = new Kocka(boja, gustina, visina, sirina, dlabocina);
        }
    }

    // Podatoci za igrachkata na Petra
    char boja_petra[100];
    int gustina_petra, visina_petra, shirina_petra, dlabochina_petra;
    cin >> boja_petra;
    cin >> gustina_petra;
    cin >> visina_petra;
    cin >> shirina_petra;
    cin >> dlabochina_petra;

    Kocka petra(boja_petra, gustina_petra, visina_petra, shirina_petra, dlabochina_petra);

    // Baranje 1
    float total_mass = 0;
    for (int i = 0; i < n; i++) {
        total_mass += kupche[i]->getMasa();
    }

    cout << (total_mass > petra.getMasa() ? "DA" : "NE") << endl;

    // Baranje 2
    float max_volume_diff = 0;
    for (int i = 0; i < n; i++) {
        float volume_diff = abs(kupche[i]->getVolumen() - petra.getVolumen());
        if (volume_diff > max_volume_diff) {
            max_volume_diff = volume_diff;
        }
    }

    cout << "Razlikata e: " << max_volume_diff << endl;

    // Дополнително барање 2
    float min_area_diff = 9999999;
    for (int i = 0; i < n; i++) {
        float area_diff = abs(kupche[i]->getPlostina() - petra.getPlostina());
        if (area_diff < min_area_diff) {
            min_area_diff = area_diff;
        }
    }

    cout << "Razlikata e: " << min_area_diff << endl;

    delete[] kupche;

    return 0;
}


