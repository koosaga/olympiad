#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = pair<int, int>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
const int MAXN = 100005;
const int MAXT = 270000;

int ord[MAXN], nord[MAXN], cnt[MAXN], aux[MAXN];

void solve(int n, char *str, int *sfx, int *rev, int *lcp){
	int p = 1;
	memset(ord, 0, sizeof(ord));
	for(int i = 0; i < n; i++){
		sfx[i] = i;
		ord[i] = str[i];
	}
	int pnt = 1;
	while(true){
		memset(cnt, 0, sizeof(cnt));
		for(int i = 0; i < n; i++) cnt[ord[min(i + p, n)]]++;
		for(int i = 1; i <= n || i <= 255; i++) cnt[i] += cnt[i - 1];
		for(int i = n - 1; i >= 0; i--){
			aux[--cnt[ord[min(i + p, n)]]] = i;
		}
		memset(cnt, 0, sizeof(cnt));
		for(int i = 0; i < n; i++) cnt[ord[i]]++;
		for(int i = 1; i <= n || i <= 255; i++) cnt[i] += cnt[i - 1];
		for(int i = n - 1; i >= 0; i--){
			sfx[--cnt[ord[aux[i]]]] = aux[i];
		}
		if(pnt == n) break;
		pnt = 1;
		nord[sfx[0]] = 1;
		for(int i = 1; i < n; i++){
			if(ord[sfx[i-1]] != ord[sfx[i]] || ord[sfx[i-1] + p] != ord[sfx[i] + p]){
				pnt++;
			}
			nord[sfx[i]] = pnt;
		}
		memcpy(ord, nord, sizeof(int) * n);
		p <<= 1;
	}
	for(int i = 0; i < n; i++) rev[sfx[i]] = i;
	int h = 0;
	for(int i = 0; i < n; i++){
		if(rev[i]){
			int prv = sfx[rev[i] - 1];
			while(str[prv + h] == str[i + h]) h++;
			lcp[rev[i]] = h;
		}
		if(h) h--;
	}
}

struct seg{
	int tree[MAXT], lim;
	void init(int n, int *a){
		for(lim = 1; lim <= n; lim <<= 1);
		memset(tree, 0x3f, sizeof(tree));
		for(int i = 0; i < n; i++) tree[i + lim] = a[i];
		for(int i = lim-1; i; i--) tree[i] = min(tree[2*i], tree[2*i+1]);
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
}seg;

char s[MAXN];
int sfx[MAXN], rev[MAXN], lcp[MAXN];

int glcp(int u, int v){
	if(u > v) swap(u, v);
	return seg.query(u + 1, v);
}

int dp[MAXN], fn[MAXN];

int main(){	
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	fgets(s, MAXN, stdin);
	int n = strlen(s);
	if(s[n - 1] == '\n') n--;
	s[n] = 0;
	solve(n, s, sfx, rev, lcp);
	seg.init(n, lcp);
	set<int> st;
	for(int i = 1; i < n; i++){
		st.insert(rev[i - 1]);
		auto it = st.lower_bound(rev[i]);
		if(it != st.begin()) fn[i] = max(fn[i], glcp(*prev(it), rev[i]));
		if(it != st.end()) fn[i] = max(fn[i], glcp(*it, rev[i]));
	}
	priority_queue<pi, vector<pi>, greater<pi> > pq;
	for(int i = 1; i <= n; i++){
		dp[i] = dp[i - 1] + 1;
		pq.emplace(dp[i-1], fn[i-1] + i-1);
		while(sz(pq) && pq.top().second < i) pq.pop();
		if(sz(pq)) dp[i] = min(dp[i], pq.top().first + 3);
	}
	cout << dp[n] << "\n";
}
ㅈ