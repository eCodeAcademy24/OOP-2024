//Да се дефинира апстрактна класа Employee којашто ќе содржи име на вработениот, години и работно искуство во години (integer). Да се дефинираат чисти виртуелни функции plata() и bonus() (double).
//
//Од класата Employee да се изведе класа SalaryEmployee која покрај основните информации содржи и информација за основната плата. Бонусот на овие работници се пресметува како процент од основната плата, а процентот
//е бројот на години со работно искуство. На пример ако работеле 10 години, бонусот е 10 проценти од основната плата. Вкупната плата се пресметува како основната плата плус бонусот.
//
//Од класата Employee исто така да се изведе класа HourlyEmployee која покрај основните информации содржи информација и за вкупниот број на часови кои ги одработил работникот и платата по час. Вкупната плата се
//пресметува како бројот на часови помножен со платата по час плус бонусот, додека бонусот се пресметува на следниот начин: За секој час над 320-тиот се добива 50 проценти од платата по час.
//
//Од класата Employee на крај се изведува класата Freelancer која покрај основните информации содржи и број на проекти на кои работел вработениет и низа со суми кои ги добил за тие проекти (double). По направени 5
//проекти, за секој нареден вработените добиваат бонус од 1000 денари. Вкупната плата на овој тип на вработени изнесува вкупната сума добиена од сите проекти плус бонусот.
//
//Да се преоптовари операторот == кој ќе прима два објекти од класата Employee и ќе ги споредува според тоа дали имаат ист број на години.
//
//Да се дефинира класа Company која ќе содржи информации за името на компанијата, бројот на вработени, и динамична низа од покажувачи од класата Employee или Employee **. За потребите на оваа класа треба да се дефинира
//конструктор кој прима само еден аргумент - името на компанијата, да се преоптовари операторот += и да се дефинираат следните методи:
//
//double vkupnaPlata() - метод којшто ја враќа вкупната плата на сите вработени во компанијата
//double filtriranaPlata(Employee * emp) - метод којшто ја враќа платата само на работниците кои се еднакви со дадениот вработен (според оператор ==)
//void pecatiRabotnici() - метод којшто печати по колку вработени има од секој тип на работници во компанијата, а форматот на печатење можете да го видите од тест примерите
//Hint: За потребите на последниот метод можете да искористите статички членови и статички функции во секоја од класата, dynamic_cast, виртуелна функција која ќе ја преоптоварите во секоја од класите или нешто друго по
//ваша желба.

// Input
//Advokatsko_drustvo_Bambus
//3
//1 Lidija_Andova 31 5 16000
//2 Martin_Kovacev 31 7 336 100
//2 Tea_Vinarova 29 4 330 60

// Output
// Vo kompanijata Advokatsko_drustvo_Bambus rabotat:↩
//Salary employees: 1↩
//Hourly employees: 2↩
//Freelancers: 0↩
//Vkupnata plata e: 71300↩
//Filtriranata plata e: 51200

// Input
//Market_Dejli
//6
//3 Iva_Damjanovska 37 14 6 3000 3300 2900 3450 1980 4010
//1 Lidija_Andova 31 5 16000
//2 Martin_Kovacev 54 29 336 100
//1 Krume_Petrov 44 11 27000
//2 Tea_Vinarova 29 4 330 60
//3 Luka_Mihajlovski 41 20 3 6040 2060 3000

// Output
//Vo kompanijata Market_Dejli rabotat:↩
//Salary employees: 2↩
//Hourly employees: 2↩
//Freelancers: 2↩
//Vkupnata plata e: 132010↩
//Filtriranata plata e: 16800

#include <iostream>
#include <cstring>

using namespace std;

class Employee {
protected:
    char name[100];
    int age;
    int work_experience;

public:
    Employee() {
        strcpy(this->name, "");
        age = 0;
        work_experience = 0;
    }

    Employee(char *name, int age, int work_experience) {
        strcpy(this->name, name);
        this->age = age;
        this->work_experience = work_experience;
    }

    virtual double plata() = 0;

    virtual double bonus() = 0;

    bool operator==(const Employee &other) const {
        return this->age == other.age;
    }
};

class SalaryEmployee : public Employee {
    int base_salary;

public:
    SalaryEmployee(char *name = "", int age = 0, int work_experience = 0, int base_salary = 0) :
            Employee(name, age, work_experience) {
        this->base_salary = base_salary;
    }

    double plata() override {
        return base_salary + bonus();
    }

    double bonus() override {
        return work_experience * (base_salary / 100.0);
    }
};

