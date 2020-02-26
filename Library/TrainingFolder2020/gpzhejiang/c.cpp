#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using pi = pair<lint, lint>;
using lint = long long;
const int MAXN = 200005;

struct slope{
	map<lint, lint> pq;
	lint st_slope;
	void clear(){
		st_slope = 0;
		pq.clear();
	}
	void up(int x){
		st_slope += x;
		pq[k / 2] -= x;
		pq[(k + 1) / 2] -= x;
	}
	void merge(slope &s){
		st_slope += s.st_slope;
	}
}

int n, k;
vector<pi> gph[MAXN];
int sz[MAXN];

void dfs(int x, int p){
	sz[x] = 1;
	for(auto &[w, v] : gph[x]){
		gph[v].erase(find(all(gph[v]), pi(w, x)));
		dfs(v, x);
		sz[x] += sz[v];
	}
}

int main(){
	int tc; scanf("%d",&tc);
	while(tc--){
		scanf("%d %d",&n,&k);
		for(int i=0; i<n-1; i++){
			int s, e, x; scanf("%d %d %d",&s,&e,&x);
			gph[s].emplace_back(x, e);
			gph[e].emplace_back(x, s);
		}
		dfs(1, 0);
		clear();
	}
}
