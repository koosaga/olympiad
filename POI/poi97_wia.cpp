#include <bits/stdc++.h>
using namespace std;
typedef pair<int,int> pi;
const int MAXN = 3005;

int n, m;
vector<int> gph[MAXN];
vector<int> bad[MAXN];
bool vis[MAXN], chk[MAXN];

void dfs(int x){
	if(vis[x]) return;
	vis[x] = 1;
	for(auto &i : gph[x]) dfs(i);
}

int main(){
	scanf("%d %d",&n,&m);
	for(int i=0; i<m; i++){
		int s, e; scanf("%d %d",&s,&e);
		if(e > 0) gph[s].push_back(e);
		else bad[s].push_back(-e);
	}
	bool nikt = 1;
	for(int i=1; i<=n; i++){
		dfs(i);
		bool ins = 0;
		for(int j=1; j<=n; j++){
			if(vis[j]) for(auto &k : bad[j]) chk[k] = 1;
		}
		for(int j=1; j<=n; j++){
			if(vis[j] && chk[j]){
				ins = 1;
				nikt = 0;
			}
			vis[j] = chk[j] = 0;
		}
		if(ins) printf("%d\n", i);
	}
	if(nikt) puts("NIKT");
}

