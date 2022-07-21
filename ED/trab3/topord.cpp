//Gabriel Vieira do Amaral
//121069963

#include<bits/stdc++.h>
using namespace std;

struct Pilha{ //Pilha encadeada para os int
    int n;
    struct Pilha *no;
};
typedef struct Pilha pilha;
void empilha(pilha *p, int valor);
int desimpilha(pilha *p);
void inicia(pilha *p);
bool taVazio(pilha *p);

bool taVazio(pilha *p){
    return p->no == NULL;
}
void empilha(pilha *p, int valor){
    if(p->no == NULL){ //Pilha vazia
        pilha *novo;
        novo = (pilha *) malloc(sizeof(pilha));
        novo->no = NULL;
        novo->n = valor;
        p->no = novo;
    }
    else{
        pilha * novo, *aux;
        novo = (pilha *) malloc(sizeof(pilha));
        novo->n = valor;
        novo->no = NULL;
        aux = p->no;
        while(aux->no != NULL){
            aux = aux -> no;
        }
        aux->no = novo;
    }
}

int desimpilha(pilha *p){
    if(p->no != NULL){
        int valor;
        pilha *ult, *ant;
        ult = p->no;
        ant = p;
        while(ult->no != NULL){
            ant = ult;
            ult = ult ->no;
        }
        ant->no = NULL;
        return ult->n;
    }
    return -1;
}

void inicia(pilha *p){
    p->no = NULL;
    cout << "Pilha iniciada" << endl;
}
int nVertices(string l){
    int i = 0;
    string s = "";
    while(l[i] != ' '){
        s += l[i];
        i++;
    }
    return stoi(s);
}
void top_sort(int v, bool visitado[], int adj[][1000], pilha *p, int tamAdj[]){
    visitado[v] = true;
    for(int i=0; i<tamAdj[v]; i++){
        if(!visitado[adj[v][i]]){
            top_sort(adj[v][i], visitado, adj, p, tamAdj);
        }
    }
    empilha(p, v);
}
void topological_sort(int n, bool visitado[], int adj[][1000], pilha *p, int tamAdj[]){
    for (int i = 0; i < n; ++i) {
        if (!visitado[i])
            top_sort(i, visitado, adj, p, tamAdj);
    }
}

int main(void){
    ios_base::sync_with_stdio(false);cin.tie(NULL);
    pilha *p;
    p = (pilha * )malloc(sizeof(pilha));
    inicia(p);
    string r; 
    getline(cin, r);
    int a, b;
    printf("Entre com enter pfvr\n");
    getchar();
    a = nVertices(r);
    int g[a][1000];
    bool visitado[a];
    int tam_adj[a];
    string s[a];
    for(int i = 0; i < a; i++){
        tam_adj[i] = 0;
        visitado[i] = false;
    }
    for(int i = 0; i < a; i++){
        cout << "Arestas do vertice " << i << endl;
        getline(cin, s[i]);
    }
    for(int i = 0; i < a; i++){
        stringstream str_strm;
        str_strm << s[i];
        string temp_str;
        int temp_int;
        while(!str_strm.eof()) {
            str_strm >> temp_str; 
            if(stringstream(temp_str) >> temp_int) {
                g[i][tam_adj[i]] = temp_int;
                tam_adj[i]++;
            }
            temp_str = ""; 
        }
    }
    topological_sort(a, visitado, g, p, tam_adj);
    while(!taVazio(p)){
        cout << desimpilha(p) << " ";
    }
}