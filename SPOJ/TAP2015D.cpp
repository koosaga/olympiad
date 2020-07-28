// Ivan Carvalho
// Solution to https://www.spoj.com/problems/TAP2015D/
#include <cstdio>
#include <algorithm>
#include <set>
using namespace std;
typedef long long ll;
const int MAXN = 1e3 + 1;
int pai[MAXN],n,m;
long long membros[MAXN],ligacoes[MAXN],r,e;
set<int> chefes;
int find(int x){
	if(x == pai[x]) return pai[x];
	return pai[x] = find(pai[x]);
}
void join(int x,int y){
	x = find(x);
	y = find(y);
	if(x == y){
		ligacoes[x]++;
		return;
	}
	if(membros[x] >= membros[y]){
		membros[x] += membros[y];
		ligacoes[x] += ligacoes[y];
		ligacoes[x]++;
		pai[y] = x;
	}
	else{
		membros[y] += membros[x];
		ligacoes[y] += ligacoes[x];
		ligacoes[y]++;
		pai[x] = y;
	}
}
int main(){
	while(scanf("%d %d %lld %lld",&n,&m,&r,&e) != EOF){
		chefes.clear();
		for(int i=1;i<=n;i++){
			pai[i] = i;
			membros[i] = 1;
			ligacoes[i] = 0;
		}
		while(m--){
			int x,y;
			scanf("%d %d",&x,&y);
			join(x,y);
		}
		for(int i=1;i<=n;i++){
			chefes.insert(find(i));
		}
		ll resposta = 0;
		for(auto it = chefes.begin();it != chefes.end();it++){
			int davez = *it;
			ll custo1 = (membros[davez]*(membros[davez]-1))/2;
			custo1 -= ligacoes[davez];
			custo1 *= r;
			ll custo2 = membros[davez]*e;
			resposta += min(custo1,custo2);
		}
		printf("%lld\n",resposta);
	}
	return 0;
}