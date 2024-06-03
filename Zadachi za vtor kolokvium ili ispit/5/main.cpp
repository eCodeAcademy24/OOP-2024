#include <iostream>
#include <cstring>

using namespace std;

enum typeC {
    standard, loyal, vip
};

class Customer {
private:
    string name;
    string email;
    typeC customerType;
    int baseDiscount;
    int additionalDiscount;
    int numProducts;

    static int globalBaseDiscount;

public:
    Customer(string name = "", string email = "", typeC customerType = standard, int numProducts = 0) {
        this->name = name;
        this->email = email;

        this->baseDiscount = (customerType == loyal) ? globalBaseDiscount : 0;
        this->additionalDiscount = (customerType == vip) ? 30 : 0;
        this->numProducts = numProducts;
        this->customerType = customerType;
    }

    static void setDiscount1(int discount) {
        globalBaseDiscount = discount;
    }

    string getEmail() {
        return email;
    }

    typeC getCustomerType() {
        return customerType;
    }

    void setCustomerType(typeC newType) {
        customerType = newType;
        baseDiscount = (newType == loyal) ? globalBaseDiscount : 0;
        additionalDiscount = (newType == vip) ? 30 : 0;
    }

    int getNumProducts() {
        return numProducts;
    }

    friend ostream &operator<<(ostream &os, const Customer &c) {
        os << c.name << endl
           << c.email << endl
           << c.numProducts << endl;
        switch (c.customerType) {
            case standard:
                os << "standard ";
                break;
            case loyal:
                os << "loyal ";
                break;
            case vip:
                os << "vip ";
                break;
        }
        os << (c.baseDiscount + c.additionalDiscount) << endl;
        return os;
    }
};

int Customer::globalBaseDiscount = 10;

class UserExistsException {
public:

    void message() {
        cout << "The user already exists in the list!" << endl;
    }
};

class FINKI_bookstore {
private:
    Customer *customers;
    int numCustomers;

    bool customerExists(string email) {
        for (int i = 0; i < numCustomers; ++i) {
            if (customers[i].getEmail() == email) {
                return true;
            }
        }
        return false;
    }

public:
    FINKI_bookstore() : customers(nullptr), numCustomers(0) {}

    ~FINKI_bookstore() {
        delete[] customers;
    }

    FINKI_bookstore &operator+=(Customer &c) {
        if (customerExists(c.getEmail())) {
            throw UserExistsException();
        }

        Customer *temp = new Customer[numCustomers + 1];
        for (int i = 0; i < numCustomers; ++i) {
            temp[i] = customers[i];
        }
        temp[numCustomers] = c;
        delete[] customers;
        customers = temp;
        ++numCustomers;

        return *this;
    }

    void update() {
        for (int i = 0; i < numCustomers; ++i) {
            if (customers[i].getCustomerType() == standard && customers[i].getNumProducts() > 5) {
                customers[i].setCustomerType(loyal);
            } else if (customers[i].getCustomerType() == loyal && customers[i].getNumProducts() > 10) {
                customers[i].setCustomerType(vip);
            }
        }
    }

    void setCustomers(Customer *custArray, int n) {
        customers = new Customer[n];
        numCustomers = n;
        for (int i = 0; i < n; ++i) {
            customers[i] = custArray[i];
        }
    }

    friend ostream &operator<<(ostream &os, const FINKI_bookstore &fb) {
        for (int i = 0; i < fb.numCustomers; ++i) {
            os << fb.customers[i];
        }
        return os;
    }
};

int main() {
    int testCase;
    cin >> testCase;

    char name[50];
    char email[50];
    int tC;
    int numProducts;

    if (testCase == 1) {
        cout << "===== Test Case - Customer Class ======" << endl;
        cin.get();
        cin.getline(name, 50);
        cin.getline(email, 50);
        cin >> tC;
        cin >> numProducts;
        cout << "===== CONSTRUCTOR ======" << endl;
        Customer c(name, email, (typeC) tC, numProducts);
        cout << c;
    }

    if (testCase == 2) {
        cout << "===== Test Case - Static Members ======" << endl;
        cin.get();
        cin.getline(name, 50);
        cin.getline(email, 50);
        cin >> tC;
        cin >> numProducts;
        cout << "===== CONSTRUCTOR ======" << endl;
        Customer c(name, email, (typeC) tC, numProducts);
        cout << c;

        Customer::setDiscount1(5);

        cout << c;
    }

    if (testCase == 3) {
        cout << "===== Test Case - FINKI-bookstore ======" << endl;
        FINKI_bookstore fc;
        int n;
        cin >> n;
        Customer customers[50];
        for (int i = 0; i < n; ++i) {
            cin.get();
            cin.getline(name, 50);
            cin.getline(email, 50);
            cin >> tC;
            cin >> numProducts;
            Customer c(name, email, (typeC) tC, numProducts);
            customers[i] = c;
        }

        fc.setCustomers(customers, n);

        cout << fc << endl;
    }

    if (testCase == 4) {
        cout << "===== Test Case - operator+= ======" << endl;
        FINKI_bookstore fc;
        int n;
        cin >> n;
        Customer customers[50];
        for (int i = 0; i < n; ++i) {
            cin.get();
            cin.getline(name, 50);
            cin.getline(email, 50);
            cin >> tC;
            cin >> numProducts;
            Customer c(name, email, (typeC) tC, numProducts);
            customers[i] = c;
        }

        fc.setCustomers(customers, n);
        cout << "OPERATOR +=" << endl;
        cin.get();
        cin.getline(name, 50);
        cin.getline(email, 50);
        cin >> tC;
        cin >> numProducts;
        Customer c(name, email, (typeC) tC, numProducts);
        try {
            fc += c;
        } catch (UserExistsException &e) {
            e.message();
        }

        cout << fc;
    }

    if (testCase == 5) {
        cout << "===== Test Case - operator+= (exception) ======" << endl;
        FINKI_bookstore fc;
        int n;
        cin >> n;
        Customer customers[50];
        for (int i = 0; i < n; ++i) {
            cin.get();
            cin.getline(name, 50);
            cin.getline(email, 50);
            cin >> tC;
            cin >> numProducts;
            Customer c(name, email, (typeC) tC, numProducts);
            customers[i] = c;
        }

        fc.setCustomers(customers, n);
        cout << "OPERATOR +=" << endl;
        cin.get();
        cin.getline(name, 50);
        cin.getline(email, 50);
        cin >> tC;
        cin >> numProducts;

        try {
            Customer newCustomer(name, email, (typeC) tC, numProducts);
            fc += newCustomer;
        } catch (UserExistsException &e) {
            e.message();
        }

        cout << fc;
    }

    if (testCase == 6) {
        cout << "===== Test Case - update method  ======" << endl << endl;
        FINKI_bookstore fc;
        int n;
        cin >> n;
        Customer customers[50];
        for (int i = 0; i < n; ++i) {
            cin.get();
            cin.getline(name, 50);
            cin.getline(email, 50);
            cin >> tC;
            cin >> numProducts;
            Customer c(name, email, (typeC) tC, numProducts);
            customers[i] = c;
        }

        fc.setCustomers(customers, n);

        cout << "Update:" << endl;
        fc.update();
        cout << fc;
    }
    return 0;
}
