//Да се креира класа PositiveIntegers во која што ќе се чуваат информации за:
//
//низа од позитивни броеви (>0) (динамички алоцирана низа од цели броеви)
//број на елементи во низата
//        максимален капацитет на низата
//        За класата да се имплементираат:
//
//потребниот конструктор (погледнете во главната функција како се креира објект од оваа класа)
//метод void increaseCapacity(int c) којшто го зголемува максималниот капацитет на низата за бројот с
//оператор за додавање на нов број во низата од позитивни броеви +=
//број се додава ако и само ако
//        оператор за множење * за множење на низата со друг цел број
//Пример, низата има објекти (1 2 3 4 5) и истата се множи со 2, резултатот ќе биде (1 2 3 4 5)*2 = (2 3 6 8 10)
//оператор за делење \ за делење на низата до друг цел број
//потребно е секој елемент од низата да биде делив со тој број, како и делителот не смее да биде нула.
//оператор [] за пристап до елемент од низата
//Потребно е да се дефинираат класи за исклучоци и секој од нив да има метод void message() којшто ќе принта соодветна порака кога
//исклучокот ќе биде фатен. Можните исклучоци се следните:
//
//ArithmeticException (се фрла ако се проба да се дели со нула)
//принта порака Division by zero is not allowed
//        NumbersNotDivisibleException (се фрла ако се проба да се дели низата со некој број, а барем еден елемент од низата не е делив со
//        тој број)
//принта порака Division by number [делителот] is not supported
//        ArrayFullException (се фрла ако се проба да се додади елемент во низа која и е исполнет максималниот капацитет)
//принта порака The array is full. Increase the capacity
//        IndexOutOfBoundsException (се фрла доколку се проба да се пристапи до елемент од низата со несоодветен индекс)
//принта порака Index [индексот] is out of bounds
//NumberIsNotPositiveException (се фрла доколку се проба да се внесе во низата број што не е позитивен или е нула)
//принта порака Number [бројот] is not positive integer.

#include <iostream>
#include <stdexcept>

using namespace std;

class IndexOutOfBoundsException {
    int index;
public:
    IndexOutOfBoundsException(int index) {
        this->index = index;
    }

    void message() {
        cout << "Index " << index << " is out of bounds" << endl;
    }
};

class ArithmeticException {
public:
    void message() {
        cout << "Division by zero is not allowed" << endl;
    }
};

class NumbersNotDivisibleException {
    int divisor;
public:
    NumbersNotDivisibleException(int divisor) {
        this->divisor = divisor;
    }

    void message() {
        cout << "Division by " << divisor << " is not supported" << endl;
    }
};

class ArrayFullException {
public:
    void message() {
        cout << "The array is full. Increase the capacity" << endl;
    }
};

class NumberIsNotPositiveException {
    int number;
public:
    NumberIsNotPositiveException(int number) {
        this->number = number;
    }

    void message() {
        cout << "Number " << number << " is not positive integer" << endl;
    }
};

class PositiveIntegers {
    int *numbers;
    int capacity;
    int size;

    void copy(const PositiveIntegers &other) {
        this->size = other.size;
        this->capacity = other.capacity;
        this->numbers = new int[other.capacity];
        for (int i = 0; i < other.size; i++) {
            this->numbers[i] = other.numbers[i];
        }
    }

public:
    PositiveIntegers(int capacity = 0) {
        this->size = 0;
        this->capacity = capacity;
        this->numbers = new int[capacity];
    }

    PositiveIntegers(const PositiveIntegers &other) {
        copy(other);
    }

    PositiveIntegers &operator=(const PositiveIntegers &other) {
        if (this != &other) {
            delete[] numbers;
            copy(other);
        }
        return *this;
    }

    PositiveIntegers &operator+=(int number) {
        if (size >= capacity) {
            throw ArrayFullException();
        }
        if (number <= 0) {
            throw NumberIsNotPositiveException(number);
        }
        numbers[size++] = number;
        return *this;
    }

