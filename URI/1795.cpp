// Ivan Carvalho
// Solution to https://www.urionlinejudge.com.br/judge/problems/view/1795
#include <cstdio>
int main(){
	int n;
	long long resposta=1;
	scanf("%d",&n);
	while(n--) resposta *= 3;
	printf("%lld\n",resposta);
	return 0;
}
