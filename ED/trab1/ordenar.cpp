#include<bits/stdc++.h>
using namespace std;
//GABRIEL VIEIRA DO AMARAL DRE 121069963

void quickSort(int *vetor, int inicio, int fim);
int particiona(int *vetor, int inicio, int fim);
void qs(int tamanho);
void ms(int tamanho);
void merge(int *vetor, int inicio, int meio, int fim);
void mergeSort(int* vetor, int inicio, int fim);
void bs(int tamanho);
void bubblesort(int *vetor, int tamanho); 

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
void quickSort(int *vetor, int inicio, int fim){
    int pivo; //Nome de posição de futsal kkkk
    if(inicio <= fim){
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
void qs(int tamanho){
    srand(time(NULL));
    cout << " ";
    cout << "\nQUICKSORT =)\n";
    int *vetor; 
    vetor = (int *)malloc(tamanho * sizeof(int *));
    for(int i = 0; i<tamanho; i++){
        vetor[i] = rand()%1000;
    }
    cout << "\nAntes\n";
    for(int i = 0; i<tamanho; i++){
        cout << " ";
        cout << vetor[i];
    }
    cout << "\nDepois\n";
    quickSort(vetor, 0, tamanho-1);
    for(int i = 0; i<tamanho; i++){
        cout << " ";
        cout << vetor[i];
    }
}
void ms(int tamanho){
    srand(time(NULL));
    cout << " ";
    cout << "\nMERGESORT =)\n";
    int *vetor;
    vetor = (int *)malloc(tamanho * sizeof(int));
    for(int i=0; i<tamanho; i++){
        vetor[i] = rand() % 1000;
    }
    cout << "\nAntes\n";
    for(int i = 0; i<tamanho; i++){
        cout << " ";
        cout << vetor[i];
    }
    mergeSort(vetor, 0, tamanho-1);
    cout << "\nDepois\n";
    for(int i = 0; i<tamanho; i++){
        cout << " ";
        cout << vetor[i];
    }
}
void bubblesort(int *vetor, int tamanho){
    int aux;
    for(int i = 0; i<tamanho; i++){
        for(int j=0; j<tamanho; j++){
            if(vetor[j]>vetor[i]){
                aux = vetor[i];
                vetor[i] = vetor[j];
                vetor[j] = aux;
            }
        }
    }
}
void bs(int tamanho){
    srand(time(NULL));
    cout << " ";
    cout << "\nBUBBLESORT =)\n";
    int *vetor;
    vetor = (int *)malloc(tamanho * sizeof(int));
    for(int i=0; i<tamanho; i++){
        vetor[i] = rand() % 1000;
    }
    cout << "\nAntes\n";
    for(int i = 0; i<tamanho; i++){
        cout << " ";
        cout << vetor[i];
    }
    bubblesort(vetor, tamanho);
    cout << "\nDepois\n";
    for(int i = 0; i<tamanho; i++){
        cout << " ";
        cout << vetor[i];
    }
}

int main(int argc, char** argv){
    int tamanho = atoi(argv[2]);
    if(strcmp(argv[3], "-m")==0){
        ms(tamanho);
    }
    if(strcmp(argv[3], "-q")==0){
        qs(tamanho);
    }
    if(strcmp(argv[3], "-n")==0 || argc < 3){
        bs(tamanho);
    }
}