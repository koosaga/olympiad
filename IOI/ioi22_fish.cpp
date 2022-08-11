#include "fish.h"
#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = pair<int, int>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
const int MAXT = 270000;

struct fish{
	int pos, cost, idx;
	bool operator<(const fish &f)const{
		return pos < f.pos;
	};
};

struct seg{
	lint tree[MAXT];
	int lim;
	void init(int n){
		for(lim = 1; lim <= n; lim <<= 1);
		fill(tree, tree + MAXT, -1e18);
	}
	void upd(int x, lint v){
		for(int i = x + lim; i; i >>= 1){
			tree[i] = max(tree[i], v);
		}
	}
	lint query(int s, int e){
		s += lim;
		e += lim;
		lint ret = -1e18;
		while(s < e){
			if(s%2 == 1) ret = max(ret, tree[s++]);
			if(e%2 == 0) ret = max(ret, tree[e--]);
			s >>= 1;
			e >>= 1;
		}
		if(s == e) ret = max(ret, tree[s]);
		return ret;
	}
}seg1, seg2;

long long max_weights(int N, int M, std::vector<int> X, std::vector<int> Y,
                      std::vector<int> W) {
    vector<vector<fish>> V(N);
    vector<lint> DP(N);
    vector<lint> Top(N);
    vector<lint> Down(M), Up(M);
    for(int i = 0; i < M; i++){
    	V[X[i]].push_back({Y[i], W[i], i});
	}
	seg1.init(N);
	seg2.init(N);
	for(int i = 0; i < N; i++){
		sort(all(V[i]));
		for(auto &f : V[i]){
			Up[f.idx] = seg1.query(0, f.pos - 1);
			if(i > 0) Up[f.idx] = max(Up[f.idx], DP[i - 1]);
			else Up[f.idx] = max(Up[f.idx], 0ll);
			Up[f.idx] += f.cost;
			seg1.upd(f.pos, Up[f.idx]);
		}
		reverse(all(V[i]));
		for(auto &f : V[i]){
			Down[f.idx] = seg2.query(f.pos + 1, N - 1);
			if(i > 1) Down[f.idx] = max(Down[f.idx], Top[i - 2]);
			else if(i == 1) Down[f.idx] = max(Down[f.idx], 0ll);
			Down[f.idx] += f.cost;
			seg2.upd(f.pos, Down[f.idx]);
		}
		if(i > 0) DP[i] = DP[i - 1];
		DP[i] = max(DP[i], seg2.query(0, N - 1));
		if(i > 1) Top[i] = Top[i - 2];
		{
			lint sum = 0;
			for(auto &f : V[i]) sum += f.cost;
			Top[i] += sum;
			Top[i] = max(Top[i], seg1.query(0, N - 1));
		}
		DP[i] = max(DP[i], Top[i - 1]);
	}
	return DP[N - 1];
}
