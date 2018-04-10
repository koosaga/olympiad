#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef long double llf;
typedef pair<int, int> pi;
const int MAXN = 84;

struct edg{ int pos, cap, rev, cost; };
vector<edg> gph[MAXN];

void clear(){
	for(int i=0; i<MAXN; i++) gph[i].clear();
}
void add_edge(int s, int e, int x, int c){
	gph[s].push_back({e, x, (int)gph[e].size(), c});
	gph[e].push_back({s, 0, (int)gph[s].size()-1, -c});
}

int n, a, b;
char str[44][44];

int dist[MAXN], par[MAXN], pae[MAXN];

int negative_cycle(int n){
	bool mark[MAXN] = {};
	memset(dist, 0, sizeof(dist));
	int upd = -1;
	for(int i=0; i<=n; i++){
		for(int j=0; j<n; j++){
			int idx = 0;
			for(auto &k : gph[j]){
				if(k.cap > 0 && dist[k.pos] > dist[j] + k.cost){
					dist[k.pos] = dist[j] + k.cost;
					par[k.pos] = j;
					pae[k.pos] = idx;
					if(i == n){
						upd = j;
						while(!mark[upd]){
							mark[upd] = 1;
							upd = par[upd];
						}
						return upd;
					}
				}
				idx++;
			}
		}
	}
	return -1;
}

int match(int n){
	int rt = -1;
	int ans = 0;
	while(~(rt = negative_cycle(n))){
		bool mark[MAXN] = {};
		vector<pi> cyc;
		while(!mark[rt]){
			cyc.push_back(pi(par[rt], pae[rt]));
			mark[rt] = 1;
			rt = par[rt];
		}
		reverse(cyc.begin(), cyc.end());
		int capv = 1e9;
		for(auto &i : cyc){
			auto e = &gph[i.first][i.second];
			capv = min(capv, e->cap);
		}
		for(auto &i : cyc){
			auto e = &gph[i.first][i.second];
			e->cap -= capv;
			gph[e->pos][e->rev].cap += capv;
			ans += e->cost * capv;
		}
	}
	return ans;
}

int solve(){
	int thres = 0, C = 0;
	for(int i=0; i<n; i++) thres += count(str[i], str[i] + n, '.');
	clear();
	for(int i=0; i<n; i++){
		add_edge(i, i+n, 0, 0);
	}
	for(int i=0; i<n; i++){
		for(int j=0; j<n; j++){
			if(str[i][j] == '.'){
				add_edge(i + n, j, 1, -1);
			}
			if(str[i][j] == 'C'){
				C++;
				add_edge(i + n, j, 1, -10000);
			}
		}
	}
	int mem[MAXN] = {};
	mem[0] = -10000 * C;
	int curmatch = 0;
	for(int f=1; f<=n; f++){
		for(int i=0; i<n; i++){
			gph[i][0].cap++;
		}
		curmatch += match(2*n);
		int w = curmatch + 10000 * C;
		mem[f] = -w;
	}
	while(thres >= 0){
		int k = (thres + C) * a / b;
		k = min(k, n);
		if(mem[k] == thres) break;
		thres--;
	}
	return thres;
}

int main(){
	for(int i=1; ; i++){
		cin >> n >> a >> b;
		if(!n) break;
		printf("Case %d: ", i);
		for(int i=0; i<n; i++) cin >> str[i];
		int ret = solve();
		if(ret == -1) puts("impossible");
		else printf("%d\n", ret);
	}
}



