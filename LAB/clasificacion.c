#include <stdbool.h>
#include <stdio.h>

#include "estructuras.h"
#include "clasificacion.h"

bool is_nearly_black(BMPImage* image, float threshold) {
    int black_pixels = 0;
    int total_pixels = image->width * image->height;

    // Recorrer todos los píxeles de la imagen
    for (int y = 0; y < image->height; y++) {
        for (int x = 0; x < image->width; x++) {
            Pixel pixel = image->data[y * image->width + x];
            // Verificar si el píxel es negro
            if (pixel.r == 0 && pixel.g == 0 && pixel.b == 0) {
                black_pixels++;
            }
        }
    }

    // Calcular el porcentaje de píxeles negros
    float black_percentage = (float)black_pixels / total_pixels;
    printf("el porcentaje es %f\n", black_percentage);

    // Comparar el porcentaje con el umbral
    return black_percentage >= threshold;
}