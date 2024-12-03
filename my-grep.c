/*My-grep*/
/*Lauri Ikonen*/
/*Started 11092024*/
/*Modified 03122024*/

/*Program searches a string from a file and prints the matchin line on stdout 
if such is found. File and line lengths are unspecified*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int printLine(char *line){
    fprintf(stdout, "%s", line);
    return 0;
}

//INPUT MODE 
//searching matching lines using strstr function and go through input line by line
int searchInput(char *text){
    char *line = NULL;
    size_t len = 0;

    //instruction
    //printf("Enter data (End with ctrl + D):\n");

    while ((getline(&line, &len, stdin)) != -1 ){
        if ((strstr(line, text)) != NULL){
            printLine(line);
        }
    }
        
    free(line);
    return 0;
}

//FILE MODE 
//searching matching lines using strstr function and go through file line by line
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

//return file pointer for a opened file include opening error check
FILE * openFile(FILE *pFile, char *filename){
    if ((pFile = fopen(filename, "r")) == NULL){
        fprintf(stderr, "my-grep: cannot open file '%s'\n", filename);
        exit(1);
    }
    
    return pFile;
}

int main(int argc, char *argv[]){
    FILE *pFile = NULL;
    char *filename = NULL;
    char *text = NULL;
    int i = 2;
    
    //too few parameters
    if (argc == 1){
        fprintf(stderr, "my-grep: searchterm [file ...]\n");
        exit(1);
    }

    //saving the search term to a variable
    if ((text = malloc(sizeof(char)*(strlen(argv[1])+1))) == NULL){
        fprintf(stderr, "my-grep: malloc failed\n");
        exit(1);
    }
    strcpy(text, argv[1]);

    //console input mode
    if (argc == 2){
        searchInput(text);
    } 
    
    //file input mode
    else {
        //going through all files
        while (i <= (argc-1)){
            if ((filename = malloc(sizeof(char)*(strlen(argv[i])+1))) == NULL){
                fprintf(stderr, "my-grep: malloc failed\n");
                exit(1);
            }
            strcpy(filename, argv[i]);
            pFile = openFile(pFile, filename);
            searchFile(pFile, text);
            fclose(pFile);
            free(filename);
            i++;
        }
    }
    free(text);
    return 0;
}

