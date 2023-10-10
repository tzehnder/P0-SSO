#include "os_tree.h";

void os_tree_file(FILE* disk, int index){
    unsigned char block[1024]; // 1 KB por bloque
    fseek(disk, (index ) * 1024 , SEEK_SET);
    fread(block, 1, 1024, disk);
    int* file_size_ptr = (int*)&block[0];
    int file_size = *file_size_ptr;
    printf("%d\n", file_size);
}

void os_tree_dir(FILE* disk, int index) {
    unsigned char block[1024];  // 1 KB por bloque
    fseek(disk, index * 1024 , SEEK_SET);
    fread(block, 1, 1024, disk);
    for (int i = 0; i < 32; i++){
        char dir_name[28];  // 27 caracteres + 1 para el carácter nulo
        strncpy(dir_name, (char*)&block[i*32 + 1], 27);  // Copia los siguientes 27 bytes
        dir_name[27] = '\0';  // Asegura que la cadena termine con un carácter nulo
        int type = (int)block[i*32];
        
        int* block_index_ptr = (int*)&block[i*32 + 28];
        int block_index = *block_index_ptr;

        printf("Nombre del directorio raiz: %s\n", dir_name);
        printf("Tipo: %d\n", type);
        printf("Index: %d\n", block_index);
        if (type ==  1) {
            os_tree_dir(disk, block_index);
        } else if (type == 2) {
            os_tree_file(disk, block_index);
        } 
        
    }

    return;
}