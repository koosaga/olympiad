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

vector<int> graph[200005];

int n, m, s, e, a, b;
int da[200005], db[200005];
bool vis[200005];

queue<int> q;

void bfs(int s, int *d){
	memset(vis,0,sizeof(vis));
	vis[s] = 1;
	q.push(s);
	while(!q.empty()){
		int x = q.front();
		q.pop();
		for(auto &i : graph[x]){
			if(!vis[i]){
				d[i] = d[x] + 1;
				vis[i] = 1;
				q.push(i);
			}
		}
	}
}

int bfs2(int x){
	memset(vis,0,sizeof(vis));
	vis[x] = 1;
	q.push(x);
	int tmp = da[x], ret = 0;
	while(!q.empty()){
		int x = q.front();
		ret = max(ret, tmp - da[x]);
		q.pop();
		for(auto &i : graph[x]){
			if(!vis[i] && da[i] == da[x] - 1 && db[i] == db[x] - 1){
				vis[i] = 1;
				q.push(i);
			}
		}
	}
	return ret;
}

int main(){
	scanf("%d %d %d %d %d %d",&n,&m,&s,&e,&a,&b);
	for(int i=0; i<m; i++){
		int s, e;
		scanf("%d %d",&s,&e);
		graph[s].push_back(e);
		graph[e].push_back(s);
	}
	bfs(a, da);
	bfs(b, db);
	int w1 = da[e] - da[s];
	int w2 = db[e] - db[s];
	if(w1 != w2){
		printf("%d",max(min(w1, w2),-1));
	}
	else{
		int b1 = bfs2(s);
		int b2 = bfs2(e);
		printf("%d",max(w1 - (w1 + b1 < b2), -1));
	}
}