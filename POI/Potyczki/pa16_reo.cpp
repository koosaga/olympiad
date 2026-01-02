#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<int, int> pi;

int n, m;
int inh[1005], outl[1005], ans[1005];
int vis[1005];
vector<int> gph[1005];

void my_assert(bool p){
	if(!p){
		puts("NIE");
		exit(0);
	}
}

void dfs(int x, int c){
	if(vis[x]) return;
	vis[x] = c;
	for(auto &i : gph[x]) dfs(i, c);
}

void solve(int root, vector<int> v, vector<pi> edgl, vector<pi> edgh){
	for(auto &i : v){
		vis[i] = 0;
		gph[i].clear();
	}
	memset(outl, 0, sizeof(outl));
	memset(inh, 0, sizeof(inh));
	for(auto &i : edgl){
		outl[i.second]++;
	}
	for(auto &i : edgh){
		inh[i.first]++;
	}
	int cr = -1;
	for(auto &i : v){
		if(!outl[i] && !inh[i]){
			cr = i;
			break;
		}
	}
	my_assert(cr != -1);
	ans[cr] = root;
	for(auto &i : edgl){
		if(i.first == cr || i.second == cr) continue;
		gph[i.first].push_back(i.second);
		gph[i.second].push_back(i.first);
	}
	int p = 0;
	for(auto &i : v){
		if(i == cr) continue;
		if(!vis[i]){
			dfs(i, ++p);
		}
	}
	vector<vector<pi>> edgls(p), edghs(p);
	vector<vector<int>> vtx(p);
	for(auto &i : v){
		if(vis[i]) vtx[vis[i]-1].push_back(i);
	}
	for(auto &i : edgl){
		if(vis[i.first] == vis[i.second]){
			edgls[vis[i.first]-1].push_back(i);
		}
	}
	for(auto &i : edgh){
		if(vis[i.first] == vis[i.second]){
			edghs[vis[i.first]-1].push_back(i);
		}
	}
	for(int i=0; i<p; i++){
		solve(cr, vtx[i], edgls[i], edghs[i]);
	}
}


int main(){
	cin >> n >> m;
	vector<pi> edgl, edgh;
	for(int i=1; i<=m; i++){
		int s, e;
		char t[5];
		scanf("%d %d %s",&e,&s,t);
		if(*t != 'T') edgh.push_back(pi(s, e));
		else edgl.push_back(pi(s, e));
	}
	vector<int> comp;
	for(int i=1; i<=n; i++) comp.push_back(i);
	solve(0, comp, edgl, edgh);
	for(int i=1; i<=n; i++){
		printf("%d\n", ans[i]);
	}
}