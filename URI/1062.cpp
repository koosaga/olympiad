// Ivan Carvalho
// Solution to https://www.urionlinejudge.com.br/judge/problems/view/1062
#include <cstdio>
#define MAXN 1010
int n,saida[MAXN],pilha[MAXN],tam;
void pop(){if (tam>0) tam--;}
void push(int x) {pilha[++tam]=x;}
void clear(){tam=0;}
int top(){ return pilha[tam]; }
int main(){
	while(scanf("%d",&n) && n!=0){
		while(scanf("%d",&saida[1]) && saida[1]!=0){
			for(int i=2;i<=n;i++) scanf("%d",&saida[i]);
			clear();
			int j=1;
			push(j++);
			bool deu_errado = false;
			for (int i=1;i<=n;i++){
				while (top()!=saida[i] && j<=n) push(j++);
				if (top()==saida[i]) pop();
				else {
					printf("No\n");
					deu_errado = true;
					break;
				}
			}
			if (!deu_errado) printf("Yes\n");
		}
		printf("\n");
	}
	return 0;
}
