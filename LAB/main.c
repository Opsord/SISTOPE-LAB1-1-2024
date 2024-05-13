#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "lectura.h"
#include "filtros.h"


int main(int argc, char *argv[]){
    // Variables para las opciones
    char *nombre_prefijo = NULL;
    int cantidad_filtros = 0;
    float factor_saturacion = 0.0;
    int umbral_binarizacion = 0;
    int umbral_clasificacion = 0;
    char *nombre_carpeta = NULL;
    char *nombre_archivo_csv = NULL;

    // Variable para getopt
    int option;
    printf("FUNCIONA");

    // Procesar las opciones
    while((option = getopt(argc, argv, "N:f:p:u:v:C:R:")) != -1){
        switch(option){
            case 'N':
                nombre_prefijo = optarg;
                break;
            case 'f':
                cantidad_filtros = atoi(optarg);
                break;
            case 'p':
                factor_saturacion = atof(optarg);
                break;
            case 'u':
                umbral_binarizacion = atoi(optarg);
                break;
            case 'v':
                umbral_clasificacion = atoi(optarg);
                break;
            case 'C':
                nombre_carpeta = optarg;
                break;
            case 'R':
                nombre_archivo_csv = optarg;
                break;
            default:
                printf("Opción desconocida: %c\n", option);
                return 1;
        }
    }

    // Acá se aplican las operaciones de acuerdo a lo que sea necesario (cantidad de filtros seleccionada)
    //
    
    return 0;
}