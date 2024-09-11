/*Reverse*/
/*Lauri Ikonen*/
/*Started 11092024*/
/*Modified 11092024*/

/*Program reads a file and prints contents of the file line by line on stdout.
File and line lengths are unspecified*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>

int printLine(char *line){

    fprintf(stdout, "%s", line);

    return 0;
}

int readFile(FILE *pFile){
    char *line = NULL;
    size_t len = 0;
    __ssize_t read;

    while ((read = getline(&line, &len, pFile)) != -1 ){
        printLine(line);
    }
    printf("\n"); //line break for last read line
    free(line);
    return 0;
}

FILE * openFile(FILE *pFile, char *filename){
    if ((pFile = fopen(filename, "r")) == NULL){
        fprintf(stderr, "error: cannot open file '%s'\n", filename);
        exit(1);
    }
    
    return pFile;
}

int main(int argc, char *argv[]){
    FILE *pFile = NULL;
    char *filename = "my-cat.c";
    pFile = openFile(pFile, filename);
    readFile(pFile);
    fclose(pFile);
    return 0;
}