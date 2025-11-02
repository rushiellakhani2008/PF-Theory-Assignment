#include <stdio.h>

#define MAX_BOOKS 100


void addBook(int isbns[], char titles[][50], float prices[], int quantities[], int *count);
void processSale(int isbns[], char titles[][50], float prices[], int quantities[], int count);
void generateLowStockReport(int isbns[], char titles[][50], float prices[], int quantities[], int count);


int main() {
    int isbns[MAX_BOOKS];
    char titles[MAX_BOOKS][50];
    float prices[MAX_BOOKS];
    int quantities[MAX_BOOKS];
    int count = 0;  
    int choice;

    do {
        printf("\n=== Liberty Books Inventory System ===\n");
        printf("1. Add New Book\n");
        printf("2. Process a Sale\n");
        printf("3. Generate Low-Stock Report\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1:
                addBook(isbns, titles, prices, quantities, &count);
                break;
            case 2:
                processSale(isbns, titles, prices, quantities, count);
                break;
            case 3:
                generateLowStockReport(isbns, titles, prices, quantities, count);
                break;
            case 4:
                printf("Exiting program. Goodbye!\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }

    } while(choice != 4);

    return 0;
}




void addBook(int isbns[], char titles[][50], float prices[], int quantities[], int *count) {
    if (*count >= MAX_BOOKS) {
        printf("Inventory is full. Cannot add more books.\n");
        return;
    }

    int newIsbn, i, duplicate = 0;
    printf("Enter ISBN (integer): ");
    scanf("%d", &newIsbn);


    for (i = 0; i < *count; i++) {
        if (isbns[i] == newIsbn) {
            duplicate = 1;
            break;
        }
    }

    if (duplicate) {
        printf("A book with this ISBN already exists!\n");
        return;
    }

    isbns[*count] = newIsbn;

    printf("Enter book title (single line, no spaces if possible): ");
    scanf("%s", titles[*count]);  

    printf("Enter price: ");
    scanf("%f", &prices[*count]);

    printf("Enter quantity: ");
    scanf("%d", &quantities[*count]);

    (*count)++;

    printf("Book added successfully!\n");
}


void processSale(int isbns[], char titles[][50], float prices[], int quantities[], int count) {
    if (count == 0) {
        printf("No books in inventory.\n");
        return;
    }

    int isbn, i, found = -1, sold;
    printf("Enter ISBN to sell: ");
    scanf("%d", &isbn);


    for (i = 0; i < count; i++) {
        if (isbns[i] == isbn) {
            found = i;
            break;
        }
    }

    if (found == -1) {
        printf("Book not found!\n");
        return;
    }

    printf("Enter number of copies sold: ");
    scanf("%d", &sold);

    if (quantities[found] < sold) {
        printf("Not enough stock. Available quantity: %d\n", quantities[found]);
    } else {
        quantities[found] -= sold;
        printf("Sale processed. Remaining quantity: %d\n", quantities[found]);
    }
}


void generateLowStockReport(int isbns[], char titles[][50], float prices[], int quantities[], int count) {
    if (count == 0) {
        printf("No books in inventory.\n");
        return;
    }

    int i, lowStockFound = 0;
    printf("\n--- Low Stock Report (Quantity < 5) ---\n");

    for (i = 0; i < count; i++) {
        if (quantities[i] < 5) {
            printf("ISBN: %d | Title: %s | Price: %.2f | Quantity: %d\n",
                   isbns[i], titles[i], prices[i], quantities[i]);
            lowStockFound = 1;
        }
    }

    if (!lowStockFound) {
        printf("No low-stock books.\n");
    }
}

