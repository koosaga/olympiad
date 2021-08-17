#include "chameleon.h"
#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
typedef long long lint;
typedef pair<lint, lint> pi;

namespace {
	const int MAXN = 1005;
	vector<int> gph[MAXN];
	int col[MAXN], vis[MAXN];
	void dfs(int x, int c){
		if(vis[x]) return;
		vis[x] = 1;
		col[x] = c;
		for(auto &i : gph[x]) dfs(i, 3 - c);
	}
} 

void Solve(int N) {
	for(int i = 1; i <= 2*N; i++){
		vector<int> v[2];
		for(int j = 1; j < i; j++){
			v[col[j] - 1].push_back(j);
		}
		for(int j = 0; j < 2; j++){
			auto q = [&](int s, int e){
				if(s == e) return 1;
				vector<int> foo(v[j].begin() + s, v[j].begin() + e);
				foo.push_back(i);
				return Query(foo);
			};
			int prv = 0;
			while(q(prv, sz(v[j])) != sz(v[j]) - prv + 1){
				int s = prv, e = sz(v[j]);
				while(s != e){
					int m = (s+e)/2;
					if(q(prv, m) != m - prv + 1) e = m;
					else s = m + 1;
				}
				assert(s != prv);
				gph[v[j][s-1]].push_back(i);
				gph[i].push_back(v[j][s-1]);
				prv = s;
			}
		}
		memset(vis, 0, sizeof(vis));
		dfs(i, 1);
	}
	vector<int> nxt(2*N+1, -1);
	for(int i = 1; i <= 2*N; i++){
		if(sz(gph[i]) == 1) continue;
		assert(sz(gph[i]) == 3);
		for(int j = 0; j < 3; j++){
			int q = Query({i, gph[i][(j+1)%3], gph[i][(j+2)%3]});
			if(q == 1){
				assert(nxt[i] == -1);
				nxt[i] = gph[i][j];
			}
		}
	}
	for(int i = 1; i <= 2*N; i++){
		if(~nxt[i]){
			int j = nxt[i];
			gph[i].erase(find(all(gph[i]), j));
			gph[j].erase(find(all(gph[j]), i));
		}
	}
	for (int i = 1; i <= 2*N; ++i) {
		if(gph[i][0] > i) Answer(i, gph[i][0]);
	}
}
