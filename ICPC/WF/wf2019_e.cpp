#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = pair<lint, lint>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
const int MAXN = 500005;
const int mod = 1e9 + 7;

vector<int> gph[MAXN];
vector<int> tree[MAXN];
vector<pi> soln;
int deg[MAXN], vis[MAXN];

void dfs(int x, int p){
	vis[x] = 1;
	for(auto &y : tree[x]) if(y != p) dfs(y, x);
}

int main(){
	ios_base::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
	int n, m;
	cin >> n >> m;
	for(int i = 0; i < m; i++){
		int s, e; cin >> s >> e;
		deg[s]++;
		deg[e]++;
		gph[s].push_back(e);
		gph[e].push_back(s);
	}
	queue<int> que;
	for(int i = 1; i <= n; i++){
		if(deg[i] == 1){
			que.push(i);
		}
	}
	while(sz(que)){
		int x = que.front(); que.pop();
		for(auto &y : gph[x]){
			if(deg[y]){
				tree[x].push_back(y);
				tree[y].push_back(x);
				deg[x]--;
				deg[y]--;
				if(deg[y] == 1){
					que.push(y);
				}
			}
		}
	}
	for(int i = 1; i <= n; i++){
		if(deg[i] > 1 && sz(tree[i])){
			for(auto &j : tree[i]) soln.emplace_back(i, j);
			dfs(i, -1);
		}
	}
	for(int i = 1; i <= n; i++){
		if(!vis[i] && sz(tree[i]) == 1) soln.emplace_back(i, tree[i][0]);
	}
	sort(all(soln));
	cout << sz(soln) << "\n";
	for(auto &[x, y] : soln) cout << x << " " << y << "\n";
}
