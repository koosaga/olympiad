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

int n, m, k, s;
vector<int> graph[3005];
int dep[6005];

int cnt[1000005];
int dlist[1000005];

void get_subpath(int x, int d, int p){
	if(x > n || d + dep[x] > k) return;
	cnt[d + dep[x]] += p;
	for(auto &i : graph[x]){
		get_subpath(i, d, p);
	}
}

bool ret[3005];
vector<int> cstk;

void dfs(int x){
	if(x > n){
		int dx = k - dep[x];
		if(dx == 0){
			ret[x-n] = 1;
			return;
		}
		for(int i=1; i*i<=dx; i++){
			if(dx % i == 0){
				if(cnt[i] || cnt[dx / i]){
					ret[x-n] = 1;
					return;
				}
			}
		}
		int sum = dx - s;
		for(int i=cstk.size()-1; i>=0; i--){
			if(sum + dep[cstk[i]] < 0) break;
			if(dlist[sum + dep[cstk[i]]]){
				ret[x-n] = 1;
				return;
			}
		}
		return;
	}
	get_subpath(x, s - dep[x], 1);
	cstk.push_back(x);
	for(auto &i : graph[x]){
		dfs(i);
	}
	cstk.pop_back();
	get_subpath(x, s - dep[x], -1);
}

int main(){
	scanf("%d %d %d %d",&n,&m,&k,&s);
	s++;
	dlist[0] = 1;
	for(int i=1; i<=n; i++){
		int p, l;
		scanf("%d %d",&p,&l);
		l++;
		dep[i] = dep[p] + l;
		dlist[dep[i]] = 1;
		graph[p].push_back(i);
	}
	for(int i=n+1; i<=n+m; i++){
		int p, l;
		scanf("%d %d",&p,&l);
		l++;
		dep[i] = dep[p] + l;
		graph[p].push_back(i);
	}
	dfs(0);
	for(int i=1; i<=m; i++){
		puts(ret[i] ? "YES" : "NO");
	}
}