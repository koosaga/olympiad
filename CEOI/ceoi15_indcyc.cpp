#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<int, int> pi;

int n, m;
int adj[1005][1005], edg[1005][1005];
int s[100005], e[100005];

int vis[100005], instk[100005], par[100005];
vector<int> edgs;

void dfs(int x, int y, int e){
	vis[e] = instk[e] = 1;
	for(int i=1; i<=n; i++){
		if(adj[x][i]) continue;
		if(adj[y][i]){
			int eno = edg[y][i];
			if(eno != e && instk[eno] && edgs.empty()){
				for(int i=e; i!=eno; i=par[i]){
					edgs.push_back(i);
				}
				edgs.push_back(eno);
			}
			if(!vis[eno]){
				par[eno] = e;
				dfs(y, i, eno);
			}
		}
	}
	instk[e] = 0;
}

void solve(){
	vector<int> vert;
	for(int i=0; i<edgs.size(); i++){
		int l = edgs[i], r = edgs[(i+1)%edgs.size()];
		auto x = pi(s[l], e[l]);
		auto y = pi(s[r], e[r]);
		if(x.first == y.first || x.first == y.second){
			vert.push_back(x.first);
		}
		else{
			vert.push_back(x.second);
		}
	}
	for(int i=0; i<vert.size(); i++){
		for(int j=0; j<i-1; j++){
			if(adj[vert[i]][vert[j]]){
				if(i == vert.size() - 1 && j == 0){
					continue;
				}
				for(int k=j; k<=i; k++){
					printf("%d ", vert[k]);
				}
				return;
			}
		}
	}
	for(auto &i : vert){
		printf("%d ", i);
	}
}

int main(){
	scanf("%d %d",&n,&m);
	for(int i=0; i<m; i++){
		scanf("%d %d",&s[i],&e[i]);
		edg[s[i]][e[i]] = edg[e[i]][s[i]] = i;
		adj[s[i]][e[i]] = adj[e[i]][s[i]] = 1;
	}
	for(int i=0; i<m; i++){
		if(!vis[i]){
			dfs(s[i], e[i], i);
			if(!edgs.empty()){
				solve();
				return 0;
			}
		}
	}
	puts("no");
}