/*My-cat*/
/*Lauri Ikonen*/
/*Started 11092024*/
/*Modified 11092024*/

/*Program reads a file and prints contents of the file line by line on stdout.
File and line lengths are unspecified*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER 255

int printLine(char *line){

    fprintf(stdout, "%s", line);

    return 0;
}

//send text line by line to be printed by function printLine
int readFile(FILE *pFile){
    char *line = NULL;
    size_t len = 0;

    while ((getline(&line, &len, pFile)) != -1 ){
        printLine(line);
    }
    free(line);
    return 0;
}

//return file pointer for a opened file include opening error check
FILE * openFile(FILE *pFile, char *filename){
    if ((pFile = fopen(filename, "r")) == NULL){
        fprintf(stderr, "my-cat: cannot open file '%s'\n", filename);
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
        readFile(pFile);
        fclose(pFile);
        i++;
    }
    return 0;
}

/*TODO
*Comments and documentation.
*/
