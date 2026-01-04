#ifndef BOOKINGQUEUE_H
#define BOOKINGQUEUE_H

#include <iostream>
#include <string>
#include "BookingRequest.h"
using namespace std;


struct RequestNode {
    BookingRequest requestData;
    RequestNode* next;
};

class BookingQueue {
private:
    RequestNode* frontPtr;   
    RequestNode* rearPtr;    
    int queueCount;          

public:
    BookingQueue();          
    ~BookingQueue();         

    bool isEmpty() const;
    int size() const;

    void enQueue(const BookingRequest& newRequest);
    bool deQueue(BookingRequest& removedRequest);

    bool getFront(BookingRequest& out) const;
    bool getRear(BookingRequest& out) const;


    int findPositionByUsername(const string& username) const;

    void displayQueue() const; 
};

#endif
