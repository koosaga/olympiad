// Ivan Carvalho
// Solution to https://www.urionlinejudge.com.br/judge/problems/view/1012
#include <cstdio>
int main() {
	double a,b,c;
	scanf("%lf %lf %lf",&a,&b,&c);
	printf("TRIANGULO: %.3lf\nCIRCULO: %.3lf\nTRAPEZIO: %.3lf\nQUADRADO: %.3lf\nRETANGULO: %.3lf\n",(a*c)/2.0,(c*c*3.14159),(((a+b)*c)/2.0),(b*b),(a*b));
	return 0;
}
