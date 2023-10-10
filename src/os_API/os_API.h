// Tells the compiler to compile this file once
#include <stdint.h>
#pragma once

#define TOTAL_BLOCKS 2097152
#define BITMAP_BLOCKS 256

extern char *global_disk_path;

typedef struct {
    char* filename;       // Nombre del archivo. Usamos un puntero a char para poder asignar memoria dinámicamente.
    uint32_t fileSize;    // Tamaño del archivo. Usamos uint32_t para asegurarnos de que tenga 4 bytes sin importar la plataforma.
    uint32_t blockIndex;  // Identificador del bloque índice del archivo.
} osFile;

osFile* createOsFile(const char* name, uint32_t size, uint32_t index);

void destroyOsFile(osFile* file);

void os_unmount();

void os_mount(const char* diskname); // ocupo const porque sino arroja una advertencia, no estoy seguro si es necesario

void os_bitmap(int num);

void os_tree();