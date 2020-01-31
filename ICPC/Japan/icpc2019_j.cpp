#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using llf = long double;
using pi = pair<int, int>;
using point = complex<llf>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
const int MAXN = 2005;
const llf eps = 1e-8L;

namespace HPI{
	typedef pair<long double, long double> pi;
	bool z(long double x){ return fabs(x) < eps; }
	llf ccw(pi a, pi b, pi c){
		llf dx1 = b.first - a.first;
		llf dy1 = b.second - a.second;
		llf dx2 = c.first - a.first;
		llf dy2 = c.second - a.second;
		return dx1 * dy2 - dy1 * dx2;
	}
	struct line{
		long double a, b, c;
		bool operator<(const line &l)const{
			bool flag1 = pi(a, b) > pi(0, 0);
			bool flag2 = pi(l.a, l.b) > pi(0, 0);
			if(flag1 != flag2) return flag1 > flag2;
			long double t = ccw(pi(0, 0), pi(a, b), pi(l.a, l.b));
			return z(t) ? c * hypot(l.a, l.b) < l.c * hypot(a, b) : t > 0;
		}
		pi slope(){ return pi(a, b); }
	};
	pi cross(line a, line b){
		long double det = a.a * b.b - b.a * a.b;
		return pi((a.c * b.b - a.b * b.c) / det, (a.a * b.c - a.c * b.a) / det);
	}
	bool bad(line a, line b, line c){
		if(ccw(pi(0, 0), a.slope(), b.slope()) <= 0) return false;
		pi crs = cross(a, b);
		return crs.first * c.a + crs.second * c.b >= c.c;
	}
	bool solve(vector<line> v, vector<pi> &solution){ // ax + by <= c;
		sort(v.begin(), v.end());
		deque<line> dq;
		for(auto &i : v){
			if(!dq.empty() && z(ccw(pi(0, 0), dq.back().slope(), i.slope()))) continue;
			while(dq.size() >= 2 && bad(dq[dq.size()-2], dq.back(), i)) dq.pop_back();
			while(dq.size() >= 2 && bad(i, dq[0], dq[1])) dq.pop_front();
			dq.push_back(i);
		}
		while(dq.size() > 2 && bad(dq[dq.size()-2], dq.back(), dq[0])) dq.pop_back();
		while(dq.size() > 2 && bad(dq.back(), dq[0], dq[1])) dq.pop_front();
		vector<pi> tmp;
		for(int i=0; i<dq.size(); i++){
			line cur = dq[i], nxt = dq[(i+1)%dq.size()];
			if(ccw(pi(0, 0), cur.slope(), nxt.slope()) <= eps) return false;
			tmp.push_back(cross(cur, nxt));
		}
		solution = tmp;
		return true;
	}
}

llf solve(vector<pair<point, point>> seg){
	vector<HPI::line> v;
	for(auto &[x, y] : seg){
		llf A = (y - x).imag();
		llf B = (x - y).real();
		llf C = A * x.real() + B * x.imag();
		v.push_back({1.0L * A, 1.0L * B, 1.0L * C});
	}
	vector<pair<llf, llf>> sol;
	if(!HPI::solve(v, sol)) return 0;
//	puts("kurwa");
	llf ret = 0;
	for(int i=2; i<sz(sol); i++){
		ret += HPI::ccw(sol[0], sol[i - 1], sol[i]);
	}
	return ret / 2;
}

int n;
vector<pi> poly;

lint ccw(pi a, pi b, pi c){
	int dx1 = b.first - a.first;
	int dy1 = b.second - a.second;
	int dx2 = c.first - a.first;
	int dy2 = c.second - a.second;
	return 1ll * dx1 * dy2 - 1ll * dy1 * dx2;
}

bool insec(pi a, pi b, pi c, pi d){
	if(a == c || a == d || b == c || b == d) return 0;
	if(ccw(a, b, c) * ccw(a, b, d) > 0) return 0;
	if(ccw(c, d, a) * ccw(c, d, b) > 0) return 0;
	if(ccw(a, b, c) == 0 && ccw(a, b, d) == 0){
		if(a > b) swap(a, b);
		if(c > d) swap(c, d);
		if(a.second > b.second) swap(a.second, b.second);
		if(c.second > d.second) swap(c.second, d.second);
		return max(a.first, c.first) <= min(b.first, d.first) &&
		max(a.second, c.second) <= min(b.second, d.second);
	}
	return 1;
};

struct cut_edge{
	point st, ed;
	int idxs, idxe;
};

