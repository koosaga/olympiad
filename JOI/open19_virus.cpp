#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using lint = long long;
using pi = pair<int, int>;
const int MAXV = 1300000;

struct disj{
	int pa[MAXV];
	void init(){
		iota(pa, pa + MAXV, 0);
	}
	int find(int x){
		return pa[x] = (pa[x] == x ? x : find(pa[x]));
	}
	bool uni(int p, int q){
		p = find(p);
		q = find(q);
		if(p == q) return 0;
		pa[q] = p; return 1;
	}
}disj;

int n, m;
int V;
bool good[MAXV][16];
int pa[MAXV], nxt[MAXV], sz[MAXV];
unordered_map<int, char> nei[MAXV / 2];
vector<int> justVisit[MAXV / 2];
int idx[MAXV];

int find(int x){
	return pa[x] = (pa[x] == x ? x : find(pa[x]));
}

int find_next(int x){
	while(sz(justVisit[idx[x]]) && find(justVisit[idx[x]].back()) == x){
		justVisit[idx[x]].pop_back();
	}
	if(sz(justVisit[idx[x]]) == 0) return x;
	return justVisit[idx[x]].back();
}

void merge_to(int u, int v){
	u = find(u);
	if(u == v) return;
	pa[u] = v;
	int iu = idx[u], iv = idx[v];
	if(sz[u] > sz[v]) swap(iu, iv);
	sz[v] += sz[u];
	idx[v] = iv;
	if(iu >= MAXV / 2 || iv >= MAXV / 2) return;
	{
		for(auto &i : justVisit[iu]) justVisit[iv].push_back(i);
	}
	{
		vector<int> toKill;
		for(auto &[x, y] : nei[iu]){
			if(nei[iv].find(x) == nei[iv].end()){
				nei[iv][x] = y;
				continue;
			}
			else{
				nei[iv][x] |= y;
				if(good[x][nei[iv][x]]){
					toKill.push_back(x);
				}
			}
		}
		for(auto &x : toKill){
			nei[iv].erase(x);
			justVisit[iv].push_back(x);
		}
	}
	justVisit[iu].clear();
	justVisit[iu].shrink_to_fit();
	nei[iu].clear();
}

void solve(){
	disj.init();
	iota(pa, pa + MAXV, 0);
	fill(sz, sz + V, 1);
	iota(idx, idx + MAXV, 0);
	for(int i = 0; i < V; i++){
		nxt[i] = find_next(i);
	}
	int curV = V;
	for(int i = 0; i < V; i++){
		if(find(i) != i) continue;
		if(i == find(nxt[i])) continue;
		if(!disj.uni(i, nxt[i])){
			for(int j = find(nxt[i]); find(j) != find(V); j = find(nxt[j])){
				merge_to(j, V);
			}
			disj.uni(i, V);
			nxt[V] = find_next(V);
			V++;
		}
	}
	int dap = 1e9;
	int cnt = 0;
	for(int i = 0; i < curV; i++){
		int r = find(i);
		if(find(r) == find(nxt[r])){
			if(dap > sz[r]){
				dap = sz[r];
				cnt = 0;
			}
			if(dap == sz[r]) cnt++;
		}
	}
	printf("%d\n%d\n", dap, cnt);
}

const int MAXN = 808;
const int dx[4] = {1, 0, -1, 0};
const int dy[4] = {0, 1, 0, -1};
char buf[200005];
int mp[256];

int main(){
	int idx[MAXN][MAXN] = {};
	int dead[MAXN][MAXN] = {};

	mp['N'] = 0;
	mp['W'] = 1;
	mp['S'] = 2;
	mp['E'] = 3;
	int k;
	scanf("%d %d %d",&k,&n,&m);
	scanf("%s", buf);
	for(int i=0; i<k; i++){
		buf[i + k] = buf[i];
	}
	k <<= 1;
	int maxt[16] = {};
	for(int i=0; i<16; i++){
		int cnt = 0;
		for(int j=0; j<k; j++){
			if((i >> mp[buf[j]]) & 1){
				cnt++;
				maxt[i] = max(maxt[i], cnt);
			}
			else{
				cnt = 0;
			}
		}
		if(maxt[i] == k) maxt[i] = 1e9;
	}
	for(int i=0; i<n; i++){
		for(int j=0; j<m; j++){
			int x; scanf("%d",&x);
			if(x == 0){
				dead[i][j] = 1;
				continue;
			}
			idx[i][j] = V;
			for(int k=0; k<16; k++){
				if(x <= maxt[k]) good[V][k] = 1;
			}
			V++;
		}
	}
	auto ok = [&](int x, int y){
		return x >= 0 && x < n && y >= 0 && y < m && !dead[x][y];
	};
	for(int i = 0; i < n; i++){
		for(int j = 0; j < m; j++){
			if(!ok(i, j)) continue;
			for(int k = 0; k < 4; k++){
				if(ok(i + dx[k], j + dy[k])){
					pi v(idx[i + dx[k]][j + dy[k]], 1 << k);
					if(good[v.first][v.second]) justVisit[idx[i][j]].push_back(v.first);
					else nei[idx[i][j]].insert(v);
				}
			}
		}
	}
	solve();
}
