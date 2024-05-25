//Да се дефинира апстрактна класа User за која ќе се чуваат:
//
//username (char[50])
//password (char[50])
//email (char[50])
//Класата треба да содржи еден чист виртуелен метод double popularity().
//
//Од оваа класа да се изведат две класи и тоа FacebookUser и TwitterUser.
//
//За класата FacebookUser уште се чуваат и:
//
//број на пријатели
//број на лајкови и
//број на коментари
//Популарноста се пресметува така што се собираат бројот на пријатели, бројот на лајкови и бројот на коментари, но притоа бројот на лајкови се множи со
//коефициент на вредност на лајкот кој е ист за секој корисник и изнесува 0.1, а исто така и бројот на коментари се множи со ист таков коефициент кој е 0.5.
//
//За класата TwitterUser уште се чуваат и:
//
//број на следачи и
//број на твитови
//Популарноста се пресметува така што се собираат бројот на следачи и бројот на твитови, но притоа бројот на твитови се множи со коефициент на вредност на
//твитот кој е ист за секој корисник и изнесува 0.5.
//
//Да се креира класа SocialNetwork која ќе содржи:
//
//динамичка низа од покажувачи од класата User
//број на тековни корисници и
//максимален број на корисници кој може да го содржи мрежата и кој е ист за сите мрежи и иницијално е поставен на 5
//Да се преоптовари операторот += со кој ќе се додава нов корисник.
//
//Да се дефинира метод avgPopularity() кој ќе ја враќа просечната популарност на корисниците во мрежата.
//
//Исто така да се овозможи промена на максималната големина на низата преку методот changeMaximumSize(int number).
//
//Потребно е да се справите со следните исклучоци:
//
//Доколку лозинката на корисникот не содржи барем 1 голема буква, 1 мала буква и 1 број да се фрли исклучок од класа InvalidPassword така што како параметар
//ќе се прати пораката Password is too weak.
//Доколку емаилот на корисникот не содржи точно еднаш @ да се фрли исклучок од класа InvalidEmail така што како параметар ќе се прати пораката Mail is not valid.
//Доколку проба да се додаде корисник во социјалната мрежа, а веќе максималниот број на корисници е пополнет да се фрли исклучок од класа MaximumSizeLimit
//така што како параметар ќе се прати максималниот број на корисници во мрежата.
//Сите класи кои се справуваат со исклучоци треба да го имаат имплементирано методот void message() така што за првите две класи ќе ја печати пораката којашто
//е испратена како параметар, а за последната класа ќе печати You can't add more than N users, каде што N е параметарот кој е пратен. Исто така со try-catch
//блокови справете се со исклучоците на соодветните места во main(), каде што во catch ќе го повикате методот message() од соодветниот исклучок.
#include <iostream>
#include <cstring>
#include <cctype>

using namespace std;

class MaximumSizeLimit {
    int maxSize;
public:
    MaximumSizeLimit(int maxSize) {
        this->maxSize = maxSize;
    }

    void message() {
        cout << "You can't add more than " << maxSize << " users." << endl;
    }
};

class InvalidPassword {
    string msg;
public:
    InvalidPassword(string msg) {
        this->msg = msg;
    }

    void message() {
        cout << msg << endl;
    }
};

class InvalidEmail {
    string msg;
public:
    InvalidEmail(string msg) {
        this->msg = msg;
    }

    void message() {
        cout << msg << endl;
    }
};

class User {
protected:
    char username[50];
    char password[50];
    char email[50];

    void validatePassword() {
        bool hasUpper = false, hasLower = false, hasDigit = false;
        for (int i = 0; i < strlen(password); i++) {
            if (isupper(password[i])) hasUpper = true;
            if (islower(password[i])) hasLower = true;
            if (isdigit(password[i])) hasDigit = true;
        }
        if (!hasUpper || !hasLower || !hasDigit) {
            throw InvalidPassword("Password is too weak.");
        }
    }

