#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using lint = long long;
using pi = pair<lint, lint>;
const int MAXN = 300005;

int n, a[MAXN];
vector<pi> gph[MAXN];

lint dfs(int x, int p){
	lint needy = 0;
	vector<lint> up;
	for(auto &[u, v] : gph[x]){
		if(v != p){
			auto sol = dfs(v, x);
			if(sol < 0){
				if(sol < -u) return -1e18;
				needy += sol;
			}
			else{
				up.push_back(min(sol, u));
			}
		}
	}
	if(a[x] < 0){
		needy += a[x];
		if(sz(up)){
			lint mxv = *max_element(all(up));
			if(mxv + needy >= 0) needy += mxv;
		}
		return needy;
	}
	else{
		needy += a[x];
		if(needy < 0) return -1e18;
		return needy;
	}
}

int main(){
	scanf("%d",&n);
	for(int i=1; i<=n; i++){
		int x, y; scanf("%d %d",&x,&y);
		if(x == 1) y = -y;
		a[i] = y;
	}
	for(int i=0; i<n-1; i++){
		int s, e, x; scanf("%d %d %d",&s,&e,&x);
		gph[s].emplace_back(x, e);
		gph[e].emplace_back(x, s);
	}
	if(dfs(1, 0) < 0) puts("0");
	else puts("1");
}
