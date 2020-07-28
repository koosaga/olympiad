// Ivan Carvalho
// Solution to https://www.urionlinejudge.com.br/judge/problems/view/2063
#include <cstdio>
#include <algorithm>
typedef long long ll;
using namespace std;
ll vetor[110];
ll gcd(ll x, ll y){
	if (x < y) swap(x,y);
	if (x % y == 0) return y;
	return gcd(y,x%y);
}
int main(){
	ll n,multiplo=1;
	scanf("%lld",&n);
	for(ll i=1;i<=n;i++) scanf("%lld",&vetor[i]);
	for(ll i=1;i<=n;i++){
		ll proximo = vetor[i],tempo=1;
		while(proximo != i){
			tempo++;
			proximo = vetor[proximo];
		}
		multiplo = tempo * multiplo / gcd(tempo,multiplo);
	}
	printf("%lld\n",multiplo);
	return 0;
}
