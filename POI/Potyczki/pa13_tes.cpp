#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = pair<int, int>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
const int MAXN = 500005;
const int mod = 1e9 + 7;


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

struct twosat{
	strongly_connected scc;
	int n;
	void init(int _n){ scc.init(2 * _n); n = _n; }
	int NOT(int x){ return x >= n ? (x - n) : (x + n); }
	void add_edge(int x, int y){
		if((x >> 31) & 1) x = (~x) + n;
		if((y >> 31) & 1) y = (~y) + n;
		scc.add_edge(x, y), scc.add_edge(NOT(y), NOT(x));
	}
	bool satisfy(int *res){
		scc.get_scc(2*n);
		for(int i=0; i<n; i++){
			if(scc.comp[i] == scc.comp[NOT(i)]) return 0;
			if(scc.comp[i] < scc.comp[NOT(i)]) res[i] = 0;
			else res[i] = 1;
		}
		return 1;
	}
}twosat;

int main(){	
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int n; cin >> n;
	vector<vector<int>> x(n, vector<int>(n));
	vector<vector<int>> y(n, vector<int>(n));
	vector<vector<int>> v(n);
	for(int i = 0; i < n; i++){
		for(int j = 0; j < n; j++){
			cin >> x[i][j];
		}
	}
	for(int i = 0; i < n; i++){
		for(int j = 0; j < n; j++){
			cin >> y[i][j];
		}
	}
	for(int i = 0; i < n; i++){
		for(int j = 0; j < n; j++){
			x[i][j] = min(x[i][j], x[j][i]);
			y[i][j] = max(y[i][j], y[j][i]);
		}
	}
	for(int i = 0; i < n; i++){
		v[i] = y[i];
		v[i].push_back(1);
		sort(all(v[i]));
		v[i].resize(unique(all(v[i])) - v[i].begin());
	}
	vector<int> psum(n + 1);
	for(int i = 0; i < n; i++) psum[i + 1] = psum[i] + sz(v[i]);
	auto S = [&](int x, int y){ return psum[x] + y; };
	twosat.init(psum[n]);
	for(int i = 0; i < n; i++){
		for(int j = 0; j + 1 < sz(v[i]); j++){
			twosat.add_edge(S(i, j + 1), S(i, j));
		}
		twosat.add_edge(~S(i, 0), S(i, 0));
	}
	for(int i = 0; i < n; i++){
		for(int j = 0; j <= i; j++){
			int p = lower_bound(all(v[i]), y[i][j]) - v[i].begin();
			int q = lower_bound(all(v[j]), y[i][j]) - v[j].begin();
			twosat.add_edge(~S(i, p), S(j, q));
		}
	}
	for(int i = 0; i < n; i++){
		for(int j = 0; j <= i; j++){
			int q = sz(v[j]);
			for(int k = 0; k < sz(v[i]); k++){
				while(q > 0 && x[i][j] - v[i][k] + 1 <= v[j][q - 1]) q--;
				if(q < sz(v[j])) twosat.add_edge(S(i, k), ~S(j, q));
			}
		}
	}
	int res[100000] = {};
	assert(twosat.satisfy(res));
	for(int i = 0; i < n; i++){
		for(int j = sz(v[i]) - 1; j >= 0; j--){
			if(res[S(i, j)]){
				cout << v[i][j] << " ";
				break;
			}
		}
	}
}
	
