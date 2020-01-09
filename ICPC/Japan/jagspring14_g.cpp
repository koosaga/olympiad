#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using lint = long long;
using llf = long double;
using pi = pair<lint, lint>;
const int MAXN = 30005;

int n, m, a[MAXN];
int ansl[MAXN], ansr[MAXN];

vector<pi> conv_frac(llf x){
	vector<pi> v;
	for(int i=1; i<=40000; i++){
		v.emplace_back((lint)floor(x * i) - 1, i);
		v.emplace_back((lint)floor(x * i), i);
		v.emplace_back((lint)floor(x * i) + 1, i);
	}
	sort(all(v), [&](const pi &a, const pi &b){
		return a.first * b.second < b.first * a.second;
	});
	return v;
}

lint fceil(int x, pi y){
	return (x * y.first + y.second - 1) / y.second;
}

lint ffloor(int x, pi y){
	return (x * y.first) / y.second;
}

int main(){
	scanf("%d %d",&m,&n);
	for(int i=0; i<n; i++) scanf("%d",&a[i]);
	if(accumulate(a, a + n, 0ll) >= m){
		auto func = [&](llf m){
			lint ans = 0;
			for(int j=0; j<n; j++) ans += (lint)ceil(a[j] * m);
			return ans;
		};
		llf s = 0, e = 1;
		for(int i=0; i<200; i++){
			llf mi = (s+e)/2;
			if(func(mi) <= m) s = mi;
			else e = mi;
		}
		llf minv = 1e18, maxv = 0;
		for(int i=0; i<n; i++){
			ansl[i] = (lint)ceil(a[i] * s);
			maxv = max(maxv, (llf)ansl[i] / (a[i] + 1));
			if(a[i]) minv = min(minv, (llf)ansl[i] / a[i]);
		}
		if(minv < maxv || accumulate(ansl, ansl + n, 0ll) != m){
			puts("impossible");
		}
		else{
			for(int i=0; i<n; i++) printf("%d %d\n", ansl[i], ansl[i]);
		}
		return 0;
	}
	{ 
		auto func = [&](llf r){
			lint ans = 0;
			for(int i=0; i<n; i++) ans += (lint)floor((a[i] + 1) * r);
			for(int i=0; i<n; i++){
				lint tmp = ans - (lint)floor((a[i] + 1) * r) + (lint)ceil(a[i] * r);
				if(tmp < m) return false;
			}
			return true;
		};
		auto ffunc = [&](pi r){
			lint ans = 0;
			for(int i=0; i<n; i++) ans += (lint)ffloor((a[i] + 1), r);
			for(int i=0; i<n; i++){
				lint tmp = ans - (lint)ffloor((a[i] + 1), r) + (lint)fceil(a[i], r);
				if(tmp < m) return false;
			}
			return true;
		};
		llf s = 1, e = 1e9;
		for(int i=0; i<200; i++){
			llf m = (s+e)/2;
			if(func(m)) e = m;
			else s = m;
		}
		auto v = conv_frac(e);
		auto p = *lower_bound(all(v), pi(1e9, 1), [&](const pi &a, const pi &b){
			return ffunc(a) < ffunc(b);
		});
		for(int i=0; i<n; i++){
			ansl[i] = (a[i] * p.first + p.second - 1) / p.second;
		}
	}
	{
		auto func = [&](llf r){
			lint ans = 0;
			for(int i=0; i<n; i++) ans += (lint)ceil(a[i] * r);
			for(int i=0; i<n; i++){
				lint tmp = ans - (lint)ceil(a[i] * r) + (lint)floor((a[i] + 1) * r);
				if(tmp > m) return false;
			}
			return true;
		};
		auto ffunc = [&](pi r){
			lint ans = 0;
			for(int i=0; i<n; i++) ans += (lint)fceil(a[i], r);
			for(int i=0; i<n; i++){
				lint tmp = ans - (lint)fceil(a[i], r) + (lint)ffloor((a[i] + 1), r);
				if(tmp > m) return false;
			}
			return true;
		};
		llf s = 1, e = 1e9;
		for(int i=0; i<200; i++){
			llf m = (s+e)/2;
			if(func(m)) s = m;
			else e = m;
		}
		auto v = conv_frac(s);
		auto p = *--upper_bound(all(v), pi(0, 1), [&](const pi &a, const pi &b){
			return ffunc(a) > ffunc(b);
		});
		for(int i=0; i<n; i++){
			ansr[i] = ((a[i] + 1) * p.first) / p.second;
		}
	}
	for(int i=0; i<n; i++) printf("%d %d\n", ansl[i], ansr[i]);
}
