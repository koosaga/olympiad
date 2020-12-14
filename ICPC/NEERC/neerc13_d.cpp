#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using lint = long long;
using pi = pair<lint, lint>;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
int randint(int lb, int ub){ return uniform_int_distribution<int>(lb, ub)(rng); }

struct edge{
	int s, e;
	lint x;
	bool operator>(const edge &e)const{
		return x > e.x;
	}
};

namespace dmst{
	struct node{
		node *l, *r;
		edge val;
		lint lazy;
		void add(lint v){
			val.x += v;
			lazy += v;
		}
		void push(){
			if(l) l->add(lazy);
			if(r) r->add(lazy);
			lazy = 0;
		}
		node(){
			l = r = NULL;
			lazy = 0;
		}
		node(edge e){
			l = r = NULL;
			val = e;
			lazy = 0;
		}
	};

	node* merge(node *x, node *y){
		if(!x) return y;
		if(!y) return x;
		x->push();
		y->push();
		if(x->val.x > y->val.x) swap(x, y);
		if(randint(0, 1)) x->l = merge(x->l, y);
		else x->r = merge(x->r, y);
		return x;
	}
	edge top(node *x){
		return x->val;
	}
	node *pop(node *x){
		x->push();
		return merge(x->l, x->r);
	}

	struct disj{
		vector<int> pa, rk, mx;
		vector<pair<int*, int>> event;
		void init(int n){
			event.clear();
			pa.resize(n + 1);
			rk.resize(n + 1);
			mx.resize(n + 1);
			iota(all(pa), 0);
			iota(all(mx), 0);
			fill(all(rk), 0);
		}
		int time(){ return sz(event); }
		int find(int x){
			return pa[x] == x ? x : find(pa[x]);
		}
		bool uni(int p, int q){
			p = find(p);
			q = find(q);
			if(p == q) return 0;
			if(rk[p] < rk[q]) swap(p, q);
			event.emplace_back(&pa[q], pa[q]);
			event.emplace_back(&mx[p], mx[p]);
			pa[q] = p; 
			mx[p] = max(mx[p], mx[q]);
			if(rk[p] == rk[q]){
				event.emplace_back(&rk[p], rk[p]);
				rk[p]++;
			}
			return 1;
		}
		void rollback(int t){
			while(sz(event) > t){
				*event.back().first = event.back().second;
				event.pop_back();
			}
		}
		int getidx(int x){ return mx[find(x)]; }
	};
	vector<edge> solve(int n, int r, vector<edge> e){
		vector<edge> parent(n);
		vector<node*> gph(n);
		for(auto &i : e){
			gph[i.e] = merge(gph[i.e], new node(i));
		}
		disj dsu1, dsu2;
		dsu1.init(n*2);
		dsu2.init(n*2);
		vector<int> when;
		auto isLoop = [&](edge e){
			return dsu2.find(e.s) == dsu2.find(e.e);
		};
		int auxNode = n;
		for(int x = 0; x < auxNode; x++){
			if(x == r) continue;
			while(isLoop(top(gph[x]))) gph[x] = pop(gph[x]);
			parent[x] = top(gph[x]);
			gph[x] = pop(gph[x]);
			if(!dsu1.uni(x, parent[x].s)){
				vector<int> cycle = {x};
				for(int i = dsu2.getidx(parent[x].s); i != x; i = dsu2.getidx(parent[i].s)){
					cycle.push_back(i);
				}
				node* merged = NULL;
				when.push_back(dsu2.time());
				for(auto &i : cycle){
					dsu2.uni(i, auxNode);
					if(gph[i] != NULL){
						gph[i]->add(-parent[i].x);
						merged = merge(merged, gph[i]);
					}
				}
				gph.push_back(merged);
				parent.resize(auxNode + 1);
				dsu1.uni(x, auxNode);
				auxNode++;
			}
		}
		for(int i = auxNode - 1; i >= n; i--){
			dsu2.rollback(when.back());
			when.pop_back();
			int target = dsu2.getidx(parent[i].e);
			parent[i].x += parent[target].x;
			parent[target] = parent[i];
		}
		parent.resize(n);
		parent[r].x = 0;
		parent[r].s = r;
		return parent;
	}
};

const int MAXN = 55;
int n;
string s[MAXN];

pi cost(string a, string b){
	auto ret = pi(0, -1);
	for(int i=0; i<a.size(); i++){
		int idx = 0;
		for(int j=0; j<b.size(); j++){
			if(i+j >= a.size() || a[i+j] != b[j]) break;
			idx = j+1;
		}
		ret = max(ret, pi(idx, i));
	}
	return ret;
}

int adj[MAXN][MAXN];
int trie[505][26], piv;
vector<int> gph[MAXN];

void dfs(int v, int ptr){
	vector<int> plist = {ptr};
	for(auto &i : s[v]){
		int cur = plist.back();
		if(!trie[cur][i - 'a']){
			trie[cur][i - 'a'] = ++piv;
		}
		plist.push_back(trie[cur][i - 'a']);
	}
	for(auto &j : gph[v]){
		int x = cost(s[v], s[j]).second;
		dfs(j, plist[x]);
	}
}

int resultNum[505];
int resultChr[505];
void dfs(int x){
	for(int i=0; i<26; i++){
		if(trie[x][i]){
			resultNum[trie[x][i]] = x + 1;
			resultChr[trie[x][i]] = i + 'a';
			dfs(trie[x][i]);
		}
	}
}

int main(){
	cin >> n;
	for(int i=1; i<=n; i++) cin >> s[i];
	for(int i=1; i<=n; i++){
		for(int j=1; j<=n; j++) adj[i][j] = cost(s[i], s[j]).first;
	}
	int curmax = -1;
	vector<pi> curset;
	for(int i=1; i<=n; i++){
		int rel[MAXN] = {}, rev[MAXN], cnt = 0;
		rel[i] = 0;
		for(int j=1; j<=n; j++){
			if(i != j) rel[j] = ++cnt;
		}
		for(int j=1; j<=n; j++) rev[rel[j]] = j;
		vector<edge> edges;
		for(int i=1; i<=n; i++){
			for(int j=1; j<=n; j++){
				if(i != j){
					edges.push_back({rel[i], rel[j], -adj[i][j]});
				//	g[rel[j]].push_back({rel[i], -adj[i][j], i * (n+5) + j});
				}
			}
		}
		auto ans = dmst::solve(n, 0, edges);
		int sum = 0;
		vector<pi> curans;
		for(auto &i : ans){
			if(i.e == 0) continue;
			sum -= i.x;
			curans.emplace_back(rev[i.s], rev[i.e]);
		}
		if(curmax < sum){
			curmax = sum;
			curset = curans;
		}
	}
	set<int> s;
	for(int i=1; i<=n; i++) s.insert(i);
	for(auto &[x, y] : curset){
		gph[x].push_back(y);
		s.erase(y);
	}
	dfs(*s.begin(), 0);
	cout << piv + 1 << endl;
	puts("0");
	dfs(0);
	for(int i=1; i<=piv; i++) printf("%d %c\n", resultNum[i], resultChr[i]);
}

