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

    
    void loadMovies();
    void saveNewMovie(Movie m);
    void showMovies();
    int findMovieById(int id);
    bool movieIdExists(int id);
    void sortMoviesByTitleAsc();
    int searchMovie(string title);

    void bookTicket(const string &user);
    void showMyTickets(const string &user);
    void cancelTicket(const string &user);

    
    void runSortMenu();
    void userMenu(const string &user);
    void addMovie();
    void adminMenu();

    
    int safeInt();
    int safeChoice(int min, int max);
    string toLower(const string &s);
};
