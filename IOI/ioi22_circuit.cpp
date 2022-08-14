#include "circuit.h"
#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = pair<int, int>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
const int mod = 1e9 + 2022;
const int MAXT = 270000;

int n, m;

struct seg{
	struct node{
		lint sum[2];
		int lazy;
		void inv(){
			lazy ^= 1;
			swap(sum[0], sum[1]);
		}
		node operator+(const node &n)const{
			node ret;
			ret.lazy = 0;
			ret.sum[0] = (sum[0] + n.sum[0]) % mod;
			ret.sum[1] = (sum[1] + n.sum[1]) % mod;
			return ret;
		}
	}tree[MAXT];
	void lazydown(int p){
		if(tree[p].lazy == 0) return;
		tree[p].lazy = 0;
		for(int i = 2*p; i < 2*p+2; i++){
			tree[i].inv();
		}
	}
	void init(int s, int e, int p, vector<lint> &A, vector<int> &S){
		if(s == e){
			tree[p].sum[S[s]] = A[s];
			return;
		}
		int m = (s + e) / 2;
		init(s, m, 2*p, A, S);
		init(m + 1, e, 2*p+1, A, S);
		tree[p] = tree[2*p] + tree[2*p+1];
	}
	void update(int s, int e, int ps, int pe, int p){
		if(e < ps || pe < s) return;
		if(s <= ps && pe <= e){
			tree[p].inv();
			return;
		}
		lazydown(p);
		int pm = (ps + pe) / 2;
		update(s, e, ps, pm, 2*p);
		update(s, e, pm+1, pe, 2*p+1);
		tree[p] = tree[2*p] + tree[2*p+1];
	}
}seg;

void init(int N, int M, std::vector<int> P, std::vector<int> A) {
	vector<lint> gap(N + M);
	vector<int> state(M);
	vector<vector<int>> gph(N + M);
	for(int i = 1; i < N + M; i++){
		gph[P[i]].push_back(i);
	}
	vector<lint> sum(N + M);
	for(int i = N + M - 1; i >= 0; i--){
		sum[i] = max(1, sz(gph[i]));
		for(auto &j : gph[i]){
			sum[i] *= sum[j];
			sum[i] %= mod;
		}
	}
	gap[0] = 1;
	for(int i = 0; i < N + M; i++){
		vector<lint> pmul, smul;
		for(auto &j : gph[i]){
			pmul.push_back(sum[j]);
			smul.push_back(sum[j]);
		}
		for(int i = 1; i < sz(pmul); i++) pmul[i] = pmul[i - 1] * pmul[i] % mod;
		for(int i = sz(smul) - 2; i >= 0; i--) smul[i] = smul[i + 1] * smul[i] % mod;
		for(int j = 0; j < sz(gph[i]); j++){
			gap[gph[i][j]] = gap[i];
			if(j > 0) gap[gph[i][j]] *= pmul[j - 1], gap[gph[i][j]] %= mod;
			if(j + 1 < sz(gph[i])) gap[gph[i][j]] *= smul[j + 1], gap[gph[i][j]] %= mod;
		}
	}
	state = A;
	gap.erase(gap.begin(), gap.begin() + N);
	n = N, m = M;
	seg.init(0, m - 1, 1, gap, state);
}

int count_ways(int L, int R) {
	L -= n, R -= n;
	seg.update(L, R, 0, m - 1, 1);
	return seg.tree[1].sum[1];
}
