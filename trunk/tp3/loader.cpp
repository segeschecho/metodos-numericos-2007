#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "Matriz.h"

int main(int argc, char *argv[]){

//   	assert (argc == 4 ); //nombre del programa, archivos de entrada y salida y ruido

	char archivoEntrada[6] = "a.bmp";
	char archivoSalida[6] = "o.bmp";
	char factorRuido[2] = "r";

	FILE* pfile;
	pfile = fopen(archivoEntrada,"r");
	assert (pfile != NULL);
	printf("Archivo de Entrada: %s \n", archivoEntrada);

    char h1[16];
	char size[4];
	char bm[2];
	fscanf(pfile, "%2c", bm);
	assert(bm[0] == 'B');	// me fijo si es un bmp
	assert(bm[1] == 'M');



	fscanf(pfile, "%16c", h1);			//lo guardo para despues reconstruir el header
	fscanf(pfile, "%4c",size);
	unsigned int* ptr;				// leerlo de nuevo, me parece que basta con poner &size
	ptr = (unsigned int*) size;
	unsigned int ancho;
	ancho = *ptr;					// leerlo de nuevo, me parece que basta con poner &ancho
	                         		// fijarse en cplusplus
	char h2[32];
	fscanf(pfile, "%32c", h2);

	int offset;
	offset = ancho % 4; // calculo los bytes de basura que hay en cada fila
    	if ( offset == 4 ){
		 offset = 0;  // esto lo hago por un fallo que tiene la función % de c
	}


    Matriz<char> matriz(ancho,ancho);
    int temp;

    for (unsigned int i = 0; i < ancho; i++){
        for(unsigned int j = 0; j < ancho; j++){
            temp = fgetc(pfile);
            printf("char: %d ", temp);
            matriz.asignar(i,j,(char) temp);
            fscanf(pfile, "%*2c");
        }
     pfile += offset;
     }

	FILE* pAsalida;
	pAsalida = fopen(archivoSalida, "w+"); //crea un nuevo archivo para lectura/escritura
	assert (pAsalida != 0);

    char header[54];
    header[0] = bm[0];
    header[1] = bm[1];
    //reconstruyo el header
    for(int i = 0; i < 4; i++) header[2+i] = size[i];
    for(int i = 0; i < 16; i++) header[6+i] = h1[i];
    for(int i = 0; i < 32; i++) header[22+i] = h2[i];

	fwrite(header,1,54,pAsalida);

	fclose(pAsalida);
	fclose(pfile);

	system("PAUSE");
	return EXIT_SUCCESS;
}
