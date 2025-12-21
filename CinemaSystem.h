#ifndef CINEMASYSTEM_H
#define CINEMASYSTEM_H

#include "Movie.h"
#include "Ticket.h"
#include <string>
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

public:
    CinemaSystem();

    void loadMovies();
    void saveNewMovie(Movie m);

    void addMovieNode(Movie m);
    MovieNode* findMovieById(int id);
    bool movieIdExists(int id);
    void showMovies();
    int searchMovie(string title);

    void addTicket(Ticket t);
    void showMyTickets(const string& user);
    void cancelTicket(const string& user);

    void bookTicket(const string& user);

    void runSortMenu();
    void userMenu(const string& user);
    void addMovie();
    void adminMenu();

    int safeInt();
    int safeChoice(int min, int max);
    string toLower(const string& s);
};

#endif
