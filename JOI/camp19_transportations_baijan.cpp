#include "Baijan.h"
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 2005;
using pi = pair<int, int>;

namespace {
	vector<pi> gph[MAXN];
	int dist[MAXN];
	bool vis[MAXN];
	int n, recValue, recValue2, curMode;
	bool firstSkip = 1;
	void sendValue(int x, int b){
		for(int i=b-1; i>=0; i--){
			SendB((x >> i) & 1);
		}
	}
	void relax(int v){
	//	printf("B relaxed %d = %d\n", v, dist[v]);
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

void InitB(int N, int B, std::vector<int> S, std::vector<int> T,
		std::vector<int> D) {
	n = N;
	for(int i=0; i<B; i++){
		gph[S[i]].emplace_back(D[i], T[i]);
		gph[T[i]].emplace_back(D[i], S[i]);
	}
	memset(dist, 0x3f, sizeof(dist));
	dist[0] = 0;
	SendB(0);
}

void ReceiveB(bool y) {
	if(curMode < 9 - firstSkip){
		curMode++;
		recValue = recValue * 2 + y;
	}
	if(curMode < 9 - firstSkip) return;
	if(curMode > 999){
		curMode++;
		recValue2 = recValue2 * 2 + y;
		if(curMode >= 1011){
			dist[recValue2] = min(dist[recValue2], recValue + getMax());
			relax(recValue2);
			recValue = recValue2 = 0;
			curMode = 0;
			SendB(0);
		}
		return;
	}
	firstSkip = 0;
	int cur = 1048575, pos = -1;
	for(int i=0; i<n; i++){
		if(!vis[i] && dist[i] < cur){
			cur = dist[i];
			pos = i;
		}
	}
	cur -= getMax();
	int another_dist = recValue;
	if(cur > another_dist){
		sendValue(255, 8);
		curMode = 1000;
		// beg A to answer the vertex number
	}
	else{
		relax(pos);
		curMode = 0;
		recValue = recValue2 = 0;
		sendValue(pos, 11);
		sendValue(cur, 9);
		// tell A that vertex number with its distance
	}
}
