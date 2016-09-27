#include <cstdio>
#include <cstring>
#include <queue>
int n,v[50][50],d[50][50],f[50][50];
struct pos{int x,y,d;};
bool operator<(pos p, pos q){return p.d > q.d;}

std::priority_queue<pos> q;

int main(){
	pos c;
	memset(d,0x3f,sizeof(d));
	scanf("%d",&n);
	for (int i=0; i<n; i++) {
		for (int j=0; j<n; j++) {
			scanf("%1d",&v[i][j]);
		}
	}
	q.push({0,0,0});
	while (1) {
		while (f[q.top().x][q.top().y] && !q.empty()) q.pop();
		if(q.empty()) break;
		c = q.top();
		q.pop();
		d[c.x][c.y] = c.d;
		f[c.x][c.y] = 1;
		if(c.x) q.push({c.x-1,c.y,c.d+!v[c.x-1][c.y]});
		if(c.y) q.push({c.x,c.y-1,c.d+!v[c.x][c.y-1]});
		if(c.x+1<n) q.push({c.x+1,c.y,c.d+!v[c.x+1][c.y]});
		if(c.y+1<n) q.push({c.x,c.y+1,c.d+!v[c.x][c.y+1]});
	}
	printf("%d",d[n-1][n-1]);
}