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

int nxt[500005];
int ind[500005];
int paint[500005];
int vis[500005];
int n, k;

queue<int> q;
vector<int> graph[500005];

int cnt = 0;

int dfs(int x){
	int ret = 0;
	if(x == 1) ret = k;
	for(auto &i : graph[x]){
		ret = max(ret, dfs(i));
	}
	ret--;
	if(ret < 0) ret = k-1, cnt++; 
	return ret;
}

int col[500005], jmp[500005];

void solve_cycle(int x){
	int p = 0;
	while(!vis[x]){
		vis[x] = 1;
		col[p++] = paint[x];
		x = nxt[x];
	}
	int pcol = col[0];
	for(int i=1; i<2*p; i++){
		pcol = col[i%p] = max(pcol - 1, col[i%p]);
	}
	for(int i=p; i>=0; i--){
		if(!col[i]) jmp[i] = i;
		else jmp[i] = jmp[i+1];
	}
	int tcnt = 0;
	int pos = jmp[0];
	while(pos < p){
		pos = jmp[min(pos + k, p)];
		tcnt++;
	}
	for(int i=1; i<min(k,p); i++){
		int q = p-k+i;
		int pos = jmp[i];
		int cnt = 0;
		while(pos < q){
			pos = jmp[min(pos + k, p)];
			cnt++;
		}
		tcnt = min(tcnt, cnt + 1);
	}
	cnt += tcnt;
	memset(col, 0, sizeof(int) * (2*p+1));
	memset(jmp, 0, sizeof(int) * (p+1));
}

int main(){
	scanf("%d %d",&n,&k);
	for(int i=1; i<=n; i++){
		int x;
		scanf("%d",&x);
		scanf("%d",&nxt[x]);
		ind[nxt[x]]++;
		graph[nxt[x]].push_back(x);
	}
	for(int i=1; i<=n; i++){
		if(ind[i] == 0){
			q.push(i);
		}
	}
	while(!q.empty()){
		int qf = q.front();
		q.pop();
		vis[qf] = 1;
		ind[nxt[qf]]--;
		if(ind[nxt[qf]] == 0){
			q.push(nxt[qf]);
		}
	}
	for(int i=1; i<=n; i++){
		if(!vis[i]){
			int ret = -1;
			for(int j=0; j<graph[i].size(); j++){
				if(!vis[graph[i][j]]) continue;
				ret = max(ret, dfs(graph[i][j]) - 1);
			}
			paint[i] = ret + 1; // who will paint me
			if(i == 1) paint[i] = k + 1;
		}
	}
	for(int i=1; i<=n; i++){
		if(!vis[i]){
			solve_cycle(i);
		}
	}
	printf("%d",cnt);
}