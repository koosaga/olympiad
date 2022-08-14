#include "islands.h"
#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = pair<int, int>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()

std::variant<bool, std::vector<int>> find_journey(
    int N, int M, std::vector<int> U, std::vector<int> V) {
    vector<set<pi>> gph(N), rev(N);
    for(int i = 0; i < M; i++){
    	gph[U[i]].emplace(i, V[i]);
    	rev[V[i]].emplace(i, U[i]);
	}
	queue<int> que;
	for(int i = 0; i < N; i++){
		if(sz(gph[i]) == 0){
			que.push(i);
		}
	}
	vector<int> removed(M);
	auto remove_edge = [&](int e){
		if(removed[e]) return;
		removed[e] = 1;
		gph[U[e]].erase(pi(e, V[e]));
		rev[V[e]].erase(pi(e, U[e]));
		if(sz(gph[U[e]]) == 0) que.push(U[e]);
	};
	vector<int> P;
	for(int source = 0; ; ){
		while(sz(que)){
			int x = que.front();
			que.pop();
			vector<int> ind;
			for(auto &[e, _] : gph[x]) ind.push_back(e);
			for(auto &[e, _] : rev[x]) ind.push_back(e);
			for(auto &e : ind) remove_edge(e);
		}
		if(sz(gph[source]) == 0) return false;
		if(sz(gph[source]) == 1){
			auto i = gph[source].begin()->first;
			que.push(source);
			source = V[i];
			P.push_back(i);
			continue;
		}
		// answer exists
		for(int i = 0; i < N; i++){
			int thres = 1 + (i == source);
			while(sz(gph[i]) > thres){
				int ed = gph[i].begin()->first;
				remove_edge(ed);
			}
		}
		int vtx = source;
		int edg = -1;
		vector<int> inverted(M); int invcnt = 0;
		vector<int> seq = P;
		do{
			for(auto &[ne, nv] : gph[vtx]){
				if(ne != edg){
					seq.push_back(ne);
					tie(vtx, edg) = pi(nv, ne);
					break;
				}
			}
			gph[U[edg]].erase(pi(edg, V[edg]));
			rev[V[edg]].erase(pi(edg, U[edg]));
			swap(U[edg], V[edg]);
			gph[U[edg]].emplace(edg, V[edg]);
			rev[V[edg]].emplace(edg, U[edg]);
			if(inverted[edg]) invcnt--;
			inverted[edg] ^= 1;
			if(inverted[edg]) invcnt++;
		}while(invcnt > 0);
		reverse(all(P));
		for(auto &x : P) seq.push_back(x);
		return seq;
	}
}
