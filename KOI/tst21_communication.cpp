#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
typedef long long lint;
typedef pair<int, int> pi;
const int MAXN = 250050;

vector<int> ans;
vector<pi> gph[MAXN];

int sz[MAXN], dfn[MAXN], low[MAXN], par[MAXN], pae[MAXN], piv;
bool cut[MAXN];

void dfs(int x, int p = -1){
	dfn[x] = low[x] = ++piv;
	sz[x] = 1;
	int isbreak = 0;
	for(auto &[idx, y] : gph[x]){
		if(idx == p) continue;
		if(!dfn[y]){
			pae[y] = idx;
			par[y] = x;
			dfs(y, idx);
			sz[x] += sz[y];
			low[x] = min(low[x], low[y]);
			if(low[y] >= dfn[x]) isbreak++;
		}
		else{
			low[x] = min(low[x], dfn[y]);
		}
	}
	if(isbreak >= 2) cut[x] = 1;
	else if(isbreak == 1 && x != 0) cut[x] = 1;
}

struct bit{
	int tree[MAXN];
	int setThres;
	void add(int x, int v){
		for(int i = x; i < setThres; i += i & -i) tree[i] += v;
	}
	int query(int x){
		int ret = 0;
		for(int i = x; i; i -= i & -i) ret += tree[i];
		return ret;
	}
}bit;

namespace solver{
	vector<pi> gph[MAXN];
	vector<int> vlist, elist;
	vector<int> ord;
	int dfn[MAXN], dout[MAXN], low[MAXN], dep[MAXN], par[MAXN], pae[MAXN], piv;

	int newCutBack[MAXN], cnt[MAXN], cut[MAXN];
	pi backInfo[MAXN * 4];
	vector<int> stk;
	vector<pi> backs;

	void dfs(int x, int p){
		dfn[x] = low[x] = ++piv;
		ord.push_back(x);
		stk.push_back(x);
		for(auto &[idx, y] : gph[x]){
			if(idx == p) continue;
			if(!dfn[y]){
				dep[y] = dep[x] + 1;
				par[y] = x;
				pae[y] = idx;
				dfs(y, idx);
				low[x] = min(low[x], low[y]);
			}
			else{
				if(dep[x] >= dep[y] + 2){
					backInfo[idx] = pi(x, stk[dep[y] + 2]);
					cnt[backInfo[idx].first]++;
					cnt[par[backInfo[idx].second]]--;
				}
				if(dep[x] > dep[y]) backs.emplace_back(x, y);
				low[x] = min(low[x], dfn[y]);
			}
		}
		dout[x] = piv;
		stk.pop_back();
	}

	int upsec[MAXN];

	void add_edge(int s, int e, int id){
		gph[s].emplace_back(id, e);
		gph[e].emplace_back(id, s);
		elist.push_back(id);
	}

	bool inSub(int u, int v){
		return dfn[u] <= dfn[v] && dout[v] <= dout[u];
	}

	pi up[MAXN], above[MAXN];
	int dp[MAXN], ap[MAXN], anc[18][MAXN];
	int aux1[MAXN], aux2[MAXN];
	pi aux3[MAXN], aux4[MAXN];
	vector<pi> event1[MAXN];
	vector<pi> event2[MAXN];
	vector<pi> intv[MAXN];

	void dfsUpSec(int x, int p){
		stk.push_back(x);
		if(dep[x] > 0) upsec[x] = stk[up[x].second];
		for(auto &[idx, y] : gph[x]){
			if(par[y] == x && pae[y] == idx){
				dfsUpSec(y, idx);
			}
		}
		stk.pop_back();
	}

	void dfsEvent1(int x, int p, vector<int> &ans){
		if(dep[x] >= 2 && !cut[par[x]]){
			bit.add(dfn[ap[x]], +1);
		}
		for(auto &[vtx, coeff] : event1[x]){
			ans[pae[vtx]] += coeff * (bit.query(dout[vtx]) - bit.query(dfn[vtx] - 1));
		}
		for(auto &[idx, y] : gph[x]){
			if(par[y] == x && pae[y] == idx){
				dfsEvent1(y, idx, ans);
			}
		}
		if(dep[x] >= 2 && !cut[par[x]]){
			bit.add(dfn[ap[x]], -1);
		}
	}

