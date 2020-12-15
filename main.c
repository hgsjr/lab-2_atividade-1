#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "timer.h"

/* Estou enviando a versão com as funções printf comentadas para que somente o que for necessário seja executado e assim
 * o tempo total não seja afetado */

int * mat1; //primeira matriz de entrada
int * mat2; //segunda matriz de entrada
int * saida; //matriz de saída
int dim; //dimensão das matrizes de entrada
int nthreads; //número de threads

void exibe_matriz_quadrada(int * mat, int dim, char id[]) {

    for(int k = 0; k < dim; k++)
        printf("-");
    printf(" Matriz %s ", id);
    for(int l = 0; l < dim; l++)
        printf("-");
    printf("\n");

    printf("/ ");
    for(int i = 0; i < dim; i++) {
        if(i != 0 && i != dim - 1)
            printf("| ");
        if(i == dim - 1)
            printf("\\ ");
        for(int j = 0; j < dim; j++) {
            printf("%.d ", mat[i * (dim) + j]);
        }
        if(i == 0)
            printf("\\\n");
        else {
            if(i != dim - 1)
                printf("|\n");
            else
                printf("/\n");
        }
    }
}

//função que as threads executarão
void * tarefa(void * arg) {

    int id = (int *) arg;
    //printf("\n\nThread %d começou a executar.\n\n", id + 1);
    for(int i = id; i < dim; i+= nthreads) { //controle das linhas que serão calculadas
        for(int j = 0; j < dim; j++) { //controle da coluna usada no momento
            for(int k = 0; k < dim; k++) { //percorre os elementos da coluna
                saida[i * (dim) + j] += mat1[i * (dim) + k] * mat2[k * (dim) + j]; //faz a multiplicação
                //printf("Thread %d realizou uma operação!\n", id + 1);
            }
        }
        //printf("Thread %d terminou de processar uma linha!\n", id + 1);
    }
    pthread_exit(NULL);
}

int main(int argc, char* argv[]) {

    double inicio, fim, total; //variáveis para medir o tempo de execução

    GET_TIME(inicio);

    pthread_t *tid; //identificadores das threads no sistema

    //leitura e avaliação dos parâmetros de entrada
    if(argc < 3) {
        printf("Digite: %s <dimensão da matriz> <número de threads>\n", argv[0]);
        return 1;
    }
    dim = atoi(argv[1]);
    nthreads = atoi(argv[2]);
    if(nthreads > dim)
        nthreads = dim;

    //alocação de memória para as estruturas de dados
    mat1 = (float *) malloc(sizeof(float) * dim * dim);
    if(mat1 == NULL) {
        printf("Erro ao executar malloc();\n");
        return 2;
    }
    mat2 = (float *) malloc(sizeof(float) * dim * dim);
    if(mat2 == NULL) {
        printf("Erro ao executar malloc();\n");
        return 2;
    }
    saida = (float *) malloc(sizeof(float) * dim * dim);
    if(saida == NULL) {
        printf("Erro ao executar malloc();\n");
        return 2;
    }

    //inicialização das estruturas de dados de entrada e saída
    for(int i = 0; i < dim; i++) {
        for(int j = 0; j < dim; j++) {
            mat1[i * dim + j] = 1;
            mat2[i * dim + j] = 1;
            saida[i * dim + j] = 0;
        }
    }

    //exibição das matrizes geradas
    //exibe_matriz_quadrada(mat1, dim, "A");
    //printf("\n");
    //exibe_matriz_quadrada(mat2, dim, "B");

    //multiplicação de matrizes

    //alocação das estruturas
    tid = (pthread_t *) malloc(sizeof(pthread_t) * nthreads);
    if(tid == NULL) {
        printf("Erro ao executar malloc();");
        return 2;
    }

    //criação das threads
    for(int i = 0; i < nthreads; i++) {
        if(pthread_create(tid + i, NULL, tarefa, (void *) i)) {
            printf("Erro ao executar pthread_create();");
            return 3;
        }
    }

    //espera pelo término das threads
    for(int i = 0; i < nthreads; i ++) {
        pthread_join(*(tid + i), NULL);
    }

    GET_TIME(fim);
    total = fim - inicio;
    printf("Tempo total para multiplicar as matrizes: %lf\n", total);

    //exibição do resultado
    //printf("\n");
    //exibe_matriz_quadrada(saida, dim, "Resultante");

    //libera o espaço de memória que fora alocado antes
    free(mat1);
    free(mat2);
    free(saida);

    return 0;
}
