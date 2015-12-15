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

int n, m, px = -1, py = -1;
int a[405][405];
lint lx[805][805], ly[805][805];
bool cx[405][405], cy[405][405];

bool vis[805][805];
lint dist[805][805];
pi par[805][805];

struct edg{
	int x, y;
	lint cst;
	bool operator<(const edg &a)const{
		return cst > a.cst;
	}
};

priority_queue<edg> pq;

void input(){
	scanf("%d %d",&n,&m);
	for(int i=0; i<n; i++){
		for(int j=0; j<m; j++){
			scanf("%d",&a[i][j]);
			if(a[i][j] && px == -1){
				px = i, py = j;
			}
		}
	}
	for(int i=0; i<n; i++){
		for(int j=0; j<=m; j++){
			scanf("%lld",&lx[i][j]);
		}
	}
	for(int i=0; i<=n; i++){
		for(int j=0; j<m; j++){
			scanf("%lld",&ly[i][j]);
		}
	}
}

void dijkstra(lint lx[805][805], lint ly[805][805], int n, int m, int s, int e){
	memset(dist,0x3f,sizeof(dist));
	memset(vis,0,sizeof(vis));
	dist[s][e] = 0;
	pq.push({s,e,0});
	while(!pq.empty()){
		edg t = pq.top();
		pq.pop();
		if(vis[t.x][t.y]) continue;
		vis[t.x][t.y] = 1;
		if(t.x < n && dist[t.x+1][t.y] > t.cst + lx[t.x][t.y]){
			dist[t.x+1][t.y] = t.cst + lx[t.x][t.y];
			par[t.x+1][t.y] = pi(t.x, t.y);
			pq.push({t.x + 1, t.y, dist[t.x+1][t.y]});
		}
		if(t.y < m && dist[t.x][t.y+1] > t.cst + ly[t.x][t.y]){
			dist[t.x][t.y+1] = t.cst + ly[t.x][t.y];
			par[t.x][t.y+1] = pi(t.x, t.y);
			pq.push({t.x, t.y + 1, dist[t.x][t.y+1]});
		}
		if(t.x && dist[t.x-1][t.y] > t.cst + lx[t.x-1][t.y]){
			dist[t.x-1][t.y] = t.cst + lx[t.x-1][t.y];
			par[t.x-1][t.y] = pi(t.x, t.y);
			pq.push({t.x - 1, t.y, dist[t.x-1][t.y]});
		}
		if(t.y && dist[t.x][t.y-1] > t.cst + ly[t.x][t.y-1]){
			dist[t.x][t.y-1] = t.cst + ly[t.x][t.y-1];
			par[t.x][t.y-1] = pi(t.x, t.y);
			pq.push({t.x, t.y - 1, dist[t.x][t.y-1]});
		}
	}
}

lint lx2[805][805], ly2[805][805];

void paintpath(int x, int y){
	if(x == 0 && y == 0) return;
	pi t = par[x][y];
	if(t.first == x-1 && !cx[x-1][y]){
		cx[x-1][y] = 1;
		paintpath(x-1, y);
	}
	if(t.first == x+1 && !cx[x][y]){
		cx[x][y] = 1;
		paintpath(x+1, y);
	}
	if(t.second == y-1 && !cy[x][y-1]){
		cy[x][y-1] = 1;
		paintpath(x, y-1);
	}
	if(t.second == y+1 && !cy[x][y]){
		cy[x][y] = 1;
		paintpath(x, y+1);
	}
}

void add_edge(int sx, int sy, int ex, int ey, int c){
	if(sx != ex){
		lx2[min(sx, ex)][ey] = c;
	}
	if(sy != ey){
		ly2[sx][min(sy, ey)] = c;
	}
}

void make_graph(){
	for(int i=0; i<n; i++){
		for(int j=0; j<m; j++){
			if(a[i][j]) paintpath(i, j);
		}
	}
	for(int i=0; i<n; i++){
		for(int j=0; j<m; j++){
			if(a[i][j]){
				cx[i][j] = cx[i][j+1] = 1;
				cy[i][j] = cy[i+1][j] = 1;
			}
		}
	}
	memset(lx2,0x3f,sizeof(lx2));
	memset(ly2,0x3f,sizeof(ly2));
	for(int i=0; i<n; i++){
		for(int j=0; j<=m; j++){
			add_edge(2*i+1, 2*j, 2*i+2, 2*j, lx[i][j]);
			add_edge(2*i+1, 2*j+1, 2*i+2, 2*j+1, lx[i][j]);
		}
	}
	for(int i=0; i<=n; i++){
		for(int j=0; j<m; j++){
			add_edge(2*i, 2*j+1, 2*i, 2*j+2, ly[i][j]);
			add_edge(2*i+1, 2*j+1, 2*i+1, 2*j+2, ly[i][j]);
		}
	}
	for(int i=0; i<=n; i++){
		for(int j=0; j<=m; j++){
			if(i == 0 && j == 0){
				if(!cx[0][0]){
					add_edge(1, 0, 1, 1, 0);
				}
				if(!cy[0][0]){
					add_edge(0, 1, 1, 1, 0);
				}
			}
			else{
				if(!i || !cx[i-1][j]){
					add_edge(2*i, 2*j, 2*i, 2*j+1, 0);
				}
				if(!j || !cy[i][j-1]){
					add_edge(2*i, 2*j, 2*i+1, 2*j, 0);
				}
				if(i == n || !cx[i][j]){
					add_edge(2*i+1, 2*j, 2*i+1, 2*j+1, 0);
				}
				if(j == m || !cy[i][j]){
					add_edge(2*i, 2*j+1, 2*i+1, 2*j+1, 0);
				}
			}
		}
	}
}

int main(){
	input();
	dijkstra(lx, ly, n, m, 0, 0);
	make_graph();
	dijkstra(lx2, ly2, 2*n+1, 2*m+1, 1, 0);
	cout << dist[0][1];
}