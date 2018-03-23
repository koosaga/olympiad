#include "Boblib.h"
#include <bits/stdc++.h>
using namespace std;
static const int MAXN = 1500;

void Bob( int V, int U, int C[], int D[] ){
	using pi = pair<int, int>;
	if(V <= 3){
		if(V == 1) InitMap(1, 0);
		if(V == 2) InitMap(2, 0);
		if(V == 3) InitMap(2, 1), MakeMap(0, 1);
		return;
	}
	int chk[MAXN] = {};
	int real_idx[MAXN] = {};
	vector<int> gph[MAXN];
	int idx[1024] = {};
	int pcnt[1024] = {};
	for(int i=1; i<=1023; i++) pcnt[i] = pcnt[i/2] + i%2;
	int ptr = 0;
	for(int i=0; i<V-12; i++){
		while(pcnt[ptr] >= 9) ptr++;
		idx[i] = ptr++;
	}
	for(int i=0; i<U; i++){
		gph[C[i]].push_back(D[i]);
		gph[D[i]].push_back(C[i]);
	}
	int mxp = 0;
	set<int> s;
	for(int i=0; i<V; i++){
		s.insert(i);
		if(gph[i].size() > gph[mxp].size()) mxp = i;
	}
	s.erase(mxp);
	for(auto &i : gph[mxp]) s.erase(i);
	int src = *s.begin();
	for(auto &i : gph[src]) chk[i] = 1;
	chk[mxp] = -1;
	chk[src] = -1;
	vector<int> two_end;
	for(int i=0; i<V; i++){
		if(!chk[i]){
			int cnt = 0;
			for(auto &j : gph[i]){
				if(chk[j] == 0) cnt++;
			}
			if(cnt == 1) two_end.push_back(i);
		}
	}
	assert(two_end.size() == 2);
	if(gph[two_end[0]].size() > gph[two_end[1]].size()) swap(two_end[0], two_end[1]);
	int msk = (1<<9);
	for(int i=two_end[0]; msk; ){
		if(i == -1){
			InitMap(-1, 0);
			return;
		}
		chk[i] = 2;
		int nxt = -1;
		for(auto &j : gph[i]){
			if(!chk[j]){
				nxt = j;
			}
			else if(chk[j] == 1){
				real_idx[j] |= msk;
			}
		}
		msk >>= 1;
		i = nxt;
	}
	for(int i=0; i<V; i++){
		if(chk[i] != 1) continue;
		for(int j=0; j<1024; j++){
			if(real_idx[i] == idx[j]){
				real_idx[i] = j;
				break;
			}
		}
	}
	vector<pi> result_edge;
	for(int i=0; i<U; i++){
		if(chk[C[i]] == 1 && chk[D[i]] == 1){
			result_edge.emplace_back(real_idx[C[i]], real_idx[D[i]]);
		}
	}
	InitMap(V - 12, result_edge.size());
	for(auto &i : result_edge) MakeMap(i.first, i.second);
}

