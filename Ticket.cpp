#include "Ticket.h"
#include <iostream>
using namespace std;

Ticket::Ticket() {          
    ticketId = 0;
    movieId = 0;
    username = "";
    seatNumber = -1;
    total = 0.0;
}

void Ticket::display() {
    const_cast<const Ticket*>(this)->display();
}

void Ticket::display() const {
    cout << "Ticket ID: " << ticketId
         << " | Movie ID: " << movieId
         << " | User: " << username
         << " | Seat: " << seatNumber
         << " | Total: " << total << "\n";
}
