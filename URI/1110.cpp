// Ivan Carvalho
// Solution to https://www.urionlinejudge.com.br/judge/problems/view/1110
#include <cstdio>
#define MAXT 1010
int fila[MAXT],ini=1,fim;
int front(){return fila[ini];}
int back(){return fila[fim];}
int size(){return fim-ini+1;}
void push(int x){fila[++fim]=x;}
void pop(){if (size()>0) ini++;}
void clear(){ini=1;fim=0;}
int main(){
	int n;
	while(1){
		scanf("%d",&n);
		if (n==0) break;
		clear();
		for(int i=1;i<=n;i++) push(i);
		printf("Discarded cards:");
		for(int i=1;i<n;i++){
			printf(" %d", front());
			pop();
			push(front());
			pop();
			if(size()>=2) printf(",");
		}
		printf("\nRemaining card: %d\n", front());	
	}
}
