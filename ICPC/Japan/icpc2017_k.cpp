#include <bits/stdc++.h>
using namespace std;
const int MAXN = 100005;
using lint = long long;
using pi = pair<int, int>;

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

vector<int> idx;
vector<pi> bed;
int parC[66];
int cnt[66];

bool solve(int msk){
	int n = idx.size();
	memset(cnt, 0, sizeof(cnt));
	vector<pi> ed;
	for(int i=0; i<bed.size(); i++){
		if((msk >> i) & 1){
			cnt[bed[i].first]++;
			cnt[bed[i].second]++;
			ed.emplace_back(bed[i].first, bed[i].second);
		}
	}
	for(int i=n-1; i; i--){
		cnt[parC[i]] += cnt[i];
		if(cnt[i] & 1){
			ed.emplace_back(parC[i], i);
		}
	}
	disj.init(n);
	memset(cnt, 0, sizeof(cnt));
	int ret = 0;
	for(auto &i : ed){
		ret += disj.uni(i.first, i.second);
		cnt[i.first]++;
		cnt[i.second]++;
	}
	if(*max_element(cnt, cnt + n) > 2) return false;
	if(ret != ed.size() - 1) return false;
	return true;
}

int n, m;
vector<int> gph[MAXN];
int din[MAXN], dout[MAXN], par[17][MAXN], dep[MAXN], piv;

bool in(int s, int t){
	return din[s] <= din[t] && dout[t] <= dout[s];
}

int lca(int s, int e){
	if(dep[s] > dep[e]) swap(s, e);
	int dx = dep[e] - dep[s];
	for(int i=0; i<17; i++){
		if((dx >> i) & 1) e = par[i][e];
	}
	for(int i=16; i>=0; i--){
		if(par[i][s] != par[i][e]){
			s = par[i][s];
			e = par[i][e];
		}
	}
	if(s != e) return par[0][s];
	return s;
}

void dfs(int x, int p){
	din[x] = piv++;
	for(auto &i : gph[x]){
		if(i != p){
			dep[i] = dep[x] + 1;
			par[0][i] = x;
			dfs(i, x);
		}
	}
	dout[x] = piv;
}

int main(){
	scanf("%d %d",&n,&m);
	disj.init(n);
	for(int i=0; i<m; i++){
		int s, e; scanf("%d %d",&s,&e);
		if(disj.uni(s, e)){
			gph[s].push_back(e);
			gph[e].push_back(s);
		}
		else bed.emplace_back(s, e);
	}
	dfs(1, 0);
	for(int i=1; i<17; i++){
		for(int j=1; j<=n; j++) par[i][j] = par[i-1][par[i-1][j]];
	}
	for(auto &i : bed) idx.push_back(i.first), idx.push_back(i.second);
	sort(idx.begin(), idx.end(), [&](const int &a, const int &b){
		return din[a] < din[b];
	});
	{
		int tmp = idx.size();
		for(int i=1; i<tmp; i++) idx.push_back(lca(idx[i-1], idx[i]));
		sort(idx.begin(), idx.end(), [&](const int &a, const int &b){
			return din[a] < din[b];
		});
		idx.resize(unique(idx.begin(), idx.end()) - idx.begin());
	}
	vector<int> stk;
	for(int i=0; i<idx.size(); i++){
		while(!stk.empty() && in(idx[stk.back()], idx[i]) == 0) stk.pop_back();
		if(i != 0) parC[i] = stk.back();
		stk.push_back(i);
	}
	for(auto &i : bed){
		i.first = find(idx.begin(), idx.end(), i.first) - idx.begin();
		i.second = find(idx.begin(), idx.end(), i.second) - idx.begin();
	}
	int ret = 0;
	for(int i=1; i<(1<<bed.size()); i++){
		if(solve(i)) ret++;
	}
	cout << ret << endl;
}
