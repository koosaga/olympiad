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
#include <bitset>
#include <iostream>
using namespace std;
typedef long long lint;
typedef long double llf;
typedef pair<int, int> pi;

int n, m;
int s[25005], e[25005];
vector<pi> graph[10005];

int cnt[10005], nxt[25005];

int main(){
	scanf("%d %d",&n,&m);
	for(int i=0; i<m; i++){
		scanf("%d %d",&s[i],&e[i]);
		if(s[i] > e[i]) swap(s[i], e[i]);
		graph[e[i]].push_back(pi(i, s[i]));
	}
	for(int i=m-1; i>=0; i--){
		auto it = lower_bound(graph[s[i]].begin(), graph[s[i]].end(), pi(i, -1));
		if(it == graph[s[i]].end()){
			nxt[i] = s[i];
		}
		else{
			nxt[i] = nxt[it->first];
		}
	}
	for(int i=2; i<=n; i++){
		if(graph[i].empty()){
			cnt[i] = max(cnt[i], 2);
			continue;
		}
		int t1 = nxt[graph[i][0].first];
		if(t1 != 1) cnt[t1] = max(cnt[t1], 2);
		int p = i, tm = 0;
		while(p != t1){
			auto it = ++lower_bound(graph[p].begin(), graph[p].end(), pi(tm, -1));
			if(it == graph[p].end()){
				cnt[p] = max(cnt[p], 1);
			}
			else{
				int tmp = nxt[it->first];
				if(tmp != 1) cnt[tmp] = max(cnt[tmp], 1);
			}
			it--;
			tm = it->first;
			p = it->second;
		}
	}
	int ret = 0;
	for(int i=2; i<=n; i++){
		ret += cnt[i];
	}
	printf("%d",ret);
}
