
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ABOOK_FNAME "abook"
#define NAME_LENGTH 50
#define PHONE_LENGTH 30
#define EMAIL_LENGTH 30

// ИЗМЕНЕНО: структура записи вместо массива iovec
typedef struct {
    char name[NAME_LENGTH];
    char phone[PHONE_LENGTH];
    char email[EMAIL_LENGTH];
} AddressEntry;

void read_string(const char *message, char *buffer, size_t size) {
    printf("%s", message);

    if (fgets(buffer, size, stdin) == NULL) {
        fprintf(stderr, "Input error\n");
        exit(1);
    }

    buffer[strcspn(buffer, "\n")] = '\0';
}

void abook_add(void) {
    AddressEntry entry = {0};

    read_string("Name: ", entry.name, NAME_LENGTH);
    read_string("Phone number: ", entry.phone, PHONE_LENGTH);
    read_string("E-mail: ", entry.email, EMAIL_LENGTH);

    // ИЗМЕНЕНО: fopen вместо open
    FILE *file = fopen(ABOOK_FNAME, "ab");

    if (file == NULL) {
        perror("Cannot open address book");
        exit(1);
    }

    // ИЗМЕНЕНО: fwrite вместо writev
    if (fwrite(&entry, sizeof(AddressEntry), 1, file) != 1) {
        perror("Cannot write to address book");
        fclose(file);
        exit(1);
    }

    // ИЗМЕНЕНО: fclose вместо close
    fclose(file);

    printf("Record added successfully!\n");
}

void abook_find(void) {
    char find_buffer[NAME_LENGTH];

    read_string("Name: ", find_buffer, NAME_LENGTH);

    // ИЗМЕНЕНО: fopen вместо open
    FILE *file = fopen(ABOOK_FNAME, "rb");

    if (file == NULL) {
        perror("Cannot open address book");
        return;
    }

    AddressEntry entry;
    int found = 0;

    // ИЗМЕНЕНО: fread вместо readv
    while (fread(&entry, sizeof(AddressEntry), 1, file) == 1) {
        if (strcmp(find_buffer, entry.name) == 0) {
            printf("Phone: %s\n", entry.phone);
            printf("E-mail: %s\n", entry.email);
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Name '%s' hasn't found\n", find_buffer);
    }

    // ИЗМЕНЕНО: fclose вместо close
    fclose(file);
}

int main(int argc, char **argv) {
    if (argc < 2) {
        fprintf(stderr, "Too few arguments\n");
        fprintf(stderr, "Usage: ./task2 { add | find }\n");
        return 1;
    }

    if (strcmp(argv[1], "add") == 0) {
        abook_add();
    }
    else if (strcmp(argv[1], "find") == 0) {
        abook_find();
    }
    else {
        fprintf(stderr, "%s: unknown command\n", argv[1]);
        fprintf(stderr, "Usage: ./task2 { add | find }\n");
        return 1;
    }

    return 0;
}
