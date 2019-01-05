#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = pair<lint, lint>;
const int MAXN = 100005;
const int MAXT = 270000;

int n, a[MAXN], dp[MAXN];
lint k, dcnt[MAXN];

pi merge(pi a, pi b){
	if(a < b) swap(a, b);
	if(a.first == b.first) return pi(a.first, min(k, a.second + b.second));
	return a;
}

struct seg{
	pi tree[MAXT];
	int lim;
	void init(int n){
		for(lim = 1; lim <= n; lim <<= 1);
		fill(tree, tree + MAXT, pi(-1, 0));
	}
	void add(int x, pi v){
		x += lim;
		tree[x] = merge(tree[x], v);
		while(x > 1){
			x >>= 1;
			tree[x] = merge(tree[2*x], tree[2*x+1]);
		}
	}
	pi query(int s, int e){
		s += lim; e += lim;
		pi ret(-1, 0);
		while(s < e){
			if(s % 2 == 1) ret = merge(ret, tree[s++]);
			if(e % 2 == 0) ret = merge(ret, tree[e--]);
			s >>= 1;
			e >>= 1;
		}
		if(s == e) ret = merge(tree[s], ret);
		return ret;
	}
}seg;

vector<int> lispos[MAXN];

int main(){
	freopen("itout.in", "r", stdin);
	freopen("itout.out", "w", stdout);
	scanf("%d %lld",&n,&k);
	for(int i=1; i<=n; i++){
		int x; scanf("%d",&x); a[x] = i;
	}
	dcnt[n + 1] = 1;
	a[n + 1] = n + 1;
	seg.init(n + 1);
	seg.add(n + 1, pi(0, 1));
	for(int i=n; i>=0; i--){
		tie(dp[i], dcnt[i]) = seg.query(a[i] + 1, n + 1);
		dp[i]++;
		seg.add(a[i], pi(dp[i], dcnt[i]));
	}
	for(int i=n+1; i>=0; i--){
		lispos[dp[i]].push_back(i);
	}
	vector<int> kLIS = {0};
	int ptr = 0;
	for(int i=dp[0]-1; i>=0; i--){
		for(auto &j : lispos[i]){
			if(a[j] < a[ptr]) continue;
			if(dcnt[j] < k) k -= dcnt[j];
			else{
				kLIS.push_back(j); ptr = j;
				break;
			}
		}
	}
	vector<int> dap;
	for(int i=1; i<kLIS.size(); i++){
		for(int j=kLIS[i-1] + 1; j<kLIS[i]; j++) dap.push_back(j);
	}
	cout << dap.size() << endl;
	for(auto &i : dap) printf("%d\n", i);
}
