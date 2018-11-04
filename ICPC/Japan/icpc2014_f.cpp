#include <bits/stdc++.h>
using namespace std;
using pi = pair<int, int>;
const int MAXN = 505;
const int MAXE = 50005;

struct disj{
	int pa[MAXN];
	void init(int n){
		iota(pa, pa + n + 1, 0);
	}
	int find(int x){
		return pa[x] = (pa[x] == x ? x : find(pa[x]));
	}
	bool uni(int p, int q){
		p = find(p); q = find(q);
		if(p == q) return 0;
		pa[q] = p; return 1;
	}
}disj;

struct edg{
	int s, e, x;
	bool operator<(const edg &e)const{
		return x < e.x;
	}
}e[MAXE];

int n, m;
int dfn[MAXN], low[MAXN], piv;

	vector<pi> gph[MAXN];

int dfs(int x, int p){
	int ret = 0;
	dfn[x] = low[x] = ++piv;
	for(auto &i : gph[x]){
		if(i.first == p) continue;
		if(!dfn[i.second]){
			ret += dfs(i.second, i.first);
			low[x] = min(low[x], low[i.second]);
			if(low[i.second] > dfn[x]) ret++;
		}
		else low[x] = min(low[x], dfn[i.second]);
	}
	return ret;
}

int countBridge(vector<pi> v){
	for(int i=0; i<MAXN; i++) gph[i].clear();
	piv = 0;
	memset(dfn, 0, sizeof(dfn));
	memset(low, 0, sizeof(low));
	int ed = 0;
	for(auto &i : v){
		ed++;
		gph[i.first].push_back(pi(ed, i.second));
		gph[i.second].push_back(pi(ed, i.first));
	}
	int ans = 0;
	for(int i=1; i<=n; i++){
		if(!dfn[i]){
			ans += dfs(i, 0);
		}
	}
	return ans;
}

int main(){
	scanf("%d %d",&n,&m);
	for(int i=0; i<m; i++){
		scanf("%d %d %d",&e[i].s,&e[i].e,&e[i].x);
	}
	sort(e, e+m);
	disj.init(n);
	int ans1 = 0, ans2 = 0;
	for(int i=0; i<m; ){
		int j = i;
		while(j < m && e[j].x == e[i].x) j++;
		vector<pi> v;
		for(int k=i; k<j; k++){
			if(disj.find(e[k].s) != disj.find(e[k].e)){
				int l = disj.find(e[k].s);
				int r = disj.find(e[k].e);
				v.emplace_back(l, r);
			}
		}
		int w = countBridge(v);
		ans1 += w;
		ans2 += e[i].x * w;
		for(int k=i; k<j; k++){
			disj.uni(e[k].s, e[k].e);
		}
		i = j;
	}
	cout << ans1 << " " << ans2 << endl;
}
