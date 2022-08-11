#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = pair<int, int>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
const int MAXN = 1557;
const int MAXT = 4100;

int D1[MAXN][MAXN];
int D2[MAXN][MAXN];
int D3[MAXN][MAXN];
int D4[MAXN][MAXN];
int foo[4][MAXN][MAXN];

struct node{
	int lmax, rmax, opt, lazy, razy;
	node operator+(const node &nd)const{
		node ret;
		ret.lmax = max(lmax, nd.lmax);
		ret.rmax = max(rmax, nd.rmax);
		ret.opt = max({opt, nd.opt, lmax + nd.rmax});
		ret.lazy = ret.razy = 0;
		return ret;
	}
};

struct seg{
	node tree[MAXT];
	void init(int s, int e, int p, vector<int> &a, vector<int> &b){
		if(s == e){
			tree[p] = (node){a[s], b[s], a[s] + b[s], 0, 0};
			return;
		}
		int m = (s + e) / 2;
		init(s, m, 2*p, a, b);
		init(m+1, e, 2*p+1, a, b);
		tree[p] = tree[2*p] + tree[2*p+1];
	}
	void add(int s, int e, int ps, int pe, int b, int v, int p){
		if(e < ps || pe < s) return;
		if(s <= ps && pe <= e){
			tree[p].opt += v;
			if(b == 0) tree[p].lmax += v, tree[p].lazy += v;
			if(b == 1) tree[p].rmax += v, tree[p].razy += v;
			return;
		}
		int pm = (ps + pe) / 2;
		for(int i = 2*p; i < 2*p+2; i++){
			tree[i].opt += tree[p].lazy + tree[p].razy;
			tree[i].lmax += tree[p].lazy;
			tree[i].lazy += tree[p].lazy;
			tree[i].rmax += tree[p].razy;
			tree[i].razy += tree[p].razy;
		}
		tree[p].lazy = tree[p].razy = 0;
		add(s, e, ps, pm, b, v, 2*p);
		add(s, e, pm+1, pe, b, v, 2*p+1);
		tree[p] = tree[2*p] + tree[2*p+1];
	}
}seg;

struct gom{
	int l, r, x;
};

vector<vector<gom>> parse(int D[MAXN][MAXN], int n){
	vector<vector<gom>> ret(n + 1);
	for(int i = 1; i <= n; i++){
		for(int j = 0; j <= n; ){
			int k = j + 1;
			while(k <= n && D[i][j] - D[i - 1][j] == D[i][k] - D[i - 1][k]){
				k++;
			}
			ret[i - 1].push_back({j, k - 1, D[i][j] - D[i - 1][j]});
			j = k;
		}
	}
	return ret;
}

int sex_level(std::vector<int> X, std::vector<int> Y, std::vector<int> D, std::vector<int> W) {
	memset(D1, 0, sizeof(D1));
	memset(D2, 0, sizeof(D2));
	memset(D3, 0, sizeof(D3));
	memset(D4, 0, sizeof(D4));
	memset(foo, 0, sizeof(foo));
    int n = X.size();
	for(int i = 0; i < n; i++){
		D[i] = D[i] % 4 + 1;
		if(D[i] == 1) for(int j = X[i]; j <= n; j++) foo[0][j][Y[i]] = max(foo[0][j][Y[i]], W[i]);
		if(D[i] == 2) for(int j = 1; j <= Y[i]; j++) foo[1][X[i]][j] = max(foo[1][X[i]][j], W[i]);
		if(D[i] == 3) for(int j = 1; j <= X[i]; j++) foo[2][j][Y[i]] = max(foo[2][j][Y[i]], W[i]);
		if(D[i] == 4) for(int j = Y[i]; j <= n; j++) foo[3][X[i]][j] = max(foo[3][X[i]][j], W[i]);
	}
    for(int i = 1; i <= n; i++){
    	for(int j = 1; j <= n; j++){
    		D2[i][j] = max(D2[i - 1][j] + foo[3][i][j], D2[i][j - 1] + foo[0][i][j]);
		}
		for(int j = n - 1; j >= 0; j--){
			D1[i][j] = max(D1[i - 1][j] + foo[1][i][j + 1], D1[i][j + 1] + foo[0][i][j + 1]);
		}
	}
	for(int i = n - 1; i >= 0; i--){
		for(int j = 1; j <= n; j++){
			D3[i][j] = max(D3[i + 1][j] + foo[3][i + 1][j], D3[i][j - 1] + foo[2][i + 1][j]);
		}
		for(int j = n - 1; j >= 0; j--){
			D4[i][j] = max(D4[i + 1][j] + foo[1][i + 1][j + 1], D4[i][j + 1] + foo[2][i + 1][j + 1]);
		}
	}
	int ret = 0;
	{
		vector<vector<gom>> event[2];
		event[0] = parse(D2, n);
		event[1] = parse(D3, n);
		for(int x1 = 0; x1 <= n; x1++){
			vector<int> val[2];
			for(int i = 0; i < 2; i++){
				val[i].resize(n + 1);
				for(int j = 0; j <= n; j++){
					if(i == 0) val[i][j] = D1[x1][j] + D2[x1][j];
					else val[i][j] = D4[x1][j] + D3[x1][j];
				}
			}
			seg.init(0, n, 1, val[0], val[1]);
			for(int x2 = x1; x2 <= n; x2++){
				ret = max(ret, seg.tree[1].opt);
				for(auto &k : event[0][x2]){
					seg.add(k.l, k.r, 0, n, 0, k.x, 1);
				}
				for(auto &k : event[1][x2]){
					seg.add(k.l, k.r, 0, n, 1, k.x, 1);
				}
			}
		}
	}
	vector<int> XS(n + 1), FUCK1(n + 1), FUCK2(n + 1);
	for(int i = 1; i <= n; i++){
		for(int j = 0; j <= n; j++){
			XS[i] = max(XS[i], foo[3][i][j] + foo[1][i][j + 1]);
		}
		XS[i] += XS[i - 1];
	}
	for(int i = 0; i <= n; i++){
		for(int j = 0; j <= n; j++){
			FUCK1[i] = max(FUCK1[i], D1[i][j] + D2[i][j]);
			FUCK2[i] = max(FUCK2[i], D3[i][j] + D4[i][j]);
		}
	}
	for(int i = 0; i <= n; i++){
		for(int j = i; j <= n; j++){
			ret = max(ret, XS[j] - XS[i] + FUCK1[i] + FUCK2[j]);
		}
	}
	return ret;
}

int max_level(std::vector<int> X, std::vector<int> Y, std::vector<int> D, std::vector<int> W) {
	int ret = 0;
	for(int i = 0; i < 2; i++){
		ret = max(ret, sex_level(X, Y, D, W));
		for(int j = 0; j < sz(X); j++){
			swap(X[j], Y[j]);
			D[j]--;
			D[j] ^= 1;
			D[j]++;
		}
	}
	return ret;
}

