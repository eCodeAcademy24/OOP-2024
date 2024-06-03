#include <iostream>
#include <cstring>
using namespace std;

class ExistingGame {
private:
    char msg[256];
public:
    ExistingGame(const char* msg_txt) {
        strncpy(this->msg, msg_txt, 255);
        this->msg[255] = '\0';
    }

    void message() {
        cout << this->msg << endl;
    }
};

class Game {
protected:
    char name[100];
    float price;
    bool on_sale;
public:
    Game() {
        name[0] = '\0';
    }

    Game(const char* n, float p, bool s = false) {
        strncpy(name, n, 99);
        this->name[99] = '\0';
        price = p;
        on_sale = s;
    }

    virtual float get_price() const {
        return on_sale ? price * 0.3F : price;
    }

    bool operator==(const Game& g) const {
        return strcmp(this->name, g.name) == 0;
    }

    friend ostream& operator<<(ostream& o, const Game& g);
    friend istream& operator>>(istream& i, Game& g);
};

class SubscriptionGame : public Game {
private:
    float monthly_fee;
    int month, year;
public:
    SubscriptionGame() : Game(), monthly_fee(0), month(0), year(0) {}

    SubscriptionGame(const char* n, float p, bool s, float mf, int m, int y)
            : Game(n, p, s), monthly_fee(mf), month(m), year(y) {}

    float get_price() const override {
        float base_price = Game::get_price();
        int months = (year < 2018) ? (12 - this->month) + (2017 - year) * 12 + 5 : 5 - this->month;
        return base_price + months * monthly_fee;
    }

    friend ostream& operator<<(ostream& o, const SubscriptionGame& sg);
    friend istream& operator>>(istream& i, SubscriptionGame& g);
};

ostream& operator<<(ostream& o, const Game& g) {
    o << "Game: " << g.name << ", regular price: $" << g.price;
    if (g.on_sale) {
        o << ", bought on sale";
    }
    return o;
}

ostream& operator<<(ostream& o, const SubscriptionGame& sg) {
    o << "Game: " << sg.name << ", regular price: $" << sg.price;
    if (sg.on_sale) {
        o << ", bought on sale";
    }
    o << ", monthly fee: $" << sg.monthly_fee << ", purchased: " << sg.month << "-" << sg.year;
    return o;
}

istream& operator>>(istream& is, Game& g) {
    is.get();
    is.getline(g.name, 100);
    is >> g.price >> g.on_sale;
    return is;
}

istream& operator>>(istream& is, SubscriptionGame& g) {
    is.get();
    is.getline(g.name, 100);
    is >> g.price >> g.on_sale;
    is >> g.monthly_fee >> g.month >> g.year;
    return is;
}

class User {
private:
    char username[100];
    Game** games;
    int num_games;

    void copy(const User& other) {
        strcpy(this->username, other.username);
        this->num_games = other.num_games;
        this->games = new Game * [other.num_games];
        for (int i = 0; i < other.num_games; ++i) {
            if (dynamic_cast<SubscriptionGame*>(other.games[i])) {
                this->games[i] = new SubscriptionGame(*dynamic_cast<SubscriptionGame*>(other.games[i]));
            }
            else {
                this->games[i] = new Game(*other.games[i]);
            }
        }
    }
public:
    User(const char* un = "") {
        strncpy(this->username, un, 99);
        this->username[99] = '\0';
        games = nullptr;
        num_games = 0;
    }

    User(const User& other) {
        copy(other);
    }

    ~User() {
        for (int i = 0; i < this->num_games; ++i) {
            delete this->games[i];
        }
        delete[] games;
    }

    User& operator=(const User& other) {
        if (this != &other) {
            for (int i = 0; i < this->num_games; ++i) {
                delete this->games[i];
            }
            delete[] games;
            copy(other);
        }
        return *this;
    }

    User& operator+=(Game& g) {
        for (int i = 0; i < this->num_games; ++i) {
            if (*this->games[i] == g) {
                throw ExistingGame("The game is already in the collection");
            }
        }
        Game** new_games = new Game * [this->num_games + 1];
        for (int i = 0; i < this->num_games; ++i) {
            new_games[i] = this->games[i];
        }
        if (dynamic_cast<SubscriptionGame*>(&g)) {
            new_games[this->num_games] = new SubscriptionGame(*dynamic_cast<SubscriptionGame*>(&g));
        }
        else {
            new_games[this->num_games] = new Game(g);
        }
        delete[] this->games;
        this->games = new_games;
        this->num_games++;
        return *this;
    }

    float total_spent() const {
        float sum = 0.0f;
        for (int i = 0; i < this->num_games; ++i) {
            sum += games[i]->get_price();
        }
        return sum;
    }

    const char* get_username() const {
        return this->username;
    }

    int get_games_number() const {
        return this->num_games;
    }

    Game& get_game(int i) const {
        return *this->games[i];
    }

    friend ostream& operator<<(ostream& o, const User& u);
};

