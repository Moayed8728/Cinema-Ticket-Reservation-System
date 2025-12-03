#include "CinemaSystem.h"
#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
using namespace std;

// =================== UTILITIES ===================
int CinemaSystem::safeInt() {
    int number;
    cin >> number;
    while (cin.fail()) {
        cout << "Invalid input! Please enter a NUMBER: ";
        cin.clear();
        cin.ignore(10000, '\n');
        cin >> number;
    }
    return number;
}

int CinemaSystem::safeChoice(int min, int max) {
    int number = safeInt();
    while (number < min || number > max) {
        cout << "Invalid input! Please enter a valid option: ";
        number = safeInt();
    }
    return number;
}

string CinemaSystem::toLower(const string &s) {
    string res = s;
    for (char &c : res) c = tolower(c);
    return res;
}

// =================== MOVIE ===================
Movie::Movie() {
    id = 0; duration = 0; price = 0.0;
    for (int i = 0; i < 10; i++) seats[i] = false;
}

void Movie::display() {
    cout << id << " | " << title << " | " << genre
         << " | " << duration << " mins | RM " << price << endl;
}

void Movie::showSeats() {
    cout << "\nSeats (0 = free, X = taken):\n";
    for (int i = 0; i < 10; i++)
        cout << "[" << i << "] " << (seats[i] ? "X  " : "0  ");
    cout << endl;
}

// =================== TICKET ===================
Ticket::Ticket() {
    ticketId = 0; movieId = 0; seatNumber = -1; total = 0.0;
}

void Ticket::display() {
    cout << "Ticket " << ticketId
         << " | Movie: " << movieId
         << " | User: " << username
         << " | Seat: " << seatNumber
         << " | Total: RM " << total << endl;
}

// =================== CINEMA SYSTEM ===================
CinemaSystem::CinemaSystem() {
    movieCount = 0;
    ticketCount = 0;
    nextTicketId = 1;
}

// --------- LOAD MOVIES ----------
void CinemaSystem::loadMovies() {
    ifstream f("movies.txt");
    if (!f) { cout << "movies.txt not found.\n"; return; }

    while (f >> movies[movieCount].id
             >> movies[movieCount].title
             >> movies[movieCount].genre
             >> movies[movieCount].duration
             >> movies[movieCount].price)
    {
        for (int i = 0; i < 10; i++)
            movies[movieCount].seats[i] = false;
        movieCount++;
        if (movieCount >= 100) break;
    }
    f.close();
    sortMoviesByTitleAsc();
    cout << movieCount << " movies loaded.\n";
}

// --------- SAVE NEW MOVIE ----------
void CinemaSystem::saveNewMovie(Movie m) {
    ofstream f("movies.txt", ios::app);
    if (!f) { cout << "Error saving movie.\n"; return; }
    f << m.id << " " << m.title << " " << m.genre << " "
      << m.duration << " " << m.price << "\n";
    f.close();
}

// --------- SHOW MOVIES ----------
void CinemaSystem::showMovies() {
    cout << "\n--- MOVIES ---\n";
    for (int i = 0; i < movieCount; i++) movies[i].display();
}

// --------- FIND MOVIE BY ID ----------
int CinemaSystem::findMovieById(int id) {
    for (int i = 0; i < movieCount; i++)
        if (movies[i].id == id) return i;
    return -1;
}

// --------- CHECK DUPLICATE MOVIE ID ----------
bool CinemaSystem::movieIdExists(int id) {
    for (int i = 0; i < movieCount; i++)
        if (movies[i].id == id) return true;
    return false;
}

// --------- SORT MOVIES BY TITLE ASC ----------
void CinemaSystem::sortMoviesByTitleAsc() {
    for (int i = 0; i < movieCount - 1; i++) {
        int mn = i;
        for (int j = i + 1; j < movieCount; j++) {
            if (movies[j].title < movies[mn].title) mn = j;
        }
        swap(movies[i], movies[mn]);
    }
}

// --------- SEARCH MOVIE (BINARY SEARCH) ----------
int CinemaSystem::searchMovie(string title) {
    sortMoviesByTitleAsc();
    title = toLower(title);
    int left = 0, right = movieCount - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        string midTitle = toLower(movies[mid].title);
        if (midTitle == title) return mid;
        else if (title < midTitle) right = mid - 1;
        else left = mid + 1;
    }
    return -1;
}

// --------- BOOK TICKET ----------
void CinemaSystem::bookTicket(const string &user) {
    showMovies();
    cout << "\nEnter Movie ID: ";
    int id = safeInt();
    int idx = findMovieById(id);
    if (idx == -1) { cout << "Movie not found.\n"; return; }

    movies[idx].showSeats();
    cout << "\nChoose seat (0–9): ";
    int seat = safeInt();
    if (seat < 0 || seat > 9) { cout << "Invalid seat.\n"; return; }
    if (movies[idx].seats[seat]) { cout << "Seat already taken.\n"; return; }

    movies[idx].seats[seat] = true;
    Ticket &t = tickets[ticketCount++];
    t.ticketId = nextTicketId++;
    t.movieId = id;
    t.username = user;
    t.seatNumber = seat;
    t.total = movies[idx].price;

    cout << "\nTicket booked successfully!\n";
}

