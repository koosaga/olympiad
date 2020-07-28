// Ivan Carvalho
// Solution to https://www.urionlinejudge.com.br/judge/problems/view/1178
#include <cstdio>
int main(){
	int i;
	double a;
	scanf("%lf",&a);
	for(i=0;i<100;i++){
		printf("N[%d] = %.4lf\n",i,a);
		a = a/2.0;
	}
	return 0;
}
