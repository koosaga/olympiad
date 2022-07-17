#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = pair<lint, lint>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
const int MAXN = 250005;
vector<int> gph[MAXN];
int n, q, dep[MAXN], chk[MAXN], par[MAXN], cnt[MAXN];

void dfs(int x){
	for(auto &y : gph[x]){
		if(y == par[x]) continue;
		dep[y] = dep[x] + 1;
		par[y] = x;
		dfs(y);
	}
}

int main(){
	ios_base::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
	cin >> n;
	for(int i = 1; i < n; i++){
		int u, v; cin >> u >> v;
		gph[u].push_back(v);
		gph[v].push_back(u);
	}
	dfs(1);
	cin >> q;
	while(q--){
		int k; cin >> k;
		vector<int> v(k);
		for(auto &w : v) cin >> w;
		sort(all(v), [&](int a, int b){
			return dep[a] < dep[b];
		});
		lint ret = 0;
		for(auto &i : v){
			chk[i] = (chk[par[i]] ? chk[par[i]] : i);
			ret += cnt[chk[i]];
			cnt[chk[i]]++;
		}
		for(auto &w : v) chk[w] = cnt[w] = 0;
		cout << ret << "\n";
	}
}
