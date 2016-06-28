#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<int, int> pi;
 
int n, m;
char s[1005][1005];
int lx[1005][1005], ly[1005][1005], hx[1005][1005], hy[1005][1005];
int dx[4] = {1, 0, -1, 0}, dy[4] = {0, 1, 0, -1};
 
struct node{
	int x, y, d;
	bool operator>(const node &b)const{
		return d > b.d;
	}
};
 
int sx, sy, ex, ey;
int dist[1005][1005];
priority_queue<node, vector<node>, greater<node> > pq;
 
void enq(int x, int y, int d){
	if(dist[x][y] <= d){
		return;
	}
	dist[x][y] = d;
	pq.push({x, y, d});
}
 
int main(){
	cin >> n >> m;
	for(int i=0; i<n; i++){
		cin >> s[i];
	}
	for(int i=0; i<n; i++){
		ly[i][0] = -1;
		hy[i][m-1] = m;
		for(int j=0; j<m; j++){
			if(s[i][j] == '#') ly[i][j] = j;
			else if(j) ly[i][j] = ly[i][j-1];
		}
		for(int j=m-1; j>=0; j--){
			if(s[i][j] == '#') hy[i][j] = j;
			else if(j<m-1) hy[i][j] = hy[i][j+1];
		}
	}
	for(int j=0; j<m; j++){
		lx[0][j] = -1;
		hx[n-1][j] = n;
		for(int i=0; i<n; i++){
			if(s[i][j] == '#') lx[i][j] = i;
			else if(i) lx[i][j] = lx[i-1][j];
		}
		for(int i=n-1; i>=0; i--){
			if(s[i][j] == '#') hx[i][j] = i;
			else if(i<n-1) hx[i][j] = hx[i+1][j];
		}
	}
	cin >> sx >> sy >> ex >> ey;
	sx--, sy--, ex--, ey--;
	memset(dist, 0x3f, sizeof(dist));
	enq(sx, sy, 0);
	while(!pq.empty()){
		auto t = pq.top();
		pq.pop();
		if(dist[t.x][t.y] < t.d) continue;
		if(t.x == ex && t.y == ey){
			printf("%d\n", dist[t.x][t.y]);
			return 0;
		}
		for(int i=0; i<4; i++){
			int px = t.x + dx[i];
			int py = t.y + dy[i];
			if(px < 0 || py < 0 || px >= n || py >= m) continue;
			if(s[px][py] == '#') continue;
			enq(px, py, dist[t.x][t.y] + 2);
		}
		if(lx[t.x][t.y] + 1 < t.x){
			enq(lx[t.x][t.y] + 1, t.y, dist[t.x][t.y] + 1);
		}
		if(hx[t.x][t.y] - 1 > t.x){
			enq(hx[t.x][t.y] - 1, t.y, dist[t.x][t.y] + 1);
		}
		if(ly[t.x][t.y] + 1 < t.y){
			enq(t.x, ly[t.x][t.y] + 1, dist[t.x][t.y] + 1);
		}
		if(hy[t.x][t.y] - 1 > t.y){
			enq(t.x, hy[t.x][t.y] - 1, dist[t.x][t.y] + 1);
		}
	}
	if(dist[ex][ey] > 1e9){
		puts("-1");
		return 0;
	}
	cout << dist[ex][ey] << endl;
}