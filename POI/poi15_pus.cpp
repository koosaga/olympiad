#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using pi = pair<int, int>;
using lint = long long;
using ll = long long;
const int MAXN = 100005;
const int MAXT = 270005;
const int MAXG = 666666;

vector<pi> gph[MAXG];
vector<pi> rev[MAXG];
int n, s, m;
int a[MAXG];
int indeg[MAXG];
vector<int> ord;

void add_edge(int s, int e, int x = 0){
	gph[s].emplace_back(x, e);
	indeg[e]++;
	rev[e].emplace_back(x, s);
}

void solve(){
	for(auto &i : ord){
		int val = 1;
		for(auto &j : rev[i]){
			val = max(val, a[j.second] + j.first);
		}
		if(a[i] && a[i] < val){
			puts("NIE");
			exit(0);
		}
		if(val > 1000000000){
			puts("NIE");
			exit(0);
		}
		a[i] = max(a[i], val);
	}
	puts("TAK");
	for(int i=1; i<=n; i++) printf("%d ", a[i]);
}

struct seg{
	int tree[MAXT];
	int lim, n;
	void init(int _n, int m){
		n = _n + m;
		for(lim = 1; lim <= _n; lim <<= 1);
		for(int i=1; i<=_n; i++){
			add_edge(i, n + i + lim);
		}
		for(int i=lim-1; i; i--){
			add_edge(n + 2*i, n + i);
			add_edge(n + 2*i+1, n + i);
		}
	}
	void query(int s, int e, int x){
		s += lim;
		e += lim;
		while(s < e){
			if(s % 2 == 1) add_edge(n + (s++), x);
			if(e % 2 == 0) add_edge(n + (e--), x);
			s >>= 1;
			e >>= 1;
		}
		if(s == e) add_edge(n + s, x);
	}
}seg;

int main(){
	scanf("%d %d %d",&n,&s,&m);
	for(int i=0; i<s; i++){
		int x, y; scanf("%d %d",&x,&y);
		a[x] = y;
	}
	seg.init(n, m);
	for(int i=0; i<m; i++){
		int l, r, k; scanf("%d %d %d",&l,&r,&k);
		vector<int> v(k + 2);
		v[0] = l - 1;
		v[k + 1] = r + 1;
		for(int j=1; j<=k; j++){
			scanf("%d",&v[j]);
			add_edge(n + 1 + i, v[j], 1);
		}
		for(int j=1; j<=k+1; j++){
			int l = v[j-1] + 1;
			int r = v[j] - 1;
			seg.query(l, r, n + 1 + i);
		}
	}
	queue<int> que;
	int GSZ = n + m + 2 * seg.lim;
	for(int i=1; i<=GSZ; i++){
		if(!indeg[i]) que.push(i);
	}
	while(sz(que)){
		int x = que.front(); que.pop();
		ord.push_back(x);
		for(auto &j : gph[x]){
			if(indeg[j.second]){
				indeg[j.second]--;
				if(!indeg[j.second]) que.push(j.second);
			}
		}
	}
	if(sz(ord) != GSZ){
		puts("NIE");
		return 0;
	}
	solve();
}
