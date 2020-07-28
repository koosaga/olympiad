// Ivan Carvalho
// Solution to https://www.urionlinejudge.com.br/judge/problems/view/1040
#include <iostream>
int main(){
	double a,b,c,d;
	scanf("%lf %lf %lf %lf",&a,&b,&c,&d);
	double media = (2*a+3*b+4*c+d)/10.0;
	if (media>=7) printf("Media: %.1lf\nAluno aprovado.\n",media);
	else if (media<5) printf("Media: %.1lf\nAluno reprovado.\n",media);
	else {
		double e;
		scanf("%lf",&e);
		printf("Media: %.1lf\nAluno em exame.\nNota do exame: %.1lf\n",media,e);
		double novamedia = (media+e)/2.0;
		if (novamedia>=5) printf("Aluno aprovado.\nMedia final: %.1lf\n",novamedia);
		else printf("Aluno reprovado.\nMedia final: %.1lf\n",novamedia);
	}
	return 0;
}
