/*My-grep*/
/*Lauri Ikonen*/
/*Started 11092024*/
/*Modified 11092024*/

/*Program searches a string from a file and prints the matchin line on stdout 
if such is found. File and line lengths are unspecified*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>

#define BUFFER 255


int printLine(char *line){

    fprintf(stdout, "%s", line);

    return 0;
}

int searchInput(char *text){
    char *line = NULL;
    size_t len = 0;
    __ssize_t read;
    //printf("Enter data (End with ctrl + D):\n");

    while ((read = getline(&line, &len, stdin)) != -1 ){
        if ((strstr(line, text)) != NULL){
            printLine(line);
        }
    }
        
    free(line);
    return 0;
}

int searchFile(FILE *pFile, char *text){
    char *line = NULL;
    size_t len = 0;
    __ssize_t read;

    while ((read = getline(&line, &len, pFile)) != -1 ){
        if ((strstr(line, text)) != NULL){
            printLine(line);
        }
    }
    free(line);
    return 0;
}

FILE * openFile(FILE *pFile, char *filename){
    if ((pFile = fopen(filename, "r")) == NULL){
        fprintf(stderr, "my-grep: cannot open file '%s'\n", filename);
        exit(1);
    }
    
    return pFile;
}

int main(int argc, char *argv[]){
    FILE *pFile = NULL;
    char filename[BUFFER];
    char text[BUFFER];
    int i = 2;
    strncpy(text, argv[1], BUFFER);
    if (argc == 2){
        searchInput(text);
    }

    else {
        while (i <= (argc-1)){
            strncpy(filename, argv[i], BUFFER);
            pFile = openFile(pFile, filename);
            searchFile(pFile, text);
            fclose(pFile);
            i++;
        }
    }

    return 0;
}

/*TODO
* Comments and documentation
 */