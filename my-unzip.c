/*My-unzip*/
/*Lauri Ikonen*/
/*Started 11092024*/
/*Modified 11092024*/

/*Program uncompress a RLE compressed file (run length encryption). */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>

#define BUFFER 255


int uncompressLine(char *line){

    return 0;
}

int uncompressFile(FILE *pFile){
    char *line = NULL;

    int runLength = 0;
    char bufferChar;

    while ((fread(&runLength, sizeof(int), 1, pFile)) == 1 ){
        fread(&bufferChar, sizeof(char), 1, pFile);
        for (int i = 0; i < runLength; i++){
            printf("%c",bufferChar);
        }
    }
    free(line);
    return 0;
}

FILE * openFile(FILE *pFile, char *filename){
    if ((pFile = fopen(filename, "r")) == NULL){
        fprintf(stderr, "my-zip: cannot open file '%s'\n", filename);
        exit(1);
    }
    
    return pFile;
}

int main(int argc, char *argv[]){
    FILE *pFile = NULL;
    char filename[BUFFER];
    int i = 1;
    while(i <= (argc-1)){
        strncpy(filename, argv[i], BUFFER);
        pFile = openFile(pFile, filename);
        uncompressFile(pFile);
        fclose(pFile);
        i++;
    }


    return 0;
}
