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

vector<int> graph[2005];
bool vis[2005][2005];

int n, m;

void dfs(int src, int pos){
	if(vis[src][pos]) return;
	vis[src][pos] = 1;
	for(int i=0; i<graph[pos].size(); i++){
		dfs(src, graph[pos][i]);
	}
}

int NOT(int x){
	if(x > n) return x-n;
	return x+n;
}
int main(){
	scanf("%d %d",&n,&m);
	for(int i=0; i<m; i++){
		int s, e;
		char buf[5], buf2[5];
		scanf("%d %s %d %s",&s,buf,&e,buf2);
		if(*buf == 'N') s += n;
		if(*buf2 == 'N') e += n;
		s = NOT(s);
		graph[s].push_back(e);
		graph[NOT(e)].push_back(NOT(s));
	}
	for(int i=1; i<=n*2; i++){
		dfs(i, i);
	}
	for(int i=1; i<=n; i++){
		if(vis[i][i+n] && vis[i+n][i]){
			puts("IMPOSSIBLE");
			return 0;
		}
	}
	for(int i=1; i<=n; i++){
		if(vis[i][i+n]){
			putchar('N');
		}
		else if(vis[i+n][i]){
			putchar('Y');
		}
		else putchar('?');
	}
}