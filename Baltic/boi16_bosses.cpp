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

int n;
vector<int> gph[5005];

bool vis[5005];
int sz[5005];
int par[5005];

vector<int> ord;

lint solve(int r){
	memset(vis, 0, sizeof(vis));
	memset(sz, 0, sizeof(sz));
	ord.clear();
	queue<int> que;
	que.push(r);
	vis[r] = 1;
	while(!que.empty()){
		int x = que.front();
		que.pop();
		ord.push_back(x);
		for(auto &i : gph[x]){
			if(!vis[i]){
				vis[i] = 1; 
				que.push(i);
				par[i] = x;
			}
		}
	}
	if(ord.size() != n) return 1e18;
	lint ret = 0;
	for(int i=ord.size()-1; i>=0; i--){
		sz[ord[i]]++;
		ret += sz[ord[i]];
		if(ord[i] != r){
			sz[par[ord[i]]] += sz[ord[i]];
		}
	}
	return ret;
}

int main(){
	scanf("%d",&n);
	for(int i=1; i<=n; i++){
		int t;
		scanf("%d",&t);
		for(int j=0; j<t; j++){
			int p;
			scanf("%d",&p);
			gph[p].push_back(i);
		}
	}
	lint ret = 1e18;
	for(int i=1; i<=n; i++){
		ret = min(ret, solve(i));
	}
	cout << ret;
}