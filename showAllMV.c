#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv){

    int pid;
    sscanf(argv[1], "%d", &pid);
    printf("pid = %d\n", pid);

    char filename[1000],c;
    sprintf(filename, "/proc/%d/statm", pid);
    FILE *f = fopen(filename, "r");

    c = fgetc(f); 
    while (c != EOF) 
    { 
        printf ("%c", c); 
        c = fgetc(f); 
    }

    fclose(f);

    return 0;
    
}