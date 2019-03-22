#include "Azer.h"
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 2005;
using pi = pair<int, int>;

namespace {
	vector<pi> gph[MAXN];
	int dist[MAXN];
	bool vis[MAXN];
	bool firstSkip = 1;
	int n, recValue1, recValue2, curMode;	
	void sendValue(int x, int b){
		for(int i=b-1; i>=0; i--){
			SendA((x >> i) & 1);
		}
	}
	void relax(int v){	
//		printf("A relaxed %d = %d\n", v, dist[v]);
		vis[v] = 1;
		for(auto &i : gph[v]){
			dist[i.second] = min(dist[i.second], i.first + dist[v]);
		}
	}
	int getMax(){
		int ret = 0;
		for(int i=0; i<n; i++){
			if(vis[i]) ret = max(ret, dist[i]);
		}
		return ret;
	}
}  // namespace


void InitA(int N, int A, std::vector<int> U, std::vector<int> V,
		std::vector<int> C) {
	n = N;
	for(int i=0; i<A; i++){
		gph[U[i]].emplace_back(C[i], V[i]);
		gph[V[i]].emplace_back(C[i], U[i]);
	}
	memset(dist, 0x3f, sizeof(dist));
	dist[0] = 0;
}

void ReceiveA(bool x) {
	if(curMode == 0){
		curMode = 69;
		if(count(vis, vis + n, 1) == n) return;
		int cur = 1048575, pos = -1;
		for(int i=0; i<n; i++){
			if(!vis[i] && dist[i] < cur){
				cur = dist[i];
				pos = i;
			}
		}
		cur -= getMax();
		cur = min(cur, 511);
		sendValue(cur, 9 - firstSkip);
		firstSkip = 0;
		return;
	}
	if(curMode >= 69){
		if(curMode < 80){
			recValue1 = recValue1 * 2 + x;
		}
		else{
			recValue2 = recValue2 * 2 + x;
		}
		curMode++;
		if(curMode == 77 && recValue1 == 255){
			int cur = 1048575, pos = -1;
			for(int i=0; i<n; i++){
				if(!vis[i] && dist[i] < cur){
					cur = dist[i];
					pos = i;
				}
			}
			relax(pos);
			sendValue(pos, 11);
			curMode = 0;
			recValue1 = recValue2 = 0;
		}
		if(curMode == 89){
			dist[recValue1] = min(dist[recValue1], recValue2 + getMax());
			relax(recValue1);
			recValue1 = recValue2 = 0;
			curMode = 0;
			ReceiveA(0);
		}
	}
}

vector<int> Answer(){
	vector<int> v(dist, dist + n);
	return v;
}
