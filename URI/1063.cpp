// Ivan Carvalho
// Solution to https://www.urionlinejudge.com.br/judge/problems/view/1063
#include <cstdio>
#define MAX 30
int n,tam;
char saida[MAX], pilha[MAX], entrada[MAX];
void pop(){ if(tam>0) tam--; }
void push(char x){ pilha[++tam]=x; }
void clear(){ tam=0; }
char top(){ return pilha[tam]; }
int main(){
	while (scanf("%d",&n) && n != 0){
		clear();
		for (int i =1;i<=n;i++) scanf(" %c",&entrada[i]);
		for (int i=1;i<=n;i++) scanf(" %c",&saida[i]);
		int j=1;
		push(entrada[j++]);
		printf("I");
		for (int i=1;i<=n;i++){
			while (top() != saida[i] && j<=n) {
				printf("I");
				push(entrada[j++]);
			}
			if (top()==saida[i]){
				printf("R");
				pop();
			}
			else {
				printf(" Impossible");
				break;
			}
		}
		printf("\n");
	}
	return 0;
}
