//--
//
//Потребно е да конструирате абстракна класа Shape со само еден параметар:
//
//страна (int)
//Конструктори:
//
//Shape()
//Shape(int a)
//И виртуелните методи:
//
//double plostina()
//void pecati()
//int getType()
//Од таа класа вие треба да конструирате 3 изведени класи:
//
//Square
//Circle
//Triangle
//        Изведените класи немаат дополнителни парамтери, туку ја наследуваат страната од Shape
//
//        Конструктори:
//
//Конструкторот на изведените класи ќе зема еден аругмент, страната на фигурата.
//
//При пишување на конструкторот на изведените класи да се искористи констукторот на родител класата
//
//Методи:
//
//Секоја од класите си има своја формула за plostina() соодветна за нивната геометриска фигура
//
//        Формула за плоштина на квадрат а * a
//Формула за плоштина на круг 3.14 * a * a
//Формула за плоштина на триаголник (sqrt(3)/4) * side * side
//За pecati() методот упатете се кон outputot за тест случајите.
//
//getType() методот треба да враќа:
//
//1 за Square
//2 за Circle
//3 за Triangle
//Поени: 5
//
//--
//
//Дефинирајте го методот void checkNumTypes(Shape** niza, int n) така што ќе испечати во три реда колку квадрати, кругови и триаголници има во низата.
//
//Поени: 2
//
//--
//
//Покрај тоа треба да ја допишете Main класата така што ќе алоцирате динамичка низа од покажувачи кон класата Shape.
//
//Потоа кај секој покажувач од низата зависно од дадениот input да алоцирате објект од една од трите изведени класи.
//
//Input:
//
//Прво се добива n - големината на динамичката низа. Потоа n пати се добиваат пар цели броеви t i a, каде што t е типот на објектот и а е страната на објектот.
//
//Пример:
//
//3
//
//1 3 //квадрат со страна со должина 3
//
//2 2 //круг со страна со должина 2
//
//3 1 //триаголник со страна со должина 1
//
//Поени: 3
//
//--

// print format
//Kvadrat so plostina = 4
//Krug so plostina = 3.14
//Triagolnik so plostina = 3.89711
//Triagolnik so plostina = 0.433013
//Krug so plostina = 12.56
//Broj na kvadrati vo nizata = 1
//Broj na krugovi vo nizata = 2
//Broj na triagolnici vo nizata = 2

#include <iostream>
#include <cmath>

using namespace std;


class Shape {
protected:
    int side;

public:
    Shape() {
        this->side = 0;
    }

    Shape(int side) {
        this->side = side;
    }

    virtual double plostina() = 0;

    virtual void pecati() = 0;

    virtual int getType() = 0;
};

class Square : public Shape{
public:
    Square(int side) : Shape(side) {

    }

    double plostina() override {
        return side * side;
    }

    void pecati() override {
        cout << "Kvadrat so plostina = " << plostina() << endl;
    }

    int getType() override {
        return 1;
    }
};

class Circle : public Shape {
public:
    Circle(int side) : Shape(side) {

    }

    double plostina() override {
        return side * side * 3.14;
    }

    void pecati() override {
        cout << "Krug so plostina = " << plostina() << endl;
    }

    int getType() override {
        return 2;
    }
};

class Triangle : public Shape {
public:
    Triangle(int side) : Shape(side) {

    }

//    K = (1/4) * √3 * a * a
    double plostina() override {
        return (sqrt(3) / 4) * side * side;
    }

    void pecati() override {
        cout << "Triagolnik so plostina = " << plostina() << endl;
    }

    int getType() override {
        return 3;
    }
};


void checkNumTypes(Shape** niza, int n) {
    int countSquares = 0, countCircles = 0, countTriangles = 0;

    for(int i = 0; i < n; i++) {
        if(niza[i]->getType() == 1) {
            countSquares++;
        } else if(niza[i]->getType() == 2) {
            countCircles++;
        } else {
            countTriangles++;
        }
    }

    cout << "Broj na kvadrati vo nizata = " << countSquares << endl;
    cout << "Broj na krugovi vo nizata = " << countCircles << endl;
    cout << "Broj na triagolnici vo nizata = " << countTriangles << endl;
}

int main() {
    int n;
    cin >> n;

    Shape **niza = new Shape *[n];
    int classType;
    int side;

    for (int i = 0; i < n; ++i) {
        cin >> classType;
        cin >> side;

        if (classType == 1) {
            niza[i] = new Square(side);
        } else if (classType == 2) {
            niza[i] = new Circle(side);
        } else {
            niza[i] = new Triangle(side);
        }
    }


    for (int i = 0; i < n; ++i) {
        niza[i]->pecati();
    }

    checkNumTypes(niza, n);

    delete[] niza;

    return 0;
}
