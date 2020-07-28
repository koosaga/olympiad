// Ivan Carvalho
// Solution to https://www.urionlinejudge.com.br/judge/problems/view/1056
#include <cstdio>
#include <vector>
#define MAXN 210
using namespace std;
int vetor[MAXN],n,m;
vector<int> match, vis, grafo[MAXN];
int Aug(int l){
	if (vis[l]) return 0;
	vis[l] = 1;
	for(int i=0;i<(int)grafo[l].size();i++){
		int r = grafo[l][i];
		if (match[r] == -1 || Aug(match[r])){
			match[r] = l;
			return 1;
		}
	}
	return 0;
}
int main(){
	int casos;
	scanf("%d",&casos);
	for(int caso = 1; caso <= casos;caso++){
		for(int i=0;i<MAXN;i++) grafo[i].clear();
		match.clear();
		vis.clear();
		scanf("%d",&n);
		for(int i= 1; i <= n; i++) scanf("%d",&vetor[i]);
		scanf("%d",&m);
		for(int i=n+1;i<=n+m;i++) scanf("%d",&vetor[i]);
		for(int i=1;i<=n;i++){
			for(int j = n+1;j<=n+m;j++){
				if (vetor[i] == vetor[j] || (vetor[i] != 0  && (vetor[j] % vetor[i]) == 0)) grafo[i].push_back(j);
			}
		}
		int resposta = 0;
		match.assign(n+m+10,-1);
		for(int i=1;i<=n;i++){
			vis.assign(n+10,0);
			resposta += Aug(i);
		}
		printf("Case %d: %d\n",caso,resposta);
	}
	return 0;
}
