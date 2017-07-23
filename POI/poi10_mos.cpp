#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef long double llf;
typedef pair<int, int> pi;

const int MAXN = 3005;
struct maxflow{
	struct edg{int pos, cap, rev;};
	vector<edg> gph[MAXN];

	void clear(){
		for(int i=0; i<MAXN; i++){
			gph[i].clear();
		}
	}

	void add_edge(int s, int e, int x){
		gph[s].push_back({e, x, (int)gph[e].size()});
		gph[e].push_back({s, 0, (int)gph[s].size()-1});
	}

	int dis[MAXN], pnt[MAXN];

	bool bfs(int src, int sink){
		memset(dis, 0, sizeof(dis));
		memset(pnt, 0, sizeof(pnt));
		queue<int> que;
		que.push(src);
		dis[src] = 1;
		while(!que.empty()){
			int x = que.front();
			que.pop();
			for(int i=0; i<gph[x].size(); i++){
				edg e = gph[x][i];
				if(e.cap > 0 && !dis[e.pos]){
					dis[e.pos] = dis[x] + 1;
					que.push(e.pos);
				}
			}
		}
		return dis[sink] > 0;
	}

	int dfs(int x, int sink, int f){
		if(x == sink) return f;
		for(; pnt[x] < gph[x].size(); pnt[x]++){
			edg e = gph[x][pnt[x]];
			if(e.cap > 0 && dis[e.pos] == dis[x] + 1){
				int w = dfs(e.pos, sink, min(f, e.cap));
				if(w){
					gph[x][pnt[x]].cap -= w;
					gph[e.pos][e.rev].cap += w;
					return w;
				}
			}
		}
		return 0;
	}

	lint match(int src, int sink){
		lint ret = 0;
		while(bfs(src, sink)){
			int r;
			while((r = dfs(src, sink, 2e9))) ret += r;
		}
		return ret;
	}
}mf;

int n, m;
int s[2005], e[2005], l[2005], r[2005];
int deg[1005], in[1005], out[1005];

bool trial(int x){
	memset(in, 0, sizeof(in));
	memset(out, 0, sizeof(out));
	vector<int> v;
	for(int i=0; i<m; i++){
		if(l[i] > x){
			in[e[i]]++;
			out[s[i]]++;
		}
		else if(r[i] > x){
			in[s[i]]++;
			out[e[i]]++;
		}
		else{
			v.push_back(i);
		}
	}
	mf.clear();
	for(int i=1; i<=n; i++){
		if(in[i] * 2 > deg[i] || out[i] * 2 > deg[i]){
			return 0;
		}
		int new_in = deg[i] / 2 - in[i];
		mf.add_edge(0, i, new_in);
	}
	for(int j=0; j<v.size(); j++){
		mf.add_edge(s[v[j]], v[j] + n + 1, 1);
		mf.add_edge(e[v[j]], v[j] + n + 1, 1);
		mf.add_edge(v[j] + n + 1, n + m + 1, 1); 
	}
	return mf.match(0, n + m + 1) == v.size();
}

vector<pi> gph[1005];
vector<int> dfn;

void dfs(int x){
	while(!gph[x].empty()){
		auto l = gph[x].back();
		gph[x].pop_back();
		dfs(l.first);
		dfn.push_back(l.second + 1);
	}
}

int main(){
	cin >> n >> m;
	int st = 0, ed = 1000;
	for(int i=0; i<m; i++){
		cin >> s[i] >> e[i] >> l[i] >> r[i];
		deg[s[i]]++;
		deg[e[i]]++;
		st = max(st, min(l[i], r[i]));
	}
	for(int i=1; i<=n; i++){
		if(deg[i] & 1){
			puts("NIE");
			return 0;
		}
	}
	while(st != ed){
		int m = (st + ed) / 2;
		if(trial(m)) ed = m;
		else st = m+1;
	}
	trial(st);
	for(int i=0; i<m; i++){
		if(l[i] > st){
			gph[e[i]].push_back(pi(s[i], i));
		}
		else if(r[i] > st){
			gph[s[i]].push_back(pi(e[i], i));
		}
		else{
			for(auto &j : mf.gph[i + n + 1]){
				if(j.cap == 1){
					if(s[i] == j.pos) gph[s[i]].push_back(pi(e[i], i));
					else gph[e[i]].push_back(pi(s[i], i));
					break;
				}
			}
		}
	}
	cout << st << endl;
	dfs(1);
	reverse(dfn.begin(), dfn.end());
	for(auto &i : dfn) printf("%d ", i);
}
