#include <bits/stdc++.h>
using namespace std;
using pi = pair<int, int>;
using lint = long long;
#define sz(v) int((v).size())
const int MAXN = 200005;

int n, m;
vector<int> gph[MAXN], ord;
vector<pi> v[MAXN];
int dep[MAXN], par[18][MAXN], sz[MAXN];
int din[MAXN], dout[MAXN], piv;
int dx[MAXN];

bool son(int x, int y){
	return din[x] <= din[y] && dout[y] <= dout[x];
}

void dfs(int x, int p){
	din[x] = ++piv;
	ord.push_back(x);
	for(auto &i : gph[x]){
		if(i != p){
			par[0][i] = x;
			dep[i] = dep[x] + 1;
			dfs(i, x);
		}
	}
	dout[x] = piv;
}

int anc(int v, int k){
	for(int i=0; i<18; i++){
		if((k >> i) & 1) v = par[i][v];
	}
	return v;
}

int lca(int x, int y){
	if(dep[x] > dep[y]) swap(x, y);
	y = anc(y, dep[y] - dep[x]);
	for(int i=17; i>=0; i--){
		if(par[i][x] != par[i][y]){
			x = par[i][x];
			y = par[i][y];
		}
	}
	if(x != y) return par[0][x];
	return x;
}

struct bit{
	int tree[MAXN];
	void add(int x, int v){
		while(x < MAXN){
			tree[x] += v;
			x += x & -x;
		}
	}
	int query(int x){
		int ret = 0;
		while(x){
			ret += tree[x];
			x -= x & -x;
		}
		return ret;
	}
}bit;

struct swp{int s, e, x;};

vector<swp> qry[MAXN];
vector<int> pnt[MAXN];

int main(){
	freopen("exercise.in", "r", stdin);
	freopen("exercise.out", "w", stdout);
	scanf("%d %d",&n,&m);
	m -= (n - 1);
	for(int i=0; i<n-1; i++){
		int s, e; scanf("%d %d",&s,&e);
		gph[s].push_back(e);
		gph[e].push_back(s);
	}
	dfs(1, 0);
	for(int i=1; i<18; i++){
		for(int j=1; j<=n; j++){
			par[i][j] = par[i-1][par[i-1][j]];
		}
	}
	for(int i=0; i<m; i++){
		int x, y; scanf("%d %d",&x,&y);
		v[lca(x, y)].emplace_back(x, y);
		dx[x]++;
		dx[y]++;
		dx[lca(x, y)]-=2;
		if(din[x] > din[y]) swap(x, y);
		pnt[din[x]].push_back(din[y]);
	}
	lint dap = 0;
	reverse(ord.begin(), ord.end());
	for(auto &i : ord){
		for(auto &j : gph[i]){
			if(j == par[0][i]) continue;
			dx[i] += dx[j];
		}
	}
	auto dups = [&](vector<int> &v){
		sort(v.begin(), v.end());
		lint ret = 0;
		for(int i=0; i<v.size(); ){
			int e = i;
			while(e < v.size() && v[i] == v[e]) e++;
			for(int j=i; j<e; j++) ret += j - i;
			i = e;
		}
		return ret;
	};
	for(auto &i : ord){
		vector<pi> c1;
		vector<int> cx, cy;
		vector<int> c3;
		for(auto &j : v[i]){
			if(j.first == i || j.second == i){
				if(j.first == i) c3.push_back(anc(j.second, dep[j.second] - dep[i] - 1));
				else c3.push_back(anc(j.first, dep[j.first] - dep[i] - 1));
				continue;
			}
			int v1 = anc(j.first, dep[j.first] - dep[i] - 1);
			int v2 = anc(j.second, dep[j.second] - dep[i] - 1);
			if(v1 > v2) swap(v1, v2);
			c1.emplace_back(v1, v2);
			cx.push_back(v1);
			cx.push_back(v2);
		}
		dap += dups(cx);
		sort(c1.begin(), c1.end());
		for(int i=0; i<c1.size(); ){
			int e = i;
			while(e < c1.size() && c1[i] == c1[e]) e++;
			for(int j=i; j<e; j++){
				dap -= j - i;
			}
			i = e;
		}
		dap -= dups(c3);
		for(auto &i : c3){
			dap += dx[i] - 1;
		}
		if(i == 1) continue;
		for(auto &j : c1){
			qry[din[i] - 1].push_back({din[j.first], dout[j.first], 1});
			qry[din[i] - 1].push_back({din[j.second], dout[j.second], 1});
			qry[dout[j.first]].push_back({dout[i] + 1, n, 1});
			qry[dout[j.second]].push_back({dout[i] + 1, n, 1});
			qry[din[j.first] - 1].push_back({dout[i] + 1, n, -1});
			qry[din[j.second] - 1].push_back({dout[i] + 1, n, -1});
		}
	}
	for(int i=1; i<=n; i++){
		for(auto &j : pnt[i]) bit.add(j, 1);
		for(auto &j : qry[i]) dap += j.x * (bit.query(j.e) - bit.query(j.s - 1));
	}
	cout << dap << endl;
}
