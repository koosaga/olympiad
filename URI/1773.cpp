// Ivan Carvalho
// Solution to https://www.urionlinejudge.com.br/judge/problems/view/1773
#include <cstdio>
#include <vector>
#define MAXN 1001
using namespace std;
typedef int ll;
#define gc getchar_unlocked
void getint(ll &x){
    register ll c = gc();
    x = 0;
    for(;(c<48 || c>57);c = gc());
    for(;c>47 && c<58;c = gc()) {x = (x<<1) + (x<<3) + c - 48;}
}
vector<int> grafo[MAXN];
int processado[MAXN],marcado[MAXN],iteracao,requisito[MAXN],marcados,n,m;
void dfs(int x){
	//printf("X %d R %d M %d\n",x,requisito[x],marcado[requisito[x]]);
	processado[x] = iteracao;
	if(!marcado[requisito[x]]) return;
	if(!marcado[x]){
		marcado[x] = 1;
		marcados++;
	}
	for(int i=0;i < grafo[x].size();i++){
		int v = grafo[x][i];
		if(processado[v] != iteracao) dfs(v);
	}
}
int main(){
	while(scanf("%d %d",&n,&m) != EOF){
		for(int i=1;i<=n;i++){
			grafo[i].clear();
			marcado[i] = 0;
		}
		marcados = 1;
		marcado[1] = 1;
		requisito[1] = 1;
		while(m--){
			int u,v;
			getint(u);
			getint(v);
			grafo[u].push_back(v);
			grafo[v].push_back(u);
		}
		for(int i=2;i<=n;i++){
			getint(requisito[i]);
		}
		for(int vez=1;vez<=n && marcados != n;vez++){
			iteracao++;
			dfs(1);
		}
		if(marcados == n) printf("sim\n");
		else printf("nao\n");
	}
	return 0;
}
