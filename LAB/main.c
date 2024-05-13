#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>
#include "lectura.h"
#include "filtros.h"
#include "clasificacion.h"
#include "resultados.h"


int main(int argc, char *argv[]) {
    // Variables para las opciones
    char *nombre_prefijo = NULL;
    int cantidad_filtros = 3;
    float factor_saturacion = 1.3;
    float umbral_binarizacion = 0.5;
    float umbral_clasificacion = 0.5;
    char *nombre_carpeta = NULL;
    char *nombre_archivo_csv = NULL;

    // Variable para getopt
    int option;
    printf("FUNCIONA\n");

    // Process the options
    while((option = getopt(argc, argv, "N:f:p:u:v:C:R:")) != -1){
        switch(option){
            case 'N':
                nombre_prefijo = optarg;
                break;
            case 'f':
                if(optarg != NULL) {
                    cantidad_filtros = atoi(optarg);
                    break;
                }
            case 'p':
                factor_saturacion = atof(optarg);
                break;
            case 'u':
                umbral_binarizacion = atof(optarg);
                break;
            case 'v':
                umbral_clasificacion = atof(optarg);
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

    // Primero va la lectura de la imagen
    // Necesitamos juntar el prefijo con la extensión del archivo
    char nombre_archivo[256];
    sprintf(nombre_archivo, "%s%s", nombre_prefijo, ".bmp");
    printf(nombre_archivo);
    printf("\n");
    // Ahora se llama a la lectura
    BMPImage *imagen = read_bmp(nombre_archivo);
    if (imagen == NULL) {
        printf("Error al leer la imagen\n");
        return 1;
    }
    printf("Imagen leída\n");

    // Ahora se aplican los filtros
    char output_filename[256];

    // Ahora crear el directorio con los resultados
    if (create_directory(nombre_carpeta) == 1) {
        printf("Error al crear el directorio\n");
    }

    if (cantidad_filtros  == 1){
        // Saturación
        sprintf(output_filename, "%s/%s", nombre_carpeta, "saturada.bmp");
        BMPImage *imagen_saturada = saturate_bmp(imagen, factor_saturacion);
        if (imagen_saturada == NULL) {
            printf("Error al saturar la imagen\n");
            return 1;
        }
        printf("Imagen saturada\n");
        write_bmp(output_filename, imagen_saturada);
    }
    if(cantidad_filtros == 2){
        // Saturación
        sprintf(output_filename, "%s/%s", nombre_carpeta, "saturada.bmp");
        BMPImage *imagen_saturada = saturate_bmp(imagen, factor_saturacion);
        if (imagen_saturada == NULL) {
            printf("Error al saturar la imagen\n");
            return 1;
        }
        printf("Imagen saturada\n");
        write_bmp(output_filename, imagen_saturada);

        // Escala de grises
        sprintf(output_filename, "%s/%s", nombre_carpeta, "gris.bmp");
        BMPImage *imagen_gris = grayscale_bmp(imagen);
        if (imagen_gris == NULL) {
            printf("Error al convertir a escala de grises\n");
            return 1;
        }
        printf("Imagen en escala de grises\n");
        write_bmp(output_filename, imagen_gris);
    }

    if (cantidad_filtros == 3){
        // Saturación
        sprintf(output_filename, "%s/%s", nombre_carpeta, "saturada.bmp");
        BMPImage *imagen_saturada = saturate_bmp(imagen, factor_saturacion);
        if (imagen_saturada == NULL) {
            printf("Error al saturar la imagen\n");
            return 1;
        }
        printf("Imagen saturada\n");
        write_bmp(output_filename, imagen_saturada);

        // Escala de grises
        sprintf(output_filename, "%s/%s", nombre_carpeta, "gris.bmp");
        BMPImage *imagen_gris = grayscale_bmp(imagen);
        if (imagen_gris == NULL) {
            printf("Error al convertir a escala de grises\n");
            return 1;
        }
        printf("Imagen en escala de grises\n");
        write_bmp(output_filename, imagen_gris);

        // Binarización
        sprintf(output_filename, "%s/%s", nombre_carpeta, "binaria.bmp");
        BMPImage *imagen_binaria = binary_bmp(imagen, umbral_binarizacion);
        if (imagen_binaria == NULL) {
            printf("Error al binarizar la imagen\n");
            return 1;
        }
        printf("Imagen binarizada\n");
        write_bmp(output_filename, imagen_binaria);
    }


    // Ahora clasificación - Se aplica siempre
    bool clasificacion = is_nearly_black(imagen, umbral_clasificacion);
    printf("Clasificación: %d\n", clasificacion);

    // Ahora crear el archivo CSV
    if (create_csv(nombre_archivo_csv, nombre_archivo, clasificacion) == 1) {
        printf("Error al crear el archivo CSV\n");
    }
    printf("FIN\n");






    return 0;
}