ostream& operator<<(ostream& o, const User& u) {
    o << endl;
    o << "User: " << u.get_username() << endl;
    for (int i = 0; i < u.get_games_number(); ++i) {
        Game* g = &u.get_game(i);
        if (SubscriptionGame* sg = dynamic_cast<SubscriptionGame*>(g)) {
            o << "- " << *sg << endl;
        }
        else {
            o << "- " << *g << endl;
        }
    }
    return o;
}

int main() {
    int test_case_num;
    cin >> test_case_num;

    char game_name[100];
    float game_price;
    bool game_on_sale;

    float sub_game_monthly_fee;
    int sub_game_month, sub_game_year;

    char username[100];
    int num_user_games;

    if (test_case_num == 1) {
        cout << "Testing class Game and operator<< for Game" << endl;
        cin.get();
        cin.getline(game_name, 100);
        cin >> game_price >> game_on_sale;
        Game g(game_name, game_price, game_on_sale);
        cout << g;
    }
    else if (test_case_num == 2) {
        cout << "Testing class SubscriptionGame and operator<< for SubscritionGame" << endl;
        cin.get();
        cin.getline(game_name, 100);
        cin >> game_price >> game_on_sale;
        cin >> sub_game_monthly_fee >> sub_game_month >> sub_game_year;
        SubscriptionGame sg(game_name, game_price, game_on_sale, sub_game_monthly_fee, sub_game_month, sub_game_year);
        cout << sg;
    }
    else if (test_case_num == 3) {
        cout << "Testing operator>> for Game" << endl;
        Game g;
        cin >> g;
        cout << g;
    }
    else if (test_case_num == 4) {
        cout << "Testing operator>> for SubscriptionGame" << endl;
        SubscriptionGame sg;
        cin >> sg;
        cout << sg;
    }
    else if (test_case_num == 5) {
        cout << "Testing class User and operator+= for User" << endl;
        cin.get();
        cin.getline(username, 100);
        User u(username);

        cin >> num_user_games;

        try {
            for (int i = 0; i < num_user_games; ++i) {
                int game_type;
                cin >> game_type;

                Game* g;
                if (game_type == 1) {
                    cin.get();
                    cin.getline(game_name, 100);
                    cin >> game_price >> game_on_sale;
                    g = new Game(game_name, game_price, game_on_sale);
                }
                else if (game_type == 2) {
                    cin.get();
                    cin.getline(game_name, 100);
                    cin >> game_price >> game_on_sale;
                    cin >> sub_game_monthly_fee >> sub_game_month >> sub_game_year;
                    g = new SubscriptionGame(game_name, game_price, game_on_sale, sub_game_monthly_fee, sub_game_month, sub_game_year);
                }
                u += *g;
                delete g;
            }
        }
        catch (ExistingGame& ex) {
            ex.message();
        }

        cout << u;
    }
    else if (test_case_num == 6) {
        cout << "Testing exception ExistingGame for User" << endl;
        cin.get();
        cin.getline(username, 100);
        User u(username);

        cin >> num_user_games;

        try {
            for (int i = 0; i < num_user_games; ++i) {
                int game_type;
                cin >> game_type;

                Game* g;
                if (game_type == 1) {
                    cin.get();
                    cin.getline(game_name, 100);
                    cin >> game_price >> game_on_sale;
                    g = new Game(game_name, game_price, game_on_sale);
                }
                else if (game_type == 2) {
                    cin.get();
                    cin.getline(game_name, 100);
                    cin >> game_price >> game_on_sale;
                    cin >> sub_game_monthly_fee >> sub_game_month >> sub_game_year;
                    g = new SubscriptionGame(game_name, game_price, game_on_sale, sub_game_monthly_fee, sub_game_month, sub_game_year);
                }
                u += *g;
                delete g;
            }
        }
        catch (ExistingGame& ex) {
            ex.message();
        }

        cout << u;
    }
    else if (test_case_num == 7) {
        cout << "Testing total_spent method() for User" << endl;
        cin.get();
        cin.getline(username, 100);
        User u(username);

        cin >> num_user_games;

        for (int i = 0; i < num_user_games; ++i) {
            int game_type;
            cin >> game_type;

            Game* g;
            if (game_type == 1) {
                cin.get();
                cin.getline(game_name, 100);
                cin >> game_price >> game_on_sale;
                g = new Game(game_name, game_price, game_on_sale);
            }
            else if (game_type == 2) {
                cin.get();
                cin.getline(game_name, 100);
                cin >> game_price >> game_on_sale;
                cin >> sub_game_monthly_fee >> sub_game_month >> sub_game_year;
                g = new SubscriptionGame(game_name, game_price, game_on_sale, sub_game_monthly_fee, sub_game_month, sub_game_year);
            }
            u += *g;
            delete g;
        }

        cout << u << endl;
        cout << "Total money spent: $" << u.total_spent() << endl;
    }

    return 0;
}
