#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using llf = long double;
using pi = complex<llf>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
const int MAXN = 1234567;
const int mod = 998244353;
const llf eps = 1e-10L;

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
			if(ccw(pi(0, 0), cur.slope(), nxt.slope()) < 0) return false;
			tmp.push_back(cross(cur, nxt));
		}
		solution = tmp;
		return true;
	}
}

llf solve(vector<pair<pi, pi>> seg){
	vector<HPI::line> v;
	for(auto &[x, y] : seg){
		llf A = (y - x).imag();
		llf B = (x - y).real();
		llf C = A * x.real() + B * x.imag() + abs(x - y) * eps / 100;
		v.push_back({1.0L * A, 1.0L * B, 1.0L * C});
	}
	vector<pair<llf, llf>> sol;
	if(!HPI::solve(v, sol)) return 0;
	llf ret = 0;
	for(int i=2; i<sz(sol); i++){
		ret += HPI::ccw(sol[0], sol[i - 1], sol[i]);
	}
	return ret / 2;
}

int n[2];
pi a[2][11], v[2];

llf insec(llf t){
	vector<pair<pi, pi>> seg;
	for(int i=0; i<2; i++){
		for(int j=0; j<n[i]; j++){
			pi x = a[i][j] + t * v[i];
			pi y = a[i][(j+1)%n[i]] + t * v[i];
			seg.emplace_back(x, y);
		}
	}
	return solve(seg);
}
llf ccw(pi a, pi b, pi c){
	return (conj(b - a) * (c - a)).imag(); 
}

int main(){
	for(int i=0; i<2; i++){
		cin >> n[i];
		for(int j=n[i]-1; j>=0; j--){
			int x, y; cin >> x >> y;
			a[i][j] = pi(x, y);
		}
		int x, y; cin >> x >> y;
		v[i] = pi(x, y);
	}
	if(insec(69) == 0 && abs(v[0] - v[1]) < eps){
		puts("never");
		return 0;
	}
	vector<llf> time_period = {0, 1e9};
	for(int i=0; i<2; i++){
		for(int j=0; j<n[i]; j++){
			for(int k=0; k<n[i^1]; k++){
				pi cur = a[i][j];
				pi segs = a[i^1][k];
				pi sege = a[i^1][(k+1)%n[i^1]];
				pi vel = v[i] - v[i^1];
				if(ccw(segs, sege, cur) * ccw(segs, sege, cur + 100000.0L * vel) <= eps){
					llf s = 0, e = 1e5;
					for(int it=0; it<100; it++){
						llf m1 = (2*s+e)/3;
						llf m2 = (s+2*e)/3;
						pi pl = cur + m1 * vel;
						pi pr = cur + m2 * vel;
						if(abs(ccw(segs, sege, pl)) < abs(ccw(segs, sege, pr))){
							e = m2;
						}
						else s = m1;
					}
					time_period.push_back((s+e)/2);
				}
			}
		}
	}
	sort(all(time_period));
	time_period.resize(unique(all(time_period)) - time_period.begin());
	llf dap = -10;
	llf pos = -1;
	for(int i=1; i<sz(time_period); i++){
	//	cout << time_period[i - 1] << endl;
	//	cout << time_period[i] << endl;
		llf s = time_period[i - 1];
		llf e = time_period[i];
		for(int it=0; it<100; it++){
			llf m1 = (2*s+e)/3;
			llf m2 = (s+2*e)/3;
			if(insec(m1) > insec(m2) - eps){
				e = m2;
			}
			else s = m1;
		}
		llf npos = (s+e)/2;
		llf ninsec = insec(npos);
		/*
		cout << npos << endl;
		printf("%.20Lf\n", ninsec);
		cout << endl;
		*/
		if(ninsec > 0 && dap < ninsec - 1e-8L){
			dap = ninsec;
			pos = npos;
		}
	}
	if(dap < 0) puts("never");
	else printf("%.10Lf\n", pos);
}
