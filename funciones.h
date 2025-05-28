#include <stdio.h>
#include <stdbool.h>

#define MAX 5
#define MAX_RECURSOS 10
#define MAX_LETTERS 30

//funciones de utilidad
int compararStrings(const char *str1, const char *str2);
void copiarString(char *destino, const char *origen);
int buscarStringEnArray(const char *str, const char array[][MAX_LETTERS], int tamano);

//tiempo total necesario para producir
float tiempoTotalFabricacion(char nombres[MAX][MAX_LETTERS], float *tiempos_fabricacion, int *demanda);

//cantidad de recursos necesarios para producir
void cantidadRecursosProduccionProducto(char nombre[MAX_LETTERS], char recursos[MAX_RECURSOS][MAX_LETTERS], int cantidad_recursos[MAX_RECURSOS], int demanda, char recursos_unicos[MAX_RECURSOS][MAX_LETTERS], int *recursos_necesarios_total, int *num_recursos_unicos);
void cantidadRecursosProduccionTotal(char nombres[MAX][MAX_LETTERS], char recursos[MAX][MAX_RECURSOS][MAX_LETTERS], int cantidad_recursos[MAX][MAX_RECURSOS], int *demanda, int *recursos_necesarios_total);

//determinar si hay suficientes recursos para la produccion
bool SuficienteParaProduccion(char nombres[MAX][MAX_LETTERS], float *tiempos_fabricacion, int *demanda, 
                            char recursos[MAX][MAX_RECURSOS][MAX_LETTERS], int cantidad_recursos[MAX][MAX_RECURSOS], 
                            char recursos_unicos_disponibles[MAX_RECURSOS][MAX_LETTERS], int *recursos_disponibles, 
                            int num_recursos_disponibles, float tiempo_disponible_total);

//actualizar recursos disponibles cuando se agrega un nuevo producto
void actualizarRecursosDisponibles(char recursos_unicos_disponibles[MAX_RECURSOS][MAX_LETTERS], int *recursos_disponibles, int *num_recursos_disponibles, char recursos[MAX][MAX_RECURSOS][MAX_LETTERS]);

//cambiar la informacion de un producto
void cambiarInformacionProducto(char nombres[MAX][MAX_LETTERS], float *tiempos_fabricacion, int *demanda, char recursos[MAX][MAX_RECURSOS][MAX_LETTERS], int cantidad_recursos[MAX][MAX_RECURSOS], char recursos_unicos_disponibles[MAX_RECURSOS][MAX_LETTERS], int *recursos_disponibles, int *num_recursos_disponibles);

//eliminar un producto
void eliminacionProducto(char nombres[MAX][MAX_LETTERS], float *tiempos_fabricacion, int *demanda, char recursos[MAX][MAX_RECURSOS][MAX_LETTERS], int cantidad_recursos[MAX][MAX_RECURSOS]);

//funciones de ingreso
void IngresoNombreProducto(char nombres[MAX][MAX_LETTERS], int indice);
void IngresoRecursosFabricacion(char recursos[MAX][MAX_RECURSOS][MAX_LETTERS], int cantidad_recursos[MAX][MAX_RECURSOS], int indice);
void IngresoTiempoFabricacion(float *tiempos_fabricacion, int indice);
void IngresoDemandaProducto(int *demanda, int indice);
int IngresoRecursosDisponibles(char recursos_unicos_disponibles[MAX_RECURSOS][MAX_LETTERS], int *recursos_disponibles, char recursos[MAX][MAX_RECURSOS][MAX_LETTERS]);
void IngresoTiempoDisponible(int *horas, int *minutos);
