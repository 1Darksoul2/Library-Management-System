#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// Define a structure for a book
struct Book {
    char title[100];
    char author[50];
    int book_id;
    bool available;
    struct Book *next;
};

// Global variable to keep track of the head of the book list
struct Book *head = NULL;

// Function to add a book to the library
void addBook(const char *title, const char *author, int book_id) {
    struct Book *newBook = (struct Book *)malloc(sizeof(struct Book));
    strcpy(newBook->title, title);
    strcpy(newBook->author, author);
    newBook->book_id = book_id;
    newBook->available = true;
    newBook->next = NULL;

    if (head == NULL) {
        head = newBook;
    } else {
        struct Book *temp = head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newBook;
    }
    printf("Book added successfully.\n");
}

// Function to display all books in the library
void displayBooks() {
    struct Book *temp = head;
    printf("Library Catalog:\n");
    printf("Title\t\tAuthor\t\tBook ID\t\tAvailable\n");
    while (temp != NULL) {
        printf("%s\t\t%s\t\t%d\t\t%s\n", temp->title, temp->author, temp->book_id,
               temp->available ? "Yes" : "No");
        temp = temp->next;
    }
}

// Function to search for a book by title
void searchBook(const char *title) {
    struct Book *temp = head;
    bool found = false;
    printf("Search Results:\n");
    while (temp != NULL) {
        if (strcmp(temp->title, title) == 0) {
            printf("Title: %s\n", temp->title);
            printf("Author: %s\n", temp->author);
            printf("Book ID: %d\n", temp->book_id);
            printf("Available: %s\n", temp->available ? "Yes" : "No");
            found = true;
            break;
        }
        temp = temp->next;
    }
    if (!found) {
        printf("Book not found.\n");
    }
}

// Function to borrow a book
void borrowBook(const char *title) {
    struct Book *temp = head;
    bool found = false;
    while (temp != NULL) {
        if (strcmp(temp->title, title) == 0) {
            if (temp->available) {
                temp->available = false;
                printf("Book '%s' borrowed successfully.\n", title);
            } else {
                printf("Book '%s' is not available for borrowing.\n", title);
            }
            found = true;
            break;
        }
        temp = temp->next;
    }
    if (!found) {
        printf("Book not found.\n");
    }
}

int main() {
    // Adding some initial books to the library
    addBook("Introduction to Algorithms", "Thomas H. Cormen", 101);
    addBook("The C Programming Language", "Dennis Ritchie", 102);
    addBook("Data Structures and Algorithms in C", "Mark Allen Weiss", 103);

    int choice;
    char title[100];

    do {
        printf("\nWelcome to Library \n");
        printf("1. Add a Book\n");
        printf("2. Display All Books\n");
        printf("3. Search for a Book\n");
        printf("4. Borrow a Book\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter book title: ");
                scanf(" %[^\n]s", title);
                printf("Enter author: ");
                char author[50];
                scanf(" %[^\n]s", author);
                int book_id;
                printf("Enter book ID: ");
                scanf("%d", &book_id);
                addBook(title, author, book_id);
                break;
            case 2:
                displayBooks();
                break;
            case 3:
                printf("Enter book title to search: ");
                scanf(" %[^\n]s", title);
                searchBook(title);
                break;
            case 4:
                printf("Enter book title to borrow: ");
                scanf(" %[^\n]s", title);
                borrowBook(title);
                break;
            case 5:
                printf("Exiting...\n Thank you\n");
                break;
            default:
                printf("Invalid choice. Please enter a number between 1 and 5.\n");
        }
    } while (choice != 5);

    // Free memory allocated for book nodes
    struct Book *current = head;
    struct Book *next;
    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }

    return 0;
}
