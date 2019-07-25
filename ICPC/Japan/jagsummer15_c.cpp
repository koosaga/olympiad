#include<bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = pair<int, int>;
using node = pair<int, lint>;
const int MAXN = 100005;
const int MAXT = 270000;
const int oo = 1e9;

int n, q;
lint a[MAXN];
pi b[MAXN];

struct event{
	int pos, s, e, cnt; lint val;
	bool operator<(const event &e)const{
		return pos < e.pos;
	}
};

struct segtree{
	node tree[MAXT], lazy[MAXT];
	void clear(){
		fill(tree, tree + MAXT, node(0, 0));
		fill(lazy, lazy + MAXT, node(0, 0));
	}
	void add(node &a, node b){
		a.first += b.first;
		a.second += b.second;
	}
	void lazydown(int p){
		add(tree[2*p], lazy[p]);
		add(tree[2*p+1], lazy[p]);
		add(lazy[2*p], lazy[p]);
		add(lazy[2*p+1], lazy[p]);
		lazy[p] = node(0, 0 );
	}
	void upd(int s, int e, int ps, int pe, int p, node v){
		if(e < ps || pe < s) return;
		if(s <= ps && pe <= e){
			add(tree[p], v);
			add(lazy[p], v);
			return;
		}
		int pm = (ps+pe)/2;
		lazydown(p);
		upd(s, e, ps, pm, 2*p, v);
		upd(s, e, pm+1, pe, 2*p+1, v);
		tree[p] = max(tree[2*p], tree[2*p+1]);
	}
}segtree;

lint Sweep(vector<event> v){
	sort(v.begin(), v.end());
	lint ret = 1e18;
	segtree.clear();
	for(int i=0; i<v.size(); ){
		int e = i;
		while(e < v.size() && v[i].pos == v[e].pos){
			e++;
		}
		for(int j=i; j<e; j++){
			segtree.upd(v[j].s, v[j].e, 1, n, 1, node(v[j].cnt, -v[j].val));
		}
		auto quer = segtree.tree[1];
	//	printf("[%d, %lld]\n", quer.first, -quer.second);
		if(quer.first == q){
			ret = min(ret, -quer.second);
		}
		i = e;
	}
	return ret;
}

struct seg{
	int tree[MAXT], lim;
	void init(int n){
		memset(tree, 0x3f, sizeof(tree));
		for(lim = 1; lim <= n; lim <<= 1);
	}
	void upd(int x, int v){
		x += lim;
		tree[x] = min(tree[x], v);
		while(x > 1){
			x >>= 1;
			tree[x] = min(tree[2*x], tree[2*x+1]);
		}
	}
	int query(int s, int e){
		s += lim;
		e += lim;
		int ret = oo;
		while(s < e){
			if(s % 2 == 1) ret = min(ret, tree[s++]);
			if(e % 2 == 0) ret = min(ret, tree[e--]);
			s >>= 1;
			e >>= 1;
		}
		if(s == e) ret = min(ret, tree[s]);
		return ret;
	}
}seg;

vector<int> precMaxR(){
	seg.init(n + 2);
	vector<int> nxt(n + 2, oo);
	for(int i=0; i<q; i++){
		if(b[i].first < b[i].second) seg.upd(b[i].first, b[i].second);
	}
	for(int i=0; i<q; i++){
		if(b[i].first > b[i].second){
			int itr = seg.query(b[i].second + 1, b[i].first - 1); // min value
			itr = max(itr, b[i].first);
			nxt[b[i].second] = min(nxt[b[i].second], itr);
		}
	}
	seg.init(n + 2);
	for(int i=0; i<q; i++){
		if(b[i].first > b[i].second) seg.upd(b[i].second, b[i].first);
	}
	for(int i=0; i<q; i++){
		if(b[i].first < b[i].second){
			int itr = seg.query(b[i].first, b[i].second - 1); // min value
			nxt[b[i].first] = min(nxt[b[i].first], max(b[i].second + 1, itr));
			nxt[b[i].first - 1] = min(nxt[b[i].first - 1], max(b[i].second, itr));
		}
	}
	for(int i=n; i; i--) nxt[i] = min(nxt[i], nxt[i + 1]);
	return nxt;
}

lint solve2(){
	vector<event> ev;
	auto AddEvent = [&](int sx, int ex, int sy, int ey, lint v){
		sx = max(sx, 1); ex = min(ex, n);
		sy = max(sy, 1); ey = min(ey, n);
		int cnt = (v > 1e17 ? -1 : 1);
		if(sx <= ex && sy <= ey){
		//	printf("%d %d %d %d %lld\n", sx, ex, sy, ey, v);
			ev.push_back({sx, sy, ey, +cnt, v});
			ev.push_back({ex + 1, sy, ey, -cnt, -v});
		}
	};
	auto nxt = precMaxR();
	seg.init(n + 2);
	for(int i=1; i<=n; i++){
		AddEvent(i, i, 1, i, 1e18);
		AddEvent(i, i, nxt[i], n, 1e18);
	}
	for(int i=0; i<q; i++){
		if(b[i].first > b[i].second){
			seg.upd(b[i].second, b[i].first);
		}
	}
	for(int i=0; i<q; i++){
		if(b[i].first < b[i].second){
			lint cost = a[b[i].second - 1] - a[b[i].first - 1];
			AddEvent(1, b[i].first - 1, b[i].second, n, cost);
			AddEvent(b[i].first, b[i].first, b[i].second + 1, n, cost);
			AddEvent(b[i].first + 1, b[i].second, b[i].first, b[i].second, a[n] - cost);
			AddEvent(b[i].first, b[i].first, b[i].first, b[i].second - 1, a[n] - cost);
			if(a[n] - cost > cost && seg.query(b[i].first, b[i].second - 1) >= b[i].second){
				AddEvent(b[i].first, b[i].first, b[i].second, b[i].second, cost);
			}
			else{
				AddEvent(b[i].first, b[i].first, b[i].second, b[i].second, a[n] - cost);
			}
		}
		if(b[i].first > b[i].second){
			lint cost = a[b[i].first - 1] - a[b[i].second - 1];
			AddEvent(1, b[i].second - 1, b[i].first + 1, n, cost);
			AddEvent(b[i].first, n, b[i].first, n, cost);
			AddEvent(1, b[i].second, 1, b[i].second, cost);
		}
	}
	return Sweep(ev);
}

lint solve(vector<lint> v, vector<pi> qry){
	for(int i=1; i<=n; i++){
		a[i] = v[i-1] + a[i-1];
	}
	lint ret = 0;
	for(int i=0; i<q; i++){
		if(qry[i].first < qry[i].second){
			ret += a[qry[i].second - 1] - a[qry[i].first - 1];
		}
		else{
			ret += a[n] - a[qry[i].first - 1];
			ret += a[qry[i].second - 1];
		}
		b[i] = qry[i];
	}
	return min(ret, solve2());
}

int main(){
	scanf("%d %d",&n,&q);
	vector<lint> v(n);
	vector<pi> qry(q);
	for(int i=0; i<n; i++) scanf("%lld",&v[i]);
	for(int i=0; i<q; i++){
		scanf("%d %d",&qry[i].first,&qry[i].second);
		qry[i].first++;
		qry[i].second++;
	}
	lint ret = solve(v, qry);
	reverse(v.begin(), v.begin() + n - 1);
	for(int i=0; i<q; i++){
		qry[i] = pi(n + 1 - qry[i].first, n + 1 - qry[i].second);
	}
	ret = min(ret, solve(v, qry));
	cout << ret << endl;
}
