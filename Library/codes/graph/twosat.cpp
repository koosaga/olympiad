
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
			comp[i] = ncomps - comp[i] - 1;
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