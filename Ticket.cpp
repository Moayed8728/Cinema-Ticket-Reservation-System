#include "Ticket.h"
#include <iostream>
using namespace std;

void Ticket::display() const {
    cout << "Ticket ID: " << ticketId
         << " | Movie ID: " << movieId
         << " | User: " << username
         << " | Seat: " << seatNumber
         << " | Total: " << total << "\n";
}