cut_edge shoot(point a, point b, int idx){
	auto ccw = [&](point a, point b, point c){
		return (conj(b - a) * (c - a)).imag();
	};
	auto dot = [&](point a, point b, point c){
		return (conj(b - a) * (c - a)).real();
	};
	auto get_cross = [&](point a, point b, point p, point q){
		llf d1 = ccw(a, p, b);
		llf d2 = ccw(a, q, b);
		return (d1 * q - d2 * p) / (d1 - d2);
	};
	vector<point> p(n + 1);
	llf val = 1e18;
	point dap(1e18, 1e18);
	int didx = -1;
	for(int i=0; i<n; i++) p[i] = point(poly[i].first, poly[i].second);
	p[n] = p[0];
	for(int i=0; i<n; i++){
		if(i == idx || (i + 1) % n == idx) continue;
		if(fabs(ccw(a, b, p[i])) < eps && dot(a, b, p[i]) > 0){
			if(val > abs(b - p[i])){
				val = abs(b - p[i]);
				dap = p[i];
				didx = 2 * i;
			}
		}
		if(ccw(a, b, p[i]) < 0 && ccw(a, b, p[i + 1]) > 0){
			auto pnt = get_cross(a, b, p[i], p[i + 1]);
			if(dot(a, b, pnt) > 0){
				if(val > abs(b - pnt)){
					val = abs(b - pnt);
					dap = pnt;
					didx = 2 * i + 1;
				}
			}
		}
	}
	return (cut_edge){b, dap, 2 * idx, didx};
}

int main(){
	cin >> n;
	poly.resize(n);
	for(int i=0; i<n; i++){
		cin >> poly[i].first >> poly[i].second;
	}
	vector<int> vis(n);
	auto get_prv = [&](int x){
		int prv = (x + n - 1) % n;
		while(vis[prv]) prv = (prv + n - 1) % n;
		return prv;
	};
	auto get_nxt = [&](int x){
		int nxt = (x + 1) % n;
		while(vis[nxt]) nxt = (nxt + 1) % n;
		return nxt;
	};
	auto ear = [&](int cur){
		int prv = get_prv(cur);
		int nxt = get_nxt(cur);
		int nnxt = get_nxt(nxt);
		int pprv = get_prv(prv);
		if(nnxt == prv) return 1;
		if(ccw(poly[prv], poly[cur], poly[nxt]) <= 0) return 0;
		if(ccw(poly[nxt], poly[prv], poly[nnxt]) >= 0 && 
			ccw(poly[nxt], poly[nnxt], poly[cur]) >= 0) return 0;
		if(ccw(poly[prv], poly[pprv], poly[nxt]) >= 0 && 
			ccw(poly[prv], poly[cur], poly[pprv]) >= 0) return 0;
		for(int i = nxt; nnxt != prv; ){
			if(insec(poly[i], poly[nnxt], poly[prv], poly[nxt])){
				return 0;
			}
			i = nnxt;
			nnxt = get_nxt(nnxt);
		}
		return 1;
	};
	queue<int> que;
	vector<vector<int>> res;
	for(int i=0; i<n; i++){
		if(ear(i)) que.push(i);
	}
	for(int i=0; i<n-2; i++){
		while(vis[que.front()] || !ear(que.front())) que.pop();
		int x = que.front(); que.pop();
		int prv = get_prv(x);
		int nxt = get_nxt(x);
		res.push_back(vector<int>{prv, x, nxt});
		if(sz(res) == n - 2) break;
		vis[x] = 1;
		if(ear(prv)) que.push(prv);
		if(ear(nxt)) que.push(nxt);
	}
	llf ret = 0;
	vector<cut_edge> go_left;
	for(int i=0; i<n; i++){
		auto prv = poly[i];
		auto cur = poly[(i + 1) % n];
		auto nxt = poly[(i + 2) % n];
		if(ccw(prv, cur, nxt) < 0){
			point x(prv.first, prv.second);
			point y(cur.first, cur.second);
			go_left.push_back(shoot(x, y, (i + 1) % n));
		}
	}
	for(auto &v : res){
		vector<pair<point, point>> kek;
		for(int j = 0; j < 3; j++){
			point x(poly[v[j]].first, poly[v[j]].second);
			point y(poly[v[(j + 1) % 3]].first, poly[v[(j + 1) % 3]].second);
			kek.emplace_back(x, y);
		}
		auto in = [&](int s, int e, int x){
			if(s <= e) return s <= x && x <= e;
			else return s <= x || x <= e;
		};
		int coeff = 1;
		for(auto &j : go_left){
			bool has_visible = 0;
			bool has_invisible = 0;
			for(auto &k : v){
				if(!in(j.idxs, j.idxe, 2 * k)) has_visible = 1;
				if(in(j.idxs, j.idxe, 2 * k)) has_invisible = 1;
			}
			if(has_visible && has_invisible){
				kek.emplace_back(j.st, j.ed);
			}
			if(!has_visible){
				coeff = 0;
			}
		}
		if(coeff) ret += solve(kek);
	}
	printf("%.20Lf\n", ret);
}
