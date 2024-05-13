#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "estructuras.c"

// Saturar una imagen BMP (multiplicar los componentes RGB de cada píxel por un factor)
BMPImage* saturate_bmp(BMPImage* image, float factor) {
    // Asignar memoria para la nueva imagen
    BMPImage* new_image = (BMPImage*)malloc(sizeof(BMPImage));
    if (!new_image) {
        fprintf(stderr, "Error: No se pudo asignar memoria para la nueva imagen.\n");
        return NULL;
    }
    // Copiar el ancho y alto de la imagen original
    new_image->width = image->width;
    new_image->height = image->height;
    new_image->data = (Pixel*)malloc(sizeof(Pixel) * image->width * image->height);
    if (!new_image->data) {
        fprintf(stderr, "Error: No se pudo asignar memoria para los datos de la nueva imagen.\n");
        free(new_image);
        return NULL;
    }
    // Saturar los colores de la imagen original
    for (int y = 0; y < image->height; y++) {
        for (int x = 0; x < image->width; x++) {
            Pixel pixel = image->data[y * image->width + x];
            // Multiplicar los componentes RGB de cada píxel por el factor y limitar el valor a 255
            // (si el resultado es mayor a 255, se asigna 255)
            // (se convierte el resultado a unsigned char para que el valor esté en el rango [0, 255])
            pixel.r = (pixel.r * factor > 255) ? 255 : (unsigned char)(pixel.r * factor);
            pixel.g = (pixel.g * factor > 255) ? 255 : (unsigned char)(pixel.g * factor);
            pixel.b = (pixel.b * factor > 255) ? 255 : (unsigned char)(pixel.b * factor);
            new_image->data[y * image->width + x] = pixel;
        }
    }

    return new_image;
}

// Convertir una imagen BMP a escala de grises
BMPImage* grayscale_bmp(BMPImage* image) {
    // Asignar memoria para la nueva imagen
    BMPImage* new_image = (BMPImage*)malloc(sizeof(BMPImage));
    if (!new_image) {
        fprintf(stderr, "Error: No se pudo asignar memoria para la nueva imagen.\n");
        return NULL;
    }
    // Copiar el ancho y alto de la imagen original
    new_image->width = image->width;
    new_image->height = image->height;
    new_image->data = (Pixel*)malloc(sizeof(Pixel) * image->width * image->height);
    if (!new_image->data) {
        fprintf(stderr, "Error: No se pudo asignar memoria para los datos de la nueva imagen.\n");
        free(new_image);
        return NULL;
    }
    // Convertir los colores de la imagen original a escala de grises
    for (int y = 0; y < image->height; y++) {
        for (int x = 0; x < image->width; x++) {
            Pixel pixel = image->data[y * image->width + x];
            // Se altera el valor de cada componente RGB aplicandole un factor
            // Pixel = (R∗0.3) (G∗0.59) (B∗0.11)
            // (se convierte el resultado a unsigned char para que el valor esté en el rango [0, 255])
            pixel.r = (unsigned char)(pixel.r * 0.3);
            pixel.g = (unsigned char)(pixel.g * 0.59);
            pixel.b = (unsigned char)(pixel.b * 0.11);
            new_image->data[y * image->width + x] = pixel;
        }
    }
    return new_image;
}

// Binarizar una imagen BMP (convertir a blanco y negro)
BMPImage* binary_bmp(BMPImage* image) {
    // Asignar memoria para la nueva imagen
    BMPImage *new_image = (BMPImage *) malloc(sizeof(BMPImage));
    if (!new_image) {
        fprintf(stderr, "Error: No se pudo asignar memoria para la nueva imagen.\n");
        return NULL;
    }
    // Copiar el ancho y alto de la imagen original
    new_image->width = image->width;
    new_image->height = image->height;
    new_image->data = (Pixel *) malloc(sizeof(Pixel) * image->width * image->height);
    if (!new_image->data) {
        fprintf(stderr, "Error: No se pudo asignar memoria para los datos de la nueva imagen.\n");
        free(new_image);
        return NULL;
    }
    // Convertir los pixeles de la imagen a binario
    for (int y = 0; y < image->height; y++) {
        for (int x = 0; x < image->width; x++) {
            Pixel pixel = image->data[y * image->width + x];
            // Convertir a escala de grises
            unsigned char gray = (unsigned char) (pixel.r * 0.3 + pixel.g * 0.59 + pixel.b * 0.11);

            // Establecer un umbral, por ejemplo 128
            unsigned char threshold = 128;

            // Si el valor del píxel es mayor que el umbral, se convierte en blanco (255), de lo contrario, se convierte en negro (0)
            if (gray > threshold) {
                pixel.r = 255;
                pixel.g = 255;
                pixel.b = 255;
            } else {
                pixel.r = 0;
                pixel.g = 0;
                pixel.b = 0;
            }

            new_image->data[y * image->width + x] = pixel;
        }
    }
    return new_image;
}
