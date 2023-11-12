#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

// para compilar -> gcc -o a memVir.c
// para executar -> ./a

static volatile int keepRunning = 1;

void intHandler(int dummy){
    keepRunning = 0;
}

int main(){

    system("ps a");

    int pid;
    printf("Informe o id do processo: ");
    scanf("%d", &pid);

    system("clear");

    printf("pid = %d\n", pid);

    char filename[1000];
    sprintf(filename, "/proc/%d/statm", pid);
    FILE *f = fopen(filename, "r");

    int vmSize;
    int vmRSS;

    signal(SIGINT, intHandler);

    while (keepRunning)
    {
        fscanf(f, "%d %d", &vmSize, &vmRSS);

        printf("Numero de paginas da memoria real: %d\n", vmRSS);
        printf("Tamanho Total memoria Virtual = %d\n", vmSize);
        printf("O tamanho das paginas virtuais: %ld\n", sysconf(_SC_PAGE_SIZE));

        printf("\n\n Pressione Cntrl+C para parar o programa \n");
        sleep(1);
        system("clear");
    }

    fclose(f);

    return 0;
    
}