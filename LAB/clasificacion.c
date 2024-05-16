#include <stdbool.h>
#include <stdio.h>

#include "estructuras.h"
#include "clasificacion.h"


// Función para clasificar una imagen de acuerdo al umbral
// entrega verdadero o falso dependiendo del caso
bool is_nearly_black(BMPImage* image, float threshold) {
    int black_pixels = 0; // Contador de pixeles negros
    int total_pixels = image->width * image->height; // Contador de pixeles en total
    float umbral = threshold*255; // El umbral entregado está entre 0 y 1, pero nuestros pixeles van desde el 0 hasta el 255

    // Recorrer todos los píxeles de la imagen
    for (int y = 0; y < image->height; y++) { // Para cada posición de los pixeles
        for (int x = 0; x < image->width; x++) {
            Pixel pixel = image->data[y * image->width + x]; // Tomaremos dicho pixel
            // Verificar si el píxel es negro
            if (pixel.r == 0  && pixel.g == 0 && pixel.b == 0) {
                black_pixels++; // En caso de ser un pixel negro, lo contamos
            }
        }
    }

    // Calcular el porcentaje de píxeles negros
    float black_percentage = (float)black_pixels / total_pixels; // Queremos el porcentaje de pixeles negros con respecto al total
    printf("el porcentaje es %f\n", black_percentage);

    // Comparar el porcentaje con el umbral
    return black_percentage >= threshold;
}