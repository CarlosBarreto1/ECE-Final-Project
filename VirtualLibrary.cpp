
#include <iostream>
#include <string>
#include <conio.h>

using namespace std;

// book struct to store details about each book
struct Book {
    // strings to store book information
    string title;
    string author;
    string genre;
    string ISBN;
    bool isCheckedOut; 

    // book consturctor for book information
    Book(string t, string a, string g, string i)
        : title(t), author(a), genre(g), ISBN(i), isCheckedOut(false) {}
};

// node struct for the linked list
struct Node {
    Book book;
    Node* next;

    Node(Book b) : book(b), next(nullptr) {}
};

// LibraryManager class
class LibraryManager {
private:
    Node* head; // head of the linked list

public:
    // library constructor sets head pointer to null because there are no books initially
    LibraryManager() : head(nullptr) {}

    ~LibraryManager() {
        // destructor to free memory when the object goes out of scope
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }

    //recommend book function
    //checks if the book is checked out and recommends next if it is
    void recommend_book(){
        Node* current = head; // sets current to first book in list
        bool book_recommended = false; // recommend is false because nothing is recommended yet
        
        // user interface
        cout << "\nRecommended Book: \n";
        // loop keeps going until book recommended is true
        while (!book_recommended){
            // if statement checks if book is checked out or not
            if (current->book.isCheckedOut)
            {
                current = current->next; // if checked out it goes to the next book
            }
            else // if not it prints that current books informantion
            {
                cout<< "Title: " << current->book.title << "\n";
                cout<< "Author: " << current->book.author << "\n";
                cout<< "Genre: " << current->book.genre << "\n";
                cout<< "ISBN: " << current->book.ISBN << "\n\n";
                book_recommended = true; // book has been recommended so book_recommend is true
            }
        }
    }


    // add a new book to the library takes book information as strings
    void addBook(const string& title, const string& author, const string& genre, const string& ISBN) {
        Book newBook(title, author, genre, ISBN);   // new book object with user input information
        Node* newNode = new Node(newBook);          // creating a new node that includes newBook
        newNode->next = head;                       // links the new node to the existing list
        head = newNode;                             // putting newNode as the new head of the list
        cout << "Book added successfully!\n";       // feedback to user that their book has been added
    }

    // search for books by title, author, genre, or ISBN
    void searchBook(const string& query, const string& type) {
        Node* current = head;    // sets current to the begining of the list
        bool found = false;      // nothing is found so found is false
        
        // while loop keeps going until current is null
        while (current) {
            // if statement checks for title, author, genre or isbn if current and query are the same
            if ((type == "title" && current->book.title == query) ||
                (type == "author" && current->book.author == query) ||
                (type == "genre" && current->book.genre == query) ||
                (type == "ISBN" && current->book.ISBN == query)) {
                    // if any of those are true it prints the found book information
                cout << "\nBook Found:\n"
                     << "Title: " << current->book.title << "\n"
                     << "Author: " << current->book.author << "\n"
                     << "Genre: " << current->book.genre << "\n"
                     << "ISBN: " << current->book.ISBN << "\n"
                     << "Status: " << (current->book.isCheckedOut ? "Checked Out" : "Available") << "\n";
                found = true; // book has been found so found is true
            }
            current = current->next; // go to next book and checks informatnion
        }

        // if no book is found then prints message
        if (!found) {
            cout << "No matching book found.\n";
        }
    }

    // check out a book by ISBN
    void checkOutBook(const string& ISBN) {
        Node* current = head; // sets current to beginning

        // loops while current isnt null
        while (current) {
            // checks if user input matches with book isbn
            if (current->book.ISBN == ISBN) {
                if (!current->book.isCheckedOut) {
                    current->book.isCheckedOut = true; // if book is not checked out it checks it out
                    cout << "You have checked out \"" << current->book.title << "\" successfully!\n";
                } else {
                    cout << "The book \"" << current->book.title << "\" is already checked out.\n"; // if book is checked out it prints message
                }
                return;
            }
            current = current->next; // next book is list
        }
        cout << "No book with ISBN " << ISBN << " found.\n"; // if no book with user input isbn then print message
    }

