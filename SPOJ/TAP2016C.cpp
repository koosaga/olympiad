// Ivan Carvalho
// Solution to https://www.spoj.com/problems/TAP2016C/
#include <cstdio>
#include <vector>
#define MAXN 50010
using namespace std;
vector<int> transposto[MAXN];
int n,m,maior[MAXN],exibir[MAXN],processado[MAXN],entrada[MAXN],mostrar[MAXN];
void dfs(int x){
	processado[x] = 1;
	for(int i=0;i<transposto[x].size();i++){
		int v = transposto[x][i];
		if(!processado[v]) dfs(v);
		maior[x] = max(maior[x],maior[v]);
	}
	exibir[maior[x]]++;
}
int main(){
	while(scanf("%d %d",&n,&m) != EOF){
		for(int i=1;i<=n;i++){
			transposto[i].clear();
			exibir[i] = 0;
			maior[i] = 0;
			entrada[i] = 0;
			processado[i] = 0;
		}
		for(int i=1;i<=m;i++){
			int u,v;
			scanf("%d %d",&u,&v);
			transposto[v].push_back(u);
		}
		for(int i=1;i<=n;i++){
			int u;
			scanf("%d",&u);
			maior[u] = i;
			entrada[i] = u;
		}
		for(int vez=n;vez >= 1;vez--){
			if(!processado[entrada[vez]]){
				dfs(entrada[vez]);
			}
		}
		for(int i=1;i<=n;i++){
			mostrar[i] = mostrar[i-1] + exibir[i];
		}
		for(int i=1;i<=n;i++){
			printf("%d\n",mostrar[i]);
		}
	}
	return 0;
}