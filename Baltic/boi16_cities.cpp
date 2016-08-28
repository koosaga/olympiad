#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <limits.h>
#include <math.h>
#include <time.h>
#include <iostream>
#include <functional>
#include <numeric>
#include <algorithm>
#include <stack>
#include <queue>
#include <deque>
#include <vector>
#include <string>
#include <bitset>
#include <map>
#include <set>
using namespace std;
typedef long long lint;
typedef long double llf;
typedef pair<lint, int> pi;

lint ret = 1e18;
priority_queue<pi, vector<pi>, greater<pi> > pq;
vector<pi> gph[100005];

int n, m, k, a[10];
lint dist[6][100005];
lint dt[6][6][100005];

void getdt(int s, int e){
	for(int i=1; i<=n; i++){
		pq.push(pi(dist[s][i] + dist[e][i], i));
		dt[s][e][i] = dist[s][i] + dist[e][i];
	}
	while(!pq.empty()){
		auto t = pq.top();
		pq.pop();
		if(dt[s][e][t.second] < t.first) continue;
		for(auto &i : gph[t.second]){
			if(dt[s][e][i.second] > dt[s][e][t.second] + i.first){
				dt[s][e][i.second] = dt[s][e][t.second] + i.first;
				pq.push(pi(dt[s][e][i.second], i.second));
			}
		}
	}

}

void dijkstra(vector<int> &start, lint *d){
	for(auto &i : start){
		d[i] = 0;
		pq.push(pi(0, i));
	}
	while(!pq.empty()){
		auto t = pq.top();
		pq.pop();
		if(d[t.second] < t.first) continue;
		for(auto &i : gph[t.second]){
			if(d[i.second] > d[t.second] + i.first){
				d[i.second] = d[t.second] + i.first;
				pq.push(pi(d[i.second], i.second));
			}
		}
	}
}

lint solve1(int *p){
	lint ret = 1e18;
	for(int i=1; i<=n; i++){
		ret = min(ret, dt[p[0]][p[1]][i] + dt[p[2]][p[3]][i]);
	}
	return ret;
}

lint solve2(int *p){
	lint ret = 1e18;
	for(int i=1; i<=n; i++){
		ret = min(ret, dt[p[0]][p[1]][i] + dt[p[2]][p[3]][i] + dist[p[4]][i]);
	}
	return ret;
}

int main(){
	cin >> n >> k >> m;
	for(int i=1; i<=k; i++) cin >> a[i];
	sort(a+1, a+k+1);
	k = unique(a+1, a+k+1) - a - 1;
	for(int i=1; i<=m; i++){
		int s, e, x;
		scanf("%d %d %d",&s,&e,&x);
		gph[s].emplace_back(x, e);
		gph[e].emplace_back(x, s);
	}
	memset(dist, 0x3f, sizeof(dist));
	for(int i=1; i<=k; i++){
		vector<int> t;
		t.push_back(a[i]);
		dijkstra(t, dist[i]);
	}
	if(k == 1){
		puts("0");
		return 0;
	}
	if(k == 2){
		printf("%lld\n",dist[1][a[2]]);
		return 0;
	}
	if(k == 3){
		for(int i=1; i<=n; i++){
			ret = min(ret, dist[1][i] + dist[2][i] + dist[3][i]);
		}
		printf("%lld\n",ret);
		return 0;
	}
	if(k == 4){
		for(int i=1; i<=k; i++){
			for(int j=i+1; j<=k; j++){
				getdt(i, j);
			}
		}
		int perm[4] = {1, 2, 3, 4};
		do{
			if(perm[0] < perm[1] && perm[2] < perm[3] && perm[0] < perm[2]){
				ret = min(ret, solve1(perm));
			}
		}while(next_permutation(perm, perm + 4));
		printf("%lld", ret);
		return 0;
	}
	if(k == 5){
		for(int i=1; i<=k; i++){
			for(int j=i+1; j<=k; j++){
				getdt(i, j);
			}
		}
		int perm[5] = {1, 2, 3, 4, 5};
		do{
			if(perm[0] < perm[1] && perm[2] < perm[3] && perm[0] < perm[2]){
				ret = min(ret, solve2(perm));
			}
		}while(next_permutation(perm, perm + 5));
		printf("%lld", ret);
		return 0;
	}
}