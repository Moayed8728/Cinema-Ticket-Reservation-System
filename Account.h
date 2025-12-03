#pragma once
#include <string>
using namespace std;

struct Account {
    string username;
    string password;
    string role; // "admin" or "user"
};
