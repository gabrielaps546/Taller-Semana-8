#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "funciones.h"
#include "lecturas.h"

#define MAX 5
#define MAX_RECURSOS 10
#define MAX_LETTERS 30

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

    // Inicializar arrays de strings
    for (int i = 0; i < MAX; i++) {
        for (int j = 0; j < MAX_LETTERS; j++) {
            nombres[i][j] = '\0';
        }
        for (int j = 0; j < MAX_RECURSOS; j++) {
            for (int k = 0; k < MAX_LETTERS; k++) {
                recursos[i][j][k] = '\0';
            }
        }
    }
    
    for (int i = 0; i < MAX_RECURSOS; i++) {
        for (int j = 0; j < MAX_LETTERS; j++) {
            recursos_unicos_disponibles[i][j] = '\0';
        }
    }

    // Ingreso inicial de datos
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
        printf("7. Actualizar recursos disponibles\n");
        printf("8. Actualizar tiempo disponible\n");
        printf("9. Salir\n");
        printf("Seleccione una opcion: ");

        while (scanf("%d", &opcion) != 1 || opcion < 0 || opcion > 9) {
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
                    
                    printf("\nVerificando si hay nuevos recursos...\n");
                    actualizarRecursosDisponibles(recursos_unicos_disponibles, recursos_disponibles, &num_recursos_disponibles, recursos);
                }
                break;
            }
            case 2:
                cambiarInformacionProducto(nombres, tiempos_fabricacion, demanda, recursos, cantidad_recursos,
                                         recursos_unicos_disponibles, recursos_disponibles, &num_recursos_disponibles);
                break;
            case 3:
                eliminacionProducto(nombres, tiempos_fabricacion, demanda, recursos, cantidad_recursos);
                break;
            case 4:
                tiempoTotalFabricacion(nombres, tiempos_fabricacion, demanda);
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
                printf("\nActualizando recursos disponibles...\n");
                num_recursos_disponibles = IngresoRecursosDisponibles(recursos_unicos_disponibles, recursos_disponibles, recursos);
                printf("Recursos disponibles actualizados.\n");
                break;
            case 8:
                printf("\nActualizando tiempo disponible...\n");
                IngresoTiempoDisponible(&horas_disponibles, &minutos_disponibles);
                tiempo_disponible_total = horas_disponibles + ((float)minutos_disponibles / 60.0);
                printf("Tiempo disponible actualizado.\n");
                break;
            case 9:
                printf("Saliendo del programa.\n");
                break;
        }
    } while (opcion != 9);

    return 0;
}
