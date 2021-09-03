#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using pi = pair<int, int>;
const int MAXN = 500050;
const int MAXT = 1050000;

struct edge{
	int w, sx, ex, sy, ey, idx;
	bool operator<(const edge &e)const{
		return ex < e.ex;
	}
}a[MAXN];

int n, m, k;
int dist[MAXN];
set<int> s;	
priority_queue<pi, vector<pi>, greater<pi> > pq;

struct seg{
	int lim;
	edge tree[MAXT];
	void init(){
		for(lim = 1; lim <= m; lim <<= 1);
		for(int i=0; i<m; i++) tree[i+lim] = a[i];
		for(int i=lim-1; i; i--) tree[i] = max(tree[2*i], tree[2*i+1]);
	}
	void upd(int x, edge e){
		x += lim;
		tree[x] = e;
		while(x > 1){
			x >>= 1;
			tree[x] = max(tree[2*x], tree[2*x+1]);
		}
	}
	edge query(int s, int e){
		s += lim;
		e += lim;
		edge ret = {-1, -1, -1, -1, -1, -1};
		while(s < e){
			if(s%2 == 1) ret = max(ret, tree[s++]);
			if(e%2 == 0) ret = max(ret, tree[e--]);
			s >>= 1;
			e >>= 1;
		}
		if(s == e) ret = max(ret, tree[s]);
		return ret;
	}
}seg;

void enque(int l, int r, int x){
	auto itr = s.lower_bound(l);
	while(itr != s.end() && *itr <= r){
		int v = *itr; 
		itr = s.erase(itr);
		dist[v] = x;
		int pos = upper_bound(a, a + m, (edge){-1, v, -1, -1, -1, -1}, [&](const edge &x, const edge &y){
			return x.sx < y.sx;
		}) - a; 
		while(true){
			auto pp = seg.query(0, pos - 1);
			if(pp.ex < v) break;
			seg.upd(pp.idx, (edge){-1, -1, -1, -1, -1, -1});
			pq.emplace(pp.w + x, pp.idx);
		}
	}
}

int main(){
	scanf("%d %d %d",&n,&m,&k);
	for(int i=0; i<m; i++){
		int sx, ex, sy, ey;
		scanf("%d %d %d %d",&sx,&ex,&sy,&ey);
		a[i] = {1, sx, ex, sy, ey, -1};
		a[i+m] = {1, sy, ey, sx, ex, -1};
	}
	m *= 2;
	sort(a, a + m, [&](const edge &x, const edge &y){
		return x.sx < y.sx;
	});
	for(int i=0; i<m; i++) a[i].idx = i;
	seg.init();
	memset(dist, 0x3f, sizeof(dist));
	for(int i=1; i<=n; i++) s.insert(i);
	enque(k, k, 0);
	while(sz(pq)){
		auto x = pq.top(); pq.pop();
		enque(a[x.second].sy, a[x.second].ey, x.first);
	}
	for(int i=1; i<=n; i++){
		if(dist[i] > 1e8) dist[i] = -1;
		printf("%d\n", dist[i]);
	}
}