    // check in a book by ISBN
    // same as checkOutBook but printing if you can check in the book
    void checkInBook(const string& ISBN) {
        Node* current = head;

        while (current) {
            if (current->book.ISBN == ISBN) {
                if (current->book.isCheckedOut) {
                    current->book.isCheckedOut = false;
                    cout << "You have checked in \"" << current->book.title << "\" successfully!\n";
                } else {
                    cout << "The book \"" << current->book.title << "\" is not currently checked out.\n";
                }
                return;
            }
            current = current->next;
        }
        cout << "No book with ISBN " << ISBN << " found.\n";
    }

    // display all checked-out books
    void viewCheckedOutBooks() {
        Node* current = head; // sets current to first book in list
        bool found = false; // found is false because nothing is found yet

        cout << "\nChecked-Out Books:\n";
        // loop while current is not null
        while (current) {
            //if book is check out its information is printed
            if (current->book.isCheckedOut) {
                cout << "Title: " << current->book.title << "\n"
                     << "Author: " << current->book.author << "\n"
                     << "Genre: " << current->book.genre << "\n"
                     << "ISBN: " << current->book.ISBN << "\n\n";
                found = true; // book has been found
            }
            current = current->next; // next book in list
        }

        //if no books are found print message
        if (!found) {
            cout << "No books are currently checked out.\n";
        }
    }
};

// main menu function
void displayMenu() {
    cout << "\nLibrary Manager Menu:\n";
    cout << "1. Add a Book\n";
    cout << "2. Search for a Book\n";
    cout << "3. Check Out a Book\n";
    cout << "4. Check In a Book\n";
    cout << "5. View Checked-Out Books\n";
    cout << "6. Recommend Book\n";
    cout << "7. Exit\n";
}

//fuction for better output readabliaty
//asks user to press a key to continue
void press_any_key() 
{ 
    //this output prompts the user to press a key
    cout << "Press any key to continue...\n"; 
    //this function waits for a user input and continues after a key has been pressed
    getch();
}

int main() {
    LibraryManager library; //creates library variable with LibraryManager class
    int choice;//variable to store user input

    //do while loops switch case until exit option picked
    do {
        // promts user to pick one of the display options
        displayMenu();
        cout << "Enter your choice: ";
        cin >> choice; // takes user input and stores in variable
        cin.ignore(); // clear newline character from input buffer

        switch (choice) {
        case 1: {
            // case 1 adds book to library
            string title, author, genre, ISBN; //string variables for book information
            cout << "Enter the title: "; 
            getline(cin, title);
            cout << "Enter the author: ";
            getline(cin, author);
            cout << "Enter the genre: ";
            getline(cin, genre);
            cout << "Enter the ISBN: ";
            getline(cin, ISBN);
            library.addBook(title, author, genre, ISBN); // adds user inputs to addBook function
            press_any_key(); // prompts user to press a key to continue
            break;
        }
        case 2: {
            // case 2 search for book in library
            string query, type; // string variables to search different ways
            cout << "Search by (title/author/genre/ISBN): ";
            cin >> type;
            cin.ignore();
            cout << "Enter your search query: ";
            getline(cin, query);
            library.searchBook(query, type); // adds user input to searchBook function
            press_any_key(); // prompts user to press a key to continue
            break;
        }
        case 3: {
            // case 3 is for checking out books
            string ISBN;
            cout << "Enter the ISBN of the book to check out: ";
            cin >> ISBN;
            library.checkOutBook(ISBN);
            press_any_key(); // prompts user to press a key to continue
            break;
        }
        case 4: {
            // case 4 is for checking in books
            string ISBN;
            cout << "Enter the ISBN of the book to check in: ";
            cin >> ISBN;
            library.checkInBook(ISBN);
            press_any_key(); // prompts user to press a key to continue
            break;
        }
        case 5:{
            // case 5 is to see the books you have checked out
            library.viewCheckedOutBooks(); // function prints books checked out
            press_any_key(); // prompts user to press a key to continue
            break;
        }
        case 6:{
            // case 6 recommends a book
            library.recommend_book();
            press_any_key();
            break;
            
        }
        case 7:{
            // case 7 exits code
            cout << "Exiting Library Manager. Goodbye!\n";
            break;
        }
        default:
            //default case for invalid inputs
            cout << "Invalid choice. Please try again.\n";
        } 
    } while (choice != 7); //exit loop

    return 0;} //exit code