    void validateEmail() {
        int counter = 0;
        for (int i = 0; i < strlen(email); i++) {
            if (email[i] == '@') counter++;
        }
        if (counter != 1) {
            throw InvalidEmail("Mail is not valid.");
        }
    }

public:
    User(char *username, char *password, char *email) {
        strcpy(this->username, username);
        strcpy(this->password, password);
        strcpy(this->email, email);
        validateEmail();
        validatePassword();
    }

    virtual ~User() {}

    virtual double popularity() = 0;
};

class FacebookUser : public User {
    int friends;
    int likes;
    int comments;
    static double LIKE_COEF;
    static double COMMENT_COEF;

public:
    FacebookUser(char *username, char *password, char *email, int friends, int likes, int comments)
            : User(username, password, email) {
        this->friends = friends;
        this->likes = likes;
        this->comments = comments;
    }

    double popularity() override {
        return friends + likes * LIKE_COEF + comments * COMMENT_COEF;
    }
};

double FacebookUser::LIKE_COEF = 0.1;
double FacebookUser::COMMENT_COEF = 0.5;

class TwitterUser : public User {
    int followers;
    int tweets;
    static double TWEET_COEF;

public:
    TwitterUser(char *username, char *password, char *email, int followers, int tweets)
            : User(username, password, email) {
        this->followers = followers;
        this->tweets = tweets;
    }

    double popularity() override {
        return followers + tweets * TWEET_COEF;
    }
};

double TwitterUser::TWEET_COEF = 0.5;

class SocialNetwork {
    User **users;
    int currentUsers;
    static int maxUsers;

public:
    SocialNetwork() {
        this->currentUsers = 0;
        this->users = new User *[maxUsers];
    }

    SocialNetwork &operator+=(User *user) {
        if (currentUsers >= maxUsers) {
            throw MaximumSizeLimit(maxUsers);
        }
        users[currentUsers++] = user;
        return *this;
    }

    double avgPopularity() {
        double total = 0.0;
        for (int i = 0; i < currentUsers; i++) {
            total += users[i]->popularity();
        }
        return total / currentUsers;
    }

    void changeMaximumSize(int number) {
        if (number > maxUsers) {
            maxUsers = number;
            User **newUsers = new User *[maxUsers];
            for (int i = 0; i < currentUsers; i++) {
                newUsers[i] = users[i];
            }
            delete[] users;
            users = newUsers;
        }
    }

    ~SocialNetwork() {
        delete[] users;
    }
};

int SocialNetwork::maxUsers = 5;

int main() {

    SocialNetwork network = SocialNetwork();
    int n;
    cin >> n;
    char username[50];
    char password[50];
    char email[50];
    int userType;
    for (int i = 0; i < n; ++i) {
        cin >> username;
        cin >> password;
        cin >> email;
        cin >> userType;
        try {
            if (userType == 1) {
                int friends;
                int likes;
                int comments;
                cin >> friends >> likes >> comments;
                User *u = new FacebookUser(username, password, email, friends, likes, comments);
                network += u;

            } else {
                int followers;
                int tweets;
                cin >> followers >> tweets;
                User *u = new TwitterUser(username, password, email, followers, tweets);
                network += u;

            }
        } catch (InvalidPassword &e) {
            e.message();
        } catch (InvalidEmail &e) {
            e.message();
        } catch (MaximumSizeLimit &e) {
            e.message();
        }

    }
    network.changeMaximumSize(6);
    cin >> username;
    cin >> password;
    cin >> email;
    int followers;
    int tweets;
    cin >> followers >> tweets;

    try {
        User *u = new TwitterUser(username, password, email, followers, tweets);
        network += u;
    }  catch (InvalidPassword &e) {
        e.message();
    } catch (InvalidEmail &e) {
        e.message();
    } catch (MaximumSizeLimit &e) {
        e.message();
    }

    cout << network.avgPopularity();
}


