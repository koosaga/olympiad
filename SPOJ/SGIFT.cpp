// Ivan Carvalho
// Solution to https://www.spoj.com/problems/SGIFT/
#include <cstdio>
#include <algorithm>
#include <vector>
#define MAXN 100010
using namespace std;
typedef long long ll;
vector<ll> vetor;
ll acumulada[MAXN],n,q;
int main(){
	scanf("%lld",&n);
	for(ll i=1;i<=n;i++){
		ll davez;
		scanf("%lld",&davez);
		vetor.push_back(davez);
	}
	sort(vetor.begin(),vetor.end());
	for(ll i=0;i<n;i++){
		acumulada[i+1] = acumulada[i] + vetor[i];
	}
	scanf("%lld",&q);
	while(q--){
		ll a,b;
		scanf("%lld %lld",&a,&b);
		if(b < vetor[0]){
			printf("0\n");
			continue;
		}
		if(a > vetor[n-1]){
			printf("0\n");
			continue;
		}
		vector<ll>::iterator it1 = lower_bound(vetor.begin(),vetor.end(),a);
		vector<ll>::iterator it2 = upper_bound(vetor.begin(),vetor.end(),b);
		it2--;
		ll ini = it1 - vetor.begin() + 1;
		ll fim = it2 - vetor.begin() + 1;
		printf("%lld\n",acumulada[fim] - acumulada[ini-1]);
	}
	return 0;
}