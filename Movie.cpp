#include "Movie.h"
#include <iostream>
using namespace std;

Movie::Movie() {
    id = 0;
    title = "";
    genre = "";
    duration = 0;
    price = 0.0;
    for (int i = 0; i < 10; i++) seats[i] = false;
}

void Movie::display() {
    const_cast<const Movie*>(this)->display();
}

void Movie::showSeats() {
    const_cast<const Movie*>(this)->showSeats();
}

void Movie::display() const {
    cout << "ID: " << id
         << " | Title: " << title
         << " | Genre: " << genre
         << " | Duration: " << duration
         << " | Price: " << price << "\n";
}

void Movie::showSeats() const {
    cout << "Seats: ";
    for (int i = 0; i < 10; i++) {
        if (seats[i]) cout << "[X]";
        else cout << "[" << i << "]";
    }
    cout << "\n";
}
