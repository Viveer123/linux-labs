
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <errno.h>

// ИЗМЕНЕНО: размер буфера для буферизированного чтения
#define BUFFER_SIZE 4096

int main(int argc, char **argv) {
    int opt;
    char *output_name = NULL;
    char *position_str = NULL;
    char *count_str = NULL;
    int newline_flag = 0;

    const struct option long_opts[] = {
        {"help", no_argument, NULL, 'h'},
        {"output", required_argument, NULL, 'o'},
        {"position", required_argument, NULL, 'p'},
        {"count", required_argument, NULL, 'c'},
        {"newline", no_argument, NULL, 'n'},
        {NULL, 0, NULL, 0}
    };

    while ((opt = getopt_long(argc, argv, "ho:p:c:n",
                              long_opts, NULL)) != -1) {
        switch (opt) {
            case 'h':
                printf("Usage: ./task1 [OPTIONS] FILENAME\n"
                       "-h, --help\n"
                       "-o, --output FILE\n"
                       "-p, --position NUMBER\n"
                       "-c, --count NUMBER\n"
                       "-n, --newline\n");
                return 0;

            case 'o':
                output_name = optarg;
                break;

            case 'p':
                position_str = optarg;
                break;

            case 'c':
                count_str = optarg;
                break;

            case 'n':
                newline_flag = 1;
                break;

            default:
                return 1;
        }
    }

    if (count_str == NULL || optind >= argc) {
        fprintf(stderr, "Error: specify -c and input file\n");
        return 1;
    }

    // ИЗМЕНЕНО: проверяем числовые аргументы
    char *end;
    errno = 0;
    unsigned long long count = strtoull(count_str, &end, 10);

    if (errno || *end != '\0') {
        fprintf(stderr, "Invalid count\n");
        return 1;
    }

    unsigned long long position = 0;

    if (position_str != NULL) {
        errno = 0;
        position = strtoull(position_str, &end, 10);

        if (errno || *end != '\0') {
            fprintf(stderr, "Invalid position\n");
            return 1;
        }
    }

    // ИЗМЕНЕНО: fopen вместо open
    FILE *input = fopen(argv[optind], "rb");

    if (input == NULL) {
        perror("Cannot open input file");
        return 1;
    }

    // ИЗМЕНЕНО: fopen вместо open
    FILE *output = stdout;

    if (output_name != NULL) {
        output = fopen(output_name, "wb");

        if (output == NULL) {
            perror("Cannot open output file");
            fclose(input);
            return 1;
        }
    }

    // ИЗМЕНЕНО: fseek вместо lseek
    if (fseek(input, 0, SEEK_END) != 0) {
        perror("fseek");
        fclose(input);
        if (output != stdout) fclose(output);
        return 1;
    }

    long file_size = ftell(input);

    if (file_size < 0 || position > (unsigned long long)file_size) {
        fprintf(stderr, "Invalid file position\n");
        fclose(input);
        if (output != stdout) fclose(output);
        return 1;
    }

    if (fseek(input, (long)position, SEEK_SET) != 0) {
        perror("fseek");
        fclose(input);
        if (output != stdout) fclose(output);
        return 1;
    }

    // ИЗМЕНЕНО: буфер для чтения блоками вместо чтения по одному байту
    char buffer[BUFFER_SIZE];

    while (count > 0) {
        size_t chunk = count < BUFFER_SIZE ? (size_t)count : BUFFER_SIZE;

        // ИЗМЕНЕНО: fread вместо read
        size_t bytes_read = fread(buffer, 1, chunk, input);

        if (bytes_read == 0) {
            if (ferror(input)) perror("Read error");
            break;
        }

        // ИЗМЕНЕНО: fwrite вместо write
        if (fwrite(buffer, 1, bytes_read, output) != bytes_read) {
            perror("Write error");
            fclose(input);
            if (output != stdout) fclose(output);
            return 1;
        }

        count -= bytes_read;
    }

    if (newline_flag) {
        fputc('\n', output);
    }

    // ИЗМЕНЕНО: fclose вместо close
    fclose(input);

    if (output != stdout) {
        fclose(output);
    } else {
        fflush(stdout);
    }

    return 0;
}
