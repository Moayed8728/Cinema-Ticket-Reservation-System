#include <iostream>
#include <fstream>
#include <string>
#include "CinemaSystem.h"
#include "Account.h"
using namespace std;

const int MAX_ACCOUNTS = 200;

bool usernameExists(Account acc[], int count, string u) {
    for (int i = 0; i < count; i++) {
        if (acc[i].username == u) {
            return true;
        }
    }
    return false;
}

int findAccount(Account acc[], int count, string u, string p) {
    for (int i = 0; i < count; i++) {
        if (acc[i].username == u && acc[i].password == p) {
            return i;
        }
    }
    return -1;
}

void loadUsers(Account acc[], int &count) {
    ifstream f("users.txt");

    if (!f) {
        return;
    }

    string u, p;

    while (f >> u >> p) {
        acc[count].username = u;
        acc[count].password = p;
        acc[count].role = "user";
        count++;
    }

    f.close();
}

void createAccount(Account acc[], int &count) {
    cout << "\n--- CREATE ACCOUNT ---\n";

    string u, p;

    while (true) {
        cout << "Username: ";
        cin >> u;

        if (u.length() < 4 || u.length() > 15 || !isalpha(u[0])) {
            cout << "Username must start with a letter and be 4–15 chars.\n";
            continue;
        }

        bool valid = true;

        for (char c : u) {
            if (!isalnum(c)) {
                valid = false;
                break;
            }
        }

        if (!valid) {
            cout << "Letters and numbers only.\n";
            continue;
        }

        if (usernameExists(acc, count, u)) {
            cout << "Username exists.\n";
            continue;
        }

        break;
    }

    cout << "Password: ";
    cin >> p;

    acc[count].username = u;
    acc[count].password = p;
    acc[count].role = "user";
    count++;

    ofstream f("users.txt", ios::app);

    if (!f) {
        cout << "Error saving account!\n";
        return;
    }

    f << u << " " << p << "\n";
    f.close();

    cout << "Account created successfully!\n";
}

int main() {
    CinemaSystem sys;
    sys.loadMovies();

    Account acc[MAX_ACCOUNTS];
    int accCount = 0;

    acc[accCount].username = "admin";
    acc[accCount].password = "1234";
    acc[accCount].role = "admin";
    accCount++;

    loadUsers(acc, accCount);

    while (true) {
        cout << "\n============================\n";
        cout << "       CINEMA SYSTEM        \n";
        cout << "============================\n";
        cout << "1. Login\n2. Create Account\n0. Exit\nChoice: ";

        int c = sys.safeChoice(0, 2);

        if (c == 0) {
            cout << "Goodbye!\n";
            break;
        }

        if (c == 1) {
            string u, p;

            cout << "Username: ";
            cin >> u;

            cout << "Password: ";
            cin >> p;

            int idx = findAccount(acc, accCount, u, p);

            if (idx == -1) {
                cout << "Invalid login.\n";
            }
            else {
                if (acc[idx].role == "admin") {
                    sys.adminMenu();
                }
                else {
                    sys.userMenu(u);
                }
            }
        }
        else if (c == 2) {
            createAccount(acc, accCount);
        }
    }

    return 0;
}
