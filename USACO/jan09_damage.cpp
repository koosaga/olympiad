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

int n, m, k;
vector<int> graph[30005];
bool chk[30005];

struct disj{
	int pa[30005], sz[30005];
	void init(int n){
		for(int i=1; i<=n; i++) pa[i] = i, sz[i] = 1;
	}
	int find(int x){
		return pa[x] = (pa[x] == x ? x : find(pa[x]));
	}
	bool uni(int p, int q){
		p = find(p);
		q = find(q);
		if(p == q) return 0;
		pa[q] = p;
		sz[p] += sz[q];
		return 1;
	}
}disj;

int main(){
	scanf("%d %d %d",&n,&m,&k);
	for(int i=0; i<m; i++){
		int s, e;
		scanf("%d %d",&s,&e);
		graph[s].push_back(e);
		graph[e].push_back(s);
	}
	disj.init(n);
	while(k--){
		int p;
		scanf("%d",&p);
		for(auto &i : graph[p]){
			chk[i] = 1;
		}
	}
	for(int i=1; i<=n; i++){
		for(auto &j : graph[i]){
			if(!chk[i] && !chk[j]){
				disj.uni(i, j);
			}
		}
	}
	printf("%d",n - disj.sz[disj.find(1)]);
}