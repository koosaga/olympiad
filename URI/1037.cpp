// Ivan Carvalho
// Solution to https://www.urionlinejudge.com.br/judge/problems/view/1037
#include <iostream>
int main(){
	double x;
	scanf("%lf",&x);
	if (x>=0 && x<=100){
		if (x<=25) printf("Intervalo [0,25]\n");
		else if (x<=50) printf("Intervalo (25,50]\n");
		else if (x<=75) printf("Intervalo (50,75]\n");
		else printf("Intervalo (75,100]\n");
	}
	else printf("Fora de intervalo\n");
	return 0;
}
