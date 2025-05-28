#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "funciones.h"
#include "lecturas.h"

#define MAX 5
#define MAX_RECURSOS 10
#define MAX_LETTERS 30

//funcion para comparar dos strings
int compararStrings(const char *str1, const char *str2) {
    int i = 0;
    while (str1[i] != '\0' && str2[i] != '\0') {
        if (str1[i] != str2[i]) {
            return str1[i] - str2[i];
        }
        i++;
    }
    return str1[i] - str2[i];
}

//funcion para copiar un string a otro
void copiarString(char *destino, const char *origen) {
    int i = 0;
    while (origen[i] != '\0') {
        destino[i] = origen[i];
        i++;
    }
    destino[i] = '\0'; 
}

//funcion para buscar un string en un array de strings
int buscarStringEnArray(const char *str, const char array[][MAX_LETTERS], int tamano) {
    for(int i = 0; i < tamano; i++) {
        if(compararStrings(array[i], str) == 0) {
            return i;  // Retorna el índice donde se encontró
        }
    }
    return -1;  // Retorna -1 si no se encontró
}

//tiempo total necesario para producir
float tiempoTotalFabricacion(char nombres[MAX][MAX_LETTERS], float *tiempos_fabricacion, int *demanda){
    float tiempo_total = 0;
    float tiempo_producto = 0;
    int horas, minutos;

    printf("\n=== TIEMPO TOTAL DE FABRICACION ===\n");
    
    for(int i=0; i < MAX; i++){
        if(compararStrings(nombres[i], "") != 0) {  // Solo calcular para productos que existen
            tiempo_producto = tiempos_fabricacion[i] * demanda[i];
            tiempo_total += tiempo_producto;
            horas = (int)(tiempo_producto);
            minutos = (int)((tiempo_producto - horas) * 60);
            printf("Producto: %s\n", nombres[i]);
            printf("Tiempo total de fabricacion del producto: %d horas y %d minutos\n\n", horas, minutos);
        }
    }

    horas = (int)(tiempo_total);
    minutos = (int)((tiempo_total - horas) * 60);
    printf("TIEMPO TOTAL DE FABRICACION REQUERIDO: %d horas y %d minutos\n", horas, minutos);
    printf("======================================\n");
    return tiempo_total;
}

//cantidad de recursos necesarios para producir un producto
void cantidadRecursosProduccionProducto(char nombre[MAX_LETTERS], char recursos[MAX_RECURSOS][MAX_LETTERS], int cantidad_recursos[MAX_RECURSOS], int demanda, char recursos_unicos[MAX_RECURSOS][MAX_LETTERS], int *recursos_necesarios_total, int *num_recursos_unicos){
    int indice_recurso;
    
    for(int j = 0; j < MAX_RECURSOS; j++){ 
        if(compararStrings(recursos[j], "") != 0) {
            // Buscar si el recurso ya está en la lista de recursos únicos
            indice_recurso = buscarStringEnArray(recursos[j], recursos_unicos, *num_recursos_unicos);
            
            if(indice_recurso == -1) {
                // Si no existe, agregarlo a la lista de recursos únicos
                copiarString(recursos_unicos[*num_recursos_unicos], recursos[j]);
                recursos_necesarios_total[*num_recursos_unicos] = cantidad_recursos[j] * demanda;
                (*num_recursos_unicos)++;
            } else {
                // Si ya existe, sumar la cantidad necesaria
                recursos_necesarios_total[indice_recurso] += cantidad_recursos[j] * demanda;
            }
        }
    }
}

