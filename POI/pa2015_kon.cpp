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

vector<int> gph[500005];
vector<int> dag[500005];
vector<int> cyc;

int n, m, s[1000005], e[1000005];
int vis[500005], stk[500005], par[500005];

void dfs(int x){
	vis[x] = 1;
	stk[x] = 1;
	for(int i=0; i<gph[x].size(); i++){
		int v = gph[x][i];
		if(stk[v] && cyc.empty()){
			for(int j=x; j!=v; j=par[j]){
				cyc.push_back(j);
			}
			cyc.push_back(v);
			reverse(cyc.begin(), cyc.end());
		}
		if(!vis[v]){
			par[v] = x;
			dfs(v);
		}
	}
	stk[x] = 0;
}

int chk[500005];
int lab[500005], topo[500005], piv;
int indeg[500005];

int dp1[500005], dp2[500005], dp3[500005], dx[500005];

void solve(){
	memset(dp2, 0x3f, sizeof(dp2));
	for(int i=piv; i; i--){
		int v = topo[i];
		for(int j=0; j<gph[v].size(); j++){
			int w = gph[v][j];
			if(lab[w]) dp1[v] = max(dp1[v], lab[w]);
			else dp1[v] = max(dp1[v], dp1[w]);
			if(lab[w]) dp2[v] = min(dp2[v], lab[w]);
			else dp2[v] = min(dp2[v], dp2[w]);
		}
	}
	for(int i=1; i<cyc.size(); i++){
		int v = cyc[i];
		for(int j=0; j<gph[v].size(); j++){
			int w = gph[v][j];
			if(lab[w]) dp1[v] = max(dp1[v], lab[w]);
			else dp1[v] = max(dp1[v], dp1[w]);
			if(lab[w]) dp2[v] = min(dp2[v], lab[w]);
			else dp2[v] = min(dp2[v], dp2[w]);
		}
	}
	for(int i=1; i<cyc.size(); i++){
		int v = cyc[i];
		for(int j=0; j<gph[v].size(); j++){
			int w = gph[v][j];
			if(!lab[w]) dp3[w] = max(dp3[w], i);
			else dp3[w] = max(dp3[w], i);
		}
	}
	for(int i=1; i<=piv; i++){
		int v = topo[i];
		for(int j=0; j<gph[v].size(); j++){
			int w = gph[v][j];
			dp3[w] = max(dp3[w], dp3[v]);
		}
	}
	for(int i=1; i<cyc.size(); i++){
		if(i < dp1[cyc[i]]){
			dx[i+1]++;
			dx[dp1[cyc[i]]]--;
		}
	}
	for(int i=1; i<cyc.size(); i++){
		if(dp2[cyc[i]] <= i){
			dx[i+1]++;
			dx[cyc.size()]--;
			break;
		}
	}
	for(int i=(int)cyc.size()-1; i; i--){
		if(dp3[cyc[i]] >= i){
			dx[1]++;
			dx[i]--;
			break;
		}
	}
	for(int i=1; i<cyc.size(); i++){
		dx[i] += dx[i-1];
		if(!dx[i]) chk[cyc[i]] = 1;
	}
}

int main(){
	scanf("%d %d",&n,&m);
	for(int i=0; i<m; i++){
		scanf("%d %d",&s[i],&e[i]);
		gph[s[i]].push_back(e[i]);
	}
	for(int i=1; i<=n; i++){
		if(!vis[i]){
			dfs(i);
			if(cyc.size()) break;
		}
	}
	if(cyc.empty()) return !puts("NIE");
	reverse(cyc.begin(), cyc.end());
	cyc.push_back(-1);
	reverse(cyc.begin(), cyc.end());
	for(int i=1; i<cyc.size(); i++){
		lab[cyc[i]] = i;
	}
	for(int i=0; i<m; i++){
		if(!lab[s[i]] && !lab[e[i]]){
			dag[s[i]].push_back(e[i]);
			indeg[e[i]]++;
		}
	}
	queue<int> que;
	for(int i=1; i<=n; i++){
		if(!lab[i] && !indeg[i]){
			que.push(i);
		}
	}
	while(!que.empty()){
		int x = que.front();
		que.pop();
		topo[++piv] = x;
		for(int i=0; i<dag[x].size(); i++){
			indeg[dag[x][i]]--;
			if(!indeg[dag[x][i]]){
				que.push(dag[x][i]);
			}
		}
	}
	for(int i=1; i<=n; i++){
		if(indeg[i]) return !printf("0\n\n");
	}
	solve();
	printf("%d\n", count(chk+1, chk+n+1, 1));
	for(int i=1; i<=n; i++){
		if(chk[i]) printf("%d ", i);
	}
	puts("");
}
