#include <iostream>
#include <cstring>
using namespace std;
//NBAPlayer
//Да се дефинира класа NBAPlayer за која ќе се чуваат:
//
//динамички алоцирана низа од карактери за името на играчот
//низа од максимум 40 карактери за тимот во кој играчот моментално настапува
//просечен број на поени на играчот оваа сезона (double)
//просечен број на асистенции на играчот оваа сезона (double)
//просечен број на скокови на играчот оваа сезона (double)
//За потребите на класата да се дефинираат:
//
//default конструктор и конструктор со аргументи
//copy constructor и оператор =
//деструктор
//метод rating() кој го враќа рејтингот на кошаркарот кој се пресметува како:
//
//45% од поените + 30% од асистенциите + 25% од скоковите
//
//метод print() кој го печати играчот во следниот формат:
//
//Име - тим
//
//Points: поени
//
//Assists: асистенции
//
//Rebounds: скокови
//
//Rating: рејтинг
//
//AllStarPlayer
//Од претходната класа NBAPlayer да се изведе класата AllStarPlayer за која дополнително ќе се чуваат и:
//
//просечен број на поени на играчот од All Star натпреварите (double)
//просечен број на асистенции на играчот од All Star натпреварите (double)
//просечен број на скокови на играчот од All Star натпреварите (double)
//За потребите на класата да се дефинираат:
//
//default конструктор
//конструктор кој прима објект од NBAPlayer и плус додатните информации (погледни main)
//конструктор кој ги прима сите аргументи (погледни main)
//copy constructor, оператор =, деструктор
//метод allStarRating() кој го враќа рејтингот на кошаркарот од All Star натпреварите и кој се пресметува како:
//
//30% од поените + 40% од асистенциите + 30% од скоковите
//
//Да се препокријат методите:
//
//rating() кој го враќа просекот од обичниот рејтинг на кошаркарот и неговиот All Star рејтинг
//print() кој покрај основните информации за кошаркарот печати и:
//
//All Star Rating: рејтингот од All Star натпреварите
//
//New Rating: просечниот рејтинг

class NBAPlayer {
protected:
    char *name;
    char team[40];
    double points;
    double assists;
    double rebounds;

    void copy(const NBAPlayer & np) {
        this->name = new char [strlen(np.name) + 1];
        strcpy(this->name, np.name);
        strcpy(this->team, np.team);
        this->points = np.points;
        this->assists = np.assists;
        this->rebounds = np.rebounds;
    }

public:
    NBAPlayer() {
        name = new char[0];
        strcpy(this->team, "");
        points = 0;
        assists = 0;
        rebounds = 0;
    }

    NBAPlayer(char *name, char *team, double points, double assists, double rebounds) {
        this->name = new char [strlen(name) + 1];
        strcpy(this->name, name);
        strcpy(this->team, team);
        this->points = points;
        this->assists = assists;
        this->rebounds = rebounds;
    }

    NBAPlayer(const NBAPlayer & other) {
        copy(other);
    }

    NBAPlayer & operator=(const NBAPlayer & other) {
        if(this!=&other) {
            delete [] name;
            copy(other);
        }
        return *this;
    }

    ~NBAPlayer() {
        delete [] name;
    }

    double rating() {
        return points * 0.45 + assists * 0.3 + rebounds * 0.25;
    }

    void print() {
        //Име - тим
        //Points: поени
        //Assists: асистенции
        //Rebounds: скокови
        //Rating: рејтинг

        cout << name << " - " << team << endl;
        cout << "Points: " << points << endl;
        cout << "Assists: " << assists << endl;
        cout << "Rebounds: " << rebounds << endl;
        cout << "Rating: " << rating() << endl;
    }
};

class AllStarPlayer : public NBAPlayer{
    double allStarPoints;
    double allStarAssists;
    double allStarRebounds;

    void copy(const AllStarPlayer & as) {
        this->allStarPoints = as.allStarPoints;
        this->allStarAssists = as.allStarAssists;
        this->allStarRebounds = as.allStarRebounds;
    }

public:
    AllStarPlayer() : NBAPlayer() {
        allStarPoints = 0;
        allStarAssists = 0;
        allStarRebounds = 0;
    }

    AllStarPlayer(const NBAPlayer &np, double allStarPoints, double allStarAssists, double allStarRebounds) : NBAPlayer(np) {
        this->allStarPoints = allStarPoints;
        this->allStarAssists = allStarAssists;
        this->allStarRebounds = allStarRebounds;
    }

    AllStarPlayer(char *name, char *team, double points, double assists, double rebounds, double allStarPoints, double allStarAssists, double allStarRebounds) :
    NBAPlayer(name, team,points, assists, rebounds) {
        this->allStarPoints = allStarPoints;
        this->allStarAssists = allStarAssists;
        this->allStarRebounds = allStarRebounds;
    }

    AllStarPlayer(const AllStarPlayer & other) {
        copy(other);
    }

    AllStarPlayer & operator=(const AllStarPlayer & other) {
        if(this!=&other) {
            delete [] name;
            NBAPlayer::copy(other);
            copy(other);
        }
        return *this;
    }

    double allStarRating() {
        return allStarPoints * 0.3 + allStarAssists * 0.4 + allStarRebounds * 0.3;
    }

    double rating() {
        return (NBAPlayer::rating() + allStarRating()) / 2;
    }

    void print() {
        //All Star Rating: рејтингот од All Star натпреварите
        //New Rating: просечниот рејтинг
        NBAPlayer::print();
        cout << "All Star Rating: " << allStarRating() << endl;
        cout << "New Rating: " << rating() << endl;
    }
};

int main() {

    char name[50];
    char team[40];
    double points;
    double assists;
    double rebounds;
    double allStarPoints;
    double allStarAssists;
    double allStarRebounds;

    NBAPlayer * players = new NBAPlayer[5];
    AllStarPlayer * asPlayers = new AllStarPlayer[5];
    int n;
    cin >> n;

    if (n == 1) {

        cout << "NBA PLAYERS:" << endl;
        cout << "=====================================" << endl;
        for (int i = 0; i < 5; ++i) {
            cin >> name >> team >> points >> assists >> rebounds;
            players[i] = NBAPlayer(name,team,points,assists,rebounds);
            players[i].print();
        }
    }
    else if (n == 2) {

        for (int i=0; i < 5; ++i){
            cin >> name >> team >> points >> assists >> rebounds;
            cin >> allStarPoints >> allStarAssists >> allStarRebounds;
            players[i] = NBAPlayer(name,team,points,assists,rebounds);
            asPlayers[i] = AllStarPlayer(players[i],allStarPoints,allStarAssists,allStarRebounds);
        }

        cout << "NBA PLAYERS:" << endl;
        cout << "=====================================" << endl;
        for (int i=0; i < 5; ++i)
            players[i].print();

        cout << "ALL STAR PLAYERS:" << endl;
        cout << "=====================================" << endl;
        for (int i=0; i < 5; ++i)
            asPlayers[i].print();

    }
    else if (n == 3) {

        for (int i=0; i < 5; ++i){
            cin >> name >> team >> points >> assists >> rebounds;
            cin >> allStarPoints >> allStarAssists >> allStarRebounds;
            asPlayers[i] = AllStarPlayer(name, team, points, assists, rebounds,
                                         allStarPoints,allStarAssists,allStarRebounds);
        }
        cout << "ALL STAR PLAYERS:" << endl;
        cout << "=====================================" << endl;
        for (int i=0; i < 5; ++i)
            asPlayers[i].print();

    }

    delete [] players;
    delete [] asPlayers;
}