//cantidad de recursos necesarios para producir
void cantidadRecursosProduccionTotal(char nombres[MAX][MAX_LETTERS], char recursos[MAX][MAX_RECURSOS][MAX_LETTERS], int cantidad_recursos[MAX][MAX_RECURSOS], int *demanda, int *recursos_necesarios_total){

    char recursos_unicos[MAX_RECURSOS][MAX_LETTERS]; // Array para almacenar recursos únicos
    int num_recursos_unicos = 0;
    
    // Inicializar arrays
    for(int i = 0; i < MAX_RECURSOS; i++) {
        recursos_necesarios_total[i] = 0;
        for(int j = 0; j < MAX_LETTERS; j++) {
            recursos_unicos[i][j] = '\0';
        }
    }
    
    // Procesar cada producto
    for(int i = 0; i < MAX; i++){
        if(compararStrings(nombres[i], "") != 0) {  // Solo procesar productos que existen
            cantidadRecursosProduccionProducto(nombres[i], recursos[i], cantidad_recursos[i], demanda[i], 
                                             recursos_unicos, recursos_necesarios_total, &num_recursos_unicos);
        }
    }
    
    printf("\n=== TOTAL DE RECURSOS NECESARIOS ===\n");
    if(num_recursos_unicos == 0) {
        printf("No se encontraron recursos necesarios.\n");
    } else {
        for(int k = 0; k < num_recursos_unicos; k++){
            printf("Recurso %s: %d unidades\n", recursos_unicos[k], recursos_necesarios_total[k]);
        }
    }
    printf("=====================================\n");
}

//determinar si hay suficientes recursos para la produccion
bool SuficienteParaProduccion(char nombres[MAX][MAX_LETTERS], float *tiempos_fabricacion, int *demanda, char recursos[MAX][MAX_RECURSOS][MAX_LETTERS], int cantidad_recursos[MAX][MAX_RECURSOS], char recursos_unicos_disponibles[MAX_RECURSOS][MAX_LETTERS], int *recursos_disponibles, int num_recursos_disponibles, float tiempo_disponible_total){
    
    printf("\n=== VERIFICACION DE PRODUCCION ===\n");
    
    float tiempo_total = 0;
    float tiempo_producto = 0;
    
    // Calcular tiempo total sin mostrar detalles
    for(int i=0; i < MAX; i++){
        if(compararStrings(nombres[i], "") != 0) {
            tiempo_producto = tiempos_fabricacion[i] * demanda[i];
            tiempo_total += tiempo_producto;
        }
    }
    
    int recursos_necesarios[MAX_RECURSOS] = {0};
    char recursos_unicos[MAX_RECURSOS][MAX_LETTERS];
    int num_recursos_unicos = 0;
    
    // Inicializar array de recursos únicos
    for(int i = 0; i < MAX_RECURSOS; i++) {
        for(int j = 0; j < MAX_LETTERS; j++) {
            recursos_unicos[i][j] = '\0';
        }
    }
    
    // Calcular recursos necesarios totales
    for(int i = 0; i < MAX; i++){
        if(compararStrings(nombres[i], "") != 0) {
            cantidadRecursosProduccionProducto(nombres[i], recursos[i], cantidad_recursos[i], demanda[i], 
                                             recursos_unicos, recursos_necesarios, &num_recursos_unicos);
        }
    }
    
    // Mostrar información de tiempo
    int horas_necesarias = (int)tiempo_total;
    int minutos_necesarios = (int)((tiempo_total - horas_necesarias) * 60);
    int horas_disponibles = (int)tiempo_disponible_total;
    int minutos_disponibles_calc = (int)((tiempo_disponible_total - horas_disponibles) * 60);
    
    printf("Tiempo necesario: %d horas y %d minutos\n", horas_necesarias, minutos_necesarios);
    printf("Tiempo disponible: %d horas y %d minutos\n", horas_disponibles, minutos_disponibles_calc);
    
    // Mostrar comparación de recursos
    printf("\nComparacion de recursos:\n");
    bool recursos_suficientes = true;
    
    for(int i = 0; i < num_recursos_unicos; i++){
        // Buscar el índice del recurso en el array de recursos disponibles
        int indice_disponible = buscarStringEnArray(recursos_unicos[i], recursos_unicos_disponibles, num_recursos_disponibles);
        
        if(indice_disponible == -1){
            printf("ERROR: No se encontro el recurso '%s' en la lista de recursos disponibles\n", recursos_unicos[i]);
            recursos_suficientes = false;
        } else {
            printf("Recurso %s: Necesarios=%d, Disponibles=%d", 
                   recursos_unicos[i], recursos_necesarios[i], recursos_disponibles[indice_disponible]);
            
            if(recursos_necesarios[i] > recursos_disponibles[indice_disponible]){
                printf(" - INSUFICIENTE\n");
                recursos_suficientes = false;
            } else {
                printf(" - SUFICIENTE\n");
            }
        }
    }
    
    // Verificar tiempo
    bool tiempo_suficiente = (tiempo_total <= tiempo_disponible_total);
    if(!tiempo_suficiente) {
        printf("\nTIEMPO INSUFICIENTE: Se necesitan %.2f horas, pero solo hay %.2f horas disponibles\n", 
               tiempo_total, tiempo_disponible_total);
    }
    
    printf("===================================\n");
    
    return recursos_suficientes && tiempo_suficiente;
}

