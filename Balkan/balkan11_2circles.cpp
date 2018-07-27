#include <bits/stdc++.h>
using namespace std;
const int MAXN = 50005;
using real_t = double;
using pi = pair<real_t, real_t>;

const real_t eps = 1e-8;

real_t ccw(pi a, pi b, pi c){
	real_t dx1 = b.first - a.first;
	real_t dy1 = b.second - a.second;
	real_t dx2 = c.first - a.first;
	real_t dy2 = c.second - a.second;
	return dx1 * dy2 - dy1 * dx2;
}

namespace hpi{
	bool z(real_t x){ return fabs(x) < eps; }
	struct line{
		real_t a, b, c;
		bool operator<(const line &l)const{
			bool flag1 = pi(a, b) > pi(0, 0);
			bool flag2 = pi(l.a, l.b) > pi(0, 0);
			if(flag1 != flag2) return flag1 > flag2;
			real_t t = ccw(pi(0, 0), pi(a, b), pi(l.a, l.b));
			return z(t) ? c * hypot(l.a, l.b) < l.c * hypot(a, b) : t > 0;
		}
		pi slope(){ return pi(a, b);}
	};
	pi cross(line a, line b){
		real_t det = a.a * b.b - b.a * a.b;
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
};

int x[MAXN], y[MAXN], n;

pi sub(vector<pi> &v, int x, int y){
	x %= v.size(), y %= v.size();
	return pi(v[y].first - v[x].first, v[y].second - v[x].second);
}

real_t dist(pi a, pi b){
	return hypot(b.second - a.second, b.first - a.first);
}

bool trial(real_t t){
	vector<hpi::line> v;
	for(int i=0; i<n; i++){
		real_t a = y[i+1] - y[i];
		real_t b = x[i] - x[i+1];
		real_t c = a * x[i] + b * y[i] - hypot(a, b) * t;
		v.push_back({a, b, c});
	}
	vector<pi> w;
	if(!hpi::solve(v, w)){
		return false;
	}
	int p = 0;
	real_t ret = 0;
	for(int i=0; i<w.size(); i++){
		while(ccw(pi(0, 0), sub(w, p+1, p), sub(w, i, i+1)) > -eps){
			ret = max(ret, dist(w[i], w[p]));
			p = (p+1)%w.size();
			ret = max(ret, dist(w[i], w[p]));
		}
		ret = max(ret, dist(w[i], w[p]));
	}
	return ret >= 2 * t;
}

int main(){
	scanf("%d",&n);
	for(int i=0; i<n; i++){
		scanf("%d %d",&x[i],&y[i]);
	}
	x[n] = x[0], y[n] = y[0];
	double s = 0, e = 1e7;
	for(int i=0; i<50; i++){
		double m = (s+e)/2;
		if(trial(m)) s = m;
		else e = m;
	}
	printf("%.3f",s);
}
