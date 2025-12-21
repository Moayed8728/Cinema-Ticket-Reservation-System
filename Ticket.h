#ifndef TICKET_H
#define TICKET_H

#include <string>
using namespace std;

class Ticket {
public:
    int ticketId;
    int movieId;
    string username;
    int seatNumber;
    double total;

    Ticket();

    void display();
    void display() const;
};

#endif
