#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
typedef long long lint;
typedef pair<int, int> pi;
const int MAXN = 1000005;

struct tree{
	vector<int> gph[MAXN];
	vector<pi> rel[MAXN];
	int par[20][MAXN], dep[MAXN];
	int R, din[MAXN], dout[MAXN], piv;
	pi minDep;
	void dfs(int x){
		din[x] = ++piv;
		for(auto &y : gph[x]){
			dep[y] = dep[x] + 1;
			dfs(y);
		}
		dout[x] = piv;
	}
	void init(int n, int *p){
		minDep = pi(1e9, -1);
		for(int i = 0; i < n; i++){
			if(p[i] == -1){
				R = i;
				par[0][i] = i;
			}
			else{
				par[0][i] = p[i];
				gph[p[i]].push_back(i);
			}
		}
		for(int i = 1; i < 20; i++){
			for(int j = 0; j < n; j++){
				par[i][j] = par[i-1][par[i-1][j]];
			}
		}
		dfs(R);
	}
	int lca(int u, int v){
		if(dep[u] > dep[v]) swap(u, v);
		int dx = dep[v] - dep[u];
		for(int i = 0; dx; i++){
			if(dx & 1) v = par[i][v];
			dx >>= 1;
		}
		if(u == v) return u;
		for(int i = 19; i >= 0; i--){
			if(par[i][v] != par[i][u]){
				v = par[i][v];
				u = par[i][u];
			}
		}
		return par[0][v];
	}
	void upload(int u, int v, int da, int db){
		int l = lca(u, v);
		minDep = min(minDep, pi(dep[l], l));
		if(u != l){
			rel[l].emplace_back(u, +da);
			rel[u].emplace_back(l, -da);
		}
		if(v != l){
			rel[l].emplace_back(v, +db);
			rel[v].emplace_back(l, -db);
		}
	}
	int comp[MAXN], vis[MAXN];
	void compute(){
		queue<int> que;
		auto enq = [&](int x){
			if(!vis[x]){
				vis[x] = 1;
				que.push(x);
			}
		};
		enq(minDep.second);
		while(sz(que)){
			int x = que.front();
			que.pop();
			for(auto &[y, w] : rel[x]){
				comp[y] = comp[x] + w;
				enq(y);
			}
		}
	}
	int dist(int u, int v){
		return comp[u] + comp[v] - 2 * comp[lca(u, v)];
	}
}T[2];

int p[2][MAXN];

int main(){
	int n, k, q; scanf("%d %d %*d %d",&n,&k,&q);
	for(int i = 0; i < 2; i++){
		for(int j = 0; j < n; j++){
			scanf("%d",&p[i][j]);
			if(p[i][j] != -1) p[i][j]--;
		}
	}
	for(int i = 0; i < 2; i++){
		T[i].init(n, p[i]);
	}
	vector<int> v;
	{
		queue<int> que;
		que.push(T[0].R);
		while(sz(v) < k){
			int x = que.front(); que.pop();
			v.push_back(x);
			for(auto &y : T[0].gph[x]) que.push(y);
		}
	}
	for(auto &x : v) cout << x+1 << " ";
	cout << "\n";
	cout.flush();
	sort(all(v), [&](const int &a, const int &b){
		return T[1].din[a] < T[1].din[b];
	});
	for(int i = 0; i < sz(v) - 1; i++){
		cout << "? " << v[i] + 1 << " " << v[i+1] + 1 << "\n";
	}
	cout << "!" << endl;
	cout.flush();
	for(int i = 0; i < sz(v) - 1; i++){
		int a, b, c, d; scanf("%d %d %d %d",&a,&b,&c,&d);
		T[0].upload(v[i], v[i + 1], a, b);
		T[1].upload(v[i], v[i + 1], c, d);
	}
	T[0].compute();
	T[1].compute();
	vector<pi> ans(q);
	for(int i = 0; i < q; i++){
		int u, v; cin >> u >> v;
		u--; v--;
		ans[i].first = T[0].dist(u, v);
		ans[i].second = T[1].dist(u, v);
	}
	for(int i = 0; i < q; i++) cout << ans[i].first << " " << ans[i].second << "\n";
	cout.flush();
}
