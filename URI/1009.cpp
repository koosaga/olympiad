// Ivan Carvalho
// Solution to https://www.urionlinejudge.com.br/judge/problems/view/1009
#include <cstdio>
int main() {
	char nome[100];
	double a,b;
	scanf("%s",nome);
	scanf("%lf",&a);
	scanf("%lf",&b);
	printf("TOTAL = R$ %.2lf\n",a+0.15*b);
	return 0;
}
