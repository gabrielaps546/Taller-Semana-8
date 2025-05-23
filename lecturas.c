#include <stdio.h>
#include "lecturas.h"

int ReaderIntValueBetween(char* message, int min, int max) {
    int value;

        printf("%s", message);
        while(scanf("%d", &value) != 1 || value < min || value > max) {
            printf("Error: El valor debe estar entre %d y %d\n", min, max);
            while(getchar() != '\n');
        }
    return value;
}

int ReaderIntValueGreater(char* message, int min) {
    int value;
        printf("%s", message);
        while(scanf("%d", &value) != 1 || value <= min) {
            printf("Error: El valor debe ser mayor que %d\n", min);
            while(getchar() != '\n');
        }
    return value;
}
