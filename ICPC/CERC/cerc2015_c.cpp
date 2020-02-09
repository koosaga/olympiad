#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using pi = pair<int, int>;
const int MAXN = 200050;
const int MAXT = 1000050;

struct bit{
	int tree[MAXT];
	void add(int x, int v){
		for(int i=x; i<MAXT; i+=i&-i){
			tree[i] += v;
		}
	}
	int query(int x){
		int ret = 0;
		for(int i=x; i; i-=i&-i){
			ret += tree[i];
		}
		return ret;
	}
	int query(int s, int e){ return query(e) - query(s - 1); }
}bit;

struct rect{
	int sx, ex, sy, ey, idx;
};

struct point{
	int x, y, node, idx;
	point(){}
	point(int x, int y, int node, int idx): x(x), y(y), node(node), idx(idx){}
	bool operator<(const point &p)const{
		return x < p.x;
	}
};

struct event{
	int pos, mode, l, r;
	bool operator<(const event &e)const{
		return make_tuple(pos, mode, l, r) < make_tuple(e.pos, e.mode, e.l, e.r);
	}
};

struct kek{
	int l, r, cnt;
	bool operator<(const kek &k)const{
		return l < k.l;
	}
};

int ret[MAXN];

void solve1(vector<rect> a, vector<point> b, vector<point> c, bool flag){
	vector<event> v;
	vector<int> epoint;
	for(auto &i : a){
		v.push_back({i.ex + 1, 1, i.sy, i.ey});
		v.push_back({i.sx   , -1, i.sy, i.ey});
		epoint.push_back(i.ex + 1);
		epoint.push_back(i.sx);
	}
	sort(all(v));
	sort(all(b));
	sort(all(c));
	reverse(all(v));
	reverse(all(b));
	reverse(all(c));
	for(auto &i : b) bit.add(i.y, 1);
	for(auto &i : c) epoint.push_back(i.x);
	sort(all(epoint));
	epoint.resize(unique(all(epoint)) - epoint.begin());
	reverse(all(epoint));
	int posa = 0;
	int posb = 0;
	int posc = 0;
	set<kek> s;
	s.insert({1000002, 1000002, 0});
	for(auto &i : epoint){
		while(posb < sz(b) && b[posb].x >= i) bit.add(b[posb++].y, -1);
		while(posc < sz(c) && c[posc].x >= i){
			auto ll = s.lower_bound((kek){c[posc].y, -1, -1});
			int idx = c[posc].idx;
			ret[idx] += ll->cnt + bit.query(c[posc].y, ll->l - 1);
			if(flag) ret[idx] += bit.query(c[posc].y - 1);
			posc++;
		}
		vector<kek> lazy;
		while(posa < sz(v) && v[posa].pos >= i){
			if(v[posa].mode == 1){
				int cnt = 0;
				auto ll = s.lower_bound((kek){v[posa].r + 1, -1, -1});
				cnt += ll->cnt + bit.query(v[posa].l, ll->l - 1);
				lazy.push_back((kek){v[posa].l, v[posa].r, cnt});
			}
			if(v[posa].mode == -1){
				auto ll = s.lower_bound((kek){v[posa].l, v[posa].r, -1});
				s.erase(ll);
			}
			posa++;
		}
		for(auto &i : lazy) s.insert(i);
	}
	while(posb < sz(b)) bit.add(b[posb++].y, -1);
}

void solve(vector<rect> a, vector<point> b, vector<point> c){
	solve1(a, b, c, 0);
	for(auto &i : a){
		swap(i.sx, i.sy);
		swap(i.ex, i.ey);
	}
	for(auto &i : b) swap(i.x, i.y);
	for(auto &i : c) swap(i.x, i.y);
	solve1(a, b, c, 1);
	for(auto &i : c) ret[i.idx] = sz(b) - ret[i.idx];
}

