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
typedef pair<int, int> pi;

int n, a[100005], b[100005], cnt[100005], vis[100005];
vector<pi> v[100005];
vector<pi> gph[100005];

void add_edge(int s, int e, int x){
	if(s == e) return;
	gph[s].push_back({e, x});
	gph[e].push_back({s, x});
}

int col[2];

void dfs(int x, int p){
	if(vis[x]) return;
	vis[x] = 1;
	col[p]++;
	for(auto &i : gph[x]){
		dfs(i.first, p ^ i.second);
	}
}

int main(){
	cin >> n;
	for(int i=0; i<n; i++) scanf("%d",&a[i]), cnt[a[i]]++;
	for(int i=0; i<n; i++) scanf("%d",&b[i]), cnt[b[i]]++;
	for(int i=0; i<n; i++){
		v[a[i]].push_back({i, 1});
		v[b[i]].push_back({i, 2});
	}
	for(int i=1; i<=100000; i++){
		if(v[i].size() != 2) continue;
		if(v[i][0].second == v[i][1].second){
			add_edge(v[i][0].first, v[i][1].first, 1);
		}
		else{
			add_edge(v[i][0].first, v[i][1].first, 0);
		}
	}
	int ret = 0;
	for(int i=0; i<n; i++){
		if(!vis[i]){
			dfs(i, 0);
			ret += min(col[0], col[1]);
			col[0] = col[1] = 0;
		}
	}
	printf("%d\n", ret);

}
