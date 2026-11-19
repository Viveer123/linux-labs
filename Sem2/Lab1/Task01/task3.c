
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define ABOOK_FNAME "abook"
#define NAME_LENGTH 50
#define PHONE_LENGTH 30
#define EMAIL_LENGTH 30

// ИЗМЕНЕНО: структура записи вместо iovec
typedef struct {
    char name[NAME_LENGTH];
    char phone[PHONE_LENGTH];
    char email[EMAIL_LENGTH];
} AddressEntry;

void abook_delete(void) {
    char find_buffer[NAME_LENGTH];

    printf("Name: ");

    if (fgets(find_buffer, sizeof(find_buffer), stdin) == NULL) {
        fprintf(stderr, "Input error\n");
        return;
    }

    find_buffer[strcspn(find_buffer, "\n")] = '\0';

    // ИЗМЕНЕНО: создание безопасного временного файла
    char tfile[] = "/tmp/abook-XXXXXX";

    int temp_fd = mkstemp(tfile);

    if (temp_fd == -1) {
        perror("mkstemp");
        return;
    }

    // ИЗМЕНЕНО: fdopen связывает дескриптор с буферизированным потоком
    FILE *temp = fdopen(temp_fd, "w+b");

    if (temp == NULL) {
        perror("fdopen");
        close(temp_fd);
        unlink(tfile);
        return;
    }

    // ИЗМЕНЕНО: удаляем имя временного файла,
    // но продолжаем работать с открытым потоком
    if (unlink(tfile) == -1) {
        perror("unlink");
        fclose(temp);
        return;
    }

    FILE *source = fopen(ABOOK_FNAME, "rb");

    if (source == NULL) {
        perror("Cannot open address book");
        fclose(temp);
        return;
    }

    AddressEntry entry;
    int deleted = 0;

    // ИЗМЕНЕНО: fread вместо readv
    while (fread(&entry, sizeof(AddressEntry), 1, source) == 1) {

        if (strcmp(find_buffer, entry.name) == 0) {
            printf("Delete: %s\n", entry.name);
            deleted = 1;
            continue;
        }

        // ИЗМЕНЕНО: fwrite вместо writev
        if (fwrite(&entry, sizeof(AddressEntry), 1, temp) != 1) {
            perror("Temporary file write error");
            fclose(source);
            fclose(temp);
            return;
        }
    }

    if (ferror(source)) {
        perror("Address book read error");
        fclose(source);
        fclose(temp);
        return;
    }

    fclose(source);

    if (!deleted) {
        printf("Name '%s' hasn't found\n", find_buffer);
    }

    // ИЗМЕНЕНО: fseek вместо lseek
    if (fseek(temp, 0, SEEK_SET) != 0) {
        perror("fseek");
        fclose(temp);
        return;
    }

    // ИЗМЕНЕНО: fopen с режимом wb очищает исходный файл
    FILE *destination = fopen(ABOOK_FNAME, "wb");

    if (destination == NULL) {
        perror("Cannot open address book for writing");
        fclose(temp);
        return;
    }

    // ИЗМЕНЕНО: буферизированное копирование записей
    while (fread(&entry, sizeof(AddressEntry), 1, temp) == 1) {
        if (fwrite(&entry, sizeof(AddressEntry), 1, destination) != 1) {
            perror("Cannot write to address book");
            fclose(destination);
            fclose(temp);
            return;
        }
    }

    if (ferror(temp)) {
        perror("Temporary file read error");
    }

    // ИЗМЕНЕНО: fclose вместо close
    fclose(destination);
    fclose(temp);

    if (deleted) {
        printf("Record deleted successfully!\n");
    }
}

int main(void) {
    abook_delete();
    return 0;
}
