#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <limits.h>
#include <stack>
#include <queue>
#include <map>
#include <set>
#include <algorithm>
#include <string>
#include <functional>
#include <vector>
#include <numeric>
#include <deque>
#include <utility>
#include <bitset>
#include <iostream>
using namespace std;
typedef long long lint;
typedef long double llf;
typedef pair<int, int> pi;

int n, k;
vector<pi> gph[60005];

int deg[60005];
bool vis[60005];

int dfs(int x){
	deg[x] = 0;
	for(auto &i : gph[x]){
		if(deg[i.second]){
			return -dfs(i.second) + i.first;
		}
	}
	return 0;
}

int main(){
	scanf("%d %d",&n,&k);
	for(int i=0; i<2*n; i++){
		int s, e, x;
		scanf("%d %d %d",&s,&e,&x);
		e += n;
		gph[s].push_back(pi(x, e));
		gph[e].push_back(pi(x, s));
		deg[s]++;
		deg[e]++;
	}
	if(count(deg + 1, deg + 2 * n + 1, 0) != 0){
		puts("NO");
		return 0;
	}
	queue<int> que;
	for(int i=1; i<=2*n; i++){
		if(deg[i] == 1) que.push(i);
	}
	int c1 = 0;
	while(!que.empty()){
		int f = que.front();
		que.pop();
		deg[f]--;
		for(auto &i : gph[f]){
			if(deg[i.second] == 0) continue;
			deg[i.second]--;
			if(f <= n) c1 += i.first;
			else c1 -= i.first;
			if(deg[i.second] == 1){
				que.push(i.second);
			}
		}
	}
	vector<int> ret;
	for(int i=1; i<=2*n; i++){
		if(deg[i]){
			int p = i;
			int nxte = -1;
			for(int i=0; i<gph[p].size(); i++){
				if(deg[gph[p][i].second]){
					nxte = i;
					break;
				}
			}
			int tmp = -gph[p][nxte].first;
			gph[p].erase(gph[p].begin() + nxte);
			tmp += dfs(p);
			c1 += -abs(tmp);
			ret.push_back(abs(tmp));
		}
	}
	if(c1 > k){
		puts("NO");
		return 0;
	}
	int st = max(-k-c1, 0), ed = k-c1;
	st = (st+1)/2, ed = ed / 2;
	bitset<600005> bs;
	bs[0] = 1;
	for(auto &j : ret){
		bs = (bs << j) | bs;
		for(int j=st; j<=ed; j++){
			if(bs[j]){
				puts("YES");
				return 0;
			}
		}
	}
	puts("NO");
}