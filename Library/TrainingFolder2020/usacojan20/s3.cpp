#include<bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using lint = long long;
using pi = pair<int, int>;
const int MAXN = 100005;

struct disj{
	int pa[MAXN];
	void init(int n){
		iota(pa, pa + n + 1, 0);
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

struct edg{
	int s, e, x;
	bool operator<(const edg &e)const{
		return x > e.x;
	}
}e[MAXN];

int n, m, p[MAXN];
vector<pi> gph[MAXN];
int din[MAXN], dout[MAXN], piv;
int pae[MAXN], valmi[MAXN], valma[MAXN];
int ans = 2e9;

void dfs(int x, int p){
	din[x] = piv++;
	for(auto &i : gph[x]){
		if(i.second == p) continue;
		pae[i.second] = i.first;
		dfs(i.second, x);
	}
	dout[x] = piv;
}

void dfs2(int x, int par){
	valmi[x] = din[p[x]];
	valma[x] = din[p[x]] + 1;
	for(auto &i : gph[x]){
		if(i.second == par) continue;
		dfs2(i.second, x);
		valmi[x] = min(valmi[x], valmi[i.second]);
		valma[x] = max(valma[x], valma[i.second]);
	}
	if(valmi[x] != din[x] || valma[x] != dout[x]){
		ans = min(ans, pae[x]);
	}
}

int main(){
	freopen("wormsort.in", "r", stdin);
	freopen("wormsort.out", "w", stdout);
	pae[1] = 2e9;
	scanf("%d %d",&n,&m);
	for(int i=1; i<=n; i++){
		scanf("%d",&p[i]);
	}
	for(int i=0; i<m; i++){
		scanf("%d %d %d",&e[i].s,&e[i].e,&e[i].x);
	}
	sort(e, e + m);
	disj.init(n);
	for(int i=0; i<m; i++){
		if(disj.uni(e[i].s, e[i].e)){
			gph[e[i].s].emplace_back(e[i].x, e[i].e);
			gph[e[i].e].emplace_back(e[i].x, e[i].s);
		}
	}
	for(int i=2; i<=n; i++){
		if(disj.uni(i-1, i)){
			gph[i-1].emplace_back(2e9, i);
			gph[i].emplace_back(2e9, i-1);
		}
	}
	ans = 2e9;
	dfs(1, 0);
	dfs2(1, 0);
	if(ans > 1e9 + 6969) ans = -1;
	cout << ans << endl;
}
