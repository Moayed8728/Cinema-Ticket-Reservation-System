#include "CinemaSystem.h"
#include <iostream>
#include <fstream>
using namespace std;

CinemaSystem::CinemaSystem() {
    movieHead = NULL;
    ticketHead = NULL;
    nextTicketId = 1;
}

int CinemaSystem::safeInt() {
    int n;
    cin >> n;
    while (cin.fail()) {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Enter number only: ";
        cin >> n;
    }
    return n;
}

int CinemaSystem::safeChoice(int min, int max) {
    int c = safeInt();
    while (c < min || c > max) {
        cout << "Invalid choice: ";
        c = safeInt();
    }
    return c;
}

string CinemaSystem::toLower(const string& s) {
    string r = s;
    for (char& c : r)
     c = (char)tolower((unsigned char)c);
    return r;
}

void CinemaSystem::addMovieNode(Movie m) {
    MovieNode* n = new MovieNode{m, NULL};
    if (!movieHead) {
        movieHead = n;
        return;
    }
    MovieNode* curr = movieHead;
    while (curr->next) curr = curr->next;
    curr->next = n;
}

void CinemaSystem::loadMovies() {
    ifstream f("movies.txt");
    if (!f) return;

    Movie m;
    while (f >> m.id >> m.title >> m.genre >> m.duration >> m.price) {
        for (int i = 0; i < 10; i++) m.seats[i] = false;
        addMovieNode(m);
    }
    f.close();
}

void CinemaSystem::saveNewMovie(Movie m) {
    ofstream f("movies.txt", ios::app);
    f << m.id << " " << m.title << " " << m.genre << " " << m.duration << " " << m.price << "\n";
    f.close();
}

void CinemaSystem::showMovies() {
    cout << "\n--- MOVIES ---\n";
    MovieNode* curr = movieHead;
    while (curr) {
        curr->data.display();
        curr = curr->next;
    }
}

MovieNode* CinemaSystem::findMovieById(int id) {
    MovieNode* curr = movieHead;
    while (curr) {
        if (curr->data.id == id) return curr;
        curr = curr->next;
    }
    return NULL;
}

bool CinemaSystem::movieIdExists(int id) {
    return findMovieById(id) != NULL;
}

MovieNode* CinemaSystem::findMovieByTitle(const string& title) {
    string key = toLower(title);
    MovieNode* curr = movieHead;
    while (curr) {
        if (toLower(curr->data.title) == key) return curr;
        curr = curr->next;
    }
    return NULL;
}

void CinemaSystem::searchMovieMenu() {
    cout << "Enter title: ";
    string t;
    cin >> t;
    MovieNode* mn = findMovieByTitle(t);
    if (!mn) cout << "Not found.\n";
    else mn->data.display();
}

void CinemaSystem::addTicket(Ticket t) {
    TicketNode* n = new TicketNode{t, NULL};
    if (!ticketHead) {
        ticketHead = n;
        return;
    }
    TicketNode* curr = ticketHead;
    while (curr->next) curr = curr->next;
    curr->next = n;
}

void CinemaSystem::bookTicket(const string& user) {
    showMovies();
    cout << "Movie ID: ";
    int id = safeInt();

    MovieNode* mn = findMovieById(id);
    if (!mn) {
        cout << "Movie not found\n";
        return;
    }

    mn->data.showSeats();
    cout << "Seat (0-9): ";
    int seat = safeInt();

    if (seat < 0 || seat > 9 || mn->data.seats[seat]) {
        cout << "Invalid seat\n";
        return;
    }

    mn->data.seats[seat] = true;

    Ticket t;
    t.ticketId = nextTicketId++;
    t.movieId = id;
    t.username = user;
    t.seatNumber = seat;
    t.total = mn->data.price;

    addTicket(t);
    cout << "Ticket booked!\n";
}

void CinemaSystem::showMyTickets(const string& user) {
    bool found = false;
    TicketNode* curr = ticketHead;

    while (curr) {
        if (curr->data.username == user) {
            curr->data.display();
            found = true;
        }
        curr = curr->next;
    }

    if (!found) cout << "No tickets found\n";
}

void CinemaSystem::viewAllTickets() {
    double totalPrice = 0.0;
    cout << "\n--- ALL TICKETS ---\n";

    TicketNode* curr = ticketHead;
    if (!curr) {
        cout << "No tickets.\n";
        return;
    }

    while (curr) {
        curr->data.display();
        totalPrice += curr->data.total;
        curr = curr->next;
    }

    cout << "Total price of all tickets: RM " << totalPrice << "\n";
}

