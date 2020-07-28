// Ivan Carvalho
// Solution to https://www.urionlinejudge.com.br/judge/problems/view/1084
#include <cstdio>
#include <stack>
using namespace std;
int main(){
	int n,m,apagados;
	while(scanf("%d %d",&n,&m) && (n||m)){
		getchar();
		apagados = 0;
		stack<char> pilha,resposta;
		for(int i = 0;i<n;i++){
			char davez;
			scanf("%c",&davez);
			while (!pilha.empty() && apagados < m && davez > pilha.top()){
				pilha.pop();
				apagados++;
			}
			if (pilha.size()< n - m) pilha.push(davez);
		}
		while(!pilha.empty()) {
			resposta.push(pilha.top());
			pilha.pop();
		}
		while(!resposta.empty()){
			printf("%c",resposta.top());
			resposta.pop();
		}
		printf("\n");
	}
	return 0;
}
