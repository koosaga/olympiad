// Ivan Carvalho
// Solution to https://www.spoj.com/problems/OPCPIZZA/
#include <cstdio>
#include <unordered_map>
using namespace std;
typedef long long ll;
const ll MAXN = 1e5 + 1;
ll n,m,vetor[MAXN];
unordered_map<ll,ll> mapa;
int main(){
	ll TC;
	scanf("%lld",&TC);
	while(TC--){
		mapa.clear();
		scanf("%lld %lld",&n,&m);
		for(ll i=1;i<=n;i++){
			scanf("%lld",&vetor[i]);
			mapa[vetor[i]]++;
		}
		ll resp = 0;
		for(ll i=1;i<=n;i++){
			mapa[vetor[i]]--;
			if(mapa.count(m - vetor[i])) resp += mapa[m - vetor[i]];
			mapa[vetor[i]]++;
		}
		printf("%lld\n",resp/2LL);
	}
	return 0;
}