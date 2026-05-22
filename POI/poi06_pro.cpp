#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);
using namespace std;

using lint = long long;
using pi = array<lint, 2>;

const int MAXN = 1000005;
const int inf = 36501;

struct strongly_connected{
	int n, ecnt;
	vector<int> ghead, to, nxt;
	vector<int> val, comp, z;
	int Time, ncomps, piv;

	void init(int _n, int m_hint = 0){
		n = _n;
		ecnt = 0;
		ghead.assign(n, -1);
		to.clear(); nxt.clear();
		to.reserve(m_hint);
		nxt.reserve(m_hint);
	}

	void add_edge(int s, int e){
		to.push_back(e);
		nxt.push_back(ghead[s]);
		ghead[s] = ecnt++;
	}

	int dfs(int x){
		int low = val[x] = ++Time;
		z.push_back(x);
		for(int e = ghead[x]; e != -1; e = nxt[e]){
			int y = to[e];
			if(comp[y] < 0){
				if(val[y]) low = min(low, val[y]);
				else low = min(low, dfs(y));
			}
		}
		if(low == val[x]){
			while(1){
				int y = z.back();
				z.pop_back();
				comp[y] = ncomps;
				if(y == x) break;
			}
			ncomps++;
		}
		return val[x] = low;
	}

	void get_scc(int _n){
		n = _n;
		val.assign(n, 0);
		comp.assign(n, -1);
		z.clear();
		z.reserve(n);
		Time = ncomps = 0;
		for(int i=0; i<n; i++){
			if(comp[i] < 0) dfs(i);
		}
		for(int i=0; i<n; i++){
			comp[i] = ncomps - comp[i] - 1;
		}
		piv = ncomps;
		vector<int>().swap(z);
	}
}scc;

int n, m;

bitset<MAXN> chk;
bitset<MAXN> self_loop;
bitset<MAXN> vis;
bitset<MAXN> seen;
bitset<MAXN> multi;

int main(){
	scanf("%d %d",&n,&m);

	int orig_n = n;
	n++;

	scc.init(n, m);

	for(int i=0; i<m; i++){
		int s, e;
		scanf("%d %d",&s,&e);
		s--, e--;
		if(s == e) chk[s] = 1;
		else scc.add_edge(s, e);
	}

	scc.get_scc(n);

	vector<int> head(scc.piv, -1);
	vector<unsigned short> dp(scc.piv, 0);

	for(int i=0; i<n; i++){
		int c = scc.comp[i];
		scc.val[i] = head[c]; // reuse val[] as linked-list next pointer
		head[c] = i;

		if(seen[c]) multi[c] = 1;
		else seen[c] = 1;

		if(chk[i]) self_loop[c] = 1;
	}

	int sink = n - 1;
	int sink_comp = scc.comp[sink];

	vis[sink_comp] = 1;
	dp[sink_comp] = 1;

	int ans = 0;

	for(int c=sink_comp; c>=0; c--){
		if(c != sink_comp && !vis[c]){
			for(int v = head[c]; v != -1; v = scc.val[v]){
				for(int e = scc.ghead[v]; e != -1; e = scc.nxt[e]){
					int cj = scc.comp[scc.to[e]];
					if(cj != c && vis[cj]){
						vis[c] = 1;
						break;
					}
				}
				if(vis[c]) break;
			}
		}

		if(!vis[c]) continue;

		if(multi[c] || self_loop[c]){
			dp[c] = inf;
		}
		else{
			int cur = dp[c];
			int v = head[c];
			for(int e = scc.ghead[v]; e != -1; e = scc.nxt[e]){
				int cj = scc.comp[scc.to[e]];
				if(cj != c){
					cur += dp[cj];
					if(cur >= inf){
						cur = inf;
						break;
					}
				}
			}
			dp[c] = cur;
		}

		ans = max(ans, (int)dp[c]);
	}

	if(ans == inf) puts("zawsze");
	else printf("%d\n", ans);

	int cnt = 0;
	for(int i=0; i<orig_n; i++){
		if(dp[scc.comp[i]] == ans) cnt++;
	}

	printf("%d\n", cnt);

	for(int i=0; i<orig_n; i++){
		if(dp[scc.comp[i]] == ans) printf("%d ", i + 1);
	}
}