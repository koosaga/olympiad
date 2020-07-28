// Ivan Carvalho
// Solution to https://www.urionlinejudge.com.br/judge/problems/view/1080
#include <iostream>
int main(){
	int resposta=0,indice=0,i;
	for (i=0;i<100;i++){
		int momento;
		scanf("%d",&momento);
		if (momento>resposta) {
			resposta = momento;
			indice = i;
		}
	}
	printf("%d\n%d\n",resposta,indice+1);
	return 0;
}
