#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = pair<int, int>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
const int MAXN = 505;
const int MAXM = 505;

/*wtf*/
bool chk[MAXN * MAXN];
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

int n, a[MAXN][MAXN], b[MAXN][MAXN];
int X[MAXN][MAXN];

int main(){
	auto DoH = [&](int a[MAXN][MAXN], int b[MAXN][MAXN]){
		for(int i=0; i<n; i++){
			vector<int> v(b[i], b[i] + n);
			sort(all(v), [&](const int &a, const int &b){
				return (a-1)%n < (b-1)%n;
			});
			for(int j=0; j<n; j++) a[i][j] = v[j];
		}
	};
	auto DoV = [&](int a[MAXN][MAXN], int b[MAXN][MAXN]){
		for(int i=0; i<n; i++){
			vector<int> v;
			for(int j=0; j<n; j++) v.push_back(b[j][i]);
			sort(all(v));
			for(int j=0; j<n; j++) a[j][i] = v[j];
		}
	};
	auto print_grid = [&](int v[MAXN][MAXN]){
		for(int i=0; i<n; i++){
			for(int j=0; j<n; j++){
				printf("%d ", v[i][j]);
			}
			puts("");
		}
	};
	auto good_grid = [&](int v[MAXN][MAXN]){
		bool good = 1;
		for(int i=0; i<n; i++){
			for(int j=0; j<n; j++){
				if(v[i][j] != i*n+j+1){
					good = 0;
				}
			}
		}
		return good;
	};
	auto solve = [&](){
		memset(chk, 0, sizeof(chk));
		for(int i=0; i<n; i++){
			for(int i=0; i<n; i++) for(int j=0; j<n; j++) X[i][j] = 0;
			for(int i=0; i<n; i++){
				for(int j=0; j<n; j++){
					if(chk[a[i][j]]) continue;
					int col = (a[i][j] - 1) / n;
					X[i][col] = a[i][j];
				}
			}
			bpm.clear();
			for(int i=0; i<n; i++) for(int j=0; j<n; j++){
				if(X[i][j]) bpm.add_edge(i, j);
			}
			assert(bpm.match(n) == n);
			for(int j=0; j<n; j++){
				b[j][i] = X[j][bpm.l[j]];
				chk[b[j][i]] = 1;
			}
		}
		puts("3");
		print_grid(b);
		DoV(b, b);
		print_grid(b);
		DoH(b, b);
		print_grid(b);
	};
	int tc; scanf("%d",&tc);
	while(tc--){
		scanf("%d",&n);
		for(int i=0; i<n; i++){
			for(int j=0; j<n; j++){
				scanf("%d",&a[i][j]);
			}
		}
		if(good_grid(a)){
			puts("0");
			continue;
		}
		DoH(b, a);
		if(good_grid(b)){
			puts("1");
			print_grid(b);
			continue;
		}
		DoV(b, a);
		if(good_grid(b)){
			puts("1");
			print_grid(b);
			continue;
		}
		DoH(b, a);
		DoV(b, b);
		if(good_grid(b)){
			puts("2");
			DoH(b, a);
			print_grid(b);
			DoV(b, b);
			print_grid(b);
			continue;
		}
		DoV(b, a);
		DoH(b, b);
		if(good_grid(b)){
			puts("2");
			DoV(b, a);
			print_grid(b);
			DoH(b, b);
			print_grid(b);
			continue;
		}
		solve();
	}
}

