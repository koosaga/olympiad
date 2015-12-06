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
#include <iostream>
#include <utility>
#include <bitset>
using namespace std;
typedef long long lint;
typedef long double llf;
typedef pair<double, double> pi;
const int dx[4] = {1,0,-1,0}, dy[4] = {0,1,0,-1};
 
int n, m;
char str[1005][1005];
bool vis[1005][1005][4];
 
struct state{int x, y, d;};
queue<state> q;
int px, py;
 
inline bool ok(int x, int y){
	return x >= 0 && y >= 0 && x < n && y < m && str[x][y] == '.';
}
 
inline bool ok2(int x, int y){
	return x >= 0 && y >= 0 && x < n && y < m && str[x][y] != '#';
}
 
int dfn[1005][1005], low[1005][1005], piv;
pi par[1005][1005];
int size[1005][1005];
 
void dfs(int x, int y, int px, int py){
	dfn[x][y] = low[x][y] = ++piv;
	par[x][y] = pi(px, py);
	size[x][y] = 1;
	for(int i=0; i<4; i++){
		if(x + dx[i] == px && y + dy[i] == py) continue;
		if(ok2(x + dx[i], y + dy[i])){
			if(!dfn[x + dx[i]][y + dy[i]]){
				dfs(x + dx[i], y + dy[i], x, y);
				size[x][y] += size[x + dx[i]][y + dy[i]];
				low[x][y] = min(low[x][y], low[x + dx[i]][y + dy[i]]);
			}
			else{
				low[x][y] = min(low[x][y], dfn[x + dx[i]][y + dy[i]]);
			}
		}
	}
}
 
bool bvis[1005][1005];
vector<int> bcc[1005][1005];
int col;
 
void color(int x, int y, int c){
	if(c) bcc[x][y].push_back(c);
	bvis[x][y] = 1;
	for(int i=0; i<4; i++){
		if(ok2(x + dx[i], y + dy[i]) && !bvis[x + dx[i]][y + dy[i]]){
			if(low[x + dx[i]][y + dy[i]] >= dfn[x][y]){
				bcc[x][y].push_back(++col);
				color(x + dx[i], y + dy[i], col);
			}
			else{
				color(x + dx[i], y + dy[i], c);
			}
		}
	}
}
 
int tmp[1000005];
 
bool route(int sx, int sy, int ex, int ey, int bx, int by){
	for(int i=0; i<bcc[sx][sy].size(); i++){
		tmp[bcc[sx][sy][i]]++;
	}
	int fnd = 0;
	for(int i=0; i<bcc[ex][ey].size(); i++){
		if(tmp[bcc[ex][ey][i]]){
			fnd = 1;
			break;
		}
	}
	for(int i=0; i<bcc[sx][sy].size(); i++){
		tmp[bcc[sx][sy][i]]--;
	}
	return fnd;
}
 
int solve(int x, int y){
	vector<int> v;
	for(int i=0; i<4; i++){
		if(vis[x][y][i]) v.push_back(i);
	}
	if(v.empty()) return 0;
	if(bcc[x][y].size() == 1){
		return size[px][py] - 2;
	}
	int ret = 0;
	for(int i=0; i<v.size(); i++){
		if(par[x + dx[v[i]]][y + dy[v[i]]] == pi(x, y)){
			ret += size[x + dx[v[i]]][y + dy[v[i]]];
		}
		if(par[x][y] == pi(x + dx[v[i]], y + dy[v[i]])){
			ret += size[px][py] - size[x][y] - 1;
		}
	}
	return ret;
}
 
int main(){
	scanf("%d %d",&n,&m);
	for(int i=0; i<n; i++){
		scanf("%s",str[i]);
		for(int j=0; j<m; j++){
			if(str[i][j] == 'X') px = i, py = j;
		}
	}
	for(int i=0; i<4; i++){
		if(ok(px + dx[i], py + dy[i])){
			q.push({px, py, i});
			vis[px][py][i] = 1;
		}
	}
	dfs(px, py, -1, -1);
	color(px, py, 0);
	while(!q.empty()){
		state c = q.front();
		q.pop();
		if(ok(c.x + 2 * dx[c.d], c.y + 2 * dy[c.d]) && !vis[c.x + dx[c.d]][c.y + dy[c.d]][c.d]){
			vis[c.x + dx[c.d]][c.y + dy[c.d]][c.d] = 1;
			q.push({c.x + dx[c.d], c.y + dy[c.d], c.d});
		}
		for(int i=0; i<4; i++){
			if(i == c.d || !ok(c.x + dx[i], c.y + dy[i])) continue;
			if(vis[c.x][c.y][i]) continue;
			if(!route(c.x + dx[c.d], c.y + dy[c.d], c.x + dx[i], c.y + dy[i], c.x, c.y)){	
				continue;
			}
			vis[c.x][c.y][i] = 1;
			q.push({c.x, c.y, i});
		}
	}
	lint ret = 0;
	for(int i=0; i<n; i++){
		for(int j=0; j<m; j++){
			if(i == px && j == py) continue;
			ret += solve(i, j);
		}
	}
	printf("%lld\n",ret);
}