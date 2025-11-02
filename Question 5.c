#include <stdio.h>

void reverse(char str[]) {
    int length = 0;
    int i = 0, j;
    char temp;

    
    while (str[length] != '\0') {
        length++;
    }

    j = length - 1;
    while (i < j) {
        temp = str[i];
        str[i] = str[j];
        str[j] = temp;
        i++;
        j--;
    }
}

void toggleBits(char str[]) {
    int i = 0;
    while (str[i] != '\0') {
        
        str[i] = str[i] ^ (1 << 1);  
        str[i] = str[i] ^ (1 << 4);  
        i++;
    }
}


void encodeMessage(char message[]) {
    reverse(message);
    toggleBits(message);
}


void decodeMessage(char message[]) {
    toggleBits(message);
    reverse(message);
}

int main() {
    char message[200];
    int choice;
    char ch;
    int i = 0;

    while (1) {
        printf("\n===== TCS Secure Communication System =====\n");
        printf("1. Encode Message\n");
        printf("2. Decode Message\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        
        while ((ch = getchar()) != '\n' && ch != EOF);

        if (choice == 1) {
            printf("Enter message to encode: ");
            i = 0;
           
            while ((ch = getchar()) != '\n' && i < 199) {
                message[i++] = ch;
            }
            message[i] = '\0';

            encodeMessage(message);
            printf("\nEncoded message: %s\n", message);
        }

        else if (choice == 2) {
            printf("Enter message to decode: ");
            i = 0;
            while ((ch = getchar()) != '\n' && i < 199) {
                message[i++] = ch;
            }
            message[i] = '\0';

            decodeMessage(message);
            printf("\nDecoded message: %s\n", message);
        }

        else if (choice == 3) {
            printf("Exiting program... Goodbye!\n");
            break;
        }

        else {
            printf("Invalid choice! Please try again.\n");
        }
    }

    return 0;
}

