#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = pair<int, int>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
const int MAXN = 500005;

struct strongly_connected{
	vector<vector<int>> gph;

	void init(int n){
		gph.clear();
		gph.resize(n);
	}

	void add_edge(int s, int e){
		gph[s].push_back(e);
	}

	vector<int> val, comp, z, cont;
	int Time, ncomps;
	template<class G, class F> int dfs(int j, G& g, F f) {
		int low = val[j] = ++Time, x; z.push_back(j);
		for(auto e : g[j]) if (comp[e] < 0)
			low = min(low, val[e] ?: dfs(e,g,f));

		if (low == val[j]) {
			do {
				x = z.back(); z.pop_back();
				comp[x] = ncomps;
				cont.push_back(x);
			} while (x != j);
			f(cont); cont.clear();
			ncomps++;
		}
		return val[j] = low;
	}
	template<class G, class F> void scc(G& g, F f) {
		int n = sz(g);
		val.assign(n, 0); comp.assign(n, -1);
		Time = ncomps = 0;
		for(int i=0; i<n; i++) if (comp[i] < 0) dfs(i, g, f);
	}

	int piv;
	void get_scc(int n){
		scc(gph, [&](vector<int> &v){});
		for(int i=0; i<n; i++){
			comp[i] = ncomps - comp[i];
		}
		piv = ncomps;
	}
}scc;

vector<int> gph[MAXN], ord[MAXN];

int chk[MAXN], col[MAXN];

void dfs(int x, int c){
	if(col[x]) return;
	col[x] = c;
	for(auto &y : gph[x]){
		if(chk[y] && !col[y]){
			dfs(y, 3 - c);
		}
	}
}

int main(){	
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int n, m;
	cin >> n >> m;
	vector<pi> a(m);
	vector<int> deg(n);
	vector<vector<int>> rev(n);
	scc.init(n);
	for(auto &[x, y] : a){
		cin >> x >> y;
		x--; y--;
		scc.add_edge(x, y);
		deg[x]++;
		rev[y].push_back(x);
		gph[x].push_back(y);
		gph[y].push_back(x);
	}
	scc.get_scc(n);
	int M = scc.piv;
	for(int i = 0; i < n; i++){
		ord[scc.comp[i] - 1].push_back(i);
	}
	for(int i = 0; i < M; i++){
		for(auto &j : ord[i]) chk[j] = 1;
		for(auto &j : ord[i]) if(!col[j]) dfs(j, 1);
		for(auto &j : ord[i]) chk[j] = 0;
	}
	queue<int> que;
	for(int i = 0; i < n; i++){
		if(deg[i] == 0){
			que.push(i);
		}
	}
	vector<int> ans;
	vector<int> mark(n);
	for(int i = M - 1; i >= 0; i--){
		while(sz(que)){
			int x = que.front(); que.pop();
			ans.push_back(x);
			mark[x] = 1;
			for(auto &y : rev[x]){
				deg[y]--;
				if(!mark[y]){
					mark[y] = 1;
					for(auto &z : rev[y]){
						deg[z]--;
						if(!mark[z] && deg[z] == 0) que.push(z);
					}
				}
			}
		}
		for(auto &y : ord[i]){
			if(col[y] == 1 && !mark[y]){
				mark[y] = 1;
				for(auto &z : rev[y]){
					deg[z]--;
					if(!mark[z] && deg[z] == 0) que.push(z);
				}
			}
		}
		while(sz(que)){
			int x = que.front(); que.pop();
			ans.push_back(x);
			mark[x] = 1;
			for(auto &y : rev[x]){
				deg[y]--;
				if(!mark[y]){
					mark[y] = 1;
					for(auto &z : rev[y]){
						deg[z]--;
						if(!mark[z] && deg[z] == 0) que.push(z);
					}
				}
			}
		}
	}
	cout << sz(ans) << "\n";
	for(auto &y : ans) cout << y + 1 << " ";
}
