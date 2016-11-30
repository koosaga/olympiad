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

int add[500005];
int size[500005];
vector<int> graph[500005];

void calc(int x, int s, int l){
	if(s == graph[x].size()) return;
	add[l]++;
	add[size[graph[x][s]]]--;
	add[l-size[graph[x][s]]]--;
	calc(graph[x][s], 0, size[graph[x][s]] - 1);
	calc(x, s+1, l - size[graph[x][s]]);
}

void dfs(int x){
	size[x] = 1;
	for(auto &i : graph[x]){
		dfs(i);
		size[x] += size[i];
	}
}

int low[500005];

lint pw(int x, int t, int m){
	lint ret = 1, piv = x;
	while(t){
		if(t&1) ret *= piv;
		piv *= piv;
		ret %= m;
		piv %= m;
		t >>= 1;
	}
	return ret;
}

int main(){
	int t;
	scanf("%d",&t);
	memset(low,0x3f,sizeof(low));
	for(int i=2; i<=500000; i++){
		for(int j=i; j<=500000; j+=i){
			low[j] = min(low[j], i);
		}
	}
	while(t--){
		int n, m;
		scanf("%d %d",&n,&m);
		for(int i=2; i<=n; i++){
			int t;
			scanf("%d",&t);
			graph[t].push_back(i);
		}
		dfs(1);
		calc(1,0,size[1]-1);
		for(int i=n; i; i--){
			add[i] += add[i+1];
		}
		for(int i=n; i>=2; i--){
			if(low[i] != i){
				add[low[i]] += add[i];
				add[i / low[i]] += add[i];
				add[i] = 0;
			}
		}
		lint ret = 1;
		for(int i=2; i<=n; i++){
			ret *= pw(i, add[i], m);
			ret %= m;
		}
		printf("%lld\n",ret);
		memset(add,0,sizeof(add));
		memset(size,0,sizeof(size));
		for(int i=1; i<=n; i++){
			graph[i].clear();
		}
	}
}