    PositiveIntegers operator*(int multiplier) {
        PositiveIntegers afterMultiplication(capacity);
        for (int i = 0; i < size; i++) {
            afterMultiplication += numbers[i] * multiplier;
        }

        return afterMultiplication;
    }

    PositiveIntegers operator/(int divisor) {
        if (divisor == 0) {
            throw ArithmeticException();
        }
        for (int i = 0; i < size; i++) {
            if (numbers[i] % divisor != 0) {
                throw NumbersNotDivisibleException(divisor);
            }
        }

        PositiveIntegers afterDivision(capacity);
        for (int i = 0; i < size; i++) {
            afterDivision += numbers[i] / divisor;
        }

        return afterDivision;
    }

    int operator[](int index) {
        if (index < 0 || index >= size) {
            throw IndexOutOfBoundsException(index);
        }

        return numbers[index];
    }

    void increaseCapacity(int c) {
        int *newNumbers = new int[capacity + c];
        for (int i = 0; i < size; i++) {
            newNumbers[i] = numbers[i];
        }
        delete[] numbers;
        numbers = newNumbers;
        capacity += c;
    }

    void print() {
        cout << "Size: " << size << " Capacity: " << capacity << " Numbers: ";
        for (int i = 0; i < size; i++) {
            cout << numbers[i] << " ";
        }
        cout << endl;
    }

    ~PositiveIntegers() {
        delete[] numbers;
    }
};

int main() {

    int n, capacity;
    cin >> n >> capacity;
    PositiveIntegers pi(capacity);
    for (int i = 0; i < n; i++) {
        int number;
        cin >> number;
        try {
            pi += number;
        } catch (ArrayFullException &e) {
            e.message();
        } catch (NumberIsNotPositiveException &e) {
            e.message();
        }
    }
    cout << "===FIRST ATTEMPT TO ADD NUMBERS===" << endl;
    pi.print();
    int incCapacity;
    cin >> incCapacity;
    pi.increaseCapacity(incCapacity);
    cout << "===INCREASING CAPACITY===" << endl;
    pi.print();

    int n1;
    cin >> n1;
    for (int i = 0; i < n1; i++) {
        int number;
        cin >> number;
        try {
            pi += number;
        } catch (ArrayFullException &e) {
            e.message();
        } catch (NumberIsNotPositiveException &e) {
            e.message();
        }
    }
    cout << "===SECOND ATTEMPT TO ADD NUMBERS===" << endl;

    pi.print();
    PositiveIntegers pi1;

    cout << "===TESTING DIVISION===" << endl;

    try {
        pi1 = pi / 0;
        pi1.print();
    } catch (ArithmeticException &e) {
        e.message();
    }

    try {
        pi1 = pi / 1;
        pi1.print();
    } catch (NumbersNotDivisibleException &e) {
        e.message();
    }

    try {
        pi1 = pi / 2;
        pi1.print();
    } catch (NumbersNotDivisibleException &e) {
        e.message();
    }

    cout << "===TESTING MULTIPLICATION===" << endl;
    pi1 = pi * 3;
    pi1.print();


    cout << "===TESTING [] ===" << endl;
    try {
        cout << "PositiveIntegers[-1] = " << pi[-1] << endl;
    }
    catch (IndexOutOfBoundsException &e) {
        e.message();
    }

    try {
        cout << "PositiveIntegers[2] = " << pi[2] << endl;
    }
    catch (IndexOutOfBoundsException &e) {
        e.message();
    }

    try {
        cout << "PositiveIntegers[3] = " << pi[3] << endl;
    }
    catch (IndexOutOfBoundsException &e) {
        e.message();
    }

    try {
        cout << "PositiveIntegers[12] = " << pi[12] << endl;
    }
    catch (IndexOutOfBoundsException &e) {
        e.message();
    }

    return 0;
}
