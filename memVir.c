// Equipe: Alexandre Delraso, Pedro Martins, Roberto Santos
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <math.h>

// para compilar -> gcc -o a memVir.c -lm
// para executar -> ./a

// Preparacao para o handler do comando de parada (cntrl+c)
static volatile int keepRunning = 1;

// Funcao de parada do handler (cntrl+c)
void intHandler(int dummy){
    keepRunning = 0;
}

int main(){

    // Comando para o sistema operacional listar os PIDs disponiveis
    system("ps a");

    // Recebimento do PID pelo usuario
    int pid;
    printf("Informe o id do processo: ");
    scanf("%d", &pid);

    system("clear");

    printf("pid = %d\n", pid);

    // Preparacao para abertura do arquivo proc
    char filename[1000];

    // Arquivo padrao do linux que armazena os dados referentes a memoria
    sprintf(filename, "/proc/%d/statm", pid);
    FILE *f = fopen(filename, "r");

    // Variavel que armazena o tamanho total da memoria virtual que esta sendo utilizado
    float vmSize;

    // Variavel que armazena o tamanho da memoria real que esta sendo utilizado
    float vmRSS;

    // Variavel auxiliar para calcular a quantidade de paginas
    int vmPagSize = sysconf(_SC_PAGE_SIZE) / 1024;

    // Sensor que percebe o uso do comando de parada (cntrl+c) e aplica a funcao acima
    signal(SIGINT, intHandler);

    // Enquanto nao for utilizado o comando de parada (cntrl+c) continuara a repetir a execucao
    while (keepRunning)
    {
        // le os dados do arquivo proc/[PID]/statm
        fscanf(f, "%f %f", &vmSize, &vmRSS);

        printf("Tamanho da memoria real que esta sendo usada: %.2f KB\n", vmRSS);
        printf("Numero de frames da memoria real: %d \n", (int)ceil(vmRSS/vmPagSize));
        printf("Tamanho Total memoria Virtual = %.2f KB\n", vmSize);
        printf("Numero de paginas da memoria virtual: %d \n", (int)ceil(vmSize/vmPagSize));
        printf("O tamanho das paginas virtuais: %ld B\n", sysconf(_SC_PAGE_SIZE));

        printf("\n\n Pressione Cntrl+C para parar o programa \n\n");
        // Sleep para atualizar a cada um segundo
        sleep(1);
    }

    fclose(f);

    return 0;
    
}