// --------- SHOW MY TICKETS ----------
void CinemaSystem::showMyTickets(const string &user) {
    cout << "\n--- YOUR TICKETS ---\n";
    bool found = false;
    for (int i = 0; i < ticketCount; i++) {
        if (tickets[i].username == user) {
            tickets[i].display();
            found = true;
        }
    }
    if (!found) cout << "You have no tickets.\n";
}

// --------- CANCEL TICKET ----------
void CinemaSystem::cancelTicket(const string &user) {
    bool hasTickets = false;
    for (int i = 0; i < ticketCount; i++)
        if (tickets[i].username == user) { hasTickets = true; break; }
    if (!hasTickets) { cout << "You have no tickets.\n"; return; }

    showMyTickets(user);
    cout << "\nEnter Ticket ID to cancel (0 to back): ";
    int tid = safeInt();
    if (tid == 0) return;

    int pos = -1;
    for (int i = 0; i < ticketCount; i++)
        if (tickets[i].ticketId == tid && tickets[i].username == user) pos = i;

    if (pos == -1) { cout << "Ticket not found.\n"; return; }

    int mid = findMovieById(tickets[pos].movieId);
    int seat = tickets[pos].seatNumber;
    movies[mid].seats[seat] = false;

    for (int i = pos; i < ticketCount - 1; i++)
        tickets[i] = tickets[i + 1];
    ticketCount--;

    cout << "Ticket cancelled.\n";
}

// --------- SORT MENU ----------
void CinemaSystem::runSortMenu() {
    cout << "\nSort by:\n1. Title\n2. Price\n3. Duration\n0. Back\nChoice: ";
    int c = safeChoice(0, 3);
    if (c == 0) return;

    cout << "1. Asc\n2. Desc\nChoice: ";
    bool asc = (safeChoice(1, 2) == 1);

    if (c == 1) { // title
        for (int i = 0; i < movieCount - 1; i++) {
            int mn = i;
            for (int j = i + 1; j < movieCount; j++) {
                if ((asc && movies[j].title < movies[mn].title) ||
                    (!asc && movies[j].title > movies[mn].title)) mn = j;
            }
            swap(movies[i], movies[mn]);
        }
    }
    if (c == 2) { // price
        for (int i = 0; i < movieCount - 1; i++)
            for (int j = 0; j < movieCount - i - 1; j++)
                if ((asc && movies[j].price > movies[j + 1].price) ||
                    (!asc && movies[j].price < movies[j + 1].price))
                    swap(movies[j], movies[j + 1]);
    }
    if (c == 3) { // duration
        for (int i = 1; i < movieCount; i++) {
            Movie key = movies[i];
            int j = i - 1;
            while (j >= 0 &&
                  ((asc && movies[j].duration > key.duration) ||
                   (!asc && movies[j].duration < key.duration))) {
                movies[j + 1] = movies[j];
                j--;
            }
            movies[j + 1] = key;
        }
    }
    cout << "Movies sorted.\n";
}

// --------- USER MENU ----------
void CinemaSystem::userMenu(const string &user) {
    while (true) {
        cout << "\n--- USER MENU (" << user << ") ---\n";
        cout << "1. View movies\n2. Book ticket\n3. Cancel ticket\n4. View my tickets\n";
        cout << "5. Search movie\n6. Sort movies\n0. Logout\nChoice: ";

        int c = safeChoice(0, 6);
        if (c == 0) return;
        if (c == 1) showMovies();
        else if (c == 2) bookTicket(user);
        else if (c == 3) cancelTicket(user);
        else if (c == 4) showMyTickets(user);
        else if (c == 5) {
            cout << "Enter title: ";
            string t; cin >> t;
            int i = searchMovie(t);
            if (i == -1) cout << "Not found.\n";
            else movies[i].display();
        }
        else if (c == 6) runSortMenu();
    }
}

// --------- ADD MOVIE (ADMIN) ----------
void CinemaSystem::addMovie() {
    Movie m;
    cout << "\n--- ADD NEW MOVIE ---\n";
    while (true) {
        cout << "Movie ID: ";
        m.id = safeInt();
        if (movieIdExists(m.id)) cout << "ID already exists!\n";
        else break;
    }

    cout << "Title: "; cin >> m.title;
    cout << "Genre: "; cin >> m.genre;
    cout << "Duration: "; m.duration = safeInt();
    cout << "Price: RM "; cin >> m.price;

    for (int i = 0; i < 10; i++) m.seats[i] = false;
    movies[movieCount++] = m;
    saveNewMovie(m);
    cout << "Movie added successfully!\n";
}

// --------- ADMIN MENU ----------
void CinemaSystem::adminMenu() {
    while (true) {
        cout << "\n--- ADMIN MENU ---\n";
        cout << "1. View movies\n2. Add movie\n3. Sort movies\n4. Search movie\n5. View all tickets\n0. Logout\nChoice: ";
        int c = safeChoice(0, 5);
        if (c == 0) return;
        if (c == 1) showMovies();
        else if (c == 2) addMovie();
        else if (c == 3) runSortMenu();
        else if (c == 4) {
            cout << "Title: ";
            string t; cin >> t;
            int i = searchMovie(t);
            if (i == -1) cout << "Not found.\n";
            else movies[i].display();
        }
        else if (c == 5) {
            double totalPrice = 0.0;
            cout << "\n--- ALL TICKETS ---\n";
            for (int i = 0; i < ticketCount; i++) {
                tickets[i].display();
                totalPrice += tickets[i].total;
            }
            cout << "Total price of all tickets: RM " << totalPrice << endl;
        }
    }
}
