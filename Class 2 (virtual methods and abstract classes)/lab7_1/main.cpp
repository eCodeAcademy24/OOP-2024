#include <iostream>
#include <cstring>
using namespace std;

//Издавачката куќа FINKI-Education издава онлајн и печатени книги. За секоја книга се чуваат податоци за ISBN бројот (низа од најмногу 20 знаци),
// насловот (низа од најмногу 50 знаци), авторот (низа од најмногу 30 знаци) и основната цена изразена во $ (реален број). Класата за опишување на книгите
// е апстрактна (5 поени).
//
//За секоја онлајн книга дополнително се чуваат податоци за url од каде може да се симне (динамички резервирана низа од знаци) и големината изразена во MB
// (цел број). За секоја печатена книга дополнително се чуваат податоци за масата изразена во килограми (реален број) и дали ја има на залиха (логичка променлива).
// (5 поени)
//
//За секој објект од двете изведени класи треба да бидат на располагање следниве методи:
//
//Метод bookPrice, за пресметување на продажната цена на книгата на следниот начин: (10 поени)
//
//За онлајн книга - цената се зголемува за 20% од основната цена ако книгата е поголема од 20MB
//
//За печатена книга - цената се зголемува за 15% од основната цена ако масата на книгата е поголема од 0.7kg
//
//Преоптоварен оператор > за споредба на две книги од каков било вид според нивната цена. (5 поени)
//
//Преоптоварен оператор << за печатење на податоците за книгите во формат: (5 поени)
//Да се имплементира функција mostExpensiveBook со потпис:
//
//void mostExpensiveBook (Book** books, int n)
//
//во која се печати вкупниот број на онлајн, односно, печатени книги во проследената низа посебно. (5 поени) Потоа се наоѓа и печати најскапата книга. (5 поени)
//
//Да се обезбедат сите потребни функции за правилно функционирање на програмата. (5 поени)

// Input
//4
//3
//1
//0-312-31677-1
//The Moscow Vector
//        Robert Ludlum
//7
//www.finki-education/olinebooks/book1.pdf
//1
//2
//007-6092006565
//Thinking in C++
//Bruce Eckel
//52
//1.2
//1
//1
//978-0672326974
//C++ Primer Plus
//Stephen Prata
//20
//www.finki-education/olinebooks/book2.pdf
//30

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
