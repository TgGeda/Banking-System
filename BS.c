Here is an implementation of a menu-driven banking system using C  

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ACCOUNTS 1000 // Maximum number of accounts
#define TABLE_SIZE 100 // Hash table size

// Structure for account information
typedef struct {
    int account_number;
    char name[50];
    float balance;
} Account;

// Structure for hash table node
typedef struct {
    int key;
    Account *account;
} Node;

// Hash function
int hash(int key) {
    return key % TABLE_SIZE;
}

// Insert account into hash table
void insert(Node *table[], Account *account) {
    int key = account->account_number;
    int index = hash(key);
    Node *node = (Node *) malloc(sizeof(Node));
    node->key = key;
    node->account = account;
    table[index] = node;
}

// Search for account in hash table
Account *search(Node *table[], int account_number) {
    int key = account_number;
    int index = hash(key);
    Node *node = table[index];
    while (node != NULL) {
        if (node->key == key) {
            return node->account;
        }
        node = node->next;
    }
    return NULL;
}

// Delete account from hash table
void delete(Node *table[], int account_number) {
    int key = account_number;
    int index = hash(key);
    Node *node = table[index];
    Node *prev = NULL;
    while (node != NULL) {
        if (node->key == key) {
            if (prev == NULL) {
                table[index] = node->next;
            } else {
                prev->next = node->next;
            }
            free(node);
            return;
        }
        prev = node;
        node = node->next;
    }
}

// Display account information
void display(Account *account) {
    printf("Account number: %d\n", account->account_number);
    printf("Name: %s\n", account->name);
    printf("Balance: %.2f\n", account->balance);
}

// Display menu options
void display_menu() {
    printf("1. Add account\n");
    printf("2. Search account\n");
    printf("3. Delete account\n");
    printf("4. Exit\n");
}

int main() {
    Node *table[TABLE_SIZE] = {NULL}; // Initialize hash table to NULL
    int choice;
    do {
        display_menu();
        printf("Enter choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1: // Add account
                if (num_accounts < MAX_ACCOUNTS) {
                    Account *account = (Account *) malloc(sizeof(Account));
                    printf("Enter account number: ");
                    scanf("%d", &account->account_number);
                    printf("Enter name: ");
                    scanf("%s", account->name);
                    printf("Enter balance: ");
                    scanf("%f", &account->balance);
                    insert(table, account);
                    printf("Account added successfully.\n");
                } else {
                    printf("Maximum number of accounts reached.\n");
                }
                break;
            case 2: // Search account
                if (num_accounts > 0) {
                    int account_number;
                    printf("Enter account number: ");
                    scanf("%d", &account_number);
                    Account *account = search(table, account_number);
                    if (account != NULL) {
                        display(account);
                    } else {
                        printf("Account not found.\n");
                    }
                } else {
                    printf("No accounts found.\n");
                }
                break;
            case 3: // Delete account
                if (num_accounts > 0) {
                    int account_number;
                    printf("Enter account number: ");
                    scanf("%d", &account_number);
                    delete(table, account_number);
                    printf("Account deleted successfully.\n");
                } else {
                    printf("No accounts found.\n");
                }
                break;
            case 4: // Exit
                printf("Exiting program.\n");
                break;
            default:
                printf("Invalid choice.\n");
                break;
        }
    } while (choice != 4);
    return 0;
}
