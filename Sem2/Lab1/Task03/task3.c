#define _POSIX_C_SOURCE 199309L
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

// ИЗМЕНЕНО: добавлена функция расчёта варианта 1.
double calculate_function(double x) {
    return sin(5.0 * x + 1.0) - cos(x);
}

int main(void) {
    double x_min, x_max;
    size_t iterations;

    // ИЗМЕНЕНО: пользователь самостоятельно задаёт диапазон.
    printf("Enter minimum value of x: ");
    if (scanf("%lf", &x_min) != 1 || !isfinite(x_min)) {
        fprintf(stderr, "Invalid minimum value\n");
        return 1;
    }

    printf("Enter maximum value of x: ");
    if (scanf("%lf", &x_max) != 1 || !isfinite(x_max)) {
        fprintf(stderr, "Invalid maximum value\n");
        return 1;
    }

    // ИЗМЕНЕНО: проверка корректности диапазона.
    if (x_min >= x_max) {
        fprintf(stderr, "Error: x_min must be less than x_max\n");
        return 1;
    }

    printf("Enter number of iterations: ");
    if (scanf("%zu", &iterations) != 1 ||
        iterations < 2 || iterations > 10000000) {
        fprintf(stderr, "Iterations must be between 2 and 10000000\n");
        return 1;
    }

    // ИЗМЕНЕНО: измеряем время расчёта и записи.
    struct timespec start, end;

    if (clock_gettime(CLOCK_MONOTONIC, &start) == -1) {
        perror("clock_gettime");
        return 1;
    }

    // ИЗМЕНЕНО: создаём файл для результатов вычислений.
    FILE *file = fopen("funtion_data.txt", "w");

    if (file == NULL) {
        perror("Cannot create funtion_data.txt");
        return 1;
    }

    // ИЗМЕНЕНО: рассчитываем значения функции
    // на заданном пользователем диапазоне.
    for (size_t i = 0; i < iterations; i++) {
        double x = x_min +
            (x_max - x_min) * (double)i / (double)(iterations - 1);

        double y = calculate_function(x);

        if (fprintf(file, "%.10f %.10f\n", x, y) < 0) {
            fprintf(stderr, "Error writing data to file\n");
            fclose(file);
            return 1;
        }
    }

    // ИЗМЕНЕНО: проверяем закрытие файла.
    if (fclose(file) != 0) {
        perror("Error closing data file");
        return 1;
    }

    if (clock_gettime(CLOCK_MONOTONIC, &end) == -1) {
        perror("clock_gettime");
        return 1;
    }

    // ИЗМЕНЕНО: рассчитываем время выполнения в секундах.
    double elapsed_time =
        (end.tv_sec - start.tv_sec) +
        (end.tv_nsec - start.tv_nsec) / 1000000000.0;

    printf("\nCalculation completed successfully!\n");
    printf("Function: y = sin(5x + 1) - cos(x)\n");
    printf("X range: %.4f ... %.4f\n", x_min, x_max);
    printf("Number of iterations: %zu\n", iterations);
    printf("Data saved to funtion_data.txt\n");
    printf("Execution time: %.9f seconds\n", elapsed_time);

    return 0;
}

