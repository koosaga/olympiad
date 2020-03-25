#include <bits/stdc++.h>
#define sz(v) ((lint)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using lint = long long;
typedef pair<lint, lint> pi;
const int MAXN = 200005;
const int MAXT = 530005;

struct intv{
	int x, l, r, cost;
	bool operator<(const intv &i)const{
		return x < i.x;
	}
}a[MAXN];

struct seg{
	pi tree[MAXT];
	int lim;
	void init(int n){
		for(lim = 1; lim <= n; lim <<= 1);
		fill(tree, tree + MAXT, pi(1e18, 1e18));
	}
	void upd(int x, pi v){
		x += lim;
		tree[x] = v;
		while(x > 1){
			x >>= 1;
			tree[x] = min(tree[2*x], tree[2*x+1]);
		}
	}
	pi query(int s, int e){
		s += lim;
		e += lim;
		pi ret(1e18, 1e18);
		while(s < e){
			if(s%2 == 1) ret = min(ret, tree[s++]);
			if(e%2 == 0) ret = min(ret, tree[e--]);
			s >>= 1;
			e >>= 1;
		}
		if(s == e) ret = min(ret, tree[s]);
		return ret;
	}
}seg1, seg2;

int n, m;
priority_queue<pi, vector<pi>, greater<pi> > pq;
lint dist[MAXN];

int main(){
	scanf("%d %d",&m,&n);
	for(int i=0; i<n; i++) scanf("%d %d %d %d",&a[i].x,&a[i].l,&a[i].r,&a[i].cost);
	sort(a, a + n);
	memset(dist, 0x3f, sizeof(dist));
	seg1.init(n);
	seg2.init(n);
	for(int i=0; i<n; i++){
		seg1.upd(i, pi(a[i].l - a[i].x, i));
		seg2.upd(i, pi(a[i].l + a[i].x, i));
	}
	for(int i=0; i<n; i++){
		if(a[i].l == 1){
			dist[i] = a[i].cost;
			pq.emplace(dist[i], i);
		}
	}
	while(sz(pq)){
		auto x = pq.top(); pq.pop();
		if(dist[x.second] != x.first) continue;
		int i = x.second;
		while(true){
			auto l = seg1.query(0, i - 1);
			lint j = l.second;
			if(j < n && a[i].r + 1 - a[i].x >= a[j].l - a[j].x){
				if(dist[j] > dist[i] + a[j].cost){
					dist[j] = dist[i] + a[j].cost;
					pq.emplace(dist[j], j);
				}
				seg1.upd(j, pi(1e18, 1e18));
			}
			else break;
		}
		while(true){
			auto l = seg2.query(i + 1, n - 1);
			lint j = l.second;
			if(j < n && a[i].r + 1 + a[i].x >= a[j].l + a[j].x){
				if(dist[j] > dist[i] + a[j].cost){
					dist[j] = dist[i] + a[j].cost;
					pq.emplace(dist[j], j);
				}
				seg2.upd(j, pi(1e18, 1e18));
			}
			else break;
		}
	}
	lint ret = 1e18;
	for(int i=0; i<n; i++){
		if(a[i].r == m) ret = min(ret, dist[i]);
	}
	if(ret > 1e17) ret = -1;
	cout << ret << endl;
}
