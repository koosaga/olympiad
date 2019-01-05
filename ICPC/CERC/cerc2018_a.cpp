#include <bits/stdc++.h>
using namespace std;
using lint = long long;
const int MAXN = 300005;
using pi = pair<int, int>;

struct sfxarray{
	int ord[MAXN], nord[MAXN], cnt[MAXN], aux[MAXN];
	void solve(int n, char *str, int *sfx, int *rev, int *lcp){
		int p = 1;
		memset(ord, 0, sizeof(ord));
		for(int i=0; i<n; i++){
			sfx[i] = i;
			ord[i] = str[i];
		}
		int pnt = 1;
		while(1){
			memset(cnt, 0, sizeof(cnt));
			for(int i=0; i<n; i++) cnt[ord[min(i+p, n)]]++;
			for(int i=1; i<=n || i<=255; i++) cnt[i] += cnt[i-1];
			for(int i=n-1; i>=0; i--)
				aux[--cnt[ord[min(i+p, n)]]] = i;
			memset(cnt, 0, sizeof(cnt));
			for(int i=0; i<n; i++) cnt[ord[i]]++;
			for(int i=1; i<=n || i<=255; i++) cnt[i] += cnt[i-1];
			for(int i=n-1; i>=0; i--)
				sfx[--cnt[ord[aux[i]]]] = aux[i];
			if(pnt == n) break;
			pnt = 1;
			nord[sfx[0]] = 1;
			for(int i=1; i<n; i++){
				if(ord[sfx[i-1]] != ord[sfx[i]] || ord[sfx[i-1] + p] != ord[sfx[i] + p]){
					pnt++;
				}
				nord[sfx[i]] = pnt;
			}
			memcpy(ord, nord, sizeof(int) * n);
			p *= 2;
		}
		for(int i=0; i<n; i++) rev[sfx[i]] = i;
		int h = 0;
		for(int i=0; i<n; i++){
			if(rev[i]){
				int prv = sfx[rev[i] - 1];
				while(str[prv + h] == str[i + h]) h++;
				lcp[rev[i]] = h;
			}
			h = max(h-1, 0);
		}
	}
}sfxarray;

struct seg{
	int tree[MAXN];
	void init(){
		memset(tree, 0x3f, sizeof(tree));
	}
	void update(int x, int v){
		x++;
		while(x < MAXN){
			tree[x] = min(tree[x], v);
			x += x & -x;
		}
	}
	int query(int x){
		x++;
		int ret= 1e9;
		while(x){
			ret = min(ret, tree[x]);
			x -= x & -x;
		}
		return ret;
	}
}seg;

char str[MAXN], buf[MAXN];
int sfx[MAXN], lcp[MAXN], rev[MAXN];
vector<pi> ev[MAXN];
int ans[MAXN];
int dp[MAXN];
priority_queue<pi> pq;

int main(){
	int q; 
	scanf("%d %s",&q, str);
	int n = strlen(str);
	sfxarray.solve(n, str, sfx, rev, lcp);
	while(q--){
		scanf("%s", buf);
		int s = 0, e = n;
		for(int i=0; buf[i]; i++){
			int ns, ne;
			{
				int ts = s, te = e;
				while(ts != te){
					int m = (ts + te) / 2;
					if(str[sfx[m] + i] < buf[i]) ts = m + 1;
					else te = m;
				}
				ns = ts;
			}
			{
				int ts = s, te = e;
				while(ts != te){
					int m = (ts + te) / 2;
					if(str[sfx[m] + i] <= buf[i]) ts = m + 1;
					else te = m;
				}
				ne = ts;
			}
			s = ns;
			e = ne;
			if(s == e) break;
		}
		int l = strlen(buf);
		ev[s].emplace_back(l, e);
	}
	for(int i=0; i<n; i++){
		for(auto &j : ev[i]) pq.push(j);
		while(!pq.empty() && pq.top().second <= i) pq.pop();
		if(!pq.empty()) ans[sfx[i]] = pq.top().first;
	}
	seg.init();
	seg.update(n, 0);
	for(int i=n-1; i>=0; i--){
		dp[i] = seg.query(i + ans[i]) + 1;
		seg.update(i, dp[i]);
	}
	if(dp[0]> 1e8) dp[0] = -1;
	cout << dp[0] << endl;
}
