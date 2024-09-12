/*My-zip*/
/*Lauri Ikonen*/
/*Started 11092024*/
/*Modified 11092024*/

/*Program compress a file using RLE (run length encryption). */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER 255

/*write out a 4-byte integer in binary format followed by the single character in ASCII. 
Thus, a compressed file will consist of some number of 5-byte entries, 
each of which is comprised of a 4-byte integer (the run length) and the single character. */
int compressLine(char *line){
    int lineCount = 0; //position at a line
    int charCount;
    int len = strlen(line);

    while (lineCount < len){
        charCount = 1;


        /*Check how many following characters are same*/
        while(lineCount + charCount < len && line[lineCount] == line[lineCount + charCount]){
            charCount++;
        }
        fwrite(&charCount, sizeof(int), 1, stdout);
        fwrite(&line[lineCount], sizeof(char), 1, stdout);
        
        /*Move line counter forward according 'same characters' counter*/
        lineCount += charCount;
    }
    return 0;
}

//handle file reading and sends lines for compressLine function to be compressed and printed
int compressFile(FILE *pFile){
    char *line = NULL;
    size_t len = 0;

    while ((getline(&line, &len, pFile)) != -1 ){
        compressLine(line);
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
        compressFile(pFile);
        fclose(pFile);
        i++;
    }


    return 0;
}
