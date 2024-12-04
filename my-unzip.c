/*My-unzip*/
/*Lauri Ikonen*/
/*Started 11092024*/
/*Modified 03122024*/

/*Program uncompress a RLE compressed file (run length encryption). */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

//return file pointer for a opened file include opening error check
FILE * openFile(FILE *pFile, char *filename){
    if ((pFile = fopen(filename, "r")) == NULL){
        fprintf(stderr, "my-zip: cannot open file '%s'\n", filename);
        free(filename);
        exit(1);
    }
    
    return pFile;
}

int main(int argc, char *argv[]){
    FILE *pFile = NULL;
    char *filename = NULL;
    int i = 1;
    //going through all files
    while(i <= (argc-1)){
        if ((filename = malloc(sizeof(char)*(strlen(argv[i])+1))) == NULL){
            fprintf(stderr, "my-unzip: malloc failed\n");
            exit(1);
        }
        strcpy(filename, argv[i]);
        pFile = openFile(pFile, filename);
        uncompressFile(pFile);
        fclose(pFile);
        free(filename);
        i++;
    }


    return 0;
}
