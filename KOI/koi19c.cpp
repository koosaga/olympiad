#include <bits/stdc++.h>
using namespace std;
const int MAXN = 5005;
using lint = long long;
using pi = pair<int, int>;

int n, sz[MAXN], chk[MAXN];
vector<int> gph[MAXN];
int d1[MAXN][MAXN], d2[MAXN][MAXN];
pi rng[MAXN];

void dfs(int x){
	int cur = 0;
	int aux1[MAXN];
	int aux2[MAXN];
	for(auto &i : gph[x]){
		gph[i].erase(find(gph[i].begin(), gph[i].end(), x));
		dfs(i);
		memset(aux1, 0x3f, sizeof(aux1));
		memset(aux2, 0, sizeof(aux2));
		for(int j=0; j<=sz[i]; j++){
			for(int k=0; k<=cur; k++){
				aux1[j + k] = min(aux1[j + k], d1[i][j] + d1[x][k]);
				aux2[j + k] = max(aux2[j + k], d2[i][j] + d2[x][k]);
			}
		}
		cur += sz[i];
		for(int j=0; j<=cur; j++){
			d1[x][j] = aux1[j];
			d2[x][j] = aux2[j];
		}
	}
	sz[x] = cur;
	for(int j=0; j<=sz[x]; j++){
		d1[x][j]++; d2[x][j]++;
	}
	if(chk[x]){
		sz[x]++;
		for(int j=sz[x]; j; j--){
			d1[x][j] = d1[x][j-1];
			d2[x][j] = d2[x][j-1];
		}
		d1[x][0] = 0;
		d2[x][0] = 0;
	}
	else d1[x][0] = 0;
}

int main(){
	int m;
	scanf("%d %d",&n,&m);
	for(int i=0; i<m; i++){
		int v; scanf("%d",&v);
		chk[v] = 1;
	}
	for(int i=1; i<n; i++){
		int s, e; scanf("%d %d",&s,&e);
		gph[s].push_back(e);
		gph[e].push_back(s);
	}
	fill(rng, rng + m + 1, pi(1e9, -1));
	memset(d1, 0x3f, sizeof(d1));
	for(int i=1; i<=n; i++){
		d1[i][0] = 0;
		d2[i][0] = 0;
	}
	dfs(1);
	for(int i=1; i<=n; i++){
		for(int j=0; j<=sz[i]; j++){
			rng[j].first = min(rng[j].first, d1[i][j]);
			rng[j].second = max(rng[j].second, d2[i][j]);
		}
	}
	int q; scanf("%d",&q);
	int dap = 0;
	while(q--){
		int i, j; scanf("%d %d",&i,&j);
		if(rng[j].first <= i && i <= rng[j].second) dap++;
	}
	printf("%d\n", dap);
}
