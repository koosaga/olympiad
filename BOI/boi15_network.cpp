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

int n;
vector<int> graph[500005];
vector<int> v;

void dfs(int x, int p){
	int cnt = 0;
	for(auto &i : graph[x]){
		if(i == p) continue;
		dfs(i, x);
		cnt++;
	}
	if(cnt == 0) v.push_back(x);
}

int main(){
	scanf("%d",&n);
	for(int i=0; i<n-1; i++){
		int s, e;
		scanf("%d %d",&s,&e);
		graph[s].push_back(e);
		graph[e].push_back(s);
	}
	for(int i=1; i<=n; i++){
		if(graph[i].size() != 1){
			dfs(i, 0);
			break;
		}
	}
	printf("%d\n",(v.size() + 1) / 2);
	for(int i=0; i<(v.size() + 1) / 2; i++){
		printf("%d %d\n",v[i], v[i + v.size() / 2]);
	}
}