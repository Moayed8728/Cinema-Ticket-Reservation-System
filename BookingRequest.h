#ifndef BOOKINGREQUEST_H
#define BOOKINGREQUEST_H

#include <string>
using namespace std;

struct BookingRequest {
    int requestId;
    string username;
    int movieId;
    int seatNumber;
};

#endif
