#include <bits/stdc++.h>
using namespace std;
const int MAXN = 1000005;
const int dx[4] = {1, 0, -1, 0};
const int dy[4] = {0, 1, 0, -1};
typedef pair<int, int> pi;
typedef long long lint;

int n, a[MAXN], b[MAXN];
struct seg{
	pi tree[2100000];
	int lim;
	void init(int n, int *a){
		for(lim = 1; lim <= n; lim <<= 1);
		fill(tree, tree + 2100000, pi(-1e9, -1e9));
		for(int i=0; i<n; i++){
			tree[i + lim] = pi(a[i], i);
		}
		for(int i=lim-1; i; i--){
			tree[i] = max(tree[2*i], tree[2*i+1]);
		}
	}
	pi query(int s, int e){
		s += lim;
		e += lim;
		pi ret(-1e9, -1e9);
		while(s < e){
			if(s%2 == 1) ret = max(ret, tree[s++]);
			if(e%2 == 0) ret = max(ret, tree[e--]);
			s >>= 1;
			e >>= 1;
		}
		if(s == e) ret = max(ret, tree[s]);
		return ret;
	}
}sega, segb;

lint solve(int s, int e, int x){
	if(s > e) return 0;
	x = min(x, -segb.query(s, e).first);
	auto m = sega.query(s, e);
	lint ans = (e - s + 1) * max(0, x - m.first); 
	ans += solve(s, m.second - 1, m.first);
	ans += solve(m.second + 1, e, m.first);
	return ans;
}

int main(){
	int tc;
	scanf("%d",&tc);
	while(tc--){
		scanf("%d",&n);
		for(int i=0; i<n; i++) scanf("%d",&a[i]);
		for(int i=0; i<n; i++) scanf("%d",&b[i]), b[i] = -b[i];
		sega.init(n, a);
		segb.init(n, b);
		cout << solve(0, n-1, 1e9)<< endl;
	}
}