//actualizar recursos disponibles cuando se agrega un nuevo producto
void actualizarRecursosDisponibles(char recursos_unicos_disponibles[MAX_RECURSOS][MAX_LETTERS], int *recursos_disponibles, int *num_recursos_disponibles, char recursos[MAX][MAX_RECURSOS][MAX_LETTERS]){
    
    char recursos_faltantes[MAX_RECURSOS][MAX_LETTERS];
    int num_faltantes = 0;
    
    // Inicializar array de recursos faltantes
    for(int i = 0; i < MAX_RECURSOS; i++) {
        for(int j = 0; j < MAX_LETTERS; j++) {
            recursos_faltantes[i][j] = '\0';
        }
    }
    
    // Encontrar recursos que están en productos pero no en disponibles
    for(int i = 0; i < MAX; i++){
        for(int j = 0; j < MAX_RECURSOS; j++){
            if(compararStrings(recursos[i][j], "") != 0) {
                // Verificar si este recurso ya está en disponibles
                int indice_disponible = buscarStringEnArray(recursos[i][j], recursos_unicos_disponibles, *num_recursos_disponibles);
                if(indice_disponible == -1){
                    // Verificar si ya está en la lista de faltantes
                    int indice_faltante = buscarStringEnArray(recursos[i][j], recursos_faltantes, num_faltantes);
                    if(indice_faltante == -1 && num_faltantes < MAX_RECURSOS){
                        copiarString(recursos_faltantes[num_faltantes], recursos[i][j]);
                        num_faltantes++;
                    }
                }
            }
        }
    }
    
    // Si hay recursos faltantes, pedirlos al usuario
    if(num_faltantes > 0){
        printf("\nSe detectaron nuevos recursos que no estaban en la lista de disponibles:\n");
        for(int i = 0; i < num_faltantes; i++){
            if(*num_recursos_disponibles < MAX_RECURSOS) {
                printf("Recurso nuevo: %s\n", recursos_faltantes[i]);
                
                // Agregar a la lista de disponibles
                copiarString(recursos_unicos_disponibles[*num_recursos_disponibles], recursos_faltantes[i]);
                recursos_disponibles[*num_recursos_disponibles] = ReaderIntValueGreater("Ingrese la cantidad disponible: ", 0);
                (*num_recursos_disponibles)++;
            }
        }
        printf("\nRecursos disponibles actualizados.\n");
    } else {
        printf("No se detectaron nuevos recursos.\n");
    }
}

