#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
const int MAXN = 1000005;
const int MAXT = 2100000;

struct seg{
	lint tree[MAXT], lazy[MAXT];
	void lazydown(int x){
		tree[2*x] += lazy[x];
		tree[2*x+1] += lazy[x];
		lazy[2*x] += lazy[x];
		lazy[2*x+1] += lazy[x];
		lazy[x] = 0;
	}
	void add(int s, int e, int ps, int pe, int p, int v){
		if(e < ps || pe < s) return;
		if(s <= ps && pe <= e){
			tree[p] += v;
			lazy[p] += v;
			return;
		}
		int pm = (ps+pe)/2;
		lazydown(p);
		add(s, e, ps, pm, 2*p, v);
		add(s, e, pm+1, pe, 2*p+1, v);
		tree[p] = max(tree[2*p], tree[2*p+1]);
	}
}seg;

struct sweep{ int s, e, x; };
vector<sweep> sw[MAXN];
vector<int> v[MAXN];
int n, m, a[MAXN], b[MAXN];

int main(){
	scanf("%d %d",&n,&m);
	for(int i=1; i<=n; i++) scanf("%d",&a[i]), v[a[i]].push_back(i);
	for(int i=1; i<=m; i++) scanf("%d",&b[i]);
	for(int i=1; i<=m; i++){
		for(int j=0; j<v[i].size(); j++){
			int s = (j ? v[i][j-1] : 0) + 1;
			int e = (j+1 < v[i].size() ? v[i][j+1] : (n+1)) - 1;
			sw[s].push_back((sweep){v[i][j], e, b[i]});
			sw[v[i][j] + 1].push_back((sweep){v[i][j], e, -b[i]});
		}
	}
	lint ans = 0;
	for(int i=1; i<=n; i++){
		for(auto &j : sw[i]){
			seg.add(j.s, j.e, 1, n, 1, j.x);
		}
		ans = max(ans, seg.tree[1]);
	}
	cout <<ans << endl;
}
