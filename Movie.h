#pragma once
#include <string>
using namespace std;

class Movie {
public:
    int id;
    string title;
    string genre;
    int duration;
    double price;
    bool seats[10];

    Movie();
    void display();
    void showSeats();
};
