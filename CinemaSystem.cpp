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
        for (char& c : r) c = tolower(c);
        return r;
    }

    void CinemaSystem::addMovieNode(Movie m) {
        MovieNode* n = new MovieNode{m, NULL};

        if (!movieHead) {
            movieHead = n;
            return;
        }

        MovieNode* curr = movieHead;
        while (curr->next)
            curr = curr->next;

        curr->next = n;
    }

    void CinemaSystem::loadMovies() {
        ifstream f("movies.txt");
        if (!f) return;

        Movie m;
        while (f >> m.id >> m.title >> m.genre >> m.duration >> m.price) {
            for (int i = 0; i < 10; i++)
                m.seats[i] = false;
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
            if (curr->data.id == id)
                return curr;
            curr = curr->next;
        }
        return NULL;
    }


    bool CinemaSystem::movieIdExists(int id) {
        return findMovieById(id) != NULL;
    }

    int CinemaSystem::searchMovie(string title) {
        title = toLower(title);
        MovieNode* curr = movieHead;
        int idx = 0;

        while (curr) {
            if (toLower(curr->data.title) == title)
                return idx;
            curr = curr->next;
            idx++;
        }
        return -1;
    }

    void CinemaSystem::addTicket(Ticket t) {
        TicketNode* n = new TicketNode{t, NULL};

        if (!ticketHead) {
            ticketHead = n;
            return;
        }

        TicketNode* curr = ticketHead;
        while (curr->next)
            curr = curr->next;

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

        if (!found)
            cout << "No tickets found\n";
    }

    void CinemaSystem::cancelTicket(const string& user) {
        TicketNode* curr = ticketHead;
        TicketNode* prev = NULL;

        showMyTickets(user);
        cout << "Ticket ID to cancel: ";
        int id = safeInt();

        while (curr) {
            if (curr->data.ticketId == id && curr->data.username == user) {
                MovieNode* mn = findMovieById(curr->data.movieId);
                if (mn)
                    mn->data.seats[curr->data.seatNumber] = false;

                if (!prev)
                    ticketHead = curr->next;
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

        for (int i = 0; i < 10; i++)
            m.seats[i] = false;

        addMovieNode(m);
        saveNewMovie(m);
        cout << "Movie added\n";
    }

    void CinemaSystem::runSortMenu() {
        cout << "Sorting skipped (Linked List version)\n";
    }

    void CinemaSystem::userMenu(const string& user) {
        while (true) {
            cout << "\n1.View 2.Book 3.Cancel 4.MyTickets 0.Logout: ";
            int c = safeChoice(0, 4);
            if (c == 0) return;
            if (c == 1) showMovies();
            if (c == 2) bookTicket(user);
            if (c == 3) cancelTicket(user);
            if (c == 4) showMyTickets(user);
        }
    }

    void CinemaSystem::adminMenu() {
        while (true) {
            cout << "\n1.View 2.Add 0.Logout: ";
            int c = safeChoice(0, 2);
            if (c == 0) return;
            if (c == 1) showMovies();
            if (c == 2) addMovie();
        }
    }
