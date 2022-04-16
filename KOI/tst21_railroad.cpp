#include "railroad.h"
#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
const int MAXN = 205;
using namespace std;
using pi = pair<int, int>;

vector<int> gph[MAXN];
int dep[MAXN], par[MAXN];

pi dfs(int x, int p = -1){
	pi ret(0, x);
	for(auto &i : gph[x]){
		if(i == p) continue;
		par[i] = x;
		dep[i] = dep[x] + 1;
		auto w = dfs(i, x);
		w.first++;
		ret = max(ret, w);
	}
	return ret;
}

std::vector<std::pair<int, int> > encode_map(int N, int K, int &X, std::vector<std::pair<int, int> > E) {
	for(int i = 0; i < MAXN; i++){
		gph[i].clear();
		dep[i] = 0;
	}
	for(auto &[x, y] : E){
		gph[x].push_back(y);
		gph[y].push_back(x);
	}
	pi p = dfs(1);
	pi q = dfs(p.second);
	int c = q.second;
	for(int i = 0; i < q.first / 2; i++) c = par[c];
	dep[c] = 0;
	dfs(c);
    std::vector<std::pair<int, int> > ret;
	for(int i = 1; i <= N; i++){
		for(int j = i + 1; j <= N; j++){
			if(dep[i] == dep[j] && sz(ret) < K){
				ret.emplace_back(i, j);
			}
		}
	}
	X = c;
	return ret;
}

std::vector<std::pair<int, int> > decode_map(int N, int K, int X, std::vector<std::pair<int, int> > E) {
	for(int i = 0; i < MAXN; i++){
		gph[i].clear();
		dep[i] = 0;
	}
    std::vector<std::pair<int, int> > ret;
    for(auto &[x, y] : E){
    	gph[x].push_back(y);
    	gph[y].push_back(x);
	}
	memset(dep, 0x3f, sizeof(dep));
	queue<int> que;
	auto enq = [&](int x, int d){
		if(dep[x] > d){
			dep[x] = d;
			que.push(x);
		}
	};
	enq(X, 0);
	while(sz(que)){
		int x = que.front(); que.pop();
		for(auto &i : gph[x]) enq(i, dep[x] + 1);
	}
	for(auto &[x, y] : E){
		if(dep[x] != dep[y]) ret.emplace_back(x, y);
	}
    return ret;
}
