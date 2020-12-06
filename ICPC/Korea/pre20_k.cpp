// shirley smokes weed
#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using lint = long long;
using pi = pair<int, int>;
const int MAXN = 1005;
const int dx[4] = {1, 0, -1, 0};
const int dy[4] = {0, 1, 0, -1};

struct node{
	int x, y, d;
	bool operator<(const node &n)const{
		return d > n.d;
	}
};

priority_queue<node> pq;
int n, m, a[MAXN][MAXN];
int dist[MAXN][MAXN];

void enq(int x, int y, int pd){
	if(x < 0 || x >= n || y < 0 || y >= m) return;
	if(a[x][y] == -1) return;
	if(dist[x][y] > pd + a[x][y]){
		dist[x][y] = pd + a[x][y];
		pq.push({x, y, dist[x][y]});
	}
}

int main(){
	scanf("%d %d",&n,&m);
	for(int i=0; i<n; i++){
		for(int j=0; j<m; j++){
			scanf("%d",&a[i][j]);
		}
	}
	memset(dist, 0x3f, sizeof(dist));
	enq(0, 0, 0);
	while(sz(pq)){
		auto x = pq.top(); pq.pop();
		for(int i=0; i<4; i++) enq(x.x + dx[i], x.y + dy[i], x.d);
	}
	if(dist[n-1][m-1] > 1e8) dist[n-1][m-1] = -1;
	cout << dist[n-1][m-1] << endl;
}
