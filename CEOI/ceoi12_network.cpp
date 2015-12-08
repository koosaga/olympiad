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

vector<int> graph[100005];
int vis[100005], size[100005], piv;
int par[100005], chk[100005], rev[100005];
int n, m, r;

int uf[100005];
int find(int x){
	return uf[x] == x ? x : find(uf[x]);
}

void dfs(int x, int p){
	vis[x] = 1;
	size[x] = 1;
	for(auto &i : graph[x]){
		if(!vis[i]){
			par[i] = x;
			dfs(i, x);
			size[x] += size[i];
		}
		else{
			for(int j=x; j!=i; j=par[j]){
				chk[j] = 1;
				uf[j] = find(i);
			}
		}
	}
}

vector<int> ls;
int main(){
	scanf("%d %d %d",&n,&m,&r);
	for(int i=1; i<=n; i++) uf[i] = i;
	for(int i=0; i<m; i++){
		int s, e;
		scanf("%d %d",&s,&e);
		graph[s].push_back(e);
	}
	dfs(r, 0);
	chk[r] = 1;
	for(int i=1; i<=n; i++){
		printf("%d ",size[find(i)]);
		if(!chk[i]){
			int bad = 0;
			for(auto &j : graph[i]){
				if(!chk[j]){
					bad = 1;
					break;
				}
			}
			if(!bad) ls.push_back(i);
		}
	}
	vector<pi> ret;
	for(auto &i : ls){
		int j = i;
		while(!chk[j]){
			chk[j] = 1;
			j = par[j];
		}
		if(i != j) ret.push_back(pi(i, j));
	}
	printf("\n%d\n",ret.size());
	for(auto &i : ret){
		printf("%d %d\n",i.first, i.second);
	}
}