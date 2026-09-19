#include <stdio.h>
#include <string.h>

void encrypt(char* message, char* key) {
    int key_len = strlen(key);
    for (int i = 0; message[i] != '\0'; i++) {
        message[i] ^= key[i % key_len];
    }
}

void decrypt(char* data, char* key) {
    int key_len = strlen(key);
    for (int i = 0; data[i] != '\0'; i++) {
        data[i] ^= key[i % key_len];
    }
}

int main() {
    char choice[10];
    char message[256];
    char filename[256];
    char key[256];
    printf("Do you want to encrypt or decrypt? ");
    fgets(choice, sizeof(choice), stdin);

    choice[strcspn(choice, "\n")] = '\0';
    if (strcmp(choice, "encrypt") == 0) {
        printf("Enter the string to encrypt: ");
        fgets(message, sizeof(message), stdin);
        message[strcspn(message, "\n")] = '\0'; // Remove newline character
        if (strlen(message) == 0) {
            printf("Error: Empty string provided for encryption.\n");
            return 1;
        }

        printf("Enter the filename to save encrypted data: ");
        fgets(filename, sizeof(filename), stdin);
        filename[strcspn(filename, "\n")] = '\0';
        if (strlen(filename) == 0 || strstr(filename, ".txt") == NULL) {
            printf("Error: Empty filename provided or incorrect file extension.\n");
            return 1;
        }

        printf("Enter the key for encryption: ");
        fgets(key, sizeof(key), stdin);
        key[strcspn(key, "\n")] = '\0';
        if (strlen(key) == 0) {
            printf("Error: Empty key provided for encryption.\n");
            return 1;
        }
        FILE* file = fopen(filename, "w");
        if (file == NULL) {
            perror("Error opening file");
            return 1;
        }

        encrypt(message, key);
        fprintf(file, "%s", message);
        fclose(file);
        }
        else if (strcmp(choice, "decrypt") == 0) {
            printf("Enter the filename to read encrypted data: ");
            fgets(filename, sizeof(filename), stdin);
            filename[strcspn(filename, "\n")] = '\0';
            if (strlen(filename) == 0 || strstr(filename, ".txt") == NULL) {
                printf("Error: Empty filename provided or incorrect file extension.\n");
                return 1;
            }

            printf("Enter the key for decryption: ");
            fgets(key, sizeof(key), stdin);
            key[strcspn(key, "\n")] = '\0';
            if (strlen(key) == 0) {
                printf("Error: Empty key provided for encryption.\n");
                return 1;
            }

            FILE* file = fopen(filename, "r");
            if (file == NULL) {
                perror("Error opening file");
                return 1;
            }

            fgets(message, sizeof(message), file);
            fclose(file);

            decrypt(message, key);
            printf("Decrypted message: %s\n", message);
        }
        else {
            printf("Invalid choice.\n");
        }

        return 0;
    }
