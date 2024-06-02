#include <iostream>
#include <cstring>
#include <fstream>

using namespace std;

void wtf() {
    ofstream fout("input.txt");

    string line;

    while (getline(cin, line)) {
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

class Movie {
private:
    string title;
    string director;
    int year;

public:
    Movie(string &title, string &director, int year = 1900) {
        this->title = title;
        this->director = director;
        this->year = year;
    }

    friend ostream &operator<<(ostream &os, const Movie &movie) {
        os << movie.title << " directed by " << movie.director << " (" << movie.year << ")";
        return os;
    }

    bool operator==(const Movie &rhs) const {
        return title == rhs.title && director == rhs.director && year == rhs.year;
    }

    bool operator!=(const Movie &rhs) const {
        return !(rhs == *this);
    }

    string &getDirector() {
        return director;
    }
};

class MovieAlreadyExistsException {
public:
    MovieAlreadyExistsException() {
    }

    void message() {
        cout << "Movie already exists" << endl;
    }
};

class MovieLibrary {
private:
    string name;
    Movie **movies;
    int n;
public:
    MovieLibrary(string &name) {
        this->movies = new Movie *[0];
        this->n = 0;
        this->name = name;
    }

    MovieLibrary(MovieLibrary &other) {
        this->name = other.name;
        this->n = other.n;
        for (int i = 0; i < n; i++) {
            movies[i] = other.movies[i];
        }
    }

    MovieLibrary &operator=(MovieLibrary &other) {
        if (this != &other) {
            delete[] movies;
            this->name = other.name;
            this->n = other.n;
            movies = new Movie *[n];
            for (int i = 0; i < n; i++) {
                movies[i] = other.movies[i];
            }
        }
        return *this;
    }

    ~MovieLibrary() {
        delete[] movies;
    }

    MovieLibrary &operator+=(Movie *m) {
        for (int i = 0; i < n; i++) {
            if (movies[i] == m) {
                throw MovieAlreadyExistsException();
            }
        }

        Movie **tmp = new Movie *[n + 1];
        for (int i = 0; i < n; i++) {
            tmp[i] = movies[i];
        }
        tmp[n++] = m;
        delete[] movies;
        movies = tmp;

        return *this;
    }

    friend ostream &operator<<(ostream &out, const MovieLibrary &ml) {
        out << ml.name << endl;
        for (int i = 0; i < ml.n; i++) {
            out << ml.movies[i] << endl;
        }
        return out;
    }

    Movie **getMoviesByDirector(const string &director, int &numberFound) {
        numberFound = 0;
        for (int i = 0; i < n; i++) {
            if (movies[i]->getDirector() == director) {
                numberFound++;
            }
        }

        if (numberFound == 0) {
            return nullptr;
        }

        Movie **result = new Movie *[numberFound];
        int j = 0;
        for (int i = 0; i < n; i++) {
            if (movies[i]->getDirector() == director) {
                result[j++] = movies[i];
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

    MovieLibrary library(libraryName);

    int n;
    ifs >> n;

    ifs.ignore();

    string t, d;
    int year;

    for (int i = 0; i < n; i++) {
        getline(ifs, t);
        getline(ifs, d);
        ifs >> year;
        ifs.ignore();

        Movie m(t, d, year);
        try {
            library += &m;
        } catch (MovieAlreadyExistsException &e) {
            e.message();
        }
    }

    ifs.close();

    ofstream ofs1("output1.txt");
    ofs1 << library;
    ofs1.close();

    string director;
    getline(cin, director);

    ofstream ofs2("output2.txt");

    Movie **result = library.getMoviesByDirector(director, n);

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
    cout << "Movies directed by " << director << " are: " << endl;
    rff2();

    return 0;
}