rect a[MAXN];
point b[MAXN], c[MAXN];
int n, m, q, par[MAXN];

bool enclose(rect x, pi y){
	int X = y.first;
	int Y = y.second;
	return x.sx <= X && X <= x.ex && x.sy <= Y && Y <= x.ey;
}

void sweep(){
	vector<point> get_loc;
	vector<rect> rect_add;
	vector<rect> rect_del;
	for(int i=0; i<n; i++){
		rect_add.push_back(a[i]);
		rect_del.push_back(a[i]);
	}
	for(int i=0; i<m; i++){
		get_loc.emplace_back(b[i].x, b[i].y, -1, i + n);
	}
	for(int i=0; i<q; i++){
		get_loc.emplace_back(c[i].x, c[i].y, -1, i + n + m);
	}
	sort(all(get_loc));
	sort(all(rect_add), [&](const rect &a, const rect &b){
		return a.sx < b.sx;
	});
	sort(all(rect_del), [&](const rect &a, const rect &b){
		return a.ex < b.ex;
	});
	int ptr_loc = 0;
	int ptr_add = 0;
	int ptr_del = 0;
	set<pi> events;
	for(int i=0; i<1000005; i++){
		while(ptr_add < sz(rect_add) && rect_add[ptr_add].sx <= i){
			auto pos = rect_add[ptr_add++];
			if(pos.idx){
				int node = events.upper_bound(pi(pos.sy + 1, -100))->second;
				if(!enclose(a[node], pi(pos.sx, pos.sy))) node = par[node];
				par[pos.idx] = node;
			}
			events.emplace(pos.sy, pos.idx);
			events.emplace(pos.ey + 1, pos.idx);
		}
		while(ptr_loc < sz(get_loc) && get_loc[ptr_loc].x <= i){
			auto pos = get_loc[ptr_loc++];
			int node = events.upper_bound(pi(pos.y + 1, -100))->second;
			if(!enclose(a[node], pi(pos.x, pos.y))) node = par[node];
			if(pos.idx < n + m) b[pos.idx - n].node = node;
			else c[pos.idx - n - m].node = node;
		}
		while(ptr_del < sz(rect_del) && rect_del[ptr_del].ex <= i){
			auto pos = rect_del[ptr_del++];
			events.erase(pi(pos.sy, pos.idx));
			events.erase(pi(pos.ey + 1, pos.idx));
		}
	}
}

int main(){
	scanf("%d",&n);
	a[0].ex = a[0].ey = 1000001;
	for(int i=1; i<=n; i++){
		scanf("%d %d %d %d",&a[i].sx,&a[i].sy,&a[i].ex,&a[i].ey);
		a[i].idx = i;
	}
	n++;
	scanf("%d",&m);
	for(int i=0; i<m; i++){
		scanf("%d %d",&b[i].x,&b[i].y);
		b[i].idx = -1;
	}
	scanf("%d",&q);
	for(int i=0; i<q; i++){
		scanf("%d %d",&c[i].x,&c[i].y);
		c[i].idx = i;
	}
	sweep();
	sort(a + 1, a + n, [&](const rect &a, const rect &b){
		return par[a.idx] < par[b.idx];
	});
	sort(b, b + m, [&](const point &a, const point &b){
		return a.node < b.node;
	});
	sort(c, c + q, [&](const point &a, const point &b){
		return a.node < b.node;
	});
	int pa = 1, pb = 0, pc = 0;
	for(int i=0; i<n; i++){
		vector<rect> rec;
		vector<point> vx, vy;
		while(pa < n && par[a[pa].idx] == i){
			rec.push_back(a[pa++]);
		}
		while(pb < m && b[pb].node == i){
			vx.push_back(b[pb++]);
		}
		while(pc < q && c[pc].node == i){
			vy.push_back(c[pc++]);
		}
		solve(rec, vx, vy);
	}
	for(int i=0; i<q; i++) printf("%d\n", ret[i]);
}
