// Ivan Carvalho
// Solution to https://www.urionlinejudge.com.br/judge/problems/view/1039
#include <cstdio>
typedef long long ll;
int main(){
	ll a,b,c,d,e,f,q,x,y;
	while(scanf("%lld %lld %lld %lld %lld %lld",&a,&b,&c,&d,&e,&f) != EOF){
		x = e + d,y = f;
		q = (x - b)*(x - b) + (c - y)*(c-y);
		if(q > a*a){
			printf("MORTO\n");
			continue;
		}
		x = e - d,y = f;
		q = (x - b)*(x - b) + (c - y)*(c-y);
		if(q > a*a){
			printf("MORTO\n");
			continue;
		}
		x = e,y = f + d;
		q = (x - b)*(x - b) + (c - y)*(c-y);
		if(q > a*a){
			printf("MORTO\n");
			continue;
		}
		x = e,y = f - d;
		q = (x - b)*(x - b) + (c - y)*(c-y);
		if(q > a*a){
			printf("MORTO\n");
			continue;
		}
		q = (b-e)*(b-e) + (f-c)*(f-c);
		ll compara = a - d;
		if(q > compara*compara){
			printf("MORTO\n");
			continue;
		}
		printf("RICO\n");
	}
	return 0;
}
