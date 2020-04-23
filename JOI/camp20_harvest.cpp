#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using lint = long long;
using pi = pair<lint, lint>;
const int MAXN = 400005;

struct b1{
	lint tree[MAXN];
	void add(int x, lint v){
		for(int i=x+1; i<MAXN; i+=i&-i){
			tree[i] += v;
		}
	}
	lint query(int x){
		lint ret = 0;
		for(int i=x+1; i; i-=i&-i){
			ret += tree[i];
		}
		return ret;
	}
}b1, b2;

struct fuck{
	vector<int> tree[MAXN];
	vector<lint> elem[MAXN];
	int SZ;
	void prepare(vector<pi> v){
		SZ = sz(v) + 2;
		for(auto &[x, y] : v){
			for(int i=x+1; i<SZ; i+=i&-i){
				elem[i].push_back(y);
			}
		}
		for(int i=0; i<SZ; i++){
			sort(all(elem[i]));
			elem[i].resize(unique(all(elem[i])) - elem[i].begin());
			tree[i].resize(sz(elem[i]) + 1);
		}
	}
	void add(int x, lint v, int arg){
		for(int i=x+1; i<SZ; i+=i&-i){
			auto lp = lower_bound(all(elem[i]), v) - elem[i].begin() + 1;
			for(int j=lp; j<sz(tree[i]); j+=j&-j){
				tree[i][j] += arg;
			}
		}
	}
	int query(int x, lint y){
		int ret = 0;
		for(int i=x+1; i; i-=i&-i){
			int pos = upper_bound(all(elem[i]), y) - elem[i].begin();
			for(int j=pos; j; j-=j&-j){
				ret += tree[i][j];
			}
		}
		return ret;
	}
	void clear(){
		for(int i=0; i<SZ; i++){
			tree[i].clear();
			elem[i].clear();
		}
	}
}fuck;

int n, m, q, l, c;
vector<pi> v[MAXN];
vector<pi> gph[MAXN];
vector<lint> deliv[MAXN];
int nxt[MAXN]; lint len[MAXN];
lint cyclen[MAXN], ans[MAXN];

void solve(vector<int> vtx){
	lint L = cyclen[vtx[0]];
	vector<lint> sum(sz(vtx));
	vector<lint> crd;
	for(int i=sz(vtx)-1; i>=0; i--){
		sum[i] = (i+1 < sz(vtx) ? sum[i+1] : 0) + len[vtx[i]];
		for(auto &j : deliv[vtx[i]]){
			crd.push_back(j + sum[i]);
			crd.push_back(j + L + sum[i]);
		}
	}
	sort(all(crd));
	crd.resize(unique(all(crd)) - crd.begin());
	vector<pi> preps;
	for(int i=0; i<sz(crd); i++){
		preps.emplace_back(i, L - crd[i] % L);
	}
	fuck.prepare(preps);
	auto ADD = [&](lint x){
		int pos = lower_bound(all(crd), x) - crd.begin();
		b1.add(pos, +1);
		b2.add(pos, -(x/L));
		fuck.add(pos, L - x % L, +1);
	};
	auto REM = [&](lint x){
		int pos = lower_bound(all(crd), x) - crd.begin();
		b1.add(pos, -1);
		b2.add(pos, +x/L);
		fuck.add(pos, L - x % L, -1);
	};
	for(int i=sz(vtx)-1; i>=0; i--){
		sum[i] = (i+1 < sz(vtx) ? sum[i+1] : 0) + len[vtx[i]];
		for(auto &j : deliv[vtx[i]]){
			ADD(j + L + sum[i]);
		}
	}
	for(int i=0; i<sz(vtx); i++){
		for(auto &j : deliv[vtx[i]]){
			REM(j + L + sum[i]);
			ADD(j + sum[i]);
		}
		for(auto &[d, idx] : v[vtx[i]]){
			int j = lower_bound(all(crd), d + sum[i] + 1) - crd.begin();
			int cnt = b1.query(j - 1);
			ans[idx] += b2.query(j - 1);
			ans[idx] -= fuck.query(j - 1, L - 1 - (d + sum[i]) % L);
			ans[idx] += (1 + (d + sum[i]) / L) * cnt;
		}
	}
	for(int i=sz(vtx)-1; i>=0; i--){
		for(auto &j : deliv[vtx[i]]){
			REM(j + sum[i]);
		}
	}
	fuck.clear();
}

struct query{
	int st, ed;
	lint x; int idx;
};

lint dep[MAXN];
int din[MAXN], dout[MAXN], piv;

