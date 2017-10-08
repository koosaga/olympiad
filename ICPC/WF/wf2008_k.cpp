#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<lint, int> pi;
const int mod = 1e9 + 7;

struct edge{int s, e, x, dir;};

struct node{
	int pos, sel, cost;
	bool operator<(const node &n)const{
		return cost > n.cost;
	}
};

vector<int> gph[40005];
vector<edge> edg;
int v, s, e;

void solve(){
	priority_queue<node> pq;
	bool vis[40005][2] = {};
	for(auto &i : gph[s]){
		pq.push({i, 1, 2 * edg[i].x});
	}
	int ans = 2e9;
	while(!pq.empty()){
		auto x = pq.top();
		pq.pop();
		if(vis[x.pos][x.sel]) continue;
		int cp = edg[x.pos].e;
		if(cp == e){
			ans = min(ans, x.cost + (1 - x.sel) * edg[x.pos].x);
		}
		vis[x.pos][x.sel] = 1;
		for(auto &i : gph[cp]){
			if(edg[i].dir != edg[x.pos].dir){
				pq.push({i, 1, x.cost + edg[i].x * 2 + (1 - x.sel) * edg[x.pos].x});
			}
			else{
				pq.push({i, 0, x.cost + edg[i].x});
			}
		}
	}
	if(ans > 2e9 - 5) puts("Impossible");
	else printf("%d\n", ans);
}


int main(){
	int tc = 0;
	while(1){
		int n, m, r1, c1, r2, c2;
		cin >> n >> m >> r1 >> c1 >> r2 >> c2;
		if(r1 == 0) break;
		r1--, c1--, r2--, c2--;
		for(int i=0; i<n * m; i++) gph[i].clear();
		edg.clear();
		s = r1 * m + c1, e = r2 * m + c2;
		for(int i=0; i<n; i++){
			for(int j=0; j<m-1; j++){
				int x;
				scanf("%d",&x);
				if(x == 0) continue;
				int s = i * m + j, e = i * m + j + 1;
				edg.push_back({s, e, x, 0});
				gph[s].push_back(edg.size() - 1);
				edg.push_back({e, s, x, 2});
				gph[e].push_back(edg.size() - 1);
			}
			if(i + 1 == n) break;
			for(int j=0; j<m; j++){
				int x;
				scanf("%d",&x);
				if(x == 0) continue;
				int s = i * m + j, e = i * m + j + m;
				edg.push_back({s, e, x, 1});
				gph[s].push_back(edg.size() - 1);
				edg.push_back({e, s, x, 3});
				gph[e].push_back(edg.size() - 1);
			}	
		}
		printf("Case %d: ", ++tc);
		solve();
	}
}
