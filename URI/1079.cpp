// Ivan Carvalho
// Solution to https://www.urionlinejudge.com.br/judge/problems/view/1079
#include <iostream>
int main(){
	int ordem,i;
	scanf("%d",&ordem);
	for (i=0;i<ordem;i++){
		double a,b,c;
		scanf("%lf %lf %lf",&a,&b,&c);
		printf("%.1lf\n",(2*a+3*b+5*c)/10.0);
	}
	return 0;
}