void dfs(int x, vector<pi> &pinst, vector<query> &qinst){
	din[x] = ++piv;
	for(auto &i : deliv[x]){
		pinst.emplace_back(din[x], dep[x] + i);
	}
	for(auto &[w, v] : gph[x]){
		dep[v] = dep[x] + w;
		dfs(v, pinst, qinst);
	}
	dout[x] = piv;
	for(auto &[thres, idx] : v[x]){
		qinst.push_back({din[x], dout[x], thres + dep[x], (int)idx});
	}
	deliv[x].clear();
}


void solve(){
	vector<int> indeg(n);
	for(int i=0; i<n; i++){
		gph[nxt[i]].emplace_back(len[i], i);
		indeg[nxt[i]]++;
	}
	queue<int> que;
	for(int i=0; i<n; i++){
		if(!indeg[i]){
			que.push(i);
		}
	}
	while(sz(que)){
		int i = que.front();
		que.pop();
		indeg[nxt[i]]--;
		if(indeg[nxt[i]] == 0) que.push(nxt[i]);
	}
	for(int i=0; i<n; i++){
		if(indeg[i] && !cyclen[i]){
			lint tot = len[i];
			for(int j=nxt[i]; j!=i; j=nxt[j]) tot += len[j];
			for(int j=i; !cyclen[j]; j=nxt[j]){
				cyclen[j] = tot;
			}
		}
	}
	for(int i=0; i<n; i++){
		if(indeg[i]){
			vector<pi> pinst;
			vector<query> qinst;
			for(auto &[w, v] : gph[i]){
				if(indeg[v]) continue;
				dep[v] = w;
				dfs(v, pinst, qinst);
			}
			for(auto &j : pinst){
				deliv[i].push_back(j.second);
			}
			{
				vector<lint> crd;
				for(auto &[pos, thres] : pinst) crd.push_back(thres);
				sort(all(crd));
				crd.resize(unique(all(crd)) - crd.begin());
				for(auto &[pos, thres] : pinst){
					thres = lower_bound(all(crd), thres) - crd.begin();
				}
				sort(all(pinst));
				sort(all(qinst), [&](const query &a, const query &b){
					return a.st < b.st;
				});
				int p = 0;
				for(auto &i : qinst){
					while(p < sz(pinst) && pinst[p].first < i.st){
						b1.add(pinst[p++].second, +1);
					}
					int pos = upper_bound(all(crd), i.x) - crd.begin();
					ans[i.idx] -= b1.query(pos - 1);
				}
				for(int i=0; i<p; i++) b1.add(pinst[i].second, -1);
				p = 0;
				sort(all(qinst), [&](const query &a, const query &b){
					return a.ed < b.ed;
				});
				for(auto &i : qinst){
					while(p < sz(pinst) && pinst[p].first <= i.ed){
						b1.add(pinst[p++].second, +1);
					}
					int pos = upper_bound(all(crd), i.x) - crd.begin();
					ans[i.idx] += b1.query(pos - 1);
				}
				for(int i=0; i<p; i++) b1.add(pinst[i].second, -1);
			}
		}
	}
	for(int i=0; i<n; i++){
		if(!indeg[i]) continue;
		vector<int> vtx;
		for(int j=i; indeg[j]; j=nxt[j]){
			vtx.push_back(j);
			indeg[j] = 0;
		}
		solve(vtx);
	}
}

int main(){
	scanf("%d %d %d %d",&n,&m,&l,&c);
	vector<int> a(n), b(m), idx(n);
	for(int i=0; i<n; i++){
		scanf("%d",&a[i]);
		a[i] = (l - a[i]) % l;
		idx[i] = i;
	}
	for(int i=0; i<m; i++){
		scanf("%d",&b[i]);
		b[i] = (l - b[i]) % l;
	}
	reverse(all(a));
	reverse(all(idx));
	reverse(all(b));
	if(a.back() == 0){
		rotate(a.begin(), a.end() - 1, a.end());
		rotate(idx.begin(), idx.end() - 1, idx.end());
	}
	scanf("%d",&q);
	for(int i=0; i<q; i++){
		int x;
		lint t; 
		scanf("%d %lld",&x,&t);
		x = idx[x - 1];
		v[x].emplace_back(t, i);
	}
	for(int i=0; i<n; i++){
		int nxtpos = (c + a[i]) % l;
		nxt[i] = lower_bound(all(a), nxtpos) - a.begin();
		lint newpos = (c + a[i]) + (nxt[i] == n ? (a[0] + l) : a[nxt[i]]) - nxtpos;
		len[i] = newpos - a[i];
		if(nxt[i] == n) nxt[i] = 0;
	}
	for(int i=0; i<m; i++){
		int nxt = lower_bound(all(a), b[i]) - a.begin();
		if(nxt == n) nxt = 0;
		int delay = (a[nxt] - b[i] + l) % l;
		deliv[nxt].push_back(delay);
	}
	solve();
	for(int i=0; i<q; i++) printf("%lld\n", ans[i]);
}
