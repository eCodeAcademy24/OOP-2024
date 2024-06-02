#include <iostream>
#include <cstring>
#include <fstream>

using namespace std;

void wtf() {
    ofstream fout("input.txt");

    string line;

    while (getline(std::cin, line)) {
        if (line == "----") {
            break;
        }
        fout << line << endl;
    }
}

void rff1() {
    ifstream fin("output1.txt");
    string line;
    while (getline(fin, line)) {
        cout << line << endl;
    }
}

void rff2() {
    ifstream fin("output2.txt");
    string line;
    while (getline(fin, line)) {
        cout << line << endl;
    }
}

class Music {
private:
    string title;
    string artist;
    int year;

public:
    Music(const string &title = "", const string &artist = "", int year = 1900) : title(title), artist(artist), year(year) {}

    friend ostream &operator<<(ostream &os, const Music &music) {
        os << music.title << " by " << music.artist << " (" << music.year << ")";
        return os;
    }

    bool operator==(const Music &rhs) const {
        return title == rhs.title && artist == rhs.artist && year == rhs.year;
    }

    bool operator!=(const Music &rhs) const {
        return !(rhs == *this);
    }

    string &getArtist() {
        return artist;
    }
};

class MusicAlreadyExistsException {
private:
    Music m;
public:
    MusicAlreadyExistsException(const Music &m) {
        this->m = m;
    }

    void message() {
        cout << "Music \"" << m << "\" already exists in the library" << endl;
    }
};

class MusicLibrary {
private:
    string name;
    Music *musics;
    int n;
public:
    MusicLibrary(const string &name = "") : name(name), n(0), musics(new Music[0]) {}

    MusicLibrary(const MusicLibrary &other) : name(other.name), n(other.n), musics(new Music[other.n]) {
        for (int i = 0; i < n; i++) {
            musics[i] = other.musics[i];
        }
    }

    MusicLibrary &operator=(const MusicLibrary &other) {
        if (this != &other) {
            delete[] musics;
            name = other.name;
            n = other.n;
            musics = new Music[n];
            for (int i = 0; i < n; i++) {
                musics[i] = other.musics[i];
            }
        }
        return *this;
    }

    ~MusicLibrary() {
        delete[] musics;
    }

    MusicLibrary &operator+=(const Music &m) {
        for (int i = 0; i < n; i++) {
            if (musics[i] == m) {
                throw MusicAlreadyExistsException(m);
            }
        }

        Music *tmp = new Music[n + 1];
        for (int i = 0; i < n; i++) {
            tmp[i] = musics[i];
        }
        tmp[n++] = m;
        delete[] musics;
        musics = tmp;

        return *this;
    }

    friend ostream &operator<<(ostream &out, const MusicLibrary &ml) {
        out << ml.name << endl;
        for (int i = 0; i < ml.n; i++) {
            out << ml.musics[i] << endl;
        }
        return out;
    }

    Music *getMusicsByArtist(const string &artist, int &numberFound) {
        numberFound = 0;
        for (int i = 0; i < n; i++) {
            if (musics[i].getArtist() == artist) {
                numberFound++;
            }
        }

        if (numberFound == 0) {
            return nullptr;
        }

        Music *result = new Music[numberFound];
        int j = 0;
        for (int i = 0; i < n; i++) {
            if (musics[i].getArtist() == artist) {
                result[j++] = musics[i];
            }
        }
        return result;
    }
};

int main() {
    wtf();

    ifstream ifs("input.txt");

    string libraryName;
    getline(ifs, libraryName);

    MusicLibrary library(libraryName);

    int n;
    ifs >> n;

    ifs.ignore();

    string t, a;
    int year;

    for (int i = 0; i < n; i++) {
        getline(ifs, t);
        getline(ifs, a);
        ifs >> year;
        ifs.ignore();

        Music m(t, a, year);
        try {
            library += m;
        } catch (MusicAlreadyExistsException &e) {
            e.message();
        }
    }

    ifs.close();

    ofstream ofs1("output1.txt");
    ofs1 << library;
    ofs1.close();

    string artist;
    getline(std::cin, artist);

    ofstream ofs2("output2.txt");

    Music *result = library.getMusicsByArtist(artist, n);

    if (result == nullptr) {
        ofs2 << "None";
    } else {
        for (int i = 0; i < n; i++) {
            ofs2 << result[i] << endl;
        }
        delete[] result;
    }

    ofs2.close();

    rff1();
    cout << "Music by " << artist << " are: " << endl;
    rff2();

    return 0;
}
