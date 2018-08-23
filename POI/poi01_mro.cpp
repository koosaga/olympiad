#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = pair<int, int>;
const int MAXN = 5005;

int n, m, p[MAXN], c[MAXN];
vector<int> gph[MAXN];
int par[MAXN], dep[MAXN], din[MAXN], dout[MAXN], piv;

struct bit{
	int tree[MAXN];
	void clear(){
		memset(tree, 0, sizeof(tree));
	}
	void add(int x, int v){
		while(x <= n){
			tree[x] += v;
			x += x & -x;
		}
	}
	int query(int x){
		int ret = 0;
		while(x){
			ret += tree[x];
			x -= x & -x;
		}
		return ret;
	}
}bit;

void dfs(int x, int p){
	din[x] = ++piv;
	for(auto &i : gph[x]){
		if(i == p) continue;
		dep[i] = dep[x] + 1;
		par[i] = x;
		dfs(i, x);
	}
	dout[x] = piv;
}

int chk[MAXN];

void proc(int r){
	piv = 0;
	par[r] = dep[r] = 0;
	dfs(r, -1);
	vector<int> idx;
	for(int i=0; i<m; i++){
		idx.push_back(i);
	}
	sort(idx.begin(), idx.end(), [&](const int &a, const int &b){
		return pi(dep[p[a]], a) < pi(dep[p[b]], b);
	});
	c[idx[0]]++;
	while(true){
		bool fu = 0;
		for(auto &i : idx){
			if(p[i] == r){
				fu = 1; break;
			}
		}
		if(fu) break;
		vector<int> nxt;
		for(auto &i : idx){
			if(!bit.query(din[p[i]]) && !chk[par[p[i]]]){
				nxt.push_back(i);
				chk[par[p[i]]] = 1;
			}
			bit.add(din[p[i]], 1);
			bit.add(dout[p[i]] + 1, -1);
		}
		for(auto &i : idx){
			bit.add(din[p[i]], -1);
			bit.add(dout[p[i]] + 1, 1);
		}
		for(auto &i : nxt){
			chk[par[p[i]]] = 0;
			p[i] = par[p[i]];
		}
		idx = nxt;
	}
}

int main(){
	scanf("%d",&n);
	for(int i=1; i<n; i++){
		int s, e; scanf("%d %d",&s,&e);
		gph[s].push_back(e);
		gph[e].push_back(s);
	}
	scanf("%d",&m);
	for(int i=0; i<m; i++){
		scanf("%d",&p[i]);
	}
	int q; scanf("%d",&q);
	while(q--){
		int x;
		scanf("%d",&x);
		proc(x);
	}
	for(int i=0; i<m; i++) printf("%d %d\n", p[i], c[i]);
}

