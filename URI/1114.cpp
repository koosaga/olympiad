// Ivan Carvalho
// Solution to https://www.urionlinejudge.com.br/judge/problems/view/1114
#include <iostream>
int main(){
	int x;
	while(1) {
		scanf("%d",&x);
		if (x==2002) break;
		else printf("Senha Invalida\n");
	}
	printf("Acesso Permitido\n");
	return 0;
}
