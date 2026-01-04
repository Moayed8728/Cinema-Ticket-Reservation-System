#include "BookingQueue.h"

BookingQueue::BookingQueue() {
    frontPtr = NULL;
    rearPtr = NULL;
    queueCount = 0;
}

BookingQueue::~BookingQueue() {
    RequestNode* currentNode = frontPtr;

    while (currentNode != NULL) {
        RequestNode* temp = currentNode;
        currentNode = currentNode->next;
        delete temp;
    }

    frontPtr = NULL;
    rearPtr = NULL;
    queueCount = 0;
}

bool BookingQueue::isEmpty() const {
    return frontPtr == NULL; 
}

int BookingQueue::size() const {
    return queueCount;
}

void BookingQueue::enQueue(const BookingRequest& newRequest) {
    RequestNode* newNode = new RequestNode;
    newNode->requestData = newRequest;
    newNode->next = NULL;

    
    if (isEmpty()) {
        frontPtr = newNode;
        rearPtr = newNode;
    } else {
    
        rearPtr->next = newNode;
        rearPtr = newNode;
    }

    queueCount++;
}

bool BookingQueue::deQueue(BookingRequest& removedRequest) {
    if (isEmpty()) {
        return false;
    }

    RequestNode* temp = frontPtr;
    removedRequest = frontPtr->requestData;

    
    frontPtr = frontPtr->next;
    delete temp;
    queueCount--;

    
    if (frontPtr == NULL) {
        rearPtr = NULL;
    }

    return true;
}

bool BookingQueue::getFront(BookingRequest& out) const {
    if (isEmpty()) return false;
    out = frontPtr->requestData;
    return true;
}

bool BookingQueue::getRear(BookingRequest& out) const {
    if (isEmpty()) return false;
    out = rearPtr->requestData;
    return true;
}


int BookingQueue::findPositionByUsername(const string& username) const {
    int currentPosition = 1;
    RequestNode* currentNode = frontPtr;

    while (currentNode != NULL) {
        if (currentNode->requestData.username == username) {
            return currentPosition; 
        }
        currentNode = currentNode->next;
        currentPosition++;
    }

    return -1; 
}

void BookingQueue::displayQueue() const {
    if (isEmpty()) {
        cout << "Queue is empty.\n";
        return;
    }

    cout << "\n--- Pending Booking Requests (FIFO) ---\n";
    RequestNode* currentNode = frontPtr;

    while (currentNode != NULL) {
        cout << "Request ID: " << currentNode->requestData.requestId << " | User: " 
        << currentNode->requestData.username << " | Movie ID: " 
        << currentNode->requestData.movieId << " | Seat: " 
        << currentNode->requestData.seatNumber << "\n";
        
        currentNode = currentNode->next;
    }
}