	void dfsEvent2(int x, int p, vector<int> &ans){
		for(auto &[s, e] : intv[x]){
			bit.add(s + 2, +1);
			bit.add(e + 2, -1);
		}
		for(auto &[vtx, coeff] : event2[x]){
			ans[pae[vtx]] += coeff * bit.query(dep[vtx] + 2);
		}
		for(auto &[idx, y] : gph[x]){
			if(par[y] == x && pae[y] == idx){
				dfsEvent2(y, idx, ans);
			}
		}
		for(auto &[s, e] : intv[x]){
			bit.add(s + 2, -1);
			bit.add(e + 2, +1);
		}
	}

	int lg2(int x){
		return 31 - __builtin_clz(x | 1);
	}
	int lca(int x, int y){
		if(inSub(x, y)) return x;
		for(int i = lg2(dep[x]); i >= 0; i--){
			if(!inSub(anc[i][x], y)) x = anc[i][x];
		}
		return par[x];
	}

	int uf(int x, int *pa){
		return pa[x] = (pa[x] == x ? x : uf(pa[x], pa));
	}

	void uni(int x, int y, int *pa){
		x = uf(x, pa);
		y = uf(y, pa);
		pa[x] = y; return;
	}

	void find(int x, int l, int toWrite, int* pa, pi* val, pi *val2){
		while(dep[uf(x, pa)] > l + 1){
			x = uf(x, pa);
			if(val[x].second == -1) val[x].second = toWrite;
			val2[x].second = toWrite;
			uni(x, par[x], pa);
		}
		x = uf(x, pa);
		if(dep[x] == l + 1){
			if(val[x].second == -1) val[x].second = toWrite;
		}

	}


	void solve(vector<int> &vtx, vector<int> &ans){
		vlist = vtx;
		bit.setThres = sz(vlist) + 5;
		dep[vlist[0]] = 0;
		par[vlist[0]] = pae[vlist[0]] = -1;
		dfs(vlist[0], -1);
		reverse(all(ord));
		for(auto &x : ord){
			if(dep[x]) cnt[par[x]] += cnt[x];
			if(dep[x] && !cut[par[x]] && cnt[x] == 1) newCutBack[x]++;
		}
		reverse(all(ord));
		for(auto &x : ord){
			if(dep[x]) newCutBack[x] += newCutBack[par[x]];
		}
		// solve for back edges
		for(auto &e : elist){
			if(backInfo[e] == pi(0, 0)) continue;
			ans[e] += newCutBack[backInfo[e].first] - newCutBack[par[backInfo[e].second]];
		}
		// compute up
		{
			for(auto &v : vlist){
				anc[0][v] = par[v];
				if(par[v] == -1) anc[0][v] = v;
			}
			for(int i = 1; i <= lg2(sz(vlist)); i++){
				for(auto &j : vlist){
					anc[i][j] = anc[i-1][anc[i-1][j]];
				}
			}
			sort(all(backs), [&](const pi &a, const pi &b){
				return dep[a.second] > dep[b.second];
			});
			for(auto &vtx : vlist){
				up[vtx] = pi(1e9, -1);
				above[vtx] = pi(1e9, -1);
				dp[vtx] = ap[vtx] = -1;
				aux1[vtx] = vtx;
			}
			for(auto &[u, v] : backs){ // u -> v
				up[u].first = min(up[u].first, dep[v]);
				above[u].first = min(above[u].first, dep[v]);
				find(u, dep[v], dep[v], aux1, up, above);
			}
			for(auto &vtx : vlist){
				aux1[vtx] = vtx;
				aux3[vtx] = pi(-1, -1);
				aux4[vtx] = pi(-1, -1);
			}
			sort(all(backs), [&](const pi &a, const pi &b){
				return dfn[a.first] < dfn[b.first];
			});
			for(auto &[u, v] : backs){
				find(u, dep[v], u, aux1, aux3, aux4);;
			}
			reverse(all(backs));
			for(auto &vtx : vlist){
				aux1[vtx] = vtx;
				swap(aux3[vtx].first, aux3[vtx].second);
				swap(aux4[vtx].first, aux4[vtx].second);
			}
			for(auto &[u, v] : backs){
				find(u, dep[v], u, aux1, aux3, aux4);
			}
			for(auto &x : ord){
				if(dep[x] >= 1) dp[x] = lca(aux3[x].first, aux3[x].second);
				if(dep[x] >= 2) ap[x] = lca(aux4[x].first, aux4[x].second);
			}
			reverse(all(ord));
			for(auto &x : ord){
				for(auto &[idx, y] : gph[x]){
					if(par[y] == x && pae[y] == idx){
						up[x].first = min(up[x].first, up[y].first);
						above[x].first = min(above[x].first, above[y].first);
					}
				}
			}
			reverse(all(ord));
		}

		dfsUpSec(vlist[0], -1);

		for(auto &x : ord){
			if(dep[x] == 0) continue;
			if(up[x].first == up[x].second){
				if(upsec[x] != vlist[0] && !cut[upsec[x]]) ans[pae[x]]++;
			}
			event1[par[x]].emplace_back(x, +1);
			event1[upsec[x]].emplace_back(x, -1);
			if(!cut[vlist[0]] && dep[x] >= 2 && up[x].second == 0){
				ans[pae[x]]++;
			}
		}

		dfsEvent1(vlist[0], -1, ans);

		for(auto &x : ord){
			if(cut[x] || dep[x] <= 1) continue;
			vector<pi> v;
			for(auto &[idx, y] : gph[x]){
				if(par[y] == x && pae[y] == idx){
					if(above[y].first < above[y].second){
						v.push_back(above[y]);
					}
				}
			}
			sort(all(v));
			int prev = 0;
			for(int i = 0; i < sz(v); i++){
				if(prev < v[i].first){
					intv[x].emplace_back(prev + 1, v[i].first + 1);
				}
				prev = max(prev, v[i].second);
			}
			if(prev + 1< dep[x]) intv[x].emplace_back(prev + 1, dep[x]);
		}

		for(auto &x : ord){
			if(dep[x] >= 1) event2[dp[x]].emplace_back(x, +1);
		}

		dfsEvent2(vlist[0], -1, ans);
	}

