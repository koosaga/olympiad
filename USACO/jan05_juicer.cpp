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
int a[505][505];
int dx[4] = {1, 0, -1, 0}, dy[4] = {0, 1, 0, -1};

int get(int a, int b){
	if(a < 0 || a >= n || b < 0 || b >= m) return 0;
	return a * m + b + 1;
}

struct disj{
	int pa[250005];
	void init(int n){
		for(int i=0; i<=n; i++) pa[i] = i;
	}
	int find(int x){
		return pa[x] = (pa[x] == x ? x : find(pa[x]));
	}
	bool uni(int p, int q){
		p = find(p), q = find(q);
		if(p == q) return 0;
		pa[q] = p; return 1;
	}
}disj;

struct edg{int s, e, x;};
vector<edg> v;
int sp[250005];
vector<pi> graph[250005];

void dfs(int x, int p){
	for(auto &i : graph[x]){
		if(i.second == p) continue;
		sp[i.second] = max(sp[i.second], max(sp[x], i.first));
		dfs(i.second, x);
	}
}

int main(){
	scanf("%d %d",&m,&n);
	for(int i=0; i<n; i++){
		for(int j=0; j<m; j++){
			scanf("%d",&a[i][j]);
		}
	}
	for(int i=0; i<n; i++){
		for(int j=0; j<m; j++){
			for(int k=0; k<4; k++){
				int s = get(i, j), e = get(i + dx[k], j + dy[k]);
				if(s == 0 || e == 0){
					v.push_back({s, e, a[i][j]});
				}
				else{
					v.push_back({s, e, max(a[i][j], a[i+dx[k]][j+dy[k]])});
				}
			}
		}
	}
	disj.init(n*m+1);
	sort(v.begin(), v.end(), [&](const edg &a, const edg &b){return a.x < b.x;});
	for(auto &i : v){
		if(disj.uni(i.s, i.e)){
			graph[i.s].push_back(pi(i.x, i.e));
			graph[i.e].push_back(pi(i.x, i.s));
		}
	}
	dfs(0, -1);
	lint ret = 0;
	for(int i=0; i<n; i++){
		for(int j=0; j<m; j++){
			ret += sp[get(i, j)] - a[i][j];
		}
	}
	printf("%lld",ret);
}