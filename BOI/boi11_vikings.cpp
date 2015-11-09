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
#include <array>
using namespace std;
typedef long long lint;
typedef long double llf;
typedef pair<int, int> pi;

int n, m;
int dist1[705][705], dist2[705][705], dist3[705][705];
char str[705][705];

queue<int> qx, qy;
int dx[4] = {1,0,-1,0}, dy[4] = {0,1,0,-1};

void bfs(int sx, int sy, int dist[705][705]){
	memset(dist,0x3f,705 * 705 * sizeof(int));
	qx.push(sx);
	qy.push(sy);
	dist[sx][sy] = 0;
	while(!qx.empty()){
		int xf = qx.front();
		int yf = qy.front();
		qx.pop(), qy.pop();
		for(int i=0; i<4; i++){
			if(xf + dx[i] < 0 || yf + dy[i] < 0 || xf + dx[i] >= n || yf + dy[i] >= m){
				continue;
			}
			if(str[xf + dx[i]][yf + dy[i]] == 'I'){
				continue;
			}
			if(dist[xf + dx[i]][yf + dy[i]] < 1e9) continue;
			qx.push(xf + dx[i]);
			qy.push(yf + dy[i]);
			dist[xf + dx[i]][yf + dy[i]] = dist[xf][yf] + 1;
		}
	}
}

bool vis[705][705];

bool bfs(int sx, int sy){
	qx.push(sx);
	qy.push(sy);
	vis[sx][sy] = 1;
	memset(dist1,0x3f,sizeof(dist1));
	dist1[sx][sy] = 0;
	while(!qx.empty()){
		int xf = qx.front();
		int yf = qy.front();
		qx.pop(), qy.pop();
		if(str[xf][yf] == 'T') return 1;
		for(int i=0; i<4; i++){
			if(xf + dx[i] < 0 || yf + dy[i] < 0 || xf + dx[i] >= n || yf + dy[i] >= m){
				continue;
			}
			if(str[xf + dx[i]][yf + dy[i]] == 'I'){
				continue;
			}
			if(dist3[xf + dx[i]][yf + dy[i]] > dist1[xf][yf] + 1 && !vis[xf + dx[i]][yf + dy[i]]){
				vis[xf + dx[i]][yf + dy[i]] = 1;
				dist1[xf + dx[i]][yf + dy[i]] = dist1[xf][yf] + 1;
				qx.push(xf + dx[i]);
				qy.push(yf + dy[i]);
			}
		}
	}
	return 0;
}

int main(){
	scanf("%d %d",&n,&m);
	for(int i=0; i<n; i++){
		scanf("%s",str[i]);
	}
	int sx, sy;
	for(int i=0; i<n; i++){
		for(int j=0; j<m; j++){
			if(str[i][j] == 'Y') sx = i, sy = j;
			if(str[i][j] == 'V') bfs(i, j, dist2);
		}
	}
	memset(dist3,0x3f,sizeof(dist3));
	for(int i=0; i<n; i++){
		int minv = 1e9;
		for(int j=0; j<m; j++){
			if(str[i][j] == 'I') minv = 1e9;
			else minv = min(minv, dist2[i][j]);
			dist3[i][j] = min(dist3[i][j], minv);
		}
		minv = 1e9;
		for(int j=m-1; j>=0; j--){
			if(str[i][j] == 'I') minv = 1e9;
			else minv = min(minv, dist2[i][j]);
			dist3[i][j] = min(dist3[i][j], minv);
		}
	}
	for(int i=0; i<m; i++){
		int minv = 1e9;
		for(int j=0; j<n; j++){
			if(str[j][i] == 'I') minv = 1e9;
			else minv = min(minv, dist2[j][i]);
			dist3[j][i] = min(dist3[j][i], minv);
		}
		minv = 1e9;
		for(int j=n-1; j>=0; j--){
			if(str[j][i] == 'I') minv = 1e9;
			else minv = min(minv, dist2[j][i]);
			dist3[j][i] = min(dist3[j][i], minv);
		}
	}
	puts(bfs(sx, sy) ? "YES" : "NO");
}
