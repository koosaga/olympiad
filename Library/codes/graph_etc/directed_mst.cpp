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