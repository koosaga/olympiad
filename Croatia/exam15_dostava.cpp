#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef long double llf;
typedef pair<int, int> pi;
const int wcd = 1234567890;
const int maxp = 1e9 + 5;

int n;
pi a[50005];
int dst[50005];

pi ret[50005];

struct qryd{
	int pos, s, e, x;
};

struct sweep{
	int pos, s, e, x;
};

vector<sweep> swp;
vector<qryd> qry;

struct node{
	node *ls, *rs;
	int cov, oddp, evenp;
	node(int s, int e){
		ls = rs = NULL;
		cov = 0;
		if(abs(s)%2 == 1) oddp = s, evenp = s+1;
		else oddp = s+1, evenp = s;
		if(oddp > e) oddp = wcd;
		if(evenp > e) evenp = wcd;
	}
};

pi get_nearest(int s, int e){
	pi ret(s, s);
	while(abs(ret.first) % 2 == 0) ret.first++;
	while(abs(ret.second) % 2 != 0) ret.second++;
	if(ret.first > e) ret.first = wcd;
	if(ret.second > e) ret.second = wcd;
	return ret;
}

void upd(pi &a, pi b){
	a.first = min(a.first, b.first);
	a.second = min(a.second, b.second);
}

pi merge(node *p, int s, int e){
	int m = s + (e - s) / 2;
	pi ret(wcd, wcd);
	auto t = (p->ls ? pi(p->ls->oddp, p->ls->evenp) : get_nearest(s, m));
	upd(ret, t);
	t = (p->rs ? pi(p->rs->oddp, p->rs->evenp) : get_nearest(m+1, e));
	upd(ret, t);
	return ret;
}

void add(int s, int e, int ps, int pe, int x, node *p){
	if(e < ps || pe < s) return;
	if(s <= ps && pe <= e){
		p->cov+=x;
		if(p->cov){
			p->oddp = p->evenp = wcd;
		}
		else{
			tie(p->oddp, p->evenp) = merge(p, ps, pe);
		}
		return;
	}
	int pm = ps + (pe - ps) / 2;
	if(!p->ls) p->ls = new node(ps, pm);
	add(s, e, ps, pm, x, p->ls);
	if(!p->rs) p->rs = new node(pm+1, pe);
	add(s, e, pm+1, pe, x, p->rs);
	if(!p->cov) tie(p->oddp, p->evenp) = merge(p, ps, pe);
}

pi query(int s, int e, int ps, int pe, node *p){
	if(e < ps || pe < s || p->cov) return pi(wcd, wcd);
	if(s <= ps && pe <= e) return pi(p->oddp, p->evenp);
	int pm = ps + (pe - ps) / 2;
	pi ret(wcd, wcd);
	auto t = (p->ls ? query(s, e, ps, pm, p->ls) : get_nearest(ps, pm));
	upd(ret, t);
	t = (p->rs ? query(s, e, pm+1, pe, p->rs) : get_nearest(pm+1, pe));
	upd(ret, t);
	return ret;
}

void solve(bool rev){
	sort(swp.begin(), swp.end(), [&](const sweep &a, const sweep &b){
		return pi(a.pos, -a.x) < pi(b.pos, -b.x);
	});
	sort(qry.begin(), qry.end(), [&](const qryd &a, const qryd &b){
		return a.pos < b.pos;
	});
	int pnt = 0;
 	node* root = new node(-maxp, maxp);
	for(auto &i : qry){
		while(pnt < swp.size() && swp[pnt].pos <= i.pos){
			add(swp[pnt].s, swp[pnt].e, -maxp, maxp, swp[pnt].x, root);
			pnt++;
		}
		pi t = query(i.s, i.e, -maxp, maxp, root);
		if(abs(i.pos) % 2 == 1){
			if(t.first != wcd){
				ret[i.x] = pi(i.pos, t.first);
				if(rev) ret[i.x] = pi(t.first, i.pos);
			}
		}
		else{
			if(t.second != wcd){
				ret[i.x]= pi(i.pos, t.second);
				if(rev) ret[i.x] = pi(t.second, i.pos);
			}
		}
	}
}

int main(){
	cin >> n;
	for(int i=0; i<n; i++){
		int x, y;
		scanf("%d %d %d",&x, &y, &dst[i]);
		a[i] = {x+y, x-y};
	}
	for(int i=0; i<n; i++){
		int sx = a[i].first - dst[i];
		int ex = a[i].first + dst[i];
		int sy = a[i].second - dst[i];
		int ey = a[i].second + dst[i];
		swp.push_back({sx+1, sy+1, ey-1, 1});
		swp.push_back({ex, sy+1, ey-1, -1});
		qry.push_back({sx, sy, ey, i});
		qry.push_back({ex, sy, ey, i});
	}
	solve(0);
	swp.clear();
	qry.clear();
	for(int i=0; i<n; i++){
		int sx = a[i].first - dst[i];
		int ex = a[i].first + dst[i];
		int sy = a[i].second - dst[i];
		int ey = a[i].second + dst[i];
		swp.push_back({sy+1, sx+1, ex-1, 1});
		swp.push_back({ey, sx+1, ex-1, -1});
		qry.push_back({sy, sx, ex, i});
		qry.push_back({ey, sx, ex, i});
	}
	solve(1);
	for(int i=0; i<n; i++){
		int p = (ret[i].first + ret[i].second) / 2;
		int q = (ret[i].first - ret[i].second) / 2;
		printf("%d %d\n", p, q);
	}
}

