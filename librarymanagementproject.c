#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TITLE 50
#define MAX_AUTHOR 30

// --- Struct Definitions ---
typedef struct Book {
    int id;
    char title[MAX_TITLE];
    char author[MAX_AUTHOR];
    struct Book* next;
} Book;

typedef struct IssuedBook {
    int bookId;
    struct IssuedBook* next;
} IssuedBook;

typedef struct Request {
    int bookId;
    struct Request* next;
} Request;

// --- Global Pointers ---
Book* library = NULL;
IssuedBook* issuedTop = NULL;
Request* requestFront = NULL;
Request* requestRear = NULL;

// --- Functions ---
void addBook(int id, char title[], char author[]) {
    Book* newBook = (Book*)malloc(sizeof(Book));
    newBook->id = id;
    strcpy(newBook->title, title);
    strcpy(newBook->author, author);
    newBook->next = library;
    library = newBook;
    printf("✅ Book added successfully!\n");
}

void displayBooks() {
    Book* temp = library;
    if (!temp) {
        printf("📚 No books in the library.\n");
        return;
    }
    printf("📘 Books in Library:\n");
    while (temp != NULL) {
        printf("ID: %d, Title: %s, Author: %s\n", temp->id, temp->title, temp->author);
        temp = temp->next;
    }
}

void issueBook(int bookId) {
    IssuedBook* newNode = (IssuedBook*)malloc(sizeof(IssuedBook));
    newNode->bookId = bookId;
    newNode->next = issuedTop;
    issuedTop = newNode;
    printf("📦 Book with ID %d issued!\n", bookId);
}

void returnBook() {
    if (issuedTop == NULL) {
        printf("📦 No book to return.\n");
        return;
    }
    printf("📦 Book with ID %d returned!\n", issuedTop->bookId);
    IssuedBook* temp = issuedTop;
    issuedTop = issuedTop->next;
    free(temp);
}

void requestBook(int bookId) {
    Request* newReq = (Request*)malloc(sizeof(Request));
    newReq->bookId = bookId;
    newReq->next = NULL;

    if (requestRear == NULL) {
        requestFront = requestRear = newReq;
    } else {
        requestRear->next = newReq;
        requestRear = newReq;
    }
    printf("📩 Request for book ID %d added to queue.\n", bookId);
}

void processRequest() {
    if (requestFront == NULL) {
        printf("📬 No requests in queue.\n");
        return;
    }
    printf("📬 Processing request for book ID %d\n", requestFront->bookId);
    Request* temp = requestFront;
    requestFront = requestFront->next;
    if (requestFront == NULL) requestRear = NULL;
    free(temp);
}

// --- Main Menu ---
int main() {
    int choice, id;
    char title[MAX_TITLE], author[MAX_AUTHOR];

    while (1) {
        printf("\n📚--- Library Menu ---\n");
        printf("1. Add Book\n2. Display Books\n3. Issue Book\n4. Return Book\n5. Request Book\n6. Process Request\n7. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);
        getchar(); // Consume newline

        switch (choice) {
            case 1:
                printf("Enter ID: ");
                scanf("%d", &id);
                getchar();
                printf("Enter Title: ");
                fgets(title, MAX_TITLE, stdin);
                title[strcspn(title, "\n")] = 0;
                printf("Enter Author: ");
                fgets(author, MAX_AUTHOR, stdin);
                author[strcspn(author, "\n")] = 0;
                addBook(id, title, author);
                break;
            case 2:
                displayBooks();
                break;
            case 3:
                printf("Enter book ID to issue: ");
                scanf("%d", &id);
                issueBook(id);
                break;
            case 4:
                returnBook();
                break;
            case 5:
                printf("Enter book ID to request: ");
                scanf("%d", &id);
                requestBook(id);
                break;
            case 6:
                processRequest();
                break;
            case 7:
                printf("👋 Exiting Library System. Goodbye!\n");
                exit(0);
            default:
                printf("⚠️ Invalid choice!\n");
        }
    }
    return 0;
}
