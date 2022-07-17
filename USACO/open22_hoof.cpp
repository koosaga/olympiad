#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using lint = long long;
using pi = pair<lint, lint>;
const int MAXN = 100005;

set<int> gph[MAXN], rev[MAXN];
int pa[MAXN];

int find(int x){
	return pa[x] = (pa[x] == x ? x : find(pa[x]));
}

int main(){
	ios_base::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
	int n, m; cin >> n >> m;
	for(int i = 0; i < m; i++){
		int s, e; cin >> s >> e;
		gph[s].insert(e);
		rev[e].insert(s);
	}
	queue<int> que;
	for(int i = 1; i <= n; i++){
		pa[i] = i;
		if(sz(gph[i]) <= 1){
			que.push(i);
		}
	}
	while(sz(que)){
		int x = que.front(); que.pop();
		if(sz(gph[x]) == 0){
			for(auto &y : rev[x]){
				gph[y].erase(x);
				if(sz(gph[y]) <= 1) que.push(y);
			}
			rev[x].clear();
		}
		if(sz(gph[x]) == 1){
			int y = *gph[x].begin();
			if(x == y) continue;
			gph[x].clear();
			rev[y].erase(x);
			if(sz(gph[x]) + sz(rev[x]) > sz(gph[y]) + sz(rev[y])) swap(x, y);
			for(auto &j : gph[x]){
				if(j == x){
					gph[y].insert(y);
					continue;
				}
				rev[j].erase(x);
				rev[j].insert(y);
				gph[y].insert(j);
			}
			for(auto &j : rev[x]){
				if(j == x){
					rev[y].insert(y);
					continue;
				}
				gph[j].erase(x);
				rev[y].insert(j);
				gph[j].insert(y);
				if(sz(gph[j]) <= 1) que.push(j);
			}
            if(sz(gph[y]) <= 1) que.push(y);
			gph[x].clear();
			rev[x].clear();
			pa[x] = y;
		}
	}
	int q; cin >> q;
	while(q--){
		int x, y; cin >> x >> y;
		x = find(x);
		y = find(y);
		if(x == y || sz(gph[x]) == 0 || sz(gph[y]) == 0) cout << "B";
		else cout << "H";
	}
}
