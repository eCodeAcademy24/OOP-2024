#include <iostream>
using namespace std;

class Developer {
protected:
    int salary;
public:
    Developer(int salary) {
        this->salary = salary;
    }

    virtual void calculateSalary() = 0;
};

class IosDeveloper : public Developer{
public:
    IosDeveloper(int salary) : Developer(salary) {

    }

    void calculateSalary() {
        cout << salary + 200 << endl;
    }
};

class AndroidDeveloper: public Developer {
public:
    AndroidDeveloper(int salary) : Developer(salary) {

    }

    void calculateSalary() {
        cout << salary + 210 << endl;
    }
};

class WebDeveloper : public Developer{
public:
    WebDeveloper(int salary) : Developer(salary) {

    }

    void calculateSalary() {
        cout << salary + 300 << endl;
    }
};

int main() {
    Developer **developers = new Developer *[3];

    developers[0] = new IosDeveloper(1000);
    developers[1] = new AndroidDeveloper(1200);
    developers[2] = new WebDeveloper(1500);

    for(int i = 0; i < 3; i++) {
        developers[i]->calculateSalary();
    }

    return 0;
}
