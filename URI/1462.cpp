// Ivan Carvalho
// Solution to https://www.urionlinejudge.com.br/judge/problems/view/1462
#include <cstdio>
#include <algorithm>
#define MAXN 100010
using namespace std;
typedef unsigned long long ll;
ll vetor[MAXN];
bool comp(int a,int b){
	return a > b;
}
int main(){
	ll n;
	while(scanf("%llu",&n) != EOF){
		ll soma = 0, impossivel = 0;
		for(ll i=1;i <= n;i++){
			ll davez;
			scanf("%llu",&davez);
			soma += davez;
			soma %= 2;
			impossivel |= davez >= n;
			vetor[i] = davez;
		}
		sort(vetor+1,vetor+n+1,comp);
		impossivel |= soma;
		ll ini = 1, fim = n,meio;
		while(ini <= fim && !impossivel){
			meio = (ini+fim)/2;
			ll somaerdos = 0, somagalai = meio*(meio-1);
			for(ll i=1;i<=n;i++){
				if(i <= meio) somaerdos += vetor[i];
				else somagalai += min(vetor[i],meio);
			}
			if(somaerdos > somagalai){
				impossivel = 1;
			}
			fim = meio - 1;
		}
		if(impossivel) printf("impossivel\n");
		else printf("possivel\n");
	}
	return 0;
}
