#include<iostream>
#include<cstring>
#include <algorithm>

using namespace std;

//Да се дефинира апстрактна класата Task во која што се чува информација за:
//
//ID (низа од максимум 5 знаци)
//Дополнително апстрактната класа содржи два чисто виртуелни методи:
//
//int getOrder() којшто го враќа редниот број (редот) на извршување на задачата (Task-oт).
//void print() којшто печати информации за задачата (види тест примери) (1 поен)
//Постојат два вида на таскови (задачи):
//
//TimedTask во којшто се чува информација за:
//потребното време за извршување на задачата time (цел број)
//PriorityTask во којшто се чува информација за:
//степенот на приоритет priority (цел број)
//Редниот број на извршувањe на TimedTask e дефиниран со времето на извршување, додека пак на PriorityTask со степенот на приоритет. (1 поен)
//
//За двата типа на таскови да се имплементираат:
//
//оператор за споредба == којшто ги споредува според нивниот ID и според нивното време/степен на приоритетност. (2 поени)
//препокриени функции од класата Task (2 поени)
//Дополнително, да се имплементираат следните надворешни методи:
//
//void scheduleTimedTasks (Task ** tasks, int n, int t)- метод којшто ќе ги распореди сите задачи од тип TimedTask со време на извршување помало од t (ќе испечати информации
//за нив), сортирани во растечки редослед според времето на извршување. Методот прима три аргументи (низа од покажувачи кон Task, бројот на елементи во низата и времетот t)
//
//(2 поени)
//void schedulePrioritryTask(Task ** tasks, int n, int p) - метод којшто ќе ги распореди сите задачи од тип PriorityTask со степен на приоритет помал од p (ќе испечати
//информации за нив), сортирани во растечки редослед според степенот на приоритетност. Методот прима три аргументи (низа од покажувачи кон Task, бројот на елементи во
//низата и степенот на приоритетност p) (2 поени)

class Task {
protected:
    char ID[6];
public:
    Task(char *id) {
        strcpy(this->ID, id);
    }

    virtual int getOrder() = 0;

    virtual void print() = 0;

    bool operator==(Task &other) {
        return (strcmp(this->ID, other.ID) == 0) && (this->getOrder() == other.getOrder());
    }
};

class TimedTask : public Task{
    int time;
public:
    TimedTask(char *id, int time) : Task(id) {
        this->time = time;
    }

    int getOrder() override {
        return time;
    }

//    TT->B:8
    void print() override {
        cout << "TT->" << ID << ":" << time << endl;
    }
};

class PriorityTask : public Task {
    int priority;
public:
    PriorityTask(char *id, int priority) : Task(id) {
        this->priority = priority;
    }

    int getOrder() override {
        return priority;
    }

//    PT->A:2
    void print() override {
        cout << "PT->" << ID << ":" << priority << endl;
    }
};

// По што да се прави споредбата во сортирањето
bool compareByTime(Task *t1, Task *t2) {
    return t1->getOrder() < t2->getOrder();
}

void scheduleTimedTasks (Task ** tasks, int n, int t) {
    // sort очекува: покажувач кон првиот елемент во низата,
    // кон последниот и аргумент по кој што ќе ја прави споредбата
    sort(tasks, tasks + n, compareByTime);

    for(int i = 0; i < n; i++) {
        if(dynamic_cast<TimedTask *>(tasks[i])) {
            if(tasks[i]->getOrder() < t) {
                tasks[i]->print();
            }
        }
    }
}

void schedulePriorityTasks(Task ** tasks, int n, int p) {
    for(int i = 0; i < n; i++) {
        if(dynamic_cast<PriorityTask *>(tasks[i])) {
            if(tasks[i]->getOrder() < p) {
                tasks[i]->print();
            }
        }
    }
}

int main() {
    int testCase;
    int n;
    cin >> testCase;

    if (testCase == 0) {
        cin >> n;
        Task **tasks;
        tasks = new Task *[n];
        for (int i = 0; i < n; i++) {
            char id[5];
            int timeOrPriority;
            int type; //0 za timed, 1 za priority
            cin >> type >> id >> timeOrPriority;
            if (type == 0)
                tasks[i] = new TimedTask(id, timeOrPriority);
            else
                tasks[i] = new PriorityTask(id, timeOrPriority);
            //tasks[i]->print();
        }

        cout << "SCHEDULING PRIORITY TASKS WITH PRIORITY DEGREE LESS THAN 10" << endl;
        schedulePriorityTasks(tasks, n, 10);

    } else if (testCase == 1) {
        cin >> n;
        Task **tasks;
        tasks = new Task *[n];
        for (int i = 0; i < n; i++) {
            char id[5];
            int timeOrPriority;
            int type; //0 za timed, 1 za priority
            cin >> type >> id >> timeOrPriority;
            if (type == 0)
                tasks[i] = new TimedTask(id, timeOrPriority);
            else
                tasks[i] = new PriorityTask(id, timeOrPriority);
            //tasks[i]->print();
        }


        cout << "SCHEDULING TIMED TASKS WITH EXECUTION TIME LESS THAN 50" << endl;
        scheduleTimedTasks(tasks, n, 50);
    } else {
        TimedTask *tt1 = new TimedTask("11", 10);
        TimedTask *tt2 = new TimedTask("11", 11);
        TimedTask *tt3 = new TimedTask("11", 11);
        PriorityTask *pp1 = new PriorityTask("aa", 10);
        PriorityTask *pp2 = new PriorityTask("11", 10);

        cout << (*tt1 == (*tt2)) << endl;
        cout << (*tt2 == (*tt3)) << endl;
        cout << (*pp1 == (*pp2)) << endl;
        cout << (*pp2 == (*tt1)) << endl;
    }

    return 0;
}