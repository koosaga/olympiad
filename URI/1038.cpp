// Ivan Carvalho
// Solution to https://www.urionlinejudge.com.br/judge/problems/view/1038
#include <iostream>
int main(){
	int a,b;
	double c;
	scanf("%d %d",&a,&b);
	switch (a){
		case 1: c =4.0;
			break;
		case 2: c = 4.5;
			break;
		case 3: c = 5.0;
			break;
		case 4: c= 2.0;
			break;
		case 5: c= 1.5;
			break;
	}
	printf ("Total: R$ %.2lf\n",b*c);
	return 0;
}
