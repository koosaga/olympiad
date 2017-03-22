#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<lint, lint> pi;
const int mod = 1e9 + 7;

int n, k;
int a[100005], b[100005];
pi c[100005];

struct bit{
	int tree[100005];
	void add(int x, int v){
		while(x <= n){
			tree[x] += v;
			x += x & -x;
		}
	}
	int f(int x){
		int ret = 0;
		while(x){
			ret += tree[x];
			x -= x & -x;
		}
		return ret;
	}
	int query(int s, int e){
		if(s > e) return 0;
		return f(e) - f(s-1);
	}
}bit;

lint solve(int s, int e){
	if(s == e) return 0;
	int m = (s+e)/2;
	lint ret = solve(s, m) + solve(m+1, e);
	vector<pi> l, r;
	for(int i=s; i<=m; i++) l.push_back(c[i]);
	for(int i=m+1; i<=e; i++) r.push_back(c[i]);
	sort(l.begin(), l.end());
	sort(r.begin(), r.end());
	int p = 0;
	for(auto &i : l){
		while(p < r.size() && r[p].first < i.first){
			bit.add(r[p++].second, 1);
		}
		ret += bit.query(1, i.second - k - 1) + bit.query(i.second + k + 1, n);
	}
	for(int i=0; i<p; i++) bit.add(r[i].second, -1);
	return ret;
}

int main(){
	freopen("friendcross.in", "r", stdin);
	freopen("friendcross.out", "w", stdout);
	scanf("%d %d",&n,&k);
	for(int i=1; i<=n; i++){
		int x;
		scanf("%d",&x);
		a[x] = i;
	}
	for(int i=1; i<=n; i++){
		int x;
		scanf("%d",&x);
		b[x] = i;
	}
	for(int i=1; i<=n; i++){
		c[a[i]] = pi(b[i], i);
	}
	cout << solve(1, n);
}
