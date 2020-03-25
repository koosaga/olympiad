#include "Anthony.h"
#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using pi = pair<int, int>;

namespace {
	const int MAXN = 20005;
	vector<pi> gph[MAXN];
	int col[MAXN], pae[MAXN];
	void dfs(int x, int p){
		for(auto &[i, v] : gph[x]){
			if(v == p) continue;
			if(p == -1) col[i] = 0;
			else col[i] = col[pae[x]] ^ 1;
			pae[v] = i;
			if(sz(gph[v]) == 2){
				vector<int> seq = {x, v};
				while(sz(gph[seq.back()]) == 2){
					int w = seq.back();
					int nxt = -1;
					for(auto &k : gph[w]){
						if(k.second != seq[sz(seq) - 2]){
							nxt = k.second;
							pae[nxt] = k.first;
						}
					}
					seq.push_back(nxt);
				}
				vector<int> rpt; 
				if(col[i] == 0) rpt = {0, 1, 1, 0, 1, 0};
				else rpt = {1, 1, 0, 1, 0, 0};
				for(int i=2; i<sz(seq); i++){
					col[pae[seq[i]]] = rpt[(i - 1) % 6];
				}
				dfs(seq[sz(seq) - 1], seq[sz(seq) - 2]);
			}
			else{
				dfs(v, x);
			}
		}
	}
	int dist[MAXN];
	void bfs(int n, int x, int A){
		memset(dist, 0x3f, sizeof(dist));
		queue<int> que; que.push(x); dist[x] = 0;
		while(sz(que)){
			int x = que.front(); que.pop();
			for(auto &[i, j] : gph[x]){
				if(dist[j] > dist[x] + 1){
					dist[j] = dist[x] + 1;
					que.push(j);
				}
			}
		}
		for(int i=0; i<n; i++){
			for(auto &[j, v] : gph[i]){
				if(dist[i] <= dist[v]){
					col[j] = (dist[i] % A);
				}
			}
		}
	}
}  // namespace

std::vector<int> Mark(int N, int M, int A, int B,
                      std::vector<int> U, std::vector<int> V) {
    for(int i=0; i<sz(U); i++){
    	gph[U[i]].emplace_back(i, V[i]);
    	gph[V[i]].emplace_back(i, U[i]);
	}
	if(A == 2) dfs(0, -1);
	else bfs(N, 0, A);
	return vector<int>(col, col + M);
}
