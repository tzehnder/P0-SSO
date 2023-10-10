// Import the header file of this module
#include "os_API.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdint.h>

char *global_disk_path = NULL;

osFile* createOsFile(const char* name, uint32_t size, uint32_t index) {
    osFile* file = (osFile*)malloc(sizeof(osFile));
    if (file == NULL) {
        // Manejar error de asignación de memoria.
        return NULL;
    }

    file->filename = strdup(name); // strdup asigna memoria y copia la cadena.
    if (file->filename == NULL) {
        // Manejar error de asignación de memoria.
        free(file);
        return NULL;
    }

    file->fileSize = size;
    file->blockIndex = index;
    return file;
}

void freeOsFile(osFile* file) {
    if (file) {
        free(file->filename);
        free(file);
    }
}

void os_mount(const char* diskname) {
    // Liberar memoria previamente asignada si es que existe
    if (global_disk_path) {
        free(global_disk_path);
        global_disk_path = NULL;
    }

    // Verificar si diskname no es NULL y si tiene contenido
    if (diskname && *diskname) {
        // Asignar memoria dinámicamente
        global_disk_path = malloc(strlen(diskname) + 1);
        if (!global_disk_path) {
            printf("Error: No se pudo asignar memoria.\n");
            return;
        }

        // Copiar la ruta del disco a la memoria asignada
        strcpy(global_disk_path, diskname);

        printf("Disco montado en la ruta: %s\n", global_disk_path);
    } else {
        printf("Error: Ruta del disco no válida.\n");
    }
}

void os_unmount() {
    if (global_disk_path) {
        free(global_disk_path);
        global_disk_path = NULL;
        printf("Disco desmontado.\n");
    } else {
        printf("No hay ningún disco montado.\n");
    }
}

int os_exits(char* path) {
  return 0;  
}

//funcion creada con la ayuda de GPT, ni idea si hay que especificarlo
void os_bitmap(int num) {
    //leemos el archivo
    FILE* disk = fopen(global_disk_path, "rb");
    if (!disk) {
        perror("Error al abrir el disco");
        return;
    }

    unsigned char block[1024];  // 1 KB por bloque
    int occupied_blocks = 0;

    // Si num es -1, imprimir todo el bitmap
    int start_block = (num == -1) ? 0 : num;
    int end_block = (num == -1) ? BITMAP_BLOCKS : num + 1;
    printf( "start_block: %d, end_block: %d\n", start_block, end_block);

    for (int i = start_block; i < end_block; i++) {
        fseek(disk, i * 1024, SEEK_SET);
        fread(block, 1, 1024, disk);

        for (int j = 0; j < 1024; j++) {
            for (int bit = 0; bit < 8; bit++) {
                printf("%d", (block[j] >> (7 - bit)) & 1);
                if ((block[j] >> (7 - bit)) & 1) {
                    occupied_blocks++;
                }
            }
        }
        printf("\n");
    }

    printf("Bloques ocupados: %d\n", occupied_blocks);
    printf("Bloques libres: %d\n", TOTAL_BLOCKS - occupied_blocks);

    fclose(disk);
}



void os_tree(){
    //leemos el archivo
    printf("os");
    FILE* disk = fopen(global_disk_path, "rb");
    if (!disk) {
        perror("Error al abrir el disco");
        return;
    }
    

    os_tree_dir(disk, 256);
    
   
    
    fclose(disk);

}