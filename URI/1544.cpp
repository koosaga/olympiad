// Ivan Carvalho
// Solution to https://www.urionlinejudge.com.br/judge/problems/view/1544
#include <cstdio>
int main(){
	long long a,b;
	while(scanf("%lld %lld",&a,&b) != EOF){
		long long resp = 1;
		for(long long i = a - b + 1;i <= a;i++){
			resp *= i;
			while(resp % 10LL == 0LL) resp /= 10LL;
			resp %= 100000000000LL;
		}
		printf("%lld\n",resp%10);
	}
	return 0;
}
