#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = pair<int, int>;
const int MAXN = 10005;

int n, m;
pi a[MAXN];

vector<int> drog[MAXN];
vector<int> gph[MAXN];

int ccw(pi a, pi b, pi c){
	int dx1 = b.first - a.first;
	int dy1 = b.second - a.second;
	int dx2 = c.first - a.first;
	int dy2 = c.second - a.second;
	return dx1 * dy2 - dy1 * dx2;
}

int col[MAXN], vis[MAXN];
vector<int> dfn;

void dfs(int x, int cur, int nxt){
	if(vis[x]) return;
	dfn.push_back(x);
	vis[x] = 1;
	for(auto &i : gph[x]){
		if(col[i] == nxt){
			dfs(i, nxt, cur);
		}
	}
}

int main(){
	scanf("%d %d",&n,&m);
	for(int i=0; i<n; i++){
		scanf("%d %d",&a[i].first,&a[i].second);
	}
	for(int i=0; i<m; i++){
		int u, v; scanf("%d %d",&u,&v);
		u--; v--;
		if(a[u] >= a[v]) swap(u, v);
		drog[v].push_back(u);
	}
	vector<int> ord(n);
	iota(ord.begin(), ord.end(), 0);
	sort(ord.begin(), ord.end(), [&](const int &p, const int &q){
		return a[p] < a[q];
	});
	for(int i=0; i<n; i++){
		sort(drog[i].begin(), drog[i].end(), [&](const int &p, const int &q){
			return ccw(a[i], a[p], a[q]) > 0;
		});
	}
	auto insert_graph = [&](int x){
		for(auto &i : drog[x]){
			gph[i].push_back(x);
			gph[x].push_back(i);
		}
	};
	for(auto &i : ord){
		auto assign = [&]{
			int chk[5] = {};
			for(auto &j : drog[i]){
				chk[col[j]] = 1;
			}
			for(int j=1; j<=4; j++){
				if(!chk[j]){
					col[i] = j;
					return j;
				}
			}
			return 0;
		};
		if(assign()){
			insert_graph(i);
			continue;
		}
		// stop! kempe time
		assert(drog[i].size() == 4);
		for(int j=0; j<4; j++){
			int rev = j ^ 2;
			memset(vis, 0, sizeof(vis));
			dfn.clear();
			dfs(drog[i][j], col[drog[i][j]], col[drog[i][rev]]);
			if(!vis[drog[i][rev]]){
				int sum = col[drog[i][j]] + col[drog[i][rev]];
				for(auto &i : dfn){
					col[i] = sum - col[i];
				}
				break;
			}
		}
		assert(assign());
		insert_graph(i);
	}
	for(int i=0; i<n; i++){
		printf("%d\n", col[i]);
	}
}
