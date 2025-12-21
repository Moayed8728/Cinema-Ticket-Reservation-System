#include "Movie.h"
#include <iostream>
using namespace std;

void Movie::display() const {
    cout << "ID: " << id
         << " | Title: " << title
         << " | Genre: " << genre
         << " | Duration: " << duration
         << " | Price: " << price << "\n";
}

void Movie::showSeats() const {
    cout << "Seats: ";
    for(int i = 0; i < 10; i++){
        if(seats[i]) cout << "[X]";
        else         cout << "[" << i << "]";
    }
    cout << "\n";
}
