
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ACCOUNTS 1000
#define HASH_SIZE 1000

typedef struct {
    int account_number;
    char name[50];
    float balance;
} Account;

typedef struct {
    int key;
    Account* account;
} HashEntry;

typedef struct {
    HashEntry* entries;
    int size;
} HashTable;

void initialize_table(HashTable* table) {
    table->entries = (HashEntry*) malloc(sizeof(HashEntry) * HASH_SIZE);
    table->size = HASH_SIZE;
    for (int i = 0; i < table->size; i++) {
        table->entries[i].key = -1;
        table->entries[i].account = NULL;
    }
}

int hash(int key) {
    return key % HASH_SIZE;
}

void insert_account(HashTable* table, Account* account) {
    int key = hash(account->account_number);
    while (table->entries[key].account != NULL && table->entries[key].key != key) {
        key = hash(key + 1);
    }
    table->entries[key].key = key;
    table->entries[key].account = account;
}

Account* search_account(HashTable* table, int account_number) {
    int key = hash(account_number);
    while (table->entries[key].account != NULL && table->entries[key].account->account_number != account_number) {
        key = hash(key + 1);
    }
    if (table->entries[key].account == NULL) {
        return NULL;
    } else {
        return table->entries[key].account;
    }
}

void delete_account(HashTable* table, int account_number) {
    int key = hash(account_number);
    while (table->entries[key].account != NULL) {
        if (table->entries[key].account->account_number == account_number) {
            table->entries[key].key = -1;
            table->entries[key].account = NULL;
            return;
        }
        key = hash(key + 1);
    }
}

void print_account(Account* account) {
    printf("Account Number: %d\n", account->account_number);
    printf("Name: %s\n", account->name);
    printf("Balance: %.2f\n", account->balance);
}

void print_all_accounts(HashTable* table) {
    for (int i = 0; i < table->size; i++) {
        if (table->entries[i].account != NULL) {
            print_account(table->entries[i].account);
            printf("\n");
        }
    }
}

int get_account_number() {
    int account_number;
    printf("Enter account number: ");
    scanf("%d", &account_number);
    return account_number;
}

char* get_name() {
    char* name = (char*) malloc(sizeof(char) * 50);
    printf("Enter name: ");
    scanf("%s", name);
    return name;
}

float get_balance() {
    float balance;
    printf("Enter balance: ");
    scanf("%f", &balance);
    return balance;
}

Account* create_account() {
    Account* account = (Account*) malloc(sizeof(Account));
    account->account_number = get_account_number();
    strcpy(account->name, get_name());
    account->balance = get_balance();
    return account;
}

void deposit(Account* account, float amount) {
    account->balance += amount;
}

void withdraw(Account* account, float amount) {
    if (account->balance >= amount) {
        account->balance -= amount;
    } else {
        printf("Insufficient balance\n");
    }
}

void transfer(Account* source, Account* destination, float amount) {
    if (source->balance >= amount) {
        source->balance -= amount;
        destination->balance += amount;
    } else {
        printf("Insufficient balance\n");
    }
}

void menu(HashTable* table) {
    int choice;
    do {
        printf("1. Create account\n");
        printf("2. Deposit\n");
        printf("3. Withdraw\n");
        printf("4. Transfer\n");
        printf("5. Delete account\n");
        printf("6. Print all accounts\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        printf("\n");
        switch (choice) {
            case 1: {
                Account* account = create_account();
                insert_account(table, account);
                printf("Account created successfully\n");
                break;
            }
            case 2: {
                int account_number = get_account_number();
                Account* account = search_account(table, account_number);
                if (account != NULL) {
                    float amount = get_balance();
                    deposit(account, amount);
                    printf("Deposit successful\n");
                } else {
                    printf("Account not found\n");
                }
                break;
            }
            case 3: {
                int account_number = get_account_number();
                Account* account = search_account(table, account_number);
                if (account != NULL) {
                    float amount = get_balance();
                    withdraw(account, amount);
                    printf("Withdrawal successful\n");
                } else {
                    printf("Account not found\n");
                }
                break;
            }
            case 4: {
                int source_account_number = get_account_number();
                Account* source_account = search_account(table, source_account_number);
                if (source_account != NULL) {
                    int destination_account_number = get_account_number();
                    Account* destination_account = search_account(table, destination_account_number);
                    if (destination_account != NULL) {
                        float amount = get_balance();
                        transfer(source_account, destination_account, amount);
                        printf("Transfer successful\n");
                    } else {
                        printf("Destination account not found\n");
                    }
                } else {
                    printf("Source account not found\n");
                }
                break;
            }
            case 5: {
                int account_number = get_account_number();
                delete_account(table, account_number);
                printf("Account deleted successfully\n");
                break;
            }
            case 6: {
                print_all_accounts(table);
                break;
            }
            case 7: {
                printf("Exiting...\n");
                break;
            }
            default: {
                printf("Invalid choice\n");
                break;
            }
        }
        printf("\n");
    } while (choice != 7);
}

int main() {
    HashTable table;
    initialize_table(&table);
    menu(&table);
    return 0;
}
