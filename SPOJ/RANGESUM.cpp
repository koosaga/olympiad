// Ivan Carvalho
// Solution to https://www.spoj.com/problems/RANGESUM/
#include <cstdio>
#include <deque>
#define MAXN 100010
using namespace std;
typedef long long ll;
deque<ll> soma;
ll vetor[MAXN],n,q;
int main(){
	scanf("%lld",&n);
	for(ll i=0;i<n;i++) scanf("%lld",&vetor[i]);
	soma.push_front(vetor[n-1]);
	for(ll i = n-2;i>=0;i--){
		soma.push_front(soma.front() + vetor[i]);
	}
	scanf("%lld",&q);
	while(q--){
		ll op;
		scanf("%lld",&op);
		if (op == 1){
			ll a , b;
			scanf("%lld %lld",&a,&b);
			a--;
			ll resultado = soma[a];
			if (b < soma.size()) resultado -= soma[b];
			printf("%lld\n",resultado);  
		}
		if (op == 2){
			ll davez;
			scanf("%lld",&davez);
			soma.push_front(soma.front() + davez);
		}
	}
	return 0;
}