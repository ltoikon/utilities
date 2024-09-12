/*My-unzip*/
/*Lauri Ikonen*/
/*Started 11092024*/
/*Modified 11092024*/

/*Program uncompress a RLE compressed file (run length encryption). */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER 255

int uncompressFile(FILE *pFile){
    int runLength = 0;
    char bufferChar;

    /*read each 5 byte unit in a file, 
    first read 4 byte integer (how many times character is repeated) 
    and then 1 byte character */
    while ((fread(&runLength, sizeof(int), 1, pFile)) == 1 ){
        fread(&bufferChar, sizeof(char), 1, pFile);

        //printing character multiple times according rle value
        for (int i = 0; i < runLength; i++){
            printf("%c",bufferChar);
        }
    }
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
