#ifndef CINEMASYSTEM_H
#define CINEMASYSTEM_H

#include "Movie.h"
#include "Ticket.h"
#include <string>
#include "BookingQueue.h"
#include "BookingRequest.h"

using namespace std;

struct MovieNode {
    Movie data;
    MovieNode* next;
};

struct TicketNode {
    Ticket data;
    TicketNode* next;
};

class CinemaSystem {
private:
    MovieNode* movieHead;
    TicketNode* ticketHead;
    int nextTicketId;
    BookingQueue bookingRequestQueue;
    int nextRequestId;


public:
    CinemaSystem();

    void loadMovies();
    void saveNewMovie(Movie m);

    void addMovieNode(Movie m);
    MovieNode* findMovieById(int id);
    bool movieIdExists(int id);
    void showMovies();

    void addTicket(Ticket t);
    void showMyTickets(const string& user);
    void cancelTicket(const string& user);
    void bookTicket(const string& user);

    MovieNode* findMovieByTitle(const string& title);
    void searchMovieMenu();

    void sortByTitle(bool asc);
    void sortByPrice(bool asc);
    void sortByDuration(bool asc);
    void runSortMenu();

    void viewAllTickets();

    void userMenu(const string& user);
    void addMovie();
    void adminMenu();

    int safeInt();
    int safeChoice(int min, int max);
    string toLower(const string& s);


    void submitBookingRequest(const string& username);    
    void checkMyQueueStatus(const string& username);      
    void viewQueueSummary();                               
    void processNextBookingRequest();                      

};

#endif
