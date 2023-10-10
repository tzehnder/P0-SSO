#include <stdio.h>	// FILE, fopen, fclose, etc.
#include <stdlib.h> // malloc, calloc, free, etc
#include "../os_API/os_API.h"

int main(int argc, char const *argv[])
{
	/* El siguiente código es un ejemplo de lo que puede 
	contener un archivo main.c

	os_mount(argv[1]); 
	osFile* file_desc = os_open("/test.txt", 'w');
	os_write(file_desc, f); 
	os_close(file_desc); 
	os_unmount(); 

	*/
	os_mount(argv[1]); 
	// os_tree();
	os_bitmap(0);
	os_unmount();
}