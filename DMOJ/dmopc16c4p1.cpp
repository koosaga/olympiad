// Ivan Carvalho
// Solution to https://dmoj.ca/problem/dmopc16c4p1
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int main(){
	ll n;
	scanf("%lld",&n);
	while(n--){
		ll v;
		scanf("%lld",&v);
		if(__builtin_popcountll(v) == 1) printf("T\n");
		else printf("F\n");
	}
	return 0;
}