// Ivan Carvalho
// Solution to https://www.urionlinejudge.com.br/judge/problems/view/1810
#include <cstdio>
#include <algorithm>
#include <cstring>
#define MAXN 181
using namespace std;
int f[MAXN],p[MAXN],h[MAXN],d[MAXN],demandatotal[MAXN],n,instancia;
int dp[MAXN][MAXN],vis[MAXN][MAXN];
int solve(int dia,int ultimo){
	if(dia > n) return 0;
	if(vis[dia][ultimo]) return dp[dia][ultimo];
	vis[dia][ultimo] = 1;
	int melhor = 1e8,custodiario;
	if(ultimo == dia-1){
		custodiario = d[dia]*p[dia] + f[dia];
		melhor = min(melhor, solve(dia+1,dia) + custodiario );
		for(int proximo = dia+1;proximo <= n;proximo++){
			int delta = (demandatotal[proximo] - demandatotal[dia])*p[dia];
			melhor = min(melhor, solve(dia+1,proximo) + custodiario + delta);
		}
	}
	else{
		custodiario = h[dia-1]*(demandatotal[ultimo] - demandatotal[dia-1]);
		melhor = min(melhor, solve(dia+1,ultimo) + custodiario );
		for(int proximo = ultimo+1;proximo <= n;proximo++){
			int delta = (demandatotal[proximo] - demandatotal[ultimo])*p[dia] + f[dia];
			melhor = min(melhor, solve(dia+1,proximo) + custodiario + delta);
		}
	}
	return dp[dia][ultimo] = melhor;
}
int main(){
	while(scanf("%d",&n) && n){
		for(int i=1;i<=n;i++){
			scanf("%d %d %d %d",&f[i],&p[i],&h[i],&d[i]);
			demandatotal[i] = demandatotal[i-1] + d[i];
		}
		memset(vis,0,sizeof(vis));
		printf("Instancia #%d\n%d\n\n",++instancia,solve(1,0));
	}
	return 0;
}
