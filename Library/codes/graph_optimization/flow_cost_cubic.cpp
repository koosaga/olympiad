template <class T> struct MinCostCirculation {
	const int SCALE = 3; // scale by 1/(1 << SCALE)
	const T INF = numeric_limits<T>::max() / 2;
	struct EdgeStack {
		int s, e;
		T l, r, cost;
	};
	struct Edge {
		int pos, rev;
		T rem, cap, cost;
	};
	int n;
	vector<EdgeStack> estk;
	Circulation<T> circ;
	vector<vector<Edge>> gph;
	vector<T> p;
	MinCostCirculation(int k) : circ(k), gph(k), p(k) { n = k; }
	void addEdge(int s, int e, T l, T r, T cost){
		estk.push_back({s, e, l, r, cost});
	}
	pair<bool, T> solve(){
		for(auto &i : estk){
			if(i.s != i.e) circ.addEdge(i.s, i.e, i.l, i.r);
		}
		if(!circ.solve(-1, -1)){
			return make_pair(false, T(0));
		}
		vector<int> ptr(n);
		T eps = 0;
		for(auto &i : estk){
			T curFlow;
			if(i.s != i.e) curFlow = i.r - circ.mf.G[i.s + 2][ptr[i.s]].rem;
			else curFlow = i.r;
			int srev = sz(gph[i.e]);
			int erev = sz(gph[i.s]);
			if(i.s == i.e) srev++;
			gph[i.s].push_back({i.e, srev, i.r - curFlow, i.r, i.cost * (n + 1)});
			gph[i.e].push_back({i.s, erev, -i.l + curFlow, -i.l, -i.cost * (n + 1)});
			eps = max(eps, abs(i.cost) * (n + 1));
			if(i.s != i.e){
				ptr[i.s] += 2;
				ptr[i.e] += 2;
			}
		}
		while(true){
			auto cost = [&](Edge &e, int s, int t){
				return e.cost + p[s] - p[t];
			};
			eps = 0;
			for(int i = 0; i < n; i++){
				for(auto &e : gph[i]){
					if(e.rem > 0) eps = max(eps, -cost(e, i, e.pos));
				}
			}
			if(eps <= T(1)) break;
			eps = max(T(1), eps >> SCALE);
			bool upd = 1;
			for(int it = 0; it < 5 && upd; it++){
				upd = false;
				for(int i = 0; i < n; i++){
					for(auto &e : gph[i]){
						if(e.rem > 0 && p[e.pos] > p[i] + e.cost + eps){
							p[e.pos] = p[i] + e.cost + eps;
							upd = true;
						}
					}
				}
				if(!upd) break;
			}
			if(!upd) continue;
			vector<T> excess(n);
			queue<int> que;
			auto push = [&](Edge &e, int src, T flow){
				e.rem -= flow;
				gph[e.pos][e.rev].rem += flow;
				excess[src] -= flow;
				excess[e.pos] += flow;
				if(excess[e.pos] <= flow && excess[e.pos] > 0){
					que.push(e.pos);
				}
			};
			vector<int> ptr(n);
			auto relabel = [&](int v){
				ptr[v] = 0;
				p[v] = -INF;
				for(auto &e : gph[v]){
					if(e.rem > 0){
						p[v] = max(p[v], p[e.pos] - e.cost - eps);
					}
				}
			};
			for(int i = 0; i < n; i++){
				for(auto &j : gph[i]){
					if(j.rem > 0 && cost(j, i, j.pos) < 0){
						push(j, i, j.rem);
					}
				}
			}
			while(sz(que)){
				int x = que.front();
				que.pop();
				while(excess[x] > 0){
					for(; ptr[x] < sz(gph[x]); ptr[x]++){
						Edge &e = gph[x][ptr[x]];
						if(e.rem > 0 && cost(e, x, e.pos) < 0){
							push(e, x, min(e.rem, excess[x]));
							if(excess[x] == 0) break;
						}
					}
					if(excess[x] == 0) break;
					relabel(x);
				}
			}
		}
		T ans = 0;
		for(int i = 0; i < n; i++){
			for(auto &j : gph[i]){
				j.cost /= (n + 1);
				ans += j.cost * (j.cap - j.rem);
			}
		}
		return make_pair(true, ans / 2);
	}
	void bellmanFord(){
		fill(all(p), T(0));
		bool upd = 1;
		while(upd){
			upd = 0;
			for(int i = 0; i < n; i++){
				for(auto &j : gph[i]){
					if(j.rem > 0 && p[j.pos] > p[i] + j.cost){
						p[j.pos] = p[i] + j.cost;
						upd = 1;
					}
				}
			}
		}
	}
};
