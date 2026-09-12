#include <stdio.h>
#include <string.h>

void encrypt(char *message, char *key) {
    int key_len = strlen(key);
    for (int i = 0; message[i] != '\0'; i++) {
        message[i] ^= key[i % key_len];
    }
}

void decrypt(char *data, char *key) {
    int key_len = strlen(key);
    for (int i = 0; data[i] != '\0'; i++) {
        data[i] ^= key[i % key_len];
    }
}

int main() {
    char choice[10], message[256], filename[256], key[256];
    printf("Do you want to encrypt or decrypt? ");
    scanf("%s", choice);
    
    if (strcmp(choice, "encrypt") == 0) {
        printf("Enter the string to encrypt: ");
        fgets(message, sizeof(message), stdin);
        message[strcspn(message, "\n")] = '\0'; // Remove newline character
        printf("Enter the filename to save encrypted data: ");
        scanf("%s", filename);
        printf("Enter the key for encryption: ");
        scanf("%s", key);
        
        FILE *file = fopen(filename, "w");
        if (file == NULL) {
            perror("Error opening file");
            return 1;
        }
        
        encrypt(message, key);
        fprintf(file, "%s", message);
        fclose(file);
    } else if (strcmp(choice, "decrypt") == 0) {
        printf("Enter the filename to read encrypted data: ");
        scanf("%s", filename);
        printf("Enter the key for decryption: ");
        scanf("%s", key);
        
        FILE *file = fopen(filename, "r");
        if (file == NULL) {
            perror("Error opening file");
            return 1;
        }
        
        fgets(message, sizeof(message), file);
        fclose(file);
        
        decrypt(message, key);
        printf("Decrypted message: %s\n", message);
    } else {
        printf("Invalid choice.\n");
    }
    
    return 0;
}