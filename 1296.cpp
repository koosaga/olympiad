// Ivan Carvalho
// Solution to https://www.urionlinejudge.com.br/judge/problems/view/1296
#include <cmath>
using namespace std;
int main(){
	double m1,m2,m3;
	while(scanf("%lf %lf %lf",&m1,&m2,&m3) != EOF){
		m1 *= m1;
		m2 *= m2;
		m3 *= m3;
		double total = 4*(m1+m2+m3)/3.0;
		double a = (2*total - 4*m1)/3.0;
		double b = (2*total - 4*m2)/3.0;
		double c = (2*total - 4*m3)/3.0;
		if(a <= 0 || b <= 0 || c <= 0){
			printf("-1.000\n");
			continue;
		}
		a = sqrt(a);
		b = sqrt(b);
		c = sqrt(c);
		if(a < b + c && b < a + c && c < a + b){
			double p = (a+b+c)*0.5;
			double area = p*(p-a)*(p-b)*(p-c);
			printf("%.3lf\n",sqrt(area));
		}
		else{
			printf("-1.000\n");
		}
	}
	return 0;
}
