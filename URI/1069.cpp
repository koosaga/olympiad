// Ivan Carvalho
// Solution to https://www.urionlinejudge.com.br/judge/problems/view/1069
#include <cstdio>
#include <cstring>
#define MAX 1010
char pilha[MAX];
int tamanho;
void clear(){tamanho=0;}
void pop(){if (tamanho>0) tamanho--;}
void push(char x){pilha[++tamanho]=x;}
char top(){return pilha[tamanho];}
int main(){
	int n,i,j;
	char pedras[MAX];
	scanf("%d",&n);
	for(i=0;i<n;i++){
		int resposta =0;
		clear();
		scanf("%s",pedras);
		for(j=0;j<strlen(pedras);j++){
			char davez = pedras[j];
			if (davez == '<') push('<');
			if (davez == '>') {
				if (top()=='<') {
					resposta++;
					pop();
				}
				else push('>');
			} 
		}
		printf("%d\n",resposta);
	}
	return 0;
}
