// Given an undirected graph G with integer vertex & edge capacities,
// Find a *flow* f: E -> Z>=0, which respects vertex & edge capacity:
// A flow respects the capacity of vertex v if the sum of flow values on incident edges EQUALS to the vertex capacity.
// This is a special case of skew symmetric flow and it generalizes perfect matching.
// O(n^3)
// Credit: model code of Yandex Cup 2020

namespace SkewSymmetricFlow {
// #define _GLIBCXX_DEBUG
#define forn(i, n) for (int i = 0; i < (int)(n); ++i)
#define fore(i, b, e) for (int i = (int)(b); i <= (int)(e); ++i)
#define ford(i, n) for (int i = (int)(n) - 1; i >= 0; --i)
#define pb push_back
#define fi first
#define se second
typedef vector<int> vi;
typedef pair<int, int> pii;
typedef long long i64;
typedef unsigned long long u64;
typedef long double ld;
typedef long long ll;

namespace dinic {

const int maxn = 100100;
struct Edge {
	int to;
	i64 c, f;
	Edge(int to, i64 c) : to(to), c(c), f(0) {}
};

vector<Edge> es;
vector<int> e[maxn];
int q[maxn], d[maxn], pos[maxn];
int n, S, T;

bool bfs() {
	fill(d, d + n, maxn);
	d[S] = 0, q[0] = S;
	int rq = 1;
	forn(lq, rq) {
		int v = q[lq];
		for (int id : e[v]) {
			if (es[id].c == es[id].f)
				continue;
			int to = es[id].to;
			if (d[to] == maxn) {
				d[to] = d[v] + 1;
				q[rq++] = to;
			}
		}
	}
	return d[T] != maxn;
}

i64 dfs(int v, i64 curf) {
	if (v == T)
		return curf;
	i64 ret = 0;
	for (int &i = pos[v]; i < (int)e[v].size(); ++i) {
		int id = e[v][i];
		int to = es[id].to;
		i64 delta = min(curf, es[id].c - es[id].f);
		if (delta == 0 || d[to] != d[v] + 1) {
			continue;
		}
		delta = dfs(to, delta);
		curf -= delta;
		ret += delta;
		es[id].f += delta;
		es[id ^ 1].f -= delta;
		if (curf == 0)
			return ret;
	}
	return ret;
}

void addEdge(int u, int v, i64 c) {
	n = max(n, max(u, v) + 1);
	e[u].push_back(es.size());
	es.emplace_back(v, c);
	e[v].push_back(es.size());
	es.emplace_back(u, 0);
}

i64 runDinic(int S_, int T_) {
	S = S_;
	T = T_;
	i64 res = 0;
	while (bfs()) {
		fill(pos, pos + n, 0);
		while (i64 cur = dfs(S, 1e18)) {
			res += cur;
		}
	}
	return res;
}

void clear() {
	forn(i, n) e[i].clear();
	es.clear();
}

} // namespace dinic

const int maxn = 505;

int n;
int c[maxn][maxn];
int f[maxn];
int b[maxn][maxn];

void findDirectedFactor() {
	int S = n * 2, T = n * 2 + 1;
	i64 sumf = 0;
	forn(i, n) {
		dinic::addEdge(S, i, f[i]);
		dinic::addEdge(i + n, T, f[i]);
		sumf += f[i];
	}
	forn(i, n) forn(j, n) if (i != j) {
		if (c[i][j] > 0) {
			dinic::addEdge(i, j + n, c[i][j]);
		}
	}
	i64 flow = dinic::runDinic(S, T);
	if (flow != sumf) {
		//	cerr << "No directed factor\n";
		cout << "No\n";
		assert(false);
		exit(0);
	}

	forn(i, n) {
		for (int id : dinic::e[i]) {
			if (id % 2 == 0) {
				const auto &e = dinic::es[id];
				if (e.to < n * 2) {
					b[i][e.to - n] += e.f;
				}
			}
		}
	}

	forn(i, n) forn(j, i) {
		int t = b[i][j] + b[j][i];
		b[i][j] = b[j][i] = t;
	}

	// Check symmetry.
	forn(i, n) forn(j, n) assert(b[i][j] == b[j][i]);

	// Check f-factor.
	forn(i, n) {
		int x = 0;
		forn(j, n) x += b[i][j];
		assert(x == f[i] * 2);
	}
}

int oddCycleCount;
int oddCycleIndex[maxn * maxn];
int indexInCycle[maxn];
int visited[maxn];
vi oddCycle[maxn * maxn];

vector<int> path;

vi getCycleFromPath(int upTo) {
	int i = 0;
	while (path[i] != upTo) {
		++i;
	}
	return vi(path.begin() + i, path.end());
}

bool areNeighboursInCycle(int u, int v) {
	int c = oddCycleIndex[u];
	if (c == -1 || oddCycleIndex[v] != c)
		return false;
	int i = indexInCycle[u], j = indexInCycle[v];
	int len = oddCycle[c].size();
	return (i + 1) % len == j || (j + 1) % len == i;
}

bool dfs1(int v, int anc) {
	assert(visited[v] != -1);
	path.push_back(v);
	forn(i, n) {
		if (i == v || i == anc)
			continue;
		if (b[v][i] % 2 == 0)
			continue;
		if (areNeighboursInCycle(i, v))
			continue;
		if (visited[i] == -1) {
			visited[i] = 1 - visited[v];
			if (dfs1(i, v)) {
				return true;
			}
		} else {
			auto cycle = getCycleFromPath(i);
			if (cycle.size() % 2 == 0) {
				//	cerr << "Cancelling even cycle: " << cycle << "\n";
				forn(i, cycle.size()) {
					int u = cycle[i], v = cycle[(i + 1) % cycle.size()];
					if (i % 2 == 0)
						++b[u][v], ++b[v][u];
					else
						--b[u][v], --b[v][u];
				}
			} else {
				//	cerr << "Found odd cycle: " << cycle << "\n";

				int match = -1;
				for (int v : cycle) {
					if (oddCycleIndex[v] != -1) {
						match = v;
						break;
					}
				}
				if (match == -1) {
					//		cerr << "Assigned index " << oddCycleCount << "\n";
					forn(i, cycle.size()) {
						oddCycleIndex[cycle[i]] = oddCycleCount;
						indexInCycle[cycle[i]] = i;
					}
					oddCycle[oddCycleCount] = cycle;
					++oddCycleCount;
				} else {
					int val = 1;
					int other = oddCycleIndex[match];

					//			cerr << "Merging with idx " << other << ", " << oddCycle[other] << "\n";

					forn(i, cycle.size()) {
						int u = cycle[i], v = cycle[(i + 1) % cycle.size()];
						if (u == match) {
							const auto &otherCycle = oddCycle[other];
							int idx = find(all(otherCycle), match) - otherCycle.begin();
							assert(idx == indexInCycle[match]);
							forn(j, oddCycle[other].size()) {
								int uu = otherCycle[(j + idx) % otherCycle.size()];
								int vv = otherCycle[(j + idx + 1) % otherCycle.size()];
								b[uu][vv] += val;
								b[vv][uu] += val;
								val = -val;
							}
						}
						b[u][v] += val;
						b[v][u] += val;
						val = -val;
					}
					assert(val == 1);

					for (int v : oddCycle[other]) {
						oddCycleIndex[v] = -1;
					}
					oddCycle[other].clear();
				}
			}
			return true;
		}
	}
	path.pop_back();
	return false;
}

void eliminateEvenCycles() {
	forn(i, n) oddCycleIndex[i] = -1;
	while (true) {
		path.clear();
		memset(visited, -1, sizeof visited);
		bool done = false;
		forn(i, n) if (visited[i] == -1) {
			visited[i] = 0;
			if (dfs1(i, -1)) {
				done = true;
				break;
			}
		}
		if (!done)
			break;
	}

	int cnt = 0;
	forn(i, oddCycleCount) { cnt += !oddCycle[i].empty(); }
	assert(cnt % 2 == 0);
	// cerr << "There are " << cnt << " odd cycles\n";
}

namespace NBlos {

const int maxn = 1010;

int pdsu[maxn];
void init(int n = maxn) { forn(i, n) pdsu[i] = i; }
int get(int x) { return pdsu[x] == x ? x : (pdsu[x] = get(pdsu[x])); }
// X's representative is taken.
bool unite(int x, int y) {
	x = get(x);
	y = get(y);
	if (x == y)
		return false;
	pdsu[y] = x;
	return true;
}

int nv;
vi blossomL[maxn], blossomR[maxn];
int connectingEdge[maxn];
int bid[maxn];
int base[maxn];
int p[maxn];
int pe[maxn]; // edge from v to p[v]
int isS[maxn], isT[maxn];
int startCycleId;

struct Edge {
	bool alive = true;
	int u, v;
	bool isAdd;

