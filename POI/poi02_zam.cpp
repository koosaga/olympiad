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
typedef pair<lint, int> pi;

int n, m, s, e, b, a[105];
bool vis[105][1005], adj[105][105];
int par[105][1005];

int main(){
	cin >> n >> m >> s >> e >> b;
	for(int i=1; i<=n; i++) cin >> a[i];
	for(int i=0; i<m; i++){
		int x, y;
		cin >> x >> y;
		adj[x][y] = adj[y][x] = 1;
	}
	vis[s][a[s]] = 1;
	queue<pi> que;
	que.push(pi(s, a[s]));
	while(!que.empty()){
		pi x = que.front();
		que.pop();
		for(int i=1; i<=n; i++){
			if(adj[x.first][i] && x.second + a[i] <= b && !vis[i][x.second + a[i]]){
				vis[i][x.second + a[i]] = 1;
				par[i][x.second + a[i]] = x.first;
				que.push(pi(i, x.second + a[i]));
			}
		}
	}
	vector<int> v;
	for(int i=e; b; b -= a[i], i=par[i][b + a[i]]){
		v.push_back(i);
	}
	reverse(v.begin(), v.end());
	for(int i=0; i<v.size(); i++) printf("%d ", v[i]);
}
