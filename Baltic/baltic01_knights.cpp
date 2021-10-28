#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using llf = long double;
using pi = pair<int, int>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
const int MAXN = 40005;
const int MAXM = 40005;
const int mod = 1e9 + 7;

struct bpm{
	vector<int> gph[MAXN];
	int dis[MAXN], l[MAXN], r[MAXM], vis[MAXN];
	void clear(){ for(int i=0; i<MAXN; i++) gph[i].clear();	}
	void add_edge(int l, int r){ gph[l].push_back(r); }
	bool bfs(int n){
		queue<int> que;
		bool ok = 0;
		memset(dis, 0, sizeof(dis));
		for(int i=0; i<n; i++){
			if(l[i] == -1 && !dis[i]){
				que.push(i);
				dis[i] = 1;
			}
		}
		while(!que.empty()){
			int x = que.front();
			que.pop();
			for(auto &i : gph[x]){
				if(r[i] == -1) ok = 1;
				else if(!dis[r[i]]){
					dis[r[i]] = dis[x] + 1;
					que.push(r[i]);
				}
			}
		}
		return ok;
	}
	bool dfs(int x){
		if(vis[x]) return 0;
		vis[x] = 1;
		for(auto &i : gph[x]){
			if(r[i] == -1 || (!vis[r[i]] && dis[r[i]] == dis[x] + 1 && dfs(r[i]))){
				l[x] = i; r[i] = x;
				return 1;
			}
		}
		return 0;
	}
	int match(int n){
		memset(l, -1, sizeof(l));
		memset(r, -1, sizeof(r));
		int ret = 0;
		while(bfs(n)){
			memset(vis, 0, sizeof(vis));
			for(int i=0; i<n; i++) if(l[i] == -1 && dfs(i)) ret++;
		}
		return ret;
	}
	bool chk[MAXN + MAXM];
	void rdfs(int x, int n){
		if(chk[x]) return;
		chk[x] = 1;
		for(auto &i : gph[x]){
			chk[i + n] = 1;
			rdfs(r[i], n);
		}
	}
	vector<int> getcover(int n, int m){ // solve min. vertex cover
		match(n);
		memset(chk, 0, sizeof(chk));
		for(int i=0; i<n; i++) if(l[i] == -1) rdfs(i, n);
		vector<int> v;
		for(int i=0; i<n; i++) if(!chk[i]) v.push_back(i);
		for(int i=n; i<n+m; i++) if(chk[i]) v.push_back(i);
		return v;
	}
}bpm;

map<pi, int> mp;

int findOrCreate(pi p){
	if(mp.find(p) != mp.end()) return mp[p];
	int s = sz(mp);
	return mp[p] = s;
}

const int dx[8] = {1, 2, 2, 1, -1, -2, -2, -1};
const int dy[8] = {2, 1, -1, -2, -2, -1, 1, 2};

int arr[205][205];
int chk[205][205];

int main(){
	int m, n;
	scanf("%d %d",&m,&n);
	for(int i = 1; i <= n; i++){
		int x, y; scanf("%d %d",&x,&y);
		chk[x+2][y+2] = 1;
	}
	n = 0;
	for(int i = 3; i <= m + 2; i++){
		for(int j = 3; j <= m + 2; j++){
			if(!chk[i][j]) arr[i][j] = ++n;
		}
	}
	for(int x = 3; x <= m + 2; x++){
		for(int y = 3; y <= m + 2; y++){
			if(!arr[x][y]) continue;
			for(int j = 0; j < 8; j++){
				if(arr[x + dx[j]][y + dy[j]]){
					int k = arr[x + dx[j]][y + dy[j]];
					if((x + y) % 2) bpm.add_edge(arr[x][y], k);
					else bpm.add_edge(k, arr[x][y]);
				}
			}
		}
	}
	cout << n - bpm.match(n + 1) << endl;
}
