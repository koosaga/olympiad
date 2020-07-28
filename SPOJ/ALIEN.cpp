// Ivan Carvalho
// Solution to https://www.spoj.com/problems/ALIEN/
#include <cstdio>
#include <deque>
#include <algorithm>
using namespace std;
typedef long long ll;
int main(){
	ll TC;
	scanf("%lld",&TC);
	while(TC--){
		ll n,m,soma = 0, estacoes = 0,pessoas = 0;
		deque<ll> janela;
		scanf("%lld %lld",&n,&m);
		while(n--){
			ll davez;
			scanf("%lld",&davez);
			janela.push_back(davez);
			soma += davez;
			while(soma > m){
				soma -= janela.front();
				janela.pop_front();
			}
			if (janela.size() > estacoes || (janela.size() == estacoes && soma < pessoas)){
				pessoas = soma;
				estacoes = janela.size();
			}
		}
		printf("%lld %lld\n",pessoas,estacoes);
	}
	return 0;
}