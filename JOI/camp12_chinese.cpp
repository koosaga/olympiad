#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<int, int> pi;
 
int n, a[100005];
set<int> s;
vector<int> v;
 
struct seg{
	int tree[530000], lim;
	void init(int n){
		memset(tree, 0x3f, sizeof(tree));
		for(lim = 1; lim <= n; lim <<= 1);
	}
	void add(int x, int v){
		x += lim;
		tree[x] = min(tree[x], v);
		while(x > 1){
			x >>= 1;
			tree[x] = min(tree[2*x], tree[2*x+1]);
		}
	}
	int query(int s, int e){
		s += lim;
		e += lim;
		int ret = 1e9;
		while(s < e){
			if(s%2 == 1) ret = min(ret, tree[s++]);
			if(e%2 == 0) ret = min(ret, tree[e--]);
			s >>= 1;
			e >>= 1;
		}
		if(s == e) ret = min(ret, tree[s]);
		return ret;
	}
}segx, segy;
 
int solve(int x){
	auto t = s.lower_bound(x);
	auto u = s.upper_bound(n+x);
	int ret = 1e9;
	if(t != s.end()){
		ret = min(ret, n - (*t - x));
	}
	if(u != s.begin()){
		u--;
		ret = min(ret, n - (n+x - *u));
	}
	int s = 0, e = v.size()-2;
	while(s != e){
		int m = (s+e)/2;
		if(v[m] + v[m+1] <= n + 2 * x) s = m+1;
		else e = m;
	}
	auto lo = lower_bound(v.begin(), v.end(), x) - v.begin();
	auto hi = upper_bound(v.begin(), v.end(), n+x) - v.begin() - 1;
	ret = min(ret, n - x + segx.query(lo, s-1));
	ret = min(ret, 2 * n + x + segy.query(s, hi-1));
	return ret;
}
 
int main(){
	scanf("%d",&n);
	for(int i=2; i<=n; i++){
		scanf("%d",&a[i]);
		a[i] += n - i;
		a[i] %= n;
		s.insert(a[i]);
		s.insert(a[i] + n);
	}
	for(auto &i : s) v.push_back(i);
	segx.init(v.size());
	segy.init(v.size());
	for(int i=0; i+1<v.size(); i++){
		segx.add(i, 2 * v[i] - v[i+1]);
		segy.add(i, v[i] - 2 * v[i+1]);
	}
	for(int i=0; i<n; i++){
		printf("%d\n", solve(i) + min(i, n - i));
	}
}