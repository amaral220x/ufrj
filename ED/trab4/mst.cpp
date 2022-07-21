//Gabriel Vieira do Amaral
//121069963

#include<bits/stdc++.h>
using namespace std;

struct Aresta{
    int s, d, peso;
};
typedef struct Aresta aresta;
struct Grafo{
    int v, a;
    aresta *arestas;
};
typedef struct Grafo grafo;
struct subconjunto{
    int pai, rank;
};
typedef struct subconjunto subconjunto;
grafo *criaGrafo(int v, int a);

int acha(subconjunto *sub, int i);
void uniao(subconjunto *sub, int i, int j);
void kruskal(grafo *g);
int compara(const void *a, const void *b);

grafo *criaGrafo(int v, int a){
    grafo *g;
    g = (grafo *) malloc(sizeof(grafo));
    g->arestas = (aresta *) malloc(a * sizeof(aresta));
    g->a = a;
    g->v = v;
    return g;
}
int acha(subconjunto *sub, int i){
    if(sub[i].pai == i)
        return i;
    return sub[i].pai = acha(sub, sub[i].pai);
}
void uniao(subconjunto *sub, int i, int j){
    int pi, pj;
    pi = acha(sub, i);
    pj = acha(sub, j);
    if(sub[pi].rank > sub[pj].rank)
        sub[pj].pai = pi;
    else{
        sub[pi].pai = pj;
        if(sub[pi].rank == sub[pj].rank)
            sub[pj].rank++;
    }
}
void kruskal(grafo *g){
    int i, peso, v1, v2, cont = 0;
    qsort(g->arestas, g->a, sizeof(aresta), compara);
    subconjunto *sub;
    sub = (subconjunto *) malloc(g->v * sizeof(subconjunto));
    for(i = 0; i < g->v; i++){
        sub[i].pai = i;
        sub[i].rank = 0;
    }
    for(i = 0; i < g->a; i++){
        v1 = g->arestas[i].s;
        v2 = g->arestas[i].d;
        peso = g->arestas[i].peso;
        if(acha(sub, v1) != acha(sub, v2)){
            uniao(sub, v1, v2);
            cont = cont + peso;
        }
    }
    cout << cont << endl;
}
int compara(const void *a, const void *b){
    return ((aresta *) a)->peso - ((aresta *) b)->peso;
}
int main(void){
    int a, b;
    cin >> a >> b;
    grafo *graf = criaGrafo(a, b);
    for(int i = 0; i <b; i++){
        cin >> graf->arestas[i].s >> graf->arestas[i].d >> graf->arestas[i].peso;
    }
    kruskal(graf);
}