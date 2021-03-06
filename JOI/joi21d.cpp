#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using lint = long long;
using llf = long double;
using pi = pair<lint, lint>;
const int MAXN = 500005;

vector<pi> gph[MAXN];
lint dist[MAXN];

void add_edge(int s, int e, lint x){
	//printf("%d %d %d\n", s, e, x);
	gph[s].emplace_back(x, e);
}

struct edg{
	int s, e, x;
}nxte[MAXN];

int n, m;
int deg1[MAXN], deg2[MAXN];
vector<edg> edgs[MAXN];
vector<int> in[MAXN];
vector<pi> out[MAXN];
lint costOut[MAXN];

int main(){
	scanf("%d %d",&n,&m);
	int newV = n;
	for(int i = 0; i < m; i++){
		int s, e, c, p;
		scanf("%d %d %d %d",&s,&e,&c,&p);
		edgs[c].push_back({s, e, p});
		edgs[c].push_back({e, s, p});
	}
	for(int i = 1; i <= m; i++){
		for(auto &x : edgs[i]){
			deg1[x.e]++;
			out[x.s].emplace_back(x.e, x.x);
			in[x.e].push_back(x.s);
			deg2[x.s]++;
			costOut[x.s] += x.x;
			nxte[x.s] = x;
		}
		for(auto &x : edgs[i]){
			add_edge(x.s, x.e, min(1ll * x.x, costOut[x.s] - x.x));
			if(sz(out[x.s])){
				newV++;
				for(auto &[e, w] : out[x.s]){
					add_edge(newV, e, costOut[x.s] - w);
				}
				for(auto &q : in[x.s]){
					add_edge(q, newV, 0);
				}
				out[x.s].clear();
			}
		}
		for(auto &x : edgs[i]){
			deg1[x.e]--;
			costOut[x.s] = 0;
			deg2[x.s]--;
			in[x.e].clear();
		}
	}
	priority_queue<pi, vector<pi>, greater<pi> > pq;
	memset(dist, 0x3f, sizeof(dist));
	auto enq = [&](int x, lint d){
		if(dist[x] > d){
			dist[x] = d;
			pq.emplace(d, x);
		}
	};
	enq(1, 0);
	while(sz(pq)){
		auto x = pq.top(); pq.pop();
		if(dist[x.second] != x.first) continue;
		for(auto &[w, v] : gph[x.second]){
			enq(v, w + x.first);
		}
	}
	if(dist[n] > 1e17) dist[n] = -1;
	cout << dist[n] << endl;
}