	void clear(){
		for(auto &x : vlist){
			gph[x].clear();
			dfn[x] = low[x] = cnt[x] = newCutBack[x] = 0;
			event1[x].clear();
			event2[x].clear();
			intv[x].clear();
		}
		backs.clear();
		piv = 0;
		vlist.clear();
		elist.clear();
		ord.clear();
	}
};

int c;
vector<int> bcc[MAXN], cmp[MAXN];
void color(int x, int p){
	if(p){
		bcc[p].push_back(x);
		cmp[x].push_back(p);
	}
	for(auto &[_, i] : gph[x]){
		if(cmp[i].size()) continue;
		if(low[i] >= dfn[x]){
			bcc[++c].push_back(x);
			cmp[x].push_back(c);
			color(i, c);
		}
		else color(i, p);
	}
}

std::vector<int> find_num_critical(int N, std::vector< std::pair<int, int> > E){
	int M = sz(E);
	for(int i = 0; i < M; i++){
		E[i].first--;
		E[i].second--;
		gph[E[i].first].emplace_back(i, E[i].second);
		gph[E[i].second].emplace_back(i, E[i].first);
	}
	ans.resize(M);
	if(N == 2) return ans;
	dfs(0);
	color(0, 0);
	for(int i = 0; i < M; i++){
		if(dfn[E[i].first] > dfn[E[i].second]) swap(E[i].first, E[i].second);
		if(pae[E[i].second] == i){
			if(low[E[i].second] > dfn[E[i].first]){
				if(sz[E[i].second] == 1 || sz[E[i].second] == N - 1) ans[i] = N - 1;
				else ans[i] = N;
			}
		}
	}
	vector<vector<int>> edges(c);
	for(int i = 0; i < M; i++){
		int y = cmp[E[i].second][0];
		edges[y - 1].push_back(i);
	}
	int cutCnt = count(cut, cut + N, 1);
	vector<int> fn(N);
	for(int i = 0; i < sz(edges); i++){
		if(sz(edges[i]) == 1) continue;
		vector<int> gcc;
		for(int j = 0; j < sz(bcc[i + 1]); j++){
			fn[bcc[i+1][j]] = j;
			gcc.push_back(j);
			solver::cut[j] = cut[bcc[i+1][j]];
		}
		for(auto &j : edges[i]){
			solver::add_edge(fn[E[j].first], fn[E[j].second], j);
		}
		solver::solve(gcc, ans);
		solver::clear();
		for(auto &j : edges[i]) ans[j] += cutCnt;
	}
	return ans;
}

int main() {
	int N, M;
	scanf("%d %d", &N, &M);

	std::vector< std::pair<int, int> > E(M);
	for(int i = 1; i <= M; i++) {
		int a, b;
		scanf("%d %d", &a, &b);
		E[i-1].first = a;
		E[i-1].second = b;
	}

	std::vector<int> result = find_num_critical(N, E);

	for(int i = 0; i < (int)result.size(); i++) {
		printf("%d\n", result[i]);
	}

	return 0;
}

