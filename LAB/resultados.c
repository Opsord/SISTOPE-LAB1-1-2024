#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <stdbool.h>

#include "resultados.h"

// Function to create a directory
int create_directory(const char *dir) {
    if (mkdir(dir, 0777) == -1) {
        fprintf(stderr, "Error: No se pudo crear el directorio %s.\n", dir);
        return 1;
    }
    return 0;
}

// Function to create a CSV file with classification results
int create_csv(const char *filename, const char *image_name, bool classification) {
    FILE *file = fopen(filename, "a");
    if (!file) {
        fprintf(stderr, "Error: No se pudo abrir el archivo %s.\n", filename);
        return 1;
    }

    // Write the image name and its classification to the CSV file
    fprintf(file, "%s,%d\n", image_name, classification ? 1 : 0);

    fclose(file);
    return 0;
}