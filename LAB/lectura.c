#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "lectura.h"

    // Apertura del archivo en modo lectura binaria
    BMPImage* read_bmp(const char* filename) {
        FILE* file = fopen(filename, "rb"); // rb = read binary
        if (!file) {
            fprintf(stderr, "Error: No se pudo abrir el archivo.\n");
            return NULL;
        }

        // Lectura de la cabecera del archivo BMP
        BMPHeader header;
        if (fread(&header, sizeof(BMPHeader), 1, file) != 1) {
            fprintf(stderr, "Error: No se pudo leer la cabecera del archivo.\n");
            fclose(file);
            return NULL;
        }
        // Validación de la cabecera del archivo BMP
        if (header.type != 0x4D42) {
            fprintf(stderr, "Error: El archivo no es un BMP válido.\n");
            fclose(file);
            return NULL;
        }

        // Lectura de la información de la imagen BMP
        BMPInfoHeader info_header;
        // fread(puntero a la estructura, tamaño de la estructura, cantidad de estructuras, archivo)
        if (fread(&info_header, sizeof(BMPInfoHeader), 1, file) != 1) {
            fprintf(stderr, "Error: No se pudo leer la información de la imagen.\n");
            fclose(file);
            return NULL;
        }

        // Malloc de la estructura BMPImage
        BMPImage* image = (BMPImage*)malloc(sizeof(BMPImage));
        if (!image) {
            fprintf(stderr, "Error: No se pudo asignar memoria para la imagen.\n");
            fclose(file);
            return NULL;
        }

        // Malloc de los píxeles de la imagen
        image->width = info_header.width;
        image->height = info_header.height;
        image->data = (Pixel*)malloc(sizeof(Pixel) * image->width * image->height);
        if (!image->data) {
            fprintf(stderr, "Error: No se pudo asignar memoria para los datos de la imagen.\n");
            free(image);
            fclose(file);
            return NULL;
        }

        // SEEK_SET = inicio del archivo,
        // SEEK_CUR = posición actual del archivo
        // SEEK_END = final del archivo
        // fseek(archivo, desplazamiento, origen desde donde se desplaza)
        fseek(file, header.offset, SEEK_SET);

        // se hace padding para que la imagen tenga un tamaño múltiplo de 4, esto se hace para que la imagen sea más rápida de leer
        int padding = (4 - (info_header.width * sizeof(Pixel)) % 4) % 4; // primero se pasan a bytes los píxeles de la imagen y se calcula el residuo de la división entre 4, si el residuo es 0 no hay padding, si el residuo es 1, 2 o 3 se calcula el padding
        // Lectura de los píxeles de la imagen
        for (int y = info_header.height - 1; y >= 0; y--) {
            for (int x = 0; x < info_header.width; x++) {
                Pixel pixel;
                if (fread(&pixel, sizeof(Pixel), 1, file) != 1) {
                    fprintf(stderr, "Error: No se pudo leer los datos del pixel.\n");
                    free(image->data);
                    free(image);
                    fclose(file);
                    return NULL;
                }
                image->data[y * info_header.width + x] = pixel;
            }
            fseek(file, padding, SEEK_CUR);
        }

        fclose(file);
        return image;
    }

    // Liberación de la memoria de la imagen BMP
    void free_bmp(BMPImage* image) {
        if (image) {
            free(image->data);
            free(image);
        }
    }
