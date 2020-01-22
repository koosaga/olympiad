#include<bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using lint = long long;
using pi = pair<int, int>;
const int MAXN = 1005;
const int MAXV = 500005;
const int mod = 1e9 + 7;

struct disj{
	int pa[MAXV];
	void init(int n){
		iota(pa, pa + n + 1, 0);
	}
	int find(int x){
		return pa[x] = (pa[x] == x ? x : find(pa[x]));
	}
	bool uni(int p, int q){
		p = find(p); q = find(q);
		if(p == q) return 0;
		pa[q] = p; return 1;
	}
}disj, disj2;

int n, m, vtx;
char str[MAXN][MAXN];
int idx[MAXN][MAXN];
vector<int> gph[MAXV]; 
int indeg[MAXV];

bool vis[MAXV];
int dfs(int x){
	assert(!vis[x]);
	vis[x] = 1;
	lint ret = 1;
	sort(all(gph[x]));
	gph[x].resize(unique(all(gph[x])) - gph[x].begin());
	for(auto &i : gph[x]){
		ret = ret * dfs(i) % mod;
	}
	return (ret + 1) % mod;
}

int main(){
	freopen("cave.in", "r", stdin);
	freopen("cave.out", "w", stdout);
	scanf("%d %d",&n,&m);
	for(int i=0; i<n; i++) scanf("%s", str[i]);
	for(int i=0; i<n; i++){
		for(int j=0; j<m; j++){
			if(str[i][j] == '.'){
				int e = j;
				while(e < m && str[i][e] == '.') e++;
				vtx++;
				for(int k=j; k<e; k++){
					idx[i][k] = vtx;
				}
				j = e - 1;
			}
		}
	}
	disj2.init(vtx);
	disj.init(vtx);
	for(int i=n-2; i>=0; i--){
		for(int j=0; j<m; j++){
			if(idx[i][j] && idx[i+1][j]) disj2.uni(idx[i][j], idx[i+1][j]);
		}
		vector<pi> v;
		for(int j=1; j<m; j++){
			if(idx[i][j] == 0) continue;
			if(idx[i][j-1] && idx[i][j]) continue;
			v.emplace_back(i, j);
		}
		sort(all(v), [&](const pi &a, const pi &b){
			int p1 = disj2.find(idx[a.first][a.second]);
			int p2 = disj2.find(idx[b.first][b.second]);
			return p1 < p2;
		});
		for(int i=1; i<sz(v); i++){
			int l = idx[v[i].first][v[i].second];
			int r = idx[v[i-1].first][v[i-1].second];
			if(disj2.find(l) == disj2.find(r)) disj.uni(l, r);
		}
	}
	for(int i=0; i+1<n; i++){
		for(int j=0; j<m; j++){
			if(idx[i][j] && idx[i+1][j]){
				int l = disj.find(idx[i][j]);
				int r = disj.find(idx[i + 1][j]);
				gph[l].push_back(r);
				indeg[r] = 1;
			}
		}
	}
	lint ret = 1;
	for(int i=1; i<=vtx; i++){
		if(!indeg[i] && disj.find(i) == i){
			ret *= dfs(i);
			ret %= mod;
		}
	}
	cout << ret << endl;
}
