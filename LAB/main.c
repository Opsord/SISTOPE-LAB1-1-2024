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
    char *nombre_prefijo = "rb";
    int cantidad_filtros = 3;
    float factor_saturacion = 2.0;
    float umbral_binarizacion = 0.1;
    float umbral_clasificacion = 0.5;
    char *nombre_carpeta = "imagenes test";
    char *nombre_archivo_csv = "resultados.csv";

    // Variable para getopt
    int option;
    printf("FUNCIONA\n");


    // Acá se aplican las operaciones de acuerdo a lo que sea necesario (cantidad de filtros seleccionada)

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
    // Ahora clasificación
    bool clasificacion = is_nearly_black(imagen_binaria, umbral_clasificacion);
    printf("Clasificación: %d\n", clasificacion);


    // Ahora crear el directorio con los resultados
    if (create_directory(nombre_carpeta) == 1) {
        printf("Error al crear el directorio\n");
        return 1;
    }
    // Ahora crear el archivo CSV
    if (create_csv(nombre_archivo_csv, nombre_archivo, clasificacion) == 1) {
        printf("Error al crear el archivo CSV\n");
        return 1;
    }



    // Necesito hacer los casos para cada posible cantidad de filtros
    // Por defecto son 3 filtros, es decir, si no se ingresa otro valor





    return 0;
}