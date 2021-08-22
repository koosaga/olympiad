#include <bits/stdc++.h>
using namespace std;
using pi = pair<int, int>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
const int MAXN = 2100;
using lint = long long;

struct mf{
	struct edg{ int pos, cap, rev, cost; };
	vector<edg> gph[MAXN];
	void clear(){
		for(int i=0; i<MAXN; i++) gph[i].clear();
	}
	void add_edge(int s, int e, int x, int c){
		gph[s].push_back({e, x, (int)gph[e].size(), c});
		gph[e].push_back({s, 0, (int)gph[s].size()-1, -c});
	}
	int dist[MAXN], pa[MAXN], pe[MAXN];
	bool inque[MAXN];
	bool spfa(int src, int sink){
		memset(dist, 0x3f, sizeof(dist));
		memset(inque, 0, sizeof(inque));
		queue<int> que;
		dist[src] = 0;
		inque[src] = 1;
		que.push(src);
		bool ok = 0;
		while(!que.empty()){
			int x = que.front();
			que.pop();
			if(x == sink) ok = 1;
			inque[x] = 0;
			for(int i=0; i<gph[x].size(); i++){
				edg e = gph[x][i];
				if(e.cap > 0 && dist[e.pos] > dist[x] + e.cost){
					dist[e.pos] = dist[x] + e.cost;
					pa[e.pos] = x;
					pe[e.pos] = i;
					if(!inque[e.pos]){
						inque[e.pos] = 1;
						que.push(e.pos);
					}
				}
			}
		}
		return ok;
	}
	int match(int src, int sink){
		int ret = 0;
		while(spfa(src, sink)){
			int cap = 1e9;
			for(int pos = sink; pos != src; pos = pa[pos]){
				cap = min(cap, gph[pa[pos]][pe[pos]].cap);
			}
			if(dist[sink] > 0) break;
			ret += dist[sink] * cap;
			for(int pos = sink; pos != src; pos = pa[pos]){
				int rev = gph[pa[pos]][pe[pos]].rev;
				gph[pa[pos]][pe[pos]].cap -= cap;
				gph[pos][rev].cap += cap;
			}
		}
		return ret;
	}
	int par(int x, int n){
		x += n + 1;
		for(auto &j : gph[x]){
			if(j.pos <= n && j.cap == 1) return j.pos - 1;
		}
		return -1;
	}
}bpm;

int d, n;
string s[MAXN];
char buf[69];

bool subset(int i, int j){
	bool has_edge = 1;
	for(int k = 0; k < d; k++){
		if(s[i][k] == '0' && s[j][k] == '1'){
			has_edge = 0;
		}
	}
	return has_edge;
}

vector<int> gph[MAXN];
vector<int> ans;
vector<int> v;

void dfs(int x){
	if(sz(gph[x]) == 0){
		for(auto &i : v) ans.push_back(i);
		ans.push_back(-1);
	}
	for(auto &y : gph[x]){
		vector<int> cv = v;
		for(int i = 0; i < d; i++){
			if(s[x][i] != s[y][i]) v.push_back(i);
		}
		dfs(y);
		v = cv;
	}
}

int main(){
	scanf("%d %d",&d,&n);
	for(int i = 0; i < n; i++){
		scanf("%s", buf);
		s[i] = buf;
	}
	s[n] = string(d, '0');
	n++;
	sort(s, s + n, [&](const string &a, const string &b){
			return count(all(a), '1') > count(all(b), '1');
			});
	for(int i = 0; i < n; i++){
		for(int j = i+1; j < n; j++){
			if(subset(i, j)) bpm.add_edge(j+1, i+1+n, 1, 0);
		}
		bpm.add_edge(0, i+1, 1, -count(all(s[i]), '1') - 1);
		bpm.add_edge(i+n+1, 2*n+1, 1, 0);
	}
	bpm.match(0, 2*n+1);
	for(int i = 0; i < n-1; i++){
		int par = bpm.par(i, n);
		if(par == -1){
			for(int j = i+1; j < n; j++){
				if(subset(i, j)) par = j;
			}
		}
		gph[par].push_back(i);
	}
	dfs(n-1);
	ans.pop_back();
	printf("%d\n", sz(ans));
	for(auto &i : ans){
		if(i == -1) printf("R ");
		else printf("%d ", i);
	}
}