void CinemaSystem::cancelTicket(const string& user) {
    TicketNode* curr = ticketHead;
    TicketNode* prev = NULL;

    showMyTickets(user);
    cout << "Ticket ID to cancel (0 to back): ";
    int id = safeInt();
    if (id == 0)
     
    return;

    while (curr) {
        if (curr->data.ticketId == id && curr->data.username == user) {
            
            MovieNode* mn = findMovieById(curr->data.movieId);
            
            if (mn) mn->data.seats[curr->data.seatNumber] = false;

            if (!prev) ticketHead = curr->next;
            
            else 
            prev->next = curr->next;

            delete curr;
            cout << "Ticket cancelled\n";
            return;
        }
        prev = curr;
        curr = curr->next;
    }

    cout << "Ticket not found\n";
}

void CinemaSystem::sortByTitle(bool asc) {
    if (!movieHead) return;
    bool swapped;
    do {
        swapped = false;
        MovieNode* curr = movieHead;
        while (curr && curr->next) {
            if ((asc && curr->data.title > curr->next->data.title) ||
                (!asc && curr->data.title < curr->next->data.title)) {
                swap(curr->data, curr->next->data);
                swapped = true;
            }
            curr = curr->next;
        }
    } while (swapped);
}

void CinemaSystem::sortByPrice(bool asc) {
    if (!movieHead) return;
    bool swapped;
    do {
        swapped = false;
        MovieNode* curr = movieHead;
        while (curr && curr->next) {
            if ((asc && curr->data.price > curr->next->data.price) ||
                (!asc && curr->data.price < curr->next->data.price)) {
                swap(curr->data, curr->next->data);
                swapped = true;
            }
            curr = curr->next;
        }
    } while (swapped);
}

void CinemaSystem::sortByDuration(bool asc) {
    if (!movieHead) return;
    bool swapped;
    do {
        swapped = false;
        MovieNode* curr = movieHead;
        while (curr && curr->next) {
            if ((asc && curr->data.duration > curr->next->data.duration) ||
                (!asc && curr->data.duration < curr->next->data.duration)) {
                swap(curr->data, curr->next->data);
                swapped = true;
            }
            curr = curr->next;
        }
    } while (swapped);
}

void CinemaSystem::runSortMenu() {
    cout << "\nSort by:\n1. Title\n2. Price\n3. Duration\n0. Back\nChoice: ";
    int c = safeChoice(0, 3);
    if (c == 0) return;

    cout << "1. Asc\n2. Desc\nChoice: ";
    bool asc = (safeChoice(1, 2) == 1);

    if (c == 1) 
    sortByTitle(asc);
    
    if (c == 2) 
    sortByPrice(asc);
    
    if (c == 3) 
    sortByDuration(asc);

    cout << "Movies sorted.\n";
}

void CinemaSystem::addMovie() {
    Movie m;
    cout << "Movie ID: ";
    m.id = safeInt();

    if (movieIdExists(m.id)) {
        cout << "ID exists\n";
        return;
    }

    cout << "Title: ";
    cin >> m.title;
    cout << "Genre: ";
    cin >> m.genre;
    cout << "Duration: ";
    m.duration = safeInt();
    cout << "Price: ";
    cin >> m.price;

    for (int i = 0; i < 10; i++) m.seats[i] = false;

    addMovieNode(m);
    saveNewMovie(m);
    cout << "Movie added\n";
}

void CinemaSystem::userMenu(const string& user) {
    while (true) {
        cout << "\n--- USER MENU (" << user << ") ---\n";
        cout << "1. View movies\n2. Book ticket\n3. Cancel ticket\n4. View my tickets\n5. Search movie\n6. Sort movies\n0. Logout\nChoice: ";

        int c = safeChoice(0, 6);

        if (c == 0) 
        return;
        
        if (c == 1) 
        showMovies();
        
        if (c == 2) 
        bookTicket(user);
        
        if (c == 3) 
        cancelTicket(user);
        
        
        if (c == 4) 
        showMyTickets(user);
        
        if (c == 5) 
        searchMovieMenu();
        
        if (c == 6) 
        runSortMenu();
    }
}

void CinemaSystem::adminMenu() {
    while (true) {
        cout << "\n--- ADMIN MENU ---\n";
        cout << "1. View movies\n2. Add movie\n3. Sort movies\n4. Search movie\n5. View all tickets\n0. Logout\nChoice: ";

        int c = safeChoice(0, 5);

            if (c == 0)
            return;
            if (c == 1) 
            showMovies();
            if (c == 2)
            addMovie();
            if (c == 3) 
            runSortMenu();
            if (c == 4) 
            searchMovieMenu();
            if (c == 5) 
        viewAllTickets();
    }
}
