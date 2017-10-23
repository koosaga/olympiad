#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<int, int> pi;

struct edg{int s, e, x;};
struct disj{
	int pa[1000005];
	void init(int n){
		for(int i=0; i<n; i++) pa[i] = i;
	}
	int find(int x){
		return pa[x] = (pa[x] == x ? x : find(pa[x]));
	}
	bool uni(int p, int q){
		p = find(p);
		q = find(q);
		if(p == q) return 0;
		pa[q] = p; return 1;
	}
}disj;

int n;
char str[1005][1005];
int dis[1005][1005];
int vis[1005][1005];
queue<pi> que;
vector<pi> gph[1000005];

int par[20][1000005], pae[20][1000005], dep[1000005];

int query(int s, int e){
	if(dep[s] < dep[e]) swap(s, e);
	int dx = dep[s] - dep[e];
	int minv = 1e9;
	for(int i=0; i<20; i++){
		if((dx >> i) & 1){
			minv = min(minv, pae[i][s]);
			s = par[i][s];
		}
	}
	for(int i=19; i>=0; i--){
		if(par[i][s] != par[i][e]){
			minv = min(minv, pae[i][s]);
			minv = min(minv, pae[i][e]);
			s = par[i][s];
			e = par[i][e];
		}
	}
	if(s != e){
		minv = min({minv, pae[0][s], pae[0][e]});
	}
	return minv;
}

queue<pi> que2;

void bfs(int x, int p){
	que2.push(pi(x, p));
	pae[0][1] = 1e9;
	while(!que2.empty()){
		auto x = que2.front();
		que2.pop();
		for(auto &i : gph[x.first]){
			if(i.second != x.second){
				par[0][i.second] = x.first;
				pae[0][i.second] = i.first;
				dep[i.second] = dep[x.first] + 1;
				que2.push(pi(i.second, x.first));
			}
		}
	}
}

vector<edg> v;
int main(){
	scanf("%d",&n);
	for(int i=0; i<n; i++){
		scanf("%s", str[i]);
		for(int j=0; j<n; j++){
			if(str[i][j] == '#'){
				que.push(pi(i, j));
				vis[i][j] = 1;
			}
		}
	}
	if(que.empty()){
		memset(dis, 0x3f, sizeof(dis));
	}
	while(!que.empty()){
		auto x = que.front();
		que.pop();
		for(int i=-1; i<=1; i++){
			for(int j=-1; j<=1; j++){
				if(x.first + i < 0 || x.second + j < 0 || x.first + i >= n || x.second + j >= n) continue;
				if(!vis[x.first+i][x.second+j]){
					vis[x.first+i][x.second+j] = 1;
					dis[x.first+i][x.second+j] = dis[x.first][x.second] + 1;
					que.push(pi(x.first + i, x.second + j));
				}
			}
		}
	}
	for(int i=0; i<n; i++){
		for(int j=0; j<n; j++){
			dis[i][j] = min({dis[i][j], i+1, j+1, n-i, n-j});
		}
	}
	for(int i=0; i<n; i++){
		for(int j=0; j<n; j++){
			if(i + 1 < n){
				v.push_back({i*n+j, i*n+j+n, min(dis[i][j], dis[i+1][j])});
			}
			if(j + 1 < n){
				v.push_back({i*n+j, i*n+j+1, min(dis[i][j], dis[i][j+1])});
			}
		}
	}
	sort(v.begin(), v.end(), [&](const edg &a, const edg &b){
		return a.x > b.x;
	});
	disj.init(n*n);
	for(auto &i : v){
		if(disj.uni(i.s, i.e)){
			gph[i.s+1].push_back(pi(i.x, i.e+1));
			gph[i.e+1].push_back(pi(i.x, i.s+1));
		}
	}
	bfs(1, -1);
	for(int i=1; i<20; i++){
		for(int j=0; j<=n*n; j++){
			par[i][j] = par[i-1][par[i-1][j]];
			pae[i][j] = min(pae[i-1][j], pae[i-1][par[i-1][j]]);
		}
	}
	int q;
	scanf("%d",&q);
	while(q--){
		int sx, sy, ex, ey;
		scanf("%d %d %d %d",&sx,&sy,&ex,&ey);
		sx--,sy--,ex--,ey--;
		int p1 = sx * n + sy, p2 = ex * n + ey;
		p1++, p2++;
		int w = query(p1, p2);
		if(w == 0) puts("0");
		else printf("%d\n", 2 * w - 1);
	}
}
