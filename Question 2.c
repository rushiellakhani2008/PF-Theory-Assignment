#include <stdio.h>

#define MAX_PRODUCTS 4
#define MAX_CART 10

struct Product {
    int code;
    int quantity;
    int price;
};


struct Customer {
    char name[50];
    char cnic[20];
};


struct CartItem {
    int code;
    int quantity;
};

void getCustomerInfo(struct Customer *c) {
    int i = 0;
    char ch;

    printf("\nEnter customer name: ");
    while ((ch = getchar()) != '\n' && ch != EOF); 
    while ((ch = getchar()) != '\n' && i < 49) {
        c->name[i++] = ch;
    }
    c->name[i] = '\0';

    printf("Enter customer CNIC: ");
    i = 0;
    while ((ch = getchar()) != '\n' && i < 19) {
        c->cnic[i++] = ch;
    }
    c->cnic[i] = '\0';
}

void displayInventory(struct Product products[], int n) {
    int i;
    printf("\n%-10s %-15s %-15s\n", "Code", "Quantity", "Price");
    for (i = 0; i < n; i++) {
        printf("%-10d %-15d %-15d\n", products[i].code, products[i].quantity, products[i].price);
    }
}

int findProduct(struct Product products[], int n, int code) {
    int i;
    for (i = 0; i < n; i++) {
        if (products[i].code == code)
            return i;
    }
    return -1;
}

void updateInventory(struct Product products[], int n, int code, int qty) {
    int index = findProduct(products, n, code);
    if (index != -1 && products[index].quantity >= qty) {
        products[index].quantity -= qty;
    } else {
        printf("\nInvalid product code or insufficient stock!\n");
    }
}

float addToCart(struct Product products[], int n, struct CartItem cart[], int *cartCount) {
    int code, qty;
    printf("\nEnter product code: ");
    scanf("%d", &code);
    printf("Enter quantity: ");
    scanf("%d", &qty);

    int index = findProduct(products, n, code);
    if (index == -1) {
        printf("Product not found!\n");
        return 0;
    }
    if (products[index].quantity < qty) {
        printf("Not enough stock available!\n");
        return 0;
    }

    updateInventory(products, n, code, qty);
    cart[*cartCount].code = code;
    cart[*cartCount].quantity = qty;
    (*cartCount)++;

    printf("Item added to cart successfully!\n");
    return products[index].price * qty;
}

float calculateTotal(struct Product products[], int n, struct CartItem cart[], int cartCount) {
    int i, j;
    float total = 0;
    for (i = 0; i < cartCount; i++) {
        for (j = 0; j < n; j++) {
            if (cart[i].code == products[j].code) {
                total += (cart[i].quantity * products[j].price);
            }
        }
    }
    return total;
}

void showInvoice(struct Customer c, float total, float discountApplied) {
    int i = 0;
    printf("\n----------- INVOICE -----------\n");
    printf("Customer Name: ");
    while (c.name[i] != '\0') {
        putchar(c.name[i++]);
    }
    printf("\nCNIC: ");
    i = 0;
    while (c.cnic[i] != '\0') {
        putchar(c.cnic[i++]);
    }
    printf("\n-------------------------------\n");
    printf("Total Bill (without discount): %.2f\n", total);
    if (discountApplied > 0)
        printf("Discounted Bill (25%% off): %.2f\n", discountApplied);
    printf("-------------------------------\n");
}

int main() {
    struct Product products[MAX_PRODUCTS] = {
        {1, 50, 100},
        {2, 10, 200},
        {3, 20, 300},
        {4, 8, 150}
    };

    struct Customer customer;
    struct CartItem cart[MAX_CART];
    int cartCount = 0;
    float total = 0, discountedTotal = 0;
    int choice;
    char promo[10];
    char ch;
    int i = 0;

    printf("=== SUPERMARKET BILLING SYSTEM ===\n");

    while (1) {
        printf("\nMenu:\n");
        printf("1. Enter Customer Information\n");
        printf("2. Display Inventory\n");
        printf("3. Add Item to Cart\n");
        printf("4. Display Total Bill\n");
        printf("5. Show Invoice\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                getCustomerInfo(&customer);
                break;

            case 2:
                displayInventory(products, MAX_PRODUCTS);
                break;

            case 3:
                total += addToCart(products, MAX_PRODUCTS, cart, &cartCount);
                break;

            case 4:
                printf("\nDo you have a promo code? (y/n): ");
                scanf(" %c", &ch);
                if (ch == 'y' || ch == 'Y') {
                    printf("Enter promo code: ");
                    i = 0;
                    while ((ch = getchar()) != '\n' && ch != EOF); 
                    while ((ch = getchar()) != '\n' && i < 9) {
                        promo[i++] = ch;
                    }
                    promo[i] = '\0';

                    
                    if (promo[0] == 'E' && promo[1] == 'i' && promo[2] == 'd' &&
                        promo[3] == '2' && promo[4] == '0' && promo[5] == '2' && promo[6] == '5' && promo[7] == '\0') {
                        discountedTotal = total * 0.75;
                        printf("\nPromo applied! 25%% discount granted.\n");
                    } else {
                        printf("\nInvalid promo code.\n");
                        discountedTotal = total;
                    }
                } else {
                    discountedTotal = total;
                }
                printf("\nTotal bill (without discount): %.2f\n", total);
                printf("Total bill (with discount if any): %.2f\n", discountedTotal);
                break;

            case 5:
                showInvoice(customer, total, discountedTotal);
                break;

            case 6:
                printf("\nExiting system... Thank you!\n");
                return 0;

            default:
                printf("Invalid choice! Try again.\n");
        }
    }
}

