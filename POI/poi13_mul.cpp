#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<lint, lint> pi;
const int MAXN = 500005;

int n, par[MAXN], pth[MAXN];
vector<int> gph[MAXN];
int X[MAXN], Z[MAXN];
int dep[MAXN], mxd[MAXN], sz[MAXN];

void dfs2(int x, int p){
	sz[x] = 1;
	for(auto &i : gph[x]){
		if(pth[i] || i == p) continue;
		dep[i] = dep[x] + 1;
		dfs2(i, x);
		sz[x] += sz[i];
		mxd[x] = max(mxd[x], mxd[i]);
	}
	mxd[x] = max(mxd[x], dep[x]);
	vector<int> gs;
	int leaf = 0;
	for(auto &i : gph[x]){
		if(pth[i] || i == p) continue;
		if(mxd[i] >= dep[x] + 2){
			gs.push_back(i);
		}
		else leaf++;
	}
	if(gs.empty()){
		X[x] = 1;
		if(leaf >= 2) Z[x] = 1;
	}
	if(gs.size() == 1){
		X[x] = X[gs[0]];
		Z[x] = (leaf > 0 && X[gs[0]]);
	}
	if(gs.size() == 2){
		Z[x] = (X[gs[0]] && X[gs[1]]);
	}
}

void dfsX_real(int x, int p, int s, int e, int flg, vector<int> &ret){
	if(flg == 0) ret[s++] = x;
	else ret[--e] = x;
	vector<int> gs, lf;
	for(auto &i : gph[x]){
		if(pth[i] || i == p) continue;
		if(mxd[i] >= dep[x] + 2){
			gs.push_back(i);
		}
		else lf.push_back(i);
	}
	if(gs.empty()){
		for(auto &i : lf) ret[s++] = i;
		return;
	}
	if(gs.size() == 1){
		if(flg == 0){
			for(auto &i : lf) ret[--e] = i;
			dfsX_real(gs[0], x, s, e, 1, ret);
		}
		else{
			for(auto &i : lf) ret[s++] = i;
			dfsX_real(gs[0], x, s, e, 0, ret);
		}
	}
	if(gs.size() >= 2) assert(0);
}

void dfsX(int x, int p, vector<int> &ret){ // from root to bottom
	int s = ret.size(), e = ret.size() + sz[x];
	ret.resize(e);
	dfsX_real(x, p, s, e, 0, ret);
}

void dfsZ(int x, int p, vector<int> &ret){ // Z
	vector<int> gs, lf;
	for(auto &i : gph[x]){
		if(pth[i] || i == p) continue;
		if(mxd[i] >= dep[x] + 2){
			gs.push_back(i);
		}
		else lf.push_back(i);
	}
	if(gs.empty()){
		ret.push_back(lf[0]);
		ret.push_back(x);
		for(int i=1; i<lf.size(); i++) ret.push_back(lf[i]);
	}
	if(gs.size() == 1){
		dfsX(gs[0], x, ret);
		ret.push_back(x);
		for(auto &i : lf) ret.push_back(i);
	}
	if(gs.size() == 2){
		vector<int> lv, rv;
		dfsX(gs[0], x, lv);
		dfsX(gs[1], x, rv);
		for(auto &i : lv) ret.push_back(i);
		ret.push_back(x);
		reverse(rv.begin(), rv.end());
		for(auto &i : rv) ret.push_back(i);
		for(auto &i : lf) ret.push_back(i);
	}
}

void dfs(int x, int p){
	for(auto &i : gph[x]){
		if(i != p){
			par[i] = x;
			dfs(i, x);
		}
	}
}

int in0[MAXN], in1[MAXN], out0[MAXN], out1[MAXN], ok[MAXN];
int main(){
	scanf("%d",&n);
	for(int i=0; i<n-1; i++){
		int s, e;
		scanf("%d %d",&s,&e);
		gph[s].push_back(e);
		gph[e].push_back(s);
	}
	dfs(1, -1);
	vector<int> v;
	for(int j=n; j!=1; j=par[j]) v.push_back(j);
	v.push_back(1);
	reverse(v.begin(), v.end());
	for(auto &i : v) pth[i] = 1;
	if(gph[1].size() == 1){
		out0[1] = 1;
	}
	else{
		dfs2(1, -1);
		if(X[1]) out1[1] = 1;
	}
	for(int i=1; i<v.size(); i++){
		in0[v[i]] = out0[v[i-1]] || out1[v[i-1]];
		in1[v[i]] = out0[v[i-1]];
		if(v[i] == n){
			if(gph[n].size() == 1) out0[n] = in0[n];
			else{
				dfs2(v[i], -1);
				if(X[n]) out0[n] = in1[n];
			}
			break;
		}
		if(gph[v[i]].size() == 2){
			out0[v[i]] = out1[v[i]] = (in0[v[i]] || in1[v[i]]);
		}
		else{
			dfs2(v[i], -1);
			if(X[v[i]]) out1[v[i]] |= in0[v[i]];
			if(X[v[i]]) out0[v[i]] |= in1[v[i]];
			if(Z[v[i]]) out1[v[i]] |= in1[v[i]];
		}
	}
	if(!out0[n]){
		puts("BRAK");
	}
	else{
		vector<int> ord;
		int mode = 0;
		for(int i=v.size()-1; i > 0; i--){
			int nxt = -1;
			if(v[i] == n){
				if(gph[n].size() == 1) ord.push_back(n), nxt = 0;
				else{
					vector<int> tmp;
					dfsX(n, -1, tmp);
					for(auto &i : tmp) ord.push_back(i);
					nxt = 1;
				}
			}
			else{
				if(gph[v[i]].size() == 2){
					ord.push_back(v[i]);
					if(in0[v[i]]) nxt = 0;
					else nxt = 1;
				}
				else{
					if(mode == 1 && X[v[i]] && in0[v[i]]){
						nxt = 0;
						vector<int> tmp;
						dfsX(v[i], -1, tmp);
						reverse(tmp.begin(), tmp.end());
						for(auto &i : tmp) ord.push_back(i);
					}
					else if(mode == 0 && X[v[i]] && in1[v[i]]){
						nxt = 1;
						vector<int> tmp;
						dfsX(v[i], -1, tmp);
						for(auto &i : tmp) ord.push_back(i);
					}
					else if(mode == 1 && Z[v[i]] && in1[v[i]]){
						nxt = 1;
						vector<int> tmp;
						dfsZ(v[i], -1, tmp);
						for(auto &i : tmp) ord.push_back(i);
					}
					else assert(0);
				}
			}
			if(nxt == 1){
				mode = 0;
			}
			else{
				if(out0[v[i-1]]) mode = 0;
				else mode = 1;
			}
		}
		if(gph[1].size() == 1) ord.push_back(1);
		else{
			vector<int> tmp;
			dfsX(1, -1, tmp);
			reverse(tmp.begin(), tmp.end());
			for(auto &i : tmp) ord.push_back(i);
		}
		reverse(ord.begin(), ord.end());
		assert(ord.size() == n);
		for(auto &i : ord) printf("%d\n", i);
	}
}


