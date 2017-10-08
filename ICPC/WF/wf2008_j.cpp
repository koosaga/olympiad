#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef long double llf;
typedef pair<llf, llf> pi;
const int mod = 1e9 + 7;
const llf eps = 1e-11;

struct seg{
	pi a, b;
	seg(double pa, double pb, double pc, double pd){
		a = pi(pa, pb);
		b = pi(pc, pd);
	}
};

llf ccw(pi a, pi b, pi c){
	llf dx1 = b.first - a.first;
	llf dy1 = b.second - a.second;
	llf dx2 = c.first - a.first;
	llf dy2 = c.second - a.second;
	return dx1 * dy2 - dy1 * dx2;
}

bool cross(seg a, seg b, pi &p){
	if(ccw(a.a, a.b, b.a) * ccw(a.a, a.b, b.b) <= 0 &&
			ccw(b.a, b.b, a.a) * ccw(b.a, b.b, a.b) <= 0){
		llf s = 0, e = 1;
		auto gen = [&](double t){
			return pi(a.a.first * t + a.b.first * (1 - t), a.a.second * t + a.b.second * (1 - t));
		};
		for(int i=0; i<100; i++){
			llf m1 = (2 * s + e) / 3;
			llf m2 = (s + 2 * e) / 3;
			double e1 = ccw(b.a, b.b, gen(m1));
			double e2 = ccw(b.a, b.b, gen(m2));
			e1 = fabs(e1), e2 = fabs(e2);
			if(e1 < e2) e = m2;
			else s = m1;
		}
		p = gen(s);
		return true;
	}
	return false;
}

int main(){
int tc = 0;
	while(1){
		int n;
		int p[105], h[105], b[105];
		scanf("%d",&n);
		if(n == 0) break;
		vector<llf> ans;
		vector<seg> v;
		for(int i=0; i<n; i++){
			scanf("%d %d %d",&p[i],&h[i],&b[i]);
			ans.push_back(p[i]);
			ans.push_back(p[i] - 0.5 * b[i]);
			ans.push_back(p[i] + 0.5 * b[i]);
			v.emplace_back(p[i] - 0.5 * b[i], 0, p[i], h[i]);
			v.emplace_back(p[i], h[i], p[i] + 0.5 * b[i], 0);
		}
		for(int i=0; i<v.size(); i++){
			for(int j=0; j<i; j++){
				pi p;
				if(cross(v[i], v[j], p)){
					ans.push_back(p.first);
				}
			}
		}
		sort(ans.begin(), ans.end());
		llf dap = 0;
		for(int i=0; i+1<ans.size(); i++){
			double s = ans[i], e = ans[i+1];
			llf arg = -1, ans = 0;
			for(auto &j : v){
				llf nb1 = (s - j.a.first) / (j.b.first - j.a.first);
				llf nb2 = (e - j.a.first) / (j.b.first - j.a.first);
				if(nb1 < -eps || nb2 > 1 + eps) continue;
				llf y1 = j.a.second * (1 - nb1) + j.b.second * nb1;
				llf y2 = j.a.second * (1 - nb2) + j.b.second * nb2;
				if(arg < y1 + y2){
					arg = y1 + y2;
					ans = hypot(y2 - y1, (nb2 - nb1) * (j.b.first - j.a.first));
				}
			}
			dap += ans;
		}
		printf("Case %d: %d\n\n", ++tc, (int)round(dap));
	}
}
