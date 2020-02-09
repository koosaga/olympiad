#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using lint = long long;
using pi = pair<lint, lint>;
const int MAXN = 200005;
const int MAXT = 600050;

pi operator+(pi a, pi b){
	return pi(a.first + b.first, a.second + b.second);
}

struct bit{
	pi tree[MAXT];
	void add(int x, pi v){
		x += MAXN;
		for(int i=x; i<MAXT; i+=i&-i) tree[i] = tree[i] + v;
	}
	pi query(int x){
		x += MAXN;
		pi ret(0, 0);
		for(int i=x; i; i-=i&-i) ret = ret + tree[i];
		return ret;
	}
}bit1, bit2;

struct seg{
	pi tree[MAXT];
	int lim;
	void init(int n, int *a){
		for(lim = 1; lim <= n; lim <<= 1);
		for(int i=1; i<=n; i++){
			tree[i + lim] = pi(a[i], i);
		}
		for(int i=lim; i; i--) tree[i] = max(tree[2*i], tree[2*i+1]);
	}
	pi query(int s, int e){
		s += lim;
		e += lim;
		pi ret(-1e9, 1e9);
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

struct ev1{ // y <= QUERY
	int upd, pos, val;
	bool operator<(const ev1 &e)const{
		return upd < e.upd;
	}
};

struct ev2{ // y - t <= QUERY
	int upd, pos, val;
	bool operator<(const ev2 &e)const{
		return upd < e.upd;
	}
};

vector<ev1> kek1;
vector<ev2> kek2;

void ADD(int x, int y, int v){
	int t = y - x;
	if(t > 1e7) return;
	kek1.push_back({t, y, v});
	kek2.push_back({t, x + 1, -v});
}

void solve(int s, int e){
	if(s > e) return;
	auto m = seg.query(s, e);
	solve(s, m.second - 1);
	solve(m.second + 1, e);
	if(s == 1) s = -1e9;
	int v = m.first;
	int p = m.second;
	ADD(p, p, v);
	ADD(p, e + 1, -v);
	ADD(s - 1, p, -v);
	ADD(s - 1, e + 1, v);
}

struct query{
	int t, r, idx, buho;
	bool operator<(const query &q)const{
		return t < q.t;
	}
}qr[MAXN * 2];

int n, q, a[MAXN];
lint ret[MAXN];

int main(){
	scanf("%d %d",&n,&q);
	for(int i=1; i<=n; i++) scanf("%d",&a[i]);
	seg.init(n, a);
	solve(1, n);
	for(int i=0; i<q; i++){
		int t, l, r;
		scanf("%d %d %d",&t,&l,&r);
		qr[2 * i] = {t, r, i, +1};
		qr[2 * i + 1] = {t, l-1, i, -1};
	}
	sort(qr, qr + q + q);
	sort(all(kek1));
	sort(all(kek2));
	int ptr1 = 0;
	int ptr2 = 0;
	for(int i=0; i<q*2; i++){
		while(ptr1 < sz(kek1) && kek1[ptr1].upd <= qr[i].t){
			bit1.add(kek1[ptr1].pos, pi(kek1[ptr1].val, 1ll * kek1[ptr1].val * (1 - kek1[ptr1].pos)));
			ptr1++;
		}
		while(ptr2 < sz(kek2) && kek2[ptr2].upd <= qr[i].t){
			bit2.add(kek2[ptr2].pos, pi(kek2[ptr2].val, 1ll * kek2[ptr2].val * (1 - kek2[ptr2].pos)));
			ptr2++;
		}
		lint sum = 0;
		auto qr1 = bit1.query(qr[i].r);
		sum += qr1.first * qr[i].r + qr1.second;
		auto qr2 = bit2.query(qr[i].r - qr[i].t);
		sum += qr2.first * (qr[i].r - qr[i].t) + qr2.second;
		ret[qr[i].idx] += qr[i].buho * sum;
	}
	for(int i=0; i<q; i++) printf("%lld\n", ret[i]);
}
