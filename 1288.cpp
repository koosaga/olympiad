// Ivan Carvalho
// Solution to https://www.urionlinejudge.com.br/judge/problems/view/1288
#include <unordered_map>
#include <algorithm>
#define MAXN 1010
using namespace std;
typedef long long ll;
ll n,s,casos,peso[MAXN],valor[MAXN],r,davez,condicional;
unordered_map<ll,ll> tab[MAXN];
int knapsack(ll obj, ll aguenta){
	if (condicional) return tab[obj][aguenta] = 0;
	if (obj > n || !aguenta) return tab[obj][aguenta]=0;
	if (tab[obj].count(aguenta)) return tab[obj][aguenta];
	ll nao_coloca = knapsack(obj+1,aguenta);
	condicional += int(nao_coloca >= r);
	if (peso[obj]<=aguenta){
		ll coloca = valor[obj]+knapsack(obj+1,aguenta-peso[obj]);
		condicional += int(coloca >= r);
		return tab[obj][aguenta]=max(coloca,nao_coloca);
	}
	return tab[obj][aguenta]=nao_coloca;	
}
int main(){
	scanf("%lld",&casos);
	while(casos--){
		condicional = 0;
		scanf("%lld",&n);
		for(int i=0;i<=n+1;i++) tab[i].clear(); 
		for(ll i=1;i<=n;i++) scanf("%lld %lld",&valor[i],&peso[i]);
		scanf("%lld",&s);
		scanf("%lld",&r);
		davez = knapsack(1,s);
		if (davez>=r) printf("Missao completada com sucesso\n");
		else printf("Falha na missao\n");
	}
	return 0;
}
