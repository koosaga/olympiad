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
const char key[5] = "byrg";
const char door[5] = "BYRG";
const int dx[4] = {0, 1, 0, -1}, dy[4] = {1, 0, -1, 0};

int getkey(char x){ return find(key, key+4, x) - key; }
int getdoor(char x){ return find(door, door+4, x) - door; }

struct node{
	int x, y, d, dist;
};

bool vis[105][105][16];

int n, m;
char str[105][105];

int main(){
	while(1){
		scanf("%d %d",&n,&m);
		if(n + m == 0) break;
		for(int i=0; i<n; i++) cin >> str[i];
		memset(vis, 0, sizeof(vis));
		queue<node> q;
		for(int i=0; i<n; i++){
			for(int j=0; j<m; j++){
				if(str[i][j] == '*'){
					q.push({i, j, 0, 0});
					vis[i][j][0] = 1;
				}
			}
		}
		bool ok = 0;
		while(!q.empty()){
			auto f = q.front();
			q.pop();
			if(str[f.x][f.y] == 'X'){
				printf("Escape possible in %d steps.\n",f.dist);
				ok = 1;
				break;
			}
			for(int i=0; i<4; i++){
				if(f.x + dx[i] < 0 || f.y + dy[i] < 0 || f.x + dx[i] >= n || f.y + dy[i] >= m){
					continue;
				}
				if(str[f.x + dx[i]][f.y + dy[i]] == '#') continue;
				int t = getdoor(str[f.x + dx[i]][f.y + dy[i]]);
				if(t != 4 && (f.d >> t) % 2 == 0) continue;
				int u = getkey(str[f.x + dx[i]][f.y + dy[i]]);
				node nw = {f.x + dx[i], f.y + dy[i], (u == 4 ? f.d : (f.d | (1<<u))), f.dist + 1};
				if(vis[nw.x][nw.y][nw.d]) continue;
				vis[nw.x][nw.y][nw.d] = 1;
				q.push(nw);
			}
		}
		if(!ok) puts("The poor student is trapped!");
	}
}