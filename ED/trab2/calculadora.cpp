#include<bits/stdc++.h>
using namespace std;
//GABRIEL VIEIRA DO AMARAL DRE 121069963
#define MAX_STACK 100

float _stack[MAX_STACK];
char _stackchar[MAX_STACK];
int tos = 0;
int toschar = 0;
struct Pilha{ 
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
bool taVazioFloat();
bool taVazioChar();
bool taCheioFloat();
bool taCheioChar();
void PushFloat(float value);
void PushChar(char value);
float PopFloat();
char PopChar();

void PushFloat(float value){
	if (taCheioFloat()){
		return;
	}
	tos++;
	_stack[tos] = value;
}
void PushChar(char value){
	if (taCheioFloat()){
		return;
	}
	toschar++;
	_stackchar[toschar] = value;
}
float PopFloat(){
	float t = _stack[tos];
	tos--;
	return t;
}
char PopChar(){
	char t = _stackchar[toschar];
	toschar--;
	return t;
}
bool taCheioFloat(){
	return tos >= MAX_STACK - 1;
}
bool taCheioChar(){
	return toschar >= MAX_STACK - 1;
}
bool taVazioFloat(){
	return tos == 0;
}
bool taVazioChar(){
	return toschar == 0;
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
			PushFloat(atof(tok.c_str()));
			tok = "";
		}
		else if (isop(expression[i])){
			if (expression[i] == '+'){
				v1 = PopFloat();
				v2 = PopFloat();
				ret = (v1 + v2);
			}
			if (expression[i] == '-'){
				v1 = PopFloat();
				v2 = PopFloat();
				ret = v2 - v1;
			}
			if (expression[i] == '*'){
				v1 = PopFloat();
				v2 = PopFloat();
				ret = (v1 * v2);
			}
			if (expression[i] == '/'){
				v1 = PopFloat();
				v2 = PopFloat();
				ret = (v2 / v1);
			}
			i++;
			PushFloat(ret);
		}
		else{
			cout << "Invaild Expression." << endl;
			break;
		}
	}
	return PopFloat();
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
    string s, r;
    getline(cin, s);
    for(int i = 0; i<s.length(); i++){
        char c = s[i];
        if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9'))
            r += c;
        else if (c == '(')
            PushChar('(');
        else if (c == ')') {
            while (_stackchar[toschar] != '(') {
                r += " ";
                r += _stackchar[toschar];
                PopChar();
            }
            PopChar();
        }
        else {
            r += " ";
            while (taVazioChar() 
                   && prec(s[i]) <= prec(_stackchar[toschar])) {
                if (c == '^' && _stackchar[toschar] == '^')
                    break;
                else {
                    r += _stackchar[toschar];
                    PopChar();
                }
                r += " ";
            }
            PushChar(c);
        }
    }
    while (!taCheioChar) {
        r += " ";
        r += _stackchar[toschar];
        PopChar();
    }
    cout << calcula(r) << endl;
}