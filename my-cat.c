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

#define BUFFER 255

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
    free(line);
    return 0;
}

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
    printf("loopin ulkopuolella\n");
    while(i <= (argc-1)){
        printf("loopin sisällä\n");
        strncpy(filename, argv[i], BUFFER);
        printf("menossa aukaisemaan %s", filename);
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
