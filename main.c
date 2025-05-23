#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "funciones.h"

#define MAX 5
#define MAX_RECURSOS 10
#define MAX_LETTERS 30

float tiempoTotalFabricación(char nombres[MAX][MAX_LETTERS], float *tiempos_fabricacion, int *demanda);
void cantidadRecursosProduccionTotal(char nombres[MAX][MAX_LETTERS], char recursos[MAX][MAX_RECURSOS][MAX_LETTERS], int cantidad_recursos[MAX][MAX_RECURSOS], int *demanda, int *recursos_necesarios_total);
bool SuficienteParaProduccion(char nombres[MAX][MAX_LETTERS], float *tiempos_fabricacion, int *demanda, 
                            char recursos[MAX][MAX_RECURSOS][MAX_LETTERS], int cantidad_recursos[MAX][MAX_RECURSOS], 
                            char recursos_unicos_disponibles[MAX_RECURSOS][MAX_LETTERS], int *recursos_disponibles, 
                            int num_recursos_disponibles, float tiempo_disponible_total);
void cambiarInformacionProducto(char nombres[MAX][MAX_LETTERS], float *tiempos_fabricacion, int *demanda, char recursos[MAX][MAX_RECURSOS][MAX_LETTERS], int cantidad_recursos[MAX][MAX_RECURSOS]);
void eliminacionProducto(char nombres[MAX][MAX_LETTERS], float *tiempos_fabricacion, int *demanda, char recursos[MAX][MAX_RECURSOS][MAX_LETTERS], int cantidad_recursos[MAX][MAX_RECURSOS]);
void IngresoNombreProducto(char nombre[MAX][MAX_LETTERS], int indice);
void IngresoRecursosFabricacion(char recursos[MAX][MAX_RECURSOS][MAX_LETTERS], int cantidad_recursos[MAX][MAX_RECURSOS], int indice);
void IngresoTiempoFabricacion(float *tiempos_fabricacion, int indice);
void IngresoDemandaProducto(int *demanda, int indice);
int IngresoRecursosDisponibles(char recursos_unicos_disponibles[MAX_RECURSOS][MAX_LETTERS], int *recursos_disponibles, char recursos[MAX][MAX_RECURSOS][MAX_LETTERS]);
void IngresoTiempoDisponible(int *horas, int *minutos);
int compararStrings(const char *str1, const char *str2);

int main() {
    char nombres[MAX][MAX_LETTERS] = {""};
    float tiempos_fabricacion[MAX] = {0};
    int demanda[MAX] = {0};
    char recursos[MAX][MAX_RECURSOS][MAX_LETTERS] = {""};
    int cantidad_recursos[MAX][MAX_RECURSOS] = {0};
    char recursos_unicos_disponibles[MAX_RECURSOS][MAX_LETTERS] = {""};
    int recursos_disponibles[MAX_RECURSOS] = {0}; 
    int recursos_necesarios_total[MAX_RECURSOS] = {0};
    int horas_disponibles = 0;                    
    int minutos_disponibles = 0;                 
    float tiempo_disponible_total = 0;
    int num_recursos_disponibles = 0;
    int opcion;

    for (int i = 0; i < MAX; i++) {
        printf("\n--- Ingreso de datos para producto %d ---\n", i + 1);
        IngresoNombreProducto(nombres, i);
        IngresoTiempoFabricacion(tiempos_fabricacion, i);
        IngresoDemandaProducto(demanda, i);
        IngresoRecursosFabricacion(recursos, cantidad_recursos, i);
    }

    num_recursos_disponibles = IngresoRecursosDisponibles(recursos_unicos_disponibles, recursos_disponibles, recursos);
    IngresoTiempoDisponible(&horas_disponibles, &minutos_disponibles);
    tiempo_disponible_total = horas_disponibles + ((float)minutos_disponibles / 60.0);

    do {
        printf("\n--- MENU ---\n");
        printf("1. Ingresar nuevo producto\n");
        printf("2. Editar producto\n");
        printf("3. Eliminar producto\n");
        printf("4. Mostrar tiempo total de fabricacion\n");
        printf("5. Mostrar recursos necesarios\n");
        printf("6. Verificar si se puede cumplir con la demanda\n");
        printf("7. Salir\n");
        printf("Seleccione una opcion: ");

        while (scanf("%d", &opcion) != 1 || opcion < 0 || opcion > 7) {
            printf("Ingrese una opcion valida: ");
            while (getchar() != '\n');
        }

        switch (opcion) {
            case 1: {
                int indice = -1;
                for (int i = 0; i < MAX; i++) {
                    if (compararStrings(nombres[i], "") == 0) {
                        indice = i;
                        break;
                    }
                }
                if (indice == -1) {
                    printf("No hay espacio para mas productos.\n");
                } else {
                    IngresoNombreProducto(nombres, indice);
                    IngresoTiempoFabricacion(tiempos_fabricacion, indice);
                    IngresoDemandaProducto(demanda, indice);
                    IngresoRecursosFabricacion(recursos, cantidad_recursos, indice);
                }
                break;
            }
            case 2:
                cambiarInformacionProducto(nombres, tiempos_fabricacion, demanda, recursos, cantidad_recursos);
                break;
            case 3:
                eliminacionProducto(nombres, tiempos_fabricacion, demanda, recursos, cantidad_recursos);
                break;
            case 4:
                tiempoTotalFabricación(nombres, tiempos_fabricacion, demanda);
                break;
            case 5:
                cantidadRecursosProduccionTotal(nombres, recursos, cantidad_recursos, demanda, recursos_necesarios_total);
                break;
            case 6: {
                bool puede = SuficienteParaProduccion(nombres, tiempos_fabricacion, demanda, recursos, cantidad_recursos, 
                                                    recursos_unicos_disponibles, recursos_disponibles, num_recursos_disponibles, 
                                                    tiempo_disponible_total);
                if (puede) {
                    printf("\033[1;32mLa fabrica PUEDE cumplir con la demanda.\033[0m\n");
                } else {
                    printf("\033[1;31mLa fabrica NO puede cumplir con la demanda.\033[0m\n");
                }
                break;
            }
            case 7:
                printf("Saliendo del programa.\n");
                break;
        }
    } while (opcion != 7);

    return 0;
}

