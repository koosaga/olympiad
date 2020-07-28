// Ivan Carvalho
// Solution to https://dmoj.ca/problem/dmopc14c1p3
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int main(){
	ll soma = 0,n;
	scanf("%lld",&n);
	for(ll i=1;i<=n;i++){
		ll davez;
		scanf("%lld",&davez);
		soma += davez;
	}
	ll q;
	scanf("%lld",&q);
	while(q--){
		ll davez;
		scanf("%lld",&davez);
		soma += davez;
		n++;
		printf("%.3lf\n",double(soma)/double(n));
	}
	return 0;
}