//cambiar la informacion de un producto
void cambiarInformacionProducto(char nombres[MAX][MAX_LETTERS], float *tiempos_fabricacion, int *demanda, char recursos[MAX][MAX_RECURSOS][MAX_LETTERS], int cantidad_recursos[MAX][MAX_RECURSOS], char recursos_unicos_disponibles[MAX_RECURSOS][MAX_LETTERS], int *recursos_disponibles, int *num_recursos_disponibles){
    
    char nombre_buscar[MAX_LETTERS];
    int encontrado = -1;
    int opcion;
    
    // Mostrar productos existentes
    printf("\nProductos disponibles:\n");
    bool hay_productos = false;
    for(int i = 0; i < MAX; i++){
        if(compararStrings(nombres[i], "") != 0){
            printf("- %s\n", nombres[i]);
            hay_productos = true;
        }
    }
    
    if(!hay_productos) {
        printf("No hay productos registrados.\n");
        return;
    }
    
    printf("\nIngrese el nombre del producto a editar: ");
    scanf("%s", nombre_buscar);
    
    // Buscar el producto
    for(int i = 0; i < MAX; i++){
        if(compararStrings(nombres[i], nombre_buscar) == 0){
            encontrado = i;
            break;
        }
    }
    
    if(encontrado == -1){
        printf("\nProducto no encontrado\n");
        return;
    }
    
    // Mostrar menu de opciones
    printf("\nEditando producto: %s\n", nombres[encontrado]);
    printf("Seleccione que desea modificar:\n");
    printf("1. Nombre del producto\n");
    printf("2. Tiempo de fabricacion\n");
    printf("3. Demanda del producto\n");
    printf("4. Recursos de fabricacion\n");
    printf("5. Salir\n");
    
    opcion = ReaderIntValueBetween("Ingrese su opcion: ", 1, 5);
    
    switch(opcion) {
        case 1:
            IngresoNombreProducto(nombres, encontrado);
            break;
        case 2:
            IngresoTiempoFabricacion(tiempos_fabricacion, encontrado);
            break;
        case 3:
            IngresoDemandaProducto(demanda, encontrado);
            break;
        case 4:
            IngresoRecursosFabricacion(recursos, cantidad_recursos, encontrado);
            actualizarRecursosDisponibles(recursos_unicos_disponibles, recursos_disponibles, num_recursos_disponibles, recursos);
            break;
        case 5:
            printf("\nModificacion cancelada\n");
            return;
    }
    
    printf("\nModificacion realizada exitosamente\n");
}

//eliminar un producto
void eliminacionProducto(char nombres[MAX][MAX_LETTERS], float *tiempos_fabricacion, int *demanda, char recursos[MAX][MAX_RECURSOS][MAX_LETTERS], int cantidad_recursos[MAX][MAX_RECURSOS]){
    char nombre_buscar[MAX_LETTERS];
    int encontrado = -1;
    
    // Mostrar productos existentes
    printf("\nProductos disponibles:\n");
    bool hay_productos = false;
    for(int i = 0; i < MAX; i++){
        if(compararStrings(nombres[i], "") != 0){
            printf("- %s\n", nombres[i]);
            hay_productos = true;
        }
    }
    
    if(!hay_productos) {
        printf("No hay productos registrados para eliminar.\n");
        return;
    }
    
    printf("\nIngrese el nombre del producto a eliminar: ");
    scanf("%s", nombre_buscar);
    
    // Buscar el producto
    for(int i = 0; i < MAX; i++){
        if(compararStrings(nombres[i], nombre_buscar) == 0){
            encontrado = i;
            break;
        }
    }
    
    if(encontrado == -1){
        printf("\nProducto no encontrado\n");
        return;
    }
    
    // Confirmar eliminación
    printf("\n¿Esta seguro de que desea eliminar el producto '%s'? (1=Si, 0=No): ", nombres[encontrado]);
    int confirmacion = ReaderIntValueBetween("", 0, 1);
    
    if(confirmacion == 0) {
        printf("\nEliminacion cancelada\n");
        return;
    }
    
    // Eliminar producto
    copiarString(nombres[encontrado], "");
    tiempos_fabricacion[encontrado] = 0;
    demanda[encontrado] = 0;
    for(int j = 0; j < MAX_RECURSOS; j++){
        copiarString(recursos[encontrado][j], "");
        cantidad_recursos[encontrado][j] = 0;
    }
    
    printf("\nProducto eliminado exitosamente\n");
}