class HourlyEmployee : public Employee {
    int hours;
    int pay_per_hour;

public:
    HourlyEmployee(char *name = "", int age = 0, int work_experience = 0, int hours = 0, int pay_per_hour = 0)
            : Employee(name, age, work_experience) {
        this->hours = hours;
        this->pay_per_hour = pay_per_hour;
    }

    double plata() override {
        return hours * pay_per_hour + bonus();
    }

    double bonus() override {
        return hours > 320 ? pay_per_hour * 0.5 * (hours - 320) : 0;
    }
};

class Freelancer : public Employee {
    int num_projects;
    double *sum;

public:
    Freelancer(char *name, int age, int work_experience, int num_projects, double *sum)
            : Employee(name, age, work_experience) {
        this->num_projects = num_projects;
        this->sum = new double[this->num_projects];
        for (int i = 0; i < num_projects; ++i)
            this->sum[i] = sum[i];
    }

    double plata() override {
        return vkupnaSumaPoProekti() + bonus();
    }

    double bonus() override {
        return num_projects > 5 ? 1000 * (num_projects - 5) : 0;
    }

    double vkupnaSumaPoProekti() {
        double suma = 0;
        for (int i = 0; i < num_projects; ++i)
            suma += sum[i];
        return suma;
    }

    ~Freelancer() {
        delete[] sum;
    }
};

class Company {
    char *name;
    int numOfEmployees;
    Employee **employees;

public:
    Company(char *name = "") {
        this->name = name;
        this->numOfEmployees = 0;
        this->employees = nullptr;
    }

    Company &operator+=(Employee *emp) {
        Employee **temp = new Employee *[numOfEmployees + 1];
        for (int i = 0; i < numOfEmployees; ++i) {
            temp[i] = employees[i];
        }

        temp[numOfEmployees++] = emp;
        delete[] employees;
        employees = temp;
        return *this;
    }

    double vkupnaPlata() {
        double suma = 0;
        for (int i = 0; i < numOfEmployees; i++) {
            suma += employees[i]->plata();
        }
        return suma;
    }

    double filtriranaPlata(Employee *emp) {
        double plata = 0;
        for (int i = 0; i < numOfEmployees; ++i) {
            if (*employees[i] == *emp)
                plata += employees[i]->plata();
        }
        return plata;
    }

//    Vo kompanijata Advokatsko_drustvo_Bambus rabotat:
//    Salary employees: 1
//    Hourly employees: 2
//    Freelancers: 0
//    Vkupnata plata e: 71300
//    Filtriranata plata e: 51200
    void pecatiRabotnici() {
        int brSalary = 0, brHourly = 0, brFreelancer = 0;
        for (int i = 0; i < numOfEmployees; ++i) {
            if (dynamic_cast<SalaryEmployee *>(employees[i]))
                brSalary++;
            else if (dynamic_cast<HourlyEmployee *>(employees[i]))
                brHourly++;
            else if (dynamic_cast<Freelancer *>(employees[i]))
                brFreelancer++;
        }
        cout << "Vo kompanijata " << name << " rabotat:" << endl;
        cout << "Salary employees: " << brSalary << endl;
        cout << "Hourly employees: " << brHourly << endl;
        cout << "Freelancers: " << brFreelancer << endl;
    }

    ~Company() {
        for (int i = 0; i < numOfEmployees; ++i)
            delete employees[i];
        delete[] employees;
    }
};

int main() {

    char name[50];
    cin >> name;
    Company c(name);

    int n;
    cin >> n;

    char employeeName[50];
    int age;
    int experience;
    int type;

    for (int i = 0; i < n; ++i) {
        cin >> type;
        cin >> employeeName >> age >> experience;

        if (type == 1) {
            int basicSalary;
            cin >> basicSalary;
            c += new SalaryEmployee(employeeName, age, experience, basicSalary);
        } else if (type == 2) {
            int hoursWorked;
            int hourlyPay;
            cin >> hoursWorked >> hourlyPay;
            c += new HourlyEmployee(employeeName, age, experience, hoursWorked, hourlyPay);
        } else {
            int numProjects;
            cin >> numProjects;
            double projects[10];
            for (int i = 0; i < numProjects; ++i) {
                cin >> projects[i];
            }
            c += new Freelancer(employeeName, age, experience, numProjects, projects);
        }
    }

    c.pecatiRabotnici();
    cout << "Vkupnata plata e: " << c.vkupnaPlata() << endl;
    Employee *emp = new HourlyEmployee("Petre_Petrov", 31, 6, 340, 80);
    cout << "Filtriranata plata e: " << c.filtriranaPlata(emp);

    delete emp;
}

