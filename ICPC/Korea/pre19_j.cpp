#include <bits/stdc++.h>
using namespace std;
const int MAXN = 100005;
using lint = long long;
using pi = pair<lint, lint>;
#define sz(v) ((int)(v).size())

struct cht{
	vector<pi> v;
	long double crs(pi x, pi y){
		return 1.0L * (x.second - y.second) / (y.first - x.first);
	}
	void add(pi x){
		while(sz(v) >= 2 && crs(v[v.size()-2], v.back()) >= crs(v.back(), x)){
			v.pop_back();
		}
		v.push_back(x);
	}
	lint query(int x){
		int s = 0, e = sz(v) - 1;
		while(s != e){
			int m = (s+e)/2;
			if(v[m].first * x + v[m].second < v[m+1].first * x + v[m+1].second) e = m;
			else s = m + 1;
		}
		return v[s].first * x + v[s].second;
	}
}cht;

int n, b[MAXN], c[MAXN];
lint a[MAXN], dp[MAXN];

int main(){
	scanf("%d",&n); n--;
	for(int i=n; i; i--) scanf("%lld",&a[i]);
	for(int i=n; i; i--) scanf("%d %d",&c[i],&b[i]);
	for(int i=1; i<=n; i++) a[i] += a[i-1];
	for(int i=1; i<=n; i++){
		cht.add(pi(-a[i-1], dp[i-1]));
		dp[i] = cht.query(b[i]) + a[i] * b[i] + c[i];
	}
	cout << dp[n] << endl;
}