//ingreso nombre del producto
void IngresoNombreProducto(char nombres[MAX][MAX_LETTERS], int indice){
    printf("Ingrese el nombre del producto: ");
    scanf("%s", nombres[indice]);
}

//ingreso recursos de fabricación del producto
void IngresoRecursosFabricacion(char recursos[MAX][MAX_RECURSOS][MAX_LETTERS], int cantidad_recursos[MAX][MAX_RECURSOS], int indice){
    int num_recursos;
    
    // Limpiar recursos existentes primero
    for(int i = 0; i < MAX_RECURSOS; i++){
        copiarString(recursos[indice][i], "");
        cantidad_recursos[indice][i] = 0;
    }
    
    num_recursos = ReaderIntValueBetween("Ingrese el numero de recursos necesarios (maximo 10): ", 1, MAX_RECURSOS);
    
    for(int i = 0; i < num_recursos; i++){
        printf("\nRecurso %d:\n", i+1);
        printf("Nombre del recurso: ");
        scanf("%s", recursos[indice][i]);
        cantidad_recursos[indice][i] = ReaderIntValueGreater("Cantidad necesaria: ", 0);
    }
}

//ingreso de tiempo de fabricación del producto
void IngresoTiempoFabricacion(float *tiempos_fabricacion, int indice){
    int horas, minutos;
    printf("Ingrese el tiempo de fabricacion:\n");
    horas = ReaderIntValueGreater("Horas: ", -1);
    minutos = ReaderIntValueBetween("Minutos (0-59): ", 0, 59);
    tiempos_fabricacion[indice] = horas + (minutos / 60.0);
}

//ingreso demanda del producto
void IngresoDemandaProducto(int *demanda, int indice){
    demanda[indice] = ReaderIntValueGreater("Ingrese la cantidad demandada: ", 0);
}

//ingreso recursos disponibles
int IngresoRecursosDisponibles(char recursos_unicos_disponibles[MAX_RECURSOS][MAX_LETTERS], int *recursos_disponibles, char recursos[MAX][MAX_RECURSOS][MAX_LETTERS]){
    int num_recursos_unicos = 0;
    
    // Inicializar arrays
    for(int i = 0; i < MAX_RECURSOS; i++){
        copiarString(recursos_unicos_disponibles[i], "");
        recursos_disponibles[i] = 0;
    }
    
    // Encontrar todos los recursos únicos utilizados en los productos
    for(int i = 0; i < MAX; i++){
        for(int j = 0; j < MAX_RECURSOS; j++){
            if(compararStrings(recursos[i][j], "") != 0 && num_recursos_unicos < MAX_RECURSOS) {
                // Verificar si este recurso ya está en la lista de únicos
                int indice_existente = buscarStringEnArray(recursos[i][j], recursos_unicos_disponibles, num_recursos_unicos);
                if(indice_existente == -1){
                    // Si no existe, agregarlo
                    copiarString(recursos_unicos_disponibles[num_recursos_unicos], recursos[i][j]);
                    num_recursos_unicos++;
                }
            }
        }
    }
    
    if(num_recursos_unicos == 0) {
        printf("\nNo se encontraron recursos en los productos registrados.\n");
        return 0;
    }
    
    // Solicitar cantidades disponibles
    printf("\nIngrese la cantidad disponible de cada recurso:\n");
    for(int i = 0; i < num_recursos_unicos; i++){
        recursos_disponibles[i] = ReaderIntValueGreater(
            (printf("Recurso %s: ", recursos_unicos_disponibles[i]), ""), 0);
    }
    
    return num_recursos_unicos;
}

//ingreso tiempo disponible de fabricacion
void IngresoTiempoDisponible(int *horas, int *minutos){
    printf("\nIngrese el tiempo disponible de fabricacion:\n");
    *horas = ReaderIntValueGreater("Horas: ", -1);
    *minutos = ReaderIntValueBetween("Minutos (0-59): ", 0, 59);
}