	Edge() {}
	Edge(int u, int v, bool add) : u(u), v(v), isAdd(add) {}
};

vector<Edge> edges;
// For edge starting from the cycle, keep its original endpoint.
vector<int> originalStart;
vector<int> e[maxn];

vector<int> queue;

void buildInput(int cycle) {
	forn(i, maxn) blossomL[i].clear(), blossomR[i].clear();
	memset(connectingEdge, -1, sizeof connectingEdge);
	memset(p, -1, sizeof p);
	memset(pe, -1, sizeof pe);
	memset(base, -1, sizeof base);
	memset(isS, 0, sizeof isS);
	memset(isT, 0, sizeof isT);
	memset(bid, -1, sizeof bid);

	edges.clear();
	originalStart.clear();
	forn(i, maxn) e[i].clear();
	queue.clear();

	startCycleId = cycle;

	init();

	auto addEdge = [](int i, int j, bool c) {
		if (oddCycleIndex[i] == startCycleId) {
			originalStart.push_back(i);
			i = n;
		} else if (oddCycleIndex[j] == startCycleId) {
			originalStart.push_back(j);
			j = n;
		} else {
			originalStart.push_back(-1);
		}
		e[i].push_back(edges.size());
		e[j].push_back(edges.size());
		edges.emplace_back(i, j, c);
	};

	forn(i, n) forn(j, i) if (b[i][j] % 2 == 0) {
		if (oddCycleIndex[i] == cycle && oddCycleIndex[j] == cycle)
			continue;
		int nAdd = min(2, c[i][j] - b[i][j] / 2);
		int nSub = min(2, b[i][j] / 2);
		forn(k, nAdd) { addEdge(i, j, true); }
		forn(k, nSub) { addEdge(i, j, false); }
	}

	nv = n;

	queue.push_back(nv);
	isS[nv] = isT[nv] = true;

	++nv;
}

int lca(int u, int v) {
	static int used[maxn];
	memset(used, 0, sizeof used);

	while (u != -1)
		used[u] = 1, u = p[u] == -1 ? -1 : get(p[u]);
	while (v != -1 && !used[v])
		v = p[v] == -1 ? -1 : get(p[v]);
	assert(v != -1);
	return v;
}

int getBlossomRepresentative(int v, int b) {
	while (v != -1 && bid[v] != b)
		v = bid[v];
	return v;
}

int getTrueBase(int b) {
	while (b > n)
		b = base[b];
	return b;
}

int getEndpointInBlossom(int b, int edgeId) {
	int r1 = getBlossomRepresentative(b, edges[edgeId].u);
	int r2 = getBlossomRepresentative(b, edges[edgeId].v);
	assert((r1 == -1) != (r2 == -1));
	return max(r1, r2);
}

bool isBlossom(int v) { return v > n; }

vi unrollBlossomToTrueBase(int b, int inId);

vi unrollBlossomUp(int b, int from, int inId, int to) {
	vi res;
	assert(bid[from] == b);
	assert(bid[to] == b);

	while (from != to) {
		if (isBlossom(from)) {
			auto t = unrollBlossomToTrueBase(from, inId);
			res.insert(res.end(), all(t));
		}
		res.push_back(pe[from]);
		inId = pe[from];
		from = p[from];
		while (bid[from] != b)
			from = bid[from];
		assert(bid[from] == b);
	}
	return res;
}

vi unrollBlossomToTrueBase(int b, int inId) {
	//	std::cerr << "Unrolling blossom " << b << " to true base\n";
	auto ein = edges[inId];
	int repr;
	{
		int r1 = getBlossomRepresentative(ein.v, b);
		int r2 = getBlossomRepresentative(ein.u, b);
		assert((r1 == -1) != (r2 == -1));
		repr = max(r1, r2);
	}

	vi res;

	if ((ein.isAdd && isS[repr]) || (!ein.isAdd && isT[repr])) {
		// Can go up.
		res = unrollBlossomUp(b, repr, inId, base[b]);
	} else {
		// Must move all the way round.
		assert(!isBlossom(repr));

		vi *down = &blossomL[b];
		vi *up = &blossomR[b];
		if (!count(all(*down), repr))
			swap(down, up);
		assert(count(all(*down), repr));

		vi unrolledDown = unrollBlossomUp(b, down->front(), connectingEdge[b], repr);
		vi unrolledUp = unrollBlossomUp(b, up->front(), connectingEdge[b], base[b]);
		reverse(all(unrolledDown));

		res = unrolledDown;
		res.push_back(connectingEdge[b]);
		res.insert(res.end(), all(unrolledUp));
	}

	int base = NBlos::base[b];
	if (isBlossom(base)) {
		auto nested = unrollBlossomToTrueBase(base, res.empty() ? inId : res.back());
		res.insert(res.end(), all(nested));
	}

	return res;
}

void addValueToCycle(int v, int val) {
	int idx = indexInCycle[v];
	int c = oddCycleIndex[v];
	// cerr << "Cancelling cycle " << c << " starting with " << v << "\n";
	forn(i, oddCycle[c].size()) {
		int x = oddCycle[c][(i + idx) % oddCycle[c].size()];
		int y = oddCycle[c][(i + idx + 1) % oddCycle[c].size()];
		//	cerr << "Add " << val << " to " << x << " - " << y << "\n";
		assert(b[x][y] % 2 == 1);
		b[x][y] += val;
		b[y][x] += val;
		val = -val;
	}
	for (int x : oddCycle[c])
		oddCycleIndex[x] = -1;
	oddCycle[c].clear();
	//	cerr << "Finished cancelling cycle\n";
}

void unrollPath(int v) {
	// cerr << "Ready to unroll the path from " << v << endl;
	assert(!isBlossom(v));

	int origV = v;

	vi res;
	while (p[v] != -1) {
		res.push_back(pe[v]);
		if (isBlossom(p[v])) {
			auto nested = unrollBlossomToTrueBase(p[v], pe[v]);
			res.insert(res.end(), all(nested));
		}
		v = p[v];
	}
	forn(i, res.size() - 1) { assert(edges[res[i]].isAdd != edges[res[i + 1]].isAdd); }

	v = origV;

	assert(!res.empty());
	addValueToCycle(v, edges[res[0]].isAdd ? -1 : 1);
	forn(i, res.size()) {
		auto e = edges[res[i]];
		int u = e.u ^ e.v ^ v;
		if (u == n)
			u = originalStart[res.back()];
		assert(b[u][v] % 2 == 0);
		// cerr << "Add " << (e.isAdd ? 2 : -2) << " to " << u << " " << v << "\n";
		if (e.isAdd) {
			assert(b[u][v] + 2 <= c[u][v] * 2);
			b[u][v] += 2;
			b[v][u] += 2;
		} else {
			assert(b[u][v] >= 2);
			b[u][v] -= 2;
			b[v][u] -= 2;
		}
		v = u;
	}

	int realV = originalStart[res.back()];
	assert(v == realV);
	addValueToCycle(realV, edges[res.back()].isAdd ? -1 : 1);
}

// Returns whether the alternating walk was found.
// If it was found then both affected cycles are killed.
bool processVertex(int v) {
	// Vertex was shrunk into some blossom.
	if (get(v) != v)
		return false;

	int S, T;
	string mode;
	forn(III, 2) {
		if (III == 0)
			S = 1, T = 0, mode = ", mode = S";
		else
			S = 0, T = 1, mode = ", mode = T";

		if (S && !isS[v])
			continue;
		if (T && !isT[v])
			continue;

		//	cerr << "Processing " << v << mode << "\n";

		// Find blossoms.
		for (int id : e[v]) {
			const auto &edge = edges[id];

			int to;
			if (get(edge.u) == v)
				to = get(edge.v);
			else if (get(edge.v) == v)
				to = get(edge.u);
			else
				assert(false);
			if (to == v)
				continue;

			if (!edge.alive)
				continue;
			if (edge.isAdd != S)
				continue;

			// Blossom is found.
			if ((S && isS[to]) || (T && isT[to])) {
				//		cerr << "Found a blossom edge to " << to << "\n";
				int base = lca(v, to);
				//		cerr << "LCA is " << base << "\n";
				vi curBlossom;

				// from v
				{
					int x = v;
					while (x != base) {
						blossomL[nv].push_back(x);
						curBlossom.push_back(x);
						x = get(p[x]);
					}
					blossomL[nv].push_back(base);
					curBlossom.push_back(base);
				}

				reverse(all(curBlossom));

				// from to
				{
					int x = to;
					while (x != base) {
						blossomR[nv].push_back(x);
						curBlossom.push_back(x);
						x = get(p[x]);
					}
					blossomR[nv].push_back(base);
				}

				connectingEdge[nv] = id;

				// Wrong assertion. Wait till it fails and remove.
				// assert(curBlossom.size() % 2 == 1);

				//		cerr << "Blossom: " << curBlossom << ", new id is " << nv << "\n";
				//		cerr << "Left part: " << blossomL[nv] << "\n";
				//		cerr << "Right part: " << blossomR[nv] << "\n";

				for (int x : curBlossom) {
					unite(nv, x);
					e[nv].insert(e[nv].end(), all(e[x]));
					bid[x] = nv;
				}

				NBlos::base[nv] = base;
				assert(p[nv] == -1);
				p[nv] = p[base];
				pe[nv] = pe[base];

				isS[nv] = isT[nv] = true;
				queue.push_back(nv);
				++nv;
				return false;
			}
		}

		// Grow tree.
		for (int id : e[v]) {
			auto &edge = edges[id];

			int to;
			if (get(edge.u) == v)
				to = get(edge.v);
			else if (get(edge.v) == v)
				to = get(edge.u);
			else
				assert(false);
			if (to == v)
				continue;

			if (!edge.alive)
				continue;
			if (edge.isAdd != S)
				continue;

			if (S) {
				assert(!isS[to]);
				if (isT[to])
					continue;
			} else {
				assert(!isT[to]);
				if (isS[to])
					continue;
			}

			///	cerr << "Growing a tree to " << to << "\n";
			edge.alive = false;

			assert(p[to] == -1);
			p[to] = v;
			pe[to] = id;
			if (S)
				isT[to] = true;
			else
				isS[to] = true;
			queue.push_back(to);

			// Haven't we finished?
			if (to < n && oddCycleIndex[to] != -1 && oddCycleIndex[to] != startCycleId) {
				unrollPath(to);
				return true;
			}
		}
	}

	return false;
}

bool mergeTwoCycles() {
	int c = 0;
	while (c < oddCycleCount && oddCycle[c].empty())
		++c;
	if (c == oddCycleCount) {
		// Nothing to merge.
		return false;
	}

	//	cerr << "Will search for a walk from cycle " << c << "\n";
	buildInput(c);

	forn(i, queue.size()) {
		if (processVertex(queue[i])) {
			return true;
		}
	}

	// No solution. However, in our tests we don't expect this.
	assert(false);
}

} // namespace NBlos

vector<vector<int>> solve(int _n, vector<int> cap, vector<vector<int>> adj) {
	n = _n;
	forn(i, n) f[i] = cap[i];
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			c[i][j] = adj[i][j];
		}
	}
	// cerr << "Finding directed factor\n";
	findDirectedFactor();
	// cerr << "\n***\n\n";

	eliminateEvenCycles();
	// cerr << "\n***\n\n";

	while (NBlos::mergeTwoCycles()) {
		//		cerr << "Two cycles merged\n";
	}

	forn(i, n) forn(j, n) {
		assert(b[i][j] % 2 == 0);
		assert(b[i][j] >= 0);
		assert(b[i][j] / 2 <= c[i][j]);
		assert(b[i][j] == b[j][i]);
	}

	forn(i, n) {
		int x = 0;
		forn(j, n) x += b[i][j];
		assert(x == f[i] * 2);
	}

	vector<vector<int>> ans(n, vector<int>(n));
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			ans[i][j] = b[i][j] / 2;
		}
	}

	return ans;
}
} // namespace SkewSymmetricFlow
