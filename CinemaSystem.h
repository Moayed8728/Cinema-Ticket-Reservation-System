#pragma once
#include "Movie.h"
#include "Ticket.h"
#include <string>
using namespace std;

class CinemaSystem {
public:
    Movie movies[100];
    Ticket tickets[300];
    int movieCount;
    int ticketCount;
    int nextTicketId;

    CinemaSystem();

    // Movie functions
    void loadMovies();
    void saveNewMovie(Movie m);
    void showMovies();
    int findMovieById(int id);
    bool movieIdExists(int id);
    void sortMoviesByTitleAsc();
    int searchMovie(string title);

    // Ticket functions
    void bookTicket(const string &user);
    void showMyTickets(const string &user);
    void cancelTicket(const string &user);

    // Menus
    void runSortMenu();
    void userMenu(const string &user);
    void addMovie();
    void adminMenu();

    // Utilities
    int safeInt();
    int safeChoice(int min, int max);
    string toLower(const string &s);
};
