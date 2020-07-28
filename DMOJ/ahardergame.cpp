// Ivan Carvalho
// Solution to https://dmoj.ca/problem/ahardergame
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 1e6 + 10;
int N,pilha[MAXN],ptr;
int main(){
	scanf("%d",&N);
	int tot = 0;
	for(int i = 1;i<=N;i++){
		ptr++;
		scanf("%d",&pilha[ptr]);
		tot += pilha[ptr];
		while(ptr >= 3 && pilha[ptr - 2] <= pilha[ptr-1] && pilha[ptr-1] >= pilha[ptr]){
			pilha[ptr-2] = pilha[ptr - 2] - pilha[ptr - 1] + pilha[ptr];
			ptr -= 2;
		}
	}
	int resposta = 0,sinal = 1,ini = 1,fim = ptr;
	while(ini<=fim){
		if(pilha[ini] >= pilha[fim]){
			resposta += sinal*pilha[ini];
			ini++;
		}
		else{
			resposta += sinal*pilha[fim];
			fim--;
		}
		sinal *= -1;
	}
	printf("%d\n",(resposta+tot)/2);
	return 0;
}
