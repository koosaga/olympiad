#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = pair<lint, lint>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
const int MAXN = 200005;

int vis[MAXN], deg[MAXN];
vector<int> gph[MAXN];

int dfs(int x, int c){
	if(vis[x]) return 0;
	vis[x] = c;
	int ret = 1;
	for(auto &y : gph[x]){
		if(deg[y] && !vis[y]) ret += dfs(y, c);
	}
	return ret;
}

int main(){
	ios_base::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
	int n, m, d; cin >> n >> m >> d;
	for(int i = 0; i < m; i++){
		int s, e; cin >> s >> e;
		s--; e--;
		gph[s].push_back(e);
		gph[e].push_back(s);
		deg[s]++;
		deg[e]++;
	}
	queue<int> que;
	for(int i = 0; i < n; i++){
		if(deg[i] < d) que.push(i);
	}
	while(sz(que)){
		int x = que.front(); que.pop();
		for(auto &y : gph[x]){
			if(deg[y]){
				deg[y]--; deg[x]--;
				if(deg[y] == d - 1) que.push(y);
			}
		}
	}
	pi ret(0, 0);
	for(int i = 0; i < n; i++){
		if(deg[i] > 0 && !vis[i]){
			int w = dfs(i, i + 1);
			ret = max(ret, pi(w, -i - 1));
		}
	}
	if(ret.first == 0) cout << "NIE\n";
	else{
		cout << ret.first << "\n";
		for(int i = 0; i < n; i++){
			if(vis[i] == -ret.second) cout << i+1 << " ";
		}
		cout << "\n";
	}
}
