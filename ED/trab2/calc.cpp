#include<bits/stdc++.h>
using namespace std;
#define MAX_STACK 1000000

float _stack[MAX_STACK]; //Pilha Dinamica mt mais facil
int tos = 0; //Topo da pilha
struct Pilha{ //Pilha encadeada para os char
    char n;
    struct Pilha *no;
};
typedef struct Pilha pilha;


//Assinaturas
void inicia(pilha *p);
char desimpilha(pilha *p);
void empilha(pilha *p, char valor);
bool isop(char c);
double calcula(string expression);
bool taVazio();
bool taCheio();
void Push(float value);

void Push(float value){
	if (taCheio()){
		return;
	}
	tos++;
	_stack[tos] = value;
}
float Pop(){
	float t = _stack[tos];
	tos--;
	return t;
}
bool taCheio(){
	return tos >= MAX_STACK - 1;
}
bool taVazio(){
	return tos == 0;
}

double calcula(string expression){
	int i = 0;
	float v1, v2, ret;
	v1 = ret = v2 = 0.0;

	string tok = "";

	while (i < expression.length()){
		while (isspace(expression[i])){
			i++;
		}
		if (isdigit(expression[i]) | expression[i] == '.'){
			while (isdigit(expression[i]) | expression[i] == '.'){
				tok += expression[i];
				i++;
			}
			Push(atof(tok.c_str()));
			tok = "";
		}
		else if (isop(expression[i])){
			if (expression[i] == '+'){
				v1 = Pop();
				v2 = Pop();
				ret = (v1 + v2);
			}
			if (expression[i] == '-'){
				v1 = Pop();
				v2 = Pop();
				ret = v2 - v1;
			}
			if (expression[i] == '*'){
				v1 = Pop();
				v2 = Pop();
				ret = (v1 * v2);
			}
			if (expression[i] == '/'){
				v1 = Pop();
				v2 = Pop();
				ret = (v2 / v1);
			}
			i++;
			Push(ret);
		}
		else{
			cout << "Invaild Expression." << endl;
			break;
		}
	}
	return Pop();
}

bool isop(char c){
    return (c == '+' || c == '-' || c == '*' || c == '/' || c == '^');
}
int prec(char c)
{
    if (c == '^')
        return 3;
    else if (c == '/' || c == '*')
        return 2;
    else if (c == '+' || c == '-')
        return 1;
    else
        return -1;
}

void inicia(pilha *p){
    p->no = NULL;
}
char topo(pilha *p){
    while(p->no!=NULL){
        p = p->no;
    }
    return p->n;
}
char desimpilha(pilha *p){
    if(p->no != NULL){
        char valor;
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

void empilha(pilha *p, char valor){
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


int main(void){
    pilha *p;
    p = (pilha * )malloc(sizeof(pilha));
    inicia(p);
    string s, r;
    getline(cin, s);
    for(int i = 0; i<s.length(); i++){
        char c = s[i];
        if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9'))
            r += c;
        else if (c == '(')
            empilha(p,'(');
        else if (c == ')') {
            while (topo(p) != '(') {
                r += " ";
                r += topo(p);
                desimpilha(p);
            }
            desimpilha(p);
        }
        else {
            r += " ";
            while (p->no != NULL 
                   && prec(s[i]) <= prec(topo(p))) {
                if (c == '^' && topo(p) == '^')
                    break;
                else {
                    r += topo(p);
                    desimpilha(p);
                }
                r += " ";
            }
            empilha(p,c);
        }
    }
    while (p->no != NULL) {
        r += " ";
        r += topo(p);
        desimpilha(p);
    }
    cout << calcula(r) << endl;
}