#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = pair<int, int>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
const int mod = 1e9 + 7;
const int MAXN = 100005;
const int MAXT = 530000;

struct node{
	int to, l, r;
};

vector<node> gph[MAXN];
vector<int> vect;

pi operator+(pi a, pi b){
	pi c;
	c.first = min(a.first, b.first);
	c.second = (a.first == c.first ? a.second : 0) + (b.first == c.first ? b.second : 0);
	return c;
}

struct seg{
	pi tree[MAXT];
	int lazy[MAXT];
	void init(int s, int e, int p){
		if(s == e){
			tree[p] = pi(0, vect[s + 1] - vect[s]);
			return;
		}
		int m = (s+e)/2;
		init(s, m, 2*p);
		init(m+1, e, 2*p+1);
		tree[p] = tree[2*p] + tree[2*p+1];
	}
	void lazydown(int p){
		for(int i = 2*p; i < 2*p+2; i++){
			tree[i].first += lazy[p];
			lazy[i] += lazy[p];
		}
		lazy[p] = 0;
	}
	void add(int s, int e, int ps, int pe, int p, int v){
		if(e < ps || pe < s) return;
		if(s <= ps && pe <= e){
			tree[p].first += v;
			lazy[p] += v;
			return;
		}
		lazydown(p);
		int pm = (ps+pe)/2;
		add(s, e, ps, pm, 2*p, v);
		add(s, e, pm+1, pe, 2*p+1, v);
		tree[p] = tree[2*p] + tree[2*p+1];
	}
}seg;

int m, ans[MAXN];

void dfs(int x, int p){
	ans[x] = m - (seg.tree[1].first ? 0 : seg.tree[1].second);
	for(auto &y : gph[x]){
		if(y.to == p) continue;
		seg.add(y.l, y.r - 1, 0, sz(vect) - 2, 1, 1);
		dfs(y.to, x);
		seg.add(y.l, y.r - 1, 0, sz(vect) - 2, 1, -1);
	}
}

int main(){	
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int n;
	cin >> n >> m;
	vect.push_back(1);
	vect.push_back(m+1);
	for(int i = 0; i < n - 1; i++){
		int u, v, x, y; cin >> u >> v >> x >> y;
		gph[u].push_back({v, x, y + 1});
		gph[v].push_back({u, x, y + 1});
		vect.push_back(x);
		vect.push_back(y + 1);
	}
	sort(all(vect));
	for(int i = 1; i <= n; i++){
		for(auto &j : gph[i]){
			j.l = lower_bound(all(vect), j.l) - vect.begin();
			j.r = lower_bound(all(vect), j.r) - vect.begin();
		}
	}
	seg.init(0, sz(vect) - 2, 1);
	dfs(1, -1);
	for(int i = 2; i <= n; i++) cout << ans[i] << "\n";
	/*
	int n; cin >> n;
	string test = "banna";
	n = sz(test);
	auto query = [&](int x, int y){
		if(x % 2 == 1) x++, y--;
		if(x > y) return 1;
		if(x == y) return 1;
		cout << "? " << x/2+1 << " " << y/2+1 << endl;
		int z; cin >> z; return z;
	};
	vector<int> dp(2*n-1);
	int c = 0, p = 0, ans = 0;
	for(int i = 0; i < 2 * n - 1; i++){
		if(i < c + p) dp[i] = min(dp[2 * c - i], c + p - i);
		while(i + dp[i] + 1 < 2 * n - 1 && i - dp[i] - 1 >= 0 && query(i - dp[i] - 1, i + dp[i] + 1)) dp[i]++;
		if(i + dp[i] > c + p){
			c = i;
			p = dp[i]; 
		}
		if(i % 2 == 0) ans = max(ans, 1 + (dp[i] / 2) * 2);
		else ans = max(ans, ((dp[i] + 1) / 2) * 2);
	}
	cout << "! " << ans << endl;*/
}
