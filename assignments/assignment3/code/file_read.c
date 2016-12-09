// RR SJF PR_noPREMP PR_withPREMP

#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>

int main(void){
    FILE * fp;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;

    fp = fopen("/home/leavitia/Dropbox/Documentos/Ezequiel/SacState/F16/CSC139/assignments/assignment3/code/input.txt", "r");
    if (fp == NULL)
        exit(EXIT_FAILURE);

    while ((read = getline(&line, &len, fp)) != -1) {
        printf("Retrieved line of length %zu :\n", read);
        printf("%s", line);
    }

    fclose(fp);
    if (line)
        free(line);
    exit(EXIT_SUCCESS);
}
