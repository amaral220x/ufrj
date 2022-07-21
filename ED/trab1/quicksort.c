#include <stdio.h>
#include <stdlib.h>

void quickSort(int *vetor, int inicio, int fim){
    int pivo; //Nome de posição de futsal kkkk
    if(inicio < fim){
        pivo = particiona(vetor, inicio, fim);
        quickSort(vetor, inicio, pivo-1);
        quickSort(vetor, pivo+1, fim);
    }
}
int particiona(int *vetor, int inicio, int fim){
    int esq, dir, pivo, aux;
    esq = inicio;
    dir = fim; 
    pivo = vetor[inicio];
    while(esq < dir){
        while(vetor[esq]<=pivo){
            esq++;
        }
        while(vetor[dir] > pivo){
            dir--;
        }
        if(esq < dir){
            aux = vetor[esq];
            vetor[esq] = vetor[dir];
            vetor[dir] = aux;
        }
    }
    vetor[inicio] = vetor[dir];
    vetor[dir] = pivo;
    return dir;
}
int main(int argc, char** argv){
    /*Modus Operandi: Dividir o vetor em dois escolhendo um pivô e sair jogando os maiores para um lado e os menores para o outro
      E ficar chamando recursivamente até acabar
    */
   int tamanho = atoi(argv[1]);
   int *vetor;
   vetor = (int *)malloc(tamanho + 1 * sizeof(int));
   for(int i=0; i<tamanho; i++){
       printf("Entre com um numero: \n");
       scanf("%d", &vetor[i]);
    }
    printf("\nAntes\n");
    for(int i=0; i<tamanho; i++){
       printf("%d ",vetor[i]);
    }
    printf("\nDepois\n");
   quickSort(vetor, 0, tamanho);
   for(int i=0; i<tamanho; i++){
       printf("%d ",vetor[i]);
   }
}



