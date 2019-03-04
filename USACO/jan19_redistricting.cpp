#include <bits/stdc++.h>
using namespace std;
using pi = pair<int, int>;
const int MAXN = 300005;

int n, k, s[MAXN];
char str[MAXN];
int dp[MAXN];

struct seg{
	int tree[MAXN];
	void clear(){
		memset(tree, 0x3f, sizeof(tree));
	}
	void flush(int x){
		x++;
		while(x){
			tree[x] = 1e9;
			x -= x & -x;
		}
	}
	void upd(int x, int v){
		x++;
		while(x){
			tree[x] = min(tree[x], v);
			x -= x & -x;
		}
	}
	int query(int x){
		x++;
		x = max(x, 1);
		int ret = 1e9;
		while(x < MAXN){
			ret = min(ret, tree[x]);
			x += x & -x;
		}
		return ret;
	}
}seg;

void solve(int l, int r){
	if(l == r) return;
	int m = (l + r) / 2;
	solve(l, m);
	priority_queue<pi, vector<pi>, greater<pi> > pq;
	for(int i=l; i<=m; i++){
		pq.emplace(dp[i], i);
	}
	for(int i=m+1; i<=r; i++){
		while(!pq.empty() && pq.top().second < i - k) pq.pop();
		if(!pq.empty()) dp[i] = min(dp[i], pq.top().first + 1);
	}
	vector<pi> v1, v2;
	for(int i=l; i<=m; i++) v1.emplace_back(-s[i], i);
	for(int i=m+1; i<=r; i++) v2.emplace_back(-s[i], i);
	sort(v1.begin(), v1.end());
	sort(v2.begin(), v2.end());
	int ptr = 0;
	for(auto &i : v2){
		while(ptr < v1.size() && v1[ptr].first < i.first){
			seg.upd(v1[ptr].second, dp[v1[ptr].second]);
			ptr++;
		}
		dp[i.second] = min(dp[i.second], seg.query(i.second - k));
	}
	for(int i=0; i<ptr; i++) seg.flush(v1[i].second);
	solve(m+1, r);
}

int main(){
	freopen("redistricting.in", "r", stdin);
	freopen("redistricting.out", "w", stdout);
	scanf("%d %d %s",&n,&k,str);
	for(int i=1; i<=n; i++){
		s[i] = s[i-1];
		if(str[i-1] == 'G') s[i]++;
		else s[i]--;
	}
	memset(dp, 0x3f, sizeof(dp));
	dp[0] = 0;
	seg.clear();
	solve(0, n);
	cout << dp[n] << endl;
}
