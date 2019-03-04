#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = pair<int, int>;
const int MAXN = 200005;
const int mod = 1e9 + 7;

struct bit{
	int tree[1000050];
	void add(int x, int v){
		x++;
		while(x < 1000050){
			tree[x] = max(tree[x], v);
			x += x & -x;
		}
	}
	int query(int x){
		x++;
		int ret = 0;
		while(x){
			ret = max(ret, tree[x]);
			x -= x & -x;
		}
		return ret;
	}
}bit;

vector<int> v[MAXN];
vector<lint> ans[MAXN];
int n;
pi a[MAXN];
int dp[MAXN];

struct query{
	pi x;
	int s, e, idx;
};

void dnc(int s, int e, int x, vector<query> &proc, int l, int r){
	int m = (l+r)/2;
	lint ret = 1e18;
	int opt = -1;
	for(int i=s; i<=e; i++){
		lint val = ans[x][i] + 1ll * (proc[m].x.first - a[v[x][i]].first) * (proc[m].x.second - a[v[x][i]].second);
		if(val < ret){
			ret = val;
			opt = i;
		}
	}
	ans[x+1][proc[m].idx] = min(ans[x+1][proc[m].idx], ret);
	if(m + 1 <= r) dnc(s, opt, x, proc, m + 1, r);
	if(l <= m - 1) dnc(opt, e, x, proc, l, m - 1);
}

void solve(int s, int e, int x, vector<query> q){
	if(q.empty()) return;
	int m = (s+e)/2;
	vector<query> proc, l, r;
	for(auto &i : q){
		if(i.s <= s && e <= i.e) proc.push_back(i);
		else{
			if(i.s <= m) l.push_back(i);
			if(m < i.e) r.push_back(i);
		}
	}
	if(proc.size()) dnc(s, e, x, proc, 0, proc.size() - 1);
	solve(s, m, x, l);
	solve(m + 1, e, x, r);
}

int main(){
	freopen("mowing.in", "r", stdin);
	freopen("mowing.out", "w", stdout);
	scanf("%d",&n);
	scanf("%d",&a[n+1].first);
	a[n+1].second = a[n+1].first;
	for(int i=1; i<=n; i++){
		scanf("%d %d",&a[i].first,&a[i].second);
	}
	sort(a, a + n + 2);
	for(int i=0; i<=n+1; i++){
		dp[i] = 1 + bit.query(a[i].second - 1);
		bit.add(a[i].second, dp[i]);
		v[dp[i]].push_back(i);
	}
	ans[1].push_back(0);
	for(int i=2; i<=dp[n+1]; i++){
		ans[i].resize(v[i].size());
		fill(ans[i].begin(), ans[i].end(), 1e18);
		vector<query> qq;
		int idx = 0;
		idx = 0;
		int l = 0, r = 0;
		for(auto &j : v[i]){
			while(l < v[i-1].size() && a[v[i-1][l]].second > a[j].second) l++;
			while(r < v[i-1].size() && a[v[i-1][r]].first < a[j].first) r++;
			qq.push_back({a[j], l, r - 1, idx++});
		}
		solve(0, v[i-1].size() - 1, i-1, qq);
	}
	cout << ans[dp[n+1]][0] << endl;
}
