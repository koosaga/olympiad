#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef long double llf;
typedef pair<lint, lint> pi;
const int mod = 1e9 + 7;

lint val[100005], mat;

int n, k, q;
int a[100005], chk[100005];
vector<int> gph[100005];
bool vis[100005];

int aux[100005];
vector<int> dfn;

void dfs3(int x, int p){
	for(auto &i : gph[x]){
		if(i == p || vis[i]) continue;
		dfs3(i, x);
		if(aux[i]) aux[x] = 1;
	}
}

void dfs2(int x, int p, lint h, vector<pi> &v){
	h += val[a[x]];
	v.push_back(pi(h, x));
	for(auto &i : gph[x]){
		if(i == p || vis[i]) continue;
		dfs2(i, x, h, v);
	}
}

void solve(int r){
	for(auto &i : dfn) aux[i] = 0;
	set<lint> s;
	s.insert(val[a[r]]);
	for(auto &i : gph[r]){
		if(vis[i]) continue;
		vector<pi> sack;
		dfs2(i, r, val[a[r]], sack);
		for(auto &i : sack){
			if(s.find(mat - i.first + val[a[r]]) != s.end()){
				aux[i.second] = 1;
			}
		}
		for(auto &i : sack){
			s.insert(i.first);
		}
	}
	reverse(gph[r].begin(), gph[r].end());
	s.clear();
	s.insert(val[a[r]]);
	for(auto &i : gph[r]){
		if(vis[i]) continue;
		vector<pi> sack;
		dfs2(i, r, val[a[r]], sack);
		for(auto &i : sack){
			if(s.find(mat - i.first + val[a[r]]) != s.end()){
				aux[i.second] = 1;
			}
		}
		for(auto &i : sack){
			s.insert(i.first);
		}
	}
	dfs3(r, -1);
	for(auto &i : dfn) if(aux[i]) chk[i] = 1;
}

int msz[100005], sz[100005];

void dfs(int x, int p){
	dfn.push_back(x);
	msz[x] = 0;
	sz[x] = 1;
	for(auto &i : gph[x]){
		if(i == p || vis[i]) continue;
		dfs(i, x);
		msz[x] = max(msz[x], sz[i]);
		sz[x] += sz[i];
	}
}

int get_center(int x){
	dfn.clear();
	dfs(x, -1);
	int cur = 1e9, pos = -1;
	for(auto &i : dfn){
		int w = max((int)dfn.size() - sz[i], msz[i]);
		if(w < cur){
			cur = w;
			pos = i;
		}
	}
	return pos;
}

int main(){
	srand(987654321);
	scanf("%d %d %d",&n,&k,&q);
	for(int i=1; i<=k; i++){
		val[i] = (1ll << 32) * rand() + rand();
		mat += val[i];
	}
	for(int i=1; i<=n; i++) scanf("%d",&a[i]);
	for(int i=0; i<n-1; i++){
		int s, e;
		scanf("%d %d",&s,&e);
		gph[s].push_back(e);
		gph[e].push_back(s);
	}
	queue<int> que;
	que.push(1);
	while(!que.empty()){
		int x = que.front();
		que.pop();
		x = get_center(x);
		solve(x);
		vis[x] = 1;
		for(auto &i : gph[x]){
			if(!vis[i]) que.push(i);
		}
	}
	while(q--){
		int x;
		scanf("%d",&x);
		puts(chk[x] ? "YES" : "NO");
	}
}

