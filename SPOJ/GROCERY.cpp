// Ivan Carvalho
// Solution to https://www.spoj.com/problems/GROCERY/
#include <cstdio>
typedef int ll;
const ll maximo = 20 * 100;
int main(){
	for(ll a=8;a<=125;a++){
		for(ll b =a;a+b<=600;b++){
			for(ll c=b;a+b+c <= 1225;c++){
				if(a*b*c <= 1000000) continue;
				ll cima = 1000000 * (a+b+c);
				ll baixo = a*b*c - 1000000;
				if(cima % baixo != 0) continue;
				ll d = cima/baixo;
				if(d >= c && a + b + c + d <= maximo){
					printf("%.2lf %.2lf %.2lf %.2lf\n",double(a *0.01),double(b * 0.01),double(c*0.01),double(d*0.01));
				}
			}
		}
	}
	return 0;
}