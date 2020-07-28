// Ivan Carvalho
// Solution to https://www.urionlinejudge.com.br/judge/problems/view/1944
#include <cstdio>
#define MAXN 1001
char pilha[MAXN];
int tam,n,resp;
int main(){
	scanf("%d",&n);
	while(n--){
		if(tam == 0){
			pilha[tam++] = 'F';
			pilha[tam++] = 'A';
			pilha[tam++] = 'C';
			pilha[tam++] = 'E';
		}
		char a,b,c,d;
		scanf(" %c %c %c %c",&a,&b,&c,&d);
		pilha[tam++] = a;
		pilha[tam++] = b;
		pilha[tam++] = c;
		pilha[tam++] = d;
		//printf("%c %c %c %c\n",pilha[tam-1],pilha[tam-2],pilha[tam-3],pilha[tam-4]);
		//printf("%c %c %c %c\n",pilha[tam-5],pilha[tam-6],pilha[tam-7],pilha[tam-8]);
		if(pilha[tam-1] == pilha[tam-8] && pilha[tam-2] == pilha[tam-7] && pilha[tam-3] == pilha[tam-6] && pilha[tam-4] == pilha[tam-5]){
			resp++;
			tam -= 8;
		}
	}
	printf("%d\n",resp);
	return 0;
}
