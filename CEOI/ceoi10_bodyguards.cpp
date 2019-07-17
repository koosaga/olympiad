#include <bits/stdc++.h>
using namespace std;
const int MAXN = 200005;
using lint = long long;
using pi = pair<lint, lint>;

int n, m;
pi r[MAXN], c[MAXN];

struct cht{
	vector<pi> v;
	long double crs(pi x, pi y){
		return (long double)(y.second - x.second) / (x.first - y.first);
	}
	void add(pi x){
		while(v.size() >= 2 && crs(v[v.size() - 2], v.back()) >= crs(v.back(), x)){
			v.pop_back();
		}
		v.push_back(x);
	}
	lint query(long double x){
		while(v.size() >= 2 && v[v.size() - 2].first * x + v[v.size() - 2].second < 
			v.back().first * x + v.back().second){
			v.pop_back();
		}
		auto ans = min(3e18L, v.back().first * x + v.back().second);
		return (lint)round(ans);
	}
}cht;

int main(){
	scanf("%d",&n);
	for(int i=1; i<=n; i++) scanf("%lld %lld",&r[i].first,&r[i].second);
	scanf("%d",&m);
	for(int i=1; i<=m; i++) scanf("%lld %lld",&c[i].first,&c[i].second);
	sort(r + 1, r + n + 1);
	sort(c + 1, c + m + 1);
	for(int i=1; i<=n; i++){
		r[i].first *= r[i].second;
		r[i].first += r[i-1].first;
	}
	for(int i=1; i<=m; i++){
		c[i].first *= c[i].second;
		c[i].first += c[i-1].first;
	}
	for(int i=n; i>=0; i--){
		r[i].second += r[i+1].second;
	}
	for(int i=m; i>=0; i--){
		c[i].second += c[i+1].second;
	}
	lint ret = 2e18;
	for(int i=0; i<=m; i++) cht.add(pi(c[i + 1].second, c[i].first));
	for(int i=0; i<=n; i++) ret = min(ret, cht.query(r[i + 1].second) + r[i].first);
	if(r[n].first != ret) puts("0");
	else puts("1");
}
