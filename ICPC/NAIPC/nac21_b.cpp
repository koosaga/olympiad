#include<bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define move fuck
using namespace std;
const int MAXN = 3005;
const int mod = 1e9 + 7;
using lint = long long;
using llf = double;
 
const llf eps = 1e-8L;
typedef pair<llf, llf> pi;
bool z(llf x){ return fabs(x) < eps; }
 
llf ccw(pi a, pi b, pi c){
	llf dx1 = b.first - a.first;
	llf dy1 = b.second - a.second;
	llf dx2 = c.first - a.first;
	llf dy2 = c.second - a.second;
	return dx1 * dy2 - dy1 * dx2;
}
 
struct line{
	llf a, b, c;
	bool operator<(const line &l)const{
		bool flag1 = pi(a, b) > pi(0, 0);
		bool flag2 = pi(l.a, l.b) > pi(0, 0);
		if(flag1 != flag2) return flag1 > flag2;
		llf t = ccw(pi(0, 0), pi(a, b), pi(l.a, l.b));
		return z(t) ? c * hypot(l.a, l.b) < l.c * hypot(a, b) : t > 0;
	}
	pi slope(){ return pi(a, b); }
};
pi cross(line a, line b){
	llf det = a.a * b.b - b.a * a.b;
	return pi((a.c * b.b - a.b * b.c) / det, (a.a * b.c - a.c * b.a) / det);
}
bool bad(line a, line b, line c){
	if(ccw(pi(0, 0), a.slope(), b.slope()) <= 0) return false;
	pi crs = cross(a, b);
	return crs.first * c.a + crs.second * c.b >= c.c;
}
bool solve(vector<line> v, vector<pi> &solution){ // ax + by <= c;
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

void solve2(vector<line> &v){
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
	for(int i=0; i<dq.size(); i++){
		line cur = dq[i], nxt = dq[(i+1)%dq.size()];
		if(ccw(pi(0, 0), cur.slope(), nxt.slope()) <= eps){
			dq.clear();
			break;
		}
	}
	vector<line> w;
	for(int i=0; i<dq.size(); i++){
		w.push_back(dq[i]);
	}
	v = w;
}
 
 
namespace idk{
using pj = pair<llf, llf>;
int n;
llf r;
	llf ccw(pj a, pj b){
		return a.first * b.second - b.first * a.second;
	}

	llf solve2(pj x, pj y){
		llf ang = atan2(y.second, y.first) - atan2(x.second, x.first) + 4 * M_PI;
		while(ang >= M_PI) ang -= 2 * M_PI;
		return 0.5 * (ang * r * r - ccw(x, y));
	}

	llf solve3(pj x, pj y){
		llf ang = atan2(y.second, y.first) - atan2(x.second, x.first) + 4 * M_PI;
		while(ang >= M_PI) ang -= 2 * M_PI;
		return 0.5 * ang * r * r;
	}
	llf solve(pj x, pj y){
		if(fabs(ccw(x, y)) < 1e-7) return 0;
		if(ccw(x, y) < 0) return -solve(y, x);
		llf dis = hypot(y.first - x.first, y.second - x.second);
		llf linepnt = ccw(x, y) / dis;
		if(linepnt >= r - eps) return solve3(x, y);
		llf cx = -linepnt * (x.second - y.second) / dis;
		llf cy = -linepnt * (y.first - x.first) / dis;
		llf up = sqrt(1.0 * r * r - linepnt * linepnt) / dis;
		pj c1(cx + up * (y.first - x.first), cy + up * (y.second - x.second));
		pj c2(cx - up * (y.first - x.first), cy - up * (y.second - x.second));
		if(ccw(c1, c2) < 0) swap(c1, c2);
		{
			if(ccw(c1, x) > 0) c1 = x;
			if(ccw(y, c2) > 0) c2 = y;
			llf ret = solve3(x, y);
			if(ccw(c1, c2) > 0) ret -= solve2(c1, c2);
			return ret;
		}
	}

	llf getArea(vector<pj> a, int R){
		n = a.size();
		r = R;
		llf ret = 0;
		for(int i=0; i<n; i++){
			ret += solve(a[i], a[(i+1)%n]);
		}
		return ret;
	}

};

using punk = complex<llf>;

punk a[MAXN];
vector<line> half[MAXN];

int main(){
	int n, q; cin >> n >> q;
	vector<int> x(n), y(n);
	vector<llf> r(n);
	map<pair<int, int>, int> mp;
	for(int i=0; i<n; i++){
		cin >> x[i] >> y[i] >> r[i];
		if(mp.find(make_pair(x[i], y[i])) != mp.end()){
			int j = mp[make_pair(x[i], y[i])];
			r[j] = max(r[j], r[i]);
			i--;
			n--;
			continue;
		}
		else{
			mp[make_pair(x[i], y[i])] = i;
		}
	}

	for(int i=0; i<n; i++) a[i] = punk(x[i], y[i]);
	for(int i=0; i<n; i++){
		vector<line> v;
		v.push_back({0, 1, 1e7L});
		v.push_back({1, 0, 1e7L});
		v.push_back({0, -1, 1e7L});
		v.push_back({-1, 0, 1e7L});
		for(int j=0; j<n; j++){
			if(i == j) continue;
			llf D = hypotl(x[j] - x[i], y[j] - y[i]);
			llf magic = (1ll * r[j] * r[j] - 1ll * r[i] * r[i]) / (D * D);
			punk point = (1 - magic) * a[j] + (1 + magic) * a[i];
			point /= 2.0;
			line l = {1.0 * x[j] - x[i], 1.0 * y[j] - y[i], 69};
			l.c = point.real() * l.a + point.imag() * l.b;
			v.push_back(l);
		}
		solve2(v);
		half[i] = v;
	}
	for(int i = 0; i < q; i++){
		int X, Y, w, h;
		scanf("%d %d %d %d",&X,&Y,&w,&h);
		vector<line> foo;
		foo.push_back({0, 1, llf(Y + h)});
		foo.push_back({1, 0, llf(X + w)});
		foo.push_back({0, -1, llf(-Y)});
		foo.push_back({-1, 0, llf(-X)});
		llf ret = 0;
		for(int j = 0; j < n; j++){
			if(!sz(half[j])) continue;
			vector<line> bar = half[j];
			for(auto &k : foo){
				bar.insert(lower_bound(bar.begin(), bar.end(), k), k);
			}
			vector<pi> sol;
			if(solve(bar, sol)){
				for(auto &[px, py] : sol) px -= x[j], py -= y[j];
				ret += idk::getArea(sol, r[j]);
			}
		}
		printf("%.20Lf\n", 100L * ret / (1.0L * w * h));
	}
}


