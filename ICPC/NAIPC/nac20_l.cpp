#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
const int MAXN = 505;
const int MAXV = 505050;
typedef long long lint;
typedef pair<int, int> pi;

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
char str[MAXN][MAXN];
int C[MAXN][MAXN][4];
vector<pi> gph[MAXV]; 
vector<pi> comp[MAXV];
int vis[MAXV], ban[MAXV][2];
int ans[MAXV];

void dfs(int x, int c){
	if(vis[x]){
		if(vis[x] != c){
			ans[0] = ans[1] = 1e9;
		}
		return;
	}
	vis[x] = c;
	ans[(c-1)] += 1;
	if(ban[x][c-1]) ans[0] = 1e9;
	if(ban[x][(c-1)^1]) ans[1] = 1e9;
	for(auto &[u, v] : gph[x]){
		if(u) dfs(v, 3-c);
		else dfs(v, c);
	}
}

int main(){
	cin >> n >> m;
	int vtx = 0;
	disj.init();
	for(int i=0; i<n; i++){
		scanf("%s", str[i]);
	}
	for(int i=0; i<=n; i++){
		for(int j=0; j<=m; j++){
			if(i < n) C[i][j][0] = ++vtx;
			if(j < m) C[i][j][1] = ++vtx;
		}
	}
	for(int i=0; i<n; i++){
		for(int j=0; j<m; j++){
			if(str[i][j] == '#') continue;
			if(str[i][j] == '.'){
				disj.uni(C[i][j][0], C[i][j+1][0]);
				disj.uni(C[i][j][1], C[i+1][j][1]);
			}
			if(str[i][j] == '/'){
				disj.uni(C[i][j][0], C[i][j][1]);
				disj.uni(C[i][j+1][0], C[i+1][j][1]);
			}
			if(str[i][j] == '\\'){
				disj.uni(C[i][j][0], C[i+1][j][1]);
				disj.uni(C[i][j+1][0], C[i][j][1]);
			}
		}
	}
	int idx = 0;
	for(int i=0; i<n; i++){
		for(int j=0; j<m; j++){
			if(str[i][j] == 'V' || str[i][j] == 'H'){
				int L = disj.find(C[i][j][0]);
				int R = disj.find(C[i][j+1][0]);
				int U = disj.find(C[i][j][1]);
				int D = disj.find(C[i+1][j][1]);
				comp[L].emplace_back(idx, (str[i][j] == 'H'));
				comp[R].emplace_back(idx, (str[i][j] == 'H'));
				comp[U].emplace_back(idx, (str[i][j] == 'V'));
				comp[D].emplace_back(idx, (str[i][j] == 'V'));
				idx++;
			}
			if(str[i][j] == '#'){
				int L = disj.find(C[i][j][0]);
				int R = disj.find(C[i][j+1][0]);
				int U = disj.find(C[i][j][1]);
				int D = disj.find(C[i+1][j][1]);
				comp[L].emplace_back(-1, -1);
				comp[R].emplace_back(-1, -1);
				comp[U].emplace_back(-1, -1);
				comp[D].emplace_back(-1, -1);
			}
		}
	}
	for(int i=0; i<=vtx; i++){
		if(sz(comp[i]) <= 1) continue;
		if(find(all(comp[i]), pi(-1, -1)) == comp[i].end()){
			int x = comp[i][0].first;
			int y = comp[i][1].first;
			int z = comp[i][0].second != comp[i][1].second;
			gph[x].emplace_back(z, y);
			gph[y].emplace_back(z, x);
		}
		else{
			comp[i].erase(find(all(comp[i]), pi(-1, -1)));
			if(comp[i][0] == pi(-1, -1)) continue;
			ban[comp[i][0].first][comp[i][0].second] = 1;
		}
	}
	int ret = 0;
	for(int i=0; i<vtx; i++){
		if(!vis[i]){
			ans[0] = ans[1] = 0;
			dfs(i, 1);
			ret += min(ans[0], ans[1]);
			if(ret > 1e7) break;
		}
	}
	if(ret > 1e7) ret = -1;
	cout << ret << endl;

}
