//Да се дефинира апстрктна класа Number со следните чисто виртуелни методи:
//
//double doubleValue() -ја враќа децималната вредност на даден број
//int intValue()- ја враќа целобројната вредност на даден број
//void print() - печати информации за бројот. (1 поен)
//Од оваа класа да се изведат две класи:
//
//Integer (во која што се чува еден број од тип int)
//Double (во која што се чува еден број од тип double) (1 поен).
//За двете изведени класи да се имплементираaт соодветен конструктори, како и да се препокријат методите од основната класа. (1 поени)
//
//Да се преоптовари операторот == којшто ќе споредува два броеви според нивната вредност (објекти од класа Number) (1 поен)
//
//Дополнително да се дефинира класа Numbers во која што ќе се чуваат:
//
//динамички алоцирана низа од покажувачи кон објекти од класата Number
//број на елементи во низата од покажувачи
//За класата да се имплементира соодветен конструктор (default) , како и: (1 поени)
//
//операторот += за додавање на броеви во низата од броеви (1 поен)
//Бројот се додава ако и само ако сите броеви што се веќе додадени во низата се различни од него
//функција void statistics() која што печати информации за броевите во низата: (2 поени)
//Count of numbers: [број на броеви во низата
//
//Sum of all numbers: [сума на сите броеви во низата]
//
//Count of integer numbers: [број на цели броеви (Integer)]
//
//Sum of integer numbers: [сума на сите цели броеви (Integer)]
//
//Count of double numbers: [број на децимални броеви (Double)]
//
//Sum of double numbers: [сума на сите децимални броеви (Double)]
//
//функција void integersLessThan (Integer n) која што ги печати сите цели броеви помали од бројот n (1 поен)
//функција void doublesBiggerThan (Double n) која што ги печати сите децимални броеви поголеми од бројот n (1 поен)

// format for output
//STATISTICS FOR THE NUMBERS -> from main
//Count of numbers: 2
//Sum of all numbers: 25.5
//Count of integer numbers: 1
//Sum of integer numbers: 10
//Count of double numbers: 1
//Sum of double numbers: 15.5
//INTEGER NUMBERS LESS THAN 11 -> from main
//Integer: 10 -> print()
//DOUBLE NUMBERS BIGGER THAN 10 -> from main
//Double: 15.5 -> print()

#include <iostream>
#include <cmath>

using namespace std;

class Number {
public:
    virtual double doubleValue() = 0;

    virtual int intValue() = 0;

    virtual void print() = 0;
};

class Integer : public Number {
    int number;
public:
    Integer(int number) {
        this->number = number;
    }

    double doubleValue() override {
        return (double) number;
    }

    int intValue() override {
        return number;
    }

    void print() override {
        cout << "Integer: " << number << endl;
    }
};

class Double : public Number {
    double number;
public:
    Double(double number) {
        this->number = number;
    }

    double doubleValue() override {
        return number;
    }

    int intValue() override {
        return (int) number;
    }

    void print() override {
        cout << "Double: " << number << endl;
    }
};

class Numbers {
    Number **numbers;
    int n;

    void copy(const Numbers &other) {
        this->n = other.n;
        this->numbers = new Number *[other.n];
        for (int i = 0; i < other.n; i++) {
            this->numbers[i] = other.numbers[i];
        }
    }

public:
    Numbers() {
        this->numbers = nullptr;
        this->n = 0;
    }

    Numbers(const Numbers &other) {
        copy(other);
    }

    Numbers &operator=(const Numbers &other) {
        if (this != &other) {
            delete[] numbers;
            copy(other);
        }
        return *this;
    }

    Numbers &operator+=(Number *number) {
        Number **temp = new Number *[n + 1];
        int counter = 0;

        for (int i = 0; i < n; i++) {
            temp[i] = numbers[i];
            if (temp[i]->doubleValue() != number->doubleValue()) {
                counter++;
            }
        }

        if (n == counter) {
            temp[n++] = number;
            delete[] numbers;
            numbers = temp;
        }

        return *this;
    }

    ~Numbers() {
        delete[] numbers;
    }

    //Count of numbers: [број на броеви во низата
//Sum of all numbers: [сума на сите броеви во низата]
//Count of integer numbers: [број на цели броеви (Integer)]
//Sum of integer numbers: [сума на сите цели броеви (Integer)]
//Count of double numbers: [број на децимални броеви (Double)]
//Sum of double numbers: [сума на сите децимални броеви (Double)]

    void statistics() {
        cout << "Count of numbers: " << n << endl;

        double sumAll = 0;
        int countInt = 0;
        double sumInt = 0;
        int countDouble = 0;
        double sumDouble = 0;

        for(int i = 0; i < n; i++) {
            sumAll += numbers[i]->doubleValue();
            if(dynamic_cast<Integer *>(numbers[i])) {
                countInt++;
                sumInt += numbers[i]->intValue();
            } else {
                countDouble++;
                sumDouble += numbers[i]->doubleValue();
            }
        }

        cout << "Sum of all numbers: " << sumAll << endl;
        cout << "Count of integer numbers: " << countInt << endl;
        cout << "Sum of integer numbers: " << sumInt << endl;
        cout << "Count of double numbers: " << countDouble << endl;
        cout << "Sum of double numbers: " << sumDouble << endl;
    }

    void integersLessThan(Integer n) {
        bool flag = false;
        for(int i = 0; i < this->n; i++) {
            Integer *integerP = dynamic_cast<Integer *>(numbers[i]);
            if(integerP != nullptr && integerP->intValue() < n.intValue()) {
                flag = true;
                integerP->print();
            }
        }

        if(!flag) cout << "None" << endl;
    }

    void doublesBiggerThan(Double n) {
        bool flag = false;
        for(int i = 0; i < this->n; i++) {
            Double *doubleP = dynamic_cast<Double *>(numbers[i]);
            if(doubleP != nullptr && doubleP->doubleValue() > n.doubleValue()) {
                flag = true;
                doubleP->print();
            }
        }

        if(!flag) cout << "None" << endl;
    }
};

int main() {
    int n;
    cin >> n;
    Numbers numbers;
    for (int i = 0; i < n; i++) {
        int type;
        double number;
        cin >> type >> number;
        if (type == 0) {
            Integer *integer = new Integer((int) number);
            numbers += integer;
        } else {
            Double *doublee = new Double(number);
            numbers += doublee;
        }
    }

    int lessThan;
    double biggerThan;

    cin >> lessThan;
    cin >> biggerThan;

    cout << "STATISTICS FOR THE NUMBERS\n";
    numbers.statistics();
    cout << "INTEGER NUMBERS LESS THAN " << lessThan << endl;
    numbers.integersLessThan(Integer(lessThan));
    cout << "DOUBLE NUMBERS BIGGER THAN " << biggerThan << endl;
    numbers.doublesBiggerThan(Double(biggerThan));

    return 0;
}

