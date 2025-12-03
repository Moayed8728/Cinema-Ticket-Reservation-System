#pragma once
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
};
