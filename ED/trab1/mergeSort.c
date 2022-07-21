#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include<time.h>

void merge(int *vetor, int inicio, int meio, int fim);
void mergeSort(int* vetor, int inicio, int fim);


void merge(int *vetor, int inicio, int meio, int fim){
    int *temp, p1, p2, i, j, k; 
    int f1 = 0, f2 = 0;
    int tamanho = fim-inicio+1;
    p1 = inicio;
    p2 = meio+1;
    temp = (int*)malloc(tamanho * sizeof(int));
    int pos = 0;
    for(i=0; i<tamanho; i++){
        if(!f1 && !f2){
            if(vetor[p1] < vetor[p2]){
                temp[i] = vetor[p1];
                p1++;
            }
            else{
                temp[i] = vetor[p2];
                p2++;
            }
            if(p1>meio){
                f1 = 1;
            }
            if(p2>fim){
                f2 = 1;
            }
        }
        else{
            if(!f1){
                temp[i] = vetor[p1];
                p1++;
            }
            else{
                temp[i] = vetor[p2];
                p2++;
            }
        }
    }
    for(i=0, k=inicio; i<tamanho; i++, k++){
       vetor[k] = temp[i];
   }
   free(temp);
}

void mergeSort(int* vetor, int inicio, int fim){
    if(inicio<fim){
        int meio = floor((inicio+fim)/2);
        mergeSort(vetor, inicio, meio);
        mergeSort(vetor, meio+1, fim);
        merge(vetor, inicio, meio, fim);
    }
}

void clean_stdin(void)
{
    int c;
    do {
        c = getchar();
    } while (c != '\n' && c != EOF);
}


int main(int argc, char** argv){ 
    /*Modus Operandi: Dividir o vetor em dois sucessivamente e ordenando essas metadinhas
      E ficar chamando recursivamente até acabar
    */
   srand(time(NULL));
   int tamanho;
   int *vetor;
   if(strcmp(argv[1], "-n")==0){
       tamanho = atoi(argv[2]);
       printf("Aleatorio!");
       vetor = (int *)malloc(tamanho * sizeof(int));
       for(int i=0; i<tamanho; i++){
           vetor[i] = rand() % 1000;
        }
   
   }
   else{
       tamanho = atoi(argv[1]);
       vetor = (int *)malloc(tamanho * sizeof(int));
        for(int i=0; i<tamanho; i++){
            printf("Entre com um numero: \n");
            scanf("%d", &vetor[i]);
            clean_stdin(); // acontece que o c come um input..
        }
   }
   mergeSort(vetor, 0, tamanho);
   for(int i=0; i<tamanho; i++){
       printf("%d ",vetor[i]);
   }
}