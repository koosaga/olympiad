#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef long double llf;
typedef pair<lint, lint> pi;

int n, a[100005], dfn[100005], dfo[100005];
vector<int> gph[100005];

struct seg{
	vector<int> tree[270000];
	int lim;
	void init(int n){
		for(lim = 1; lim <= n; lim <<= 1);
		vector<pi> v;
		for(int i=1; i<=n; i++) v.push_back(pi(a[i], dfn[i]));
		sort(v.begin(), v.end());
		for(auto &i : v){
			for(int j=i.second+lim; j; j/=2){
				tree[j].push_back(i.first);
			}
		}
	}
	int query(int s, int e, int x){
		auto cnt = [&](const int &n, const int &x){
			return tree[n].end() - upper_bound(tree[n].begin(), tree[n].end(), x);
		};
		s += lim;
		e += lim;
		int ret = 0;
		while(s < e){
			if(s%2 == 1) ret += cnt(s++, x);
			if(e%2 == 0) ret += cnt(e--, x);
			s >>= 1;
			e >>= 1;
		}
		if(s == e) ret += cnt(s, x);
		return ret;
	}
}seg;

int piv;

void dfs(int x){
	dfn[x] = ++piv;
	for(auto &i : gph[x]){
		dfs(i);
	}
	dfo[x] = piv;
}

int main(){
	freopen("promote.in", "r", stdin);
	freopen("promote.out", "w", stdout);
	scanf("%d",&n);
	for(int i=1; i<=n; i++) scanf("%d",&a[i]);
	for(int i=2; i<=n; i++){
		int x;
		scanf("%d",&x);
		gph[x].push_back(i);
	}
	dfs(1);
	seg.init(n);
	for(int i=1; i<=n; i++){
		printf("%d\n", seg.query(dfn[i], dfo[i], a[i]));
	}
}
