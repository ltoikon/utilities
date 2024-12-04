/*My-cat*/
/*Lauri Ikonen*/
/*Started 11092024*/
/*Modified 04122024*/

/*Program reads a file and prints contents of the file line by line on stdout.
File and line lengths are unspecified*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h> 

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
            fprintf(stderr, "my-cat: malloc failed\n");
            exit(1);
        }
        strcpy(filename, argv[i]);
        pFile = openFile(pFile, filename);
        readFile(pFile);
        fclose(pFile);
        free(filename);
        i++;
    }
    return 0;
}

