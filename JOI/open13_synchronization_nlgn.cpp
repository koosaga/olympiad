#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> pi;
const int MAXN = 200005;
typedef long long lint;
 
struct lct{
	struct node{
		node *p, *l, *r, *pp;
		int idx;
		node(int _idx){
			p = l = r = pp = NULL;
			idx = _idx;
		}
	}*n[MAXN];
	void init(int v){
		for(int i=1; i<=v; i++) n[i] = new node(i);
	}
	void rotate(node *x){
		if(!x->p) return;
		node *p = x->p;
		bool is_left = (p->l == x);
		node *b = (is_left ? x->r : x->l);
		x->p = p->p;
		if(x->p && x->p->l == p) x->p->l = x;
		if(x->p && x->p->r == p) x->p->r = x;
		if(is_left){
			if(b) b->p = p;
			p->l = b;
			p->p = x;
			x->r = p;
		}
		else{
			if(b) b->p = p;
			p->r = b;
			p->p = x;
			x->l = p;
		}
		if(p->pp){
			x->pp = p->pp;
			p->pp = NULL;
		}
	}
	void splay(node *x){
		while(x->p){
			node *p = x->p;
			node *g = p->p;
			if(g){
				if((p->l == g) ^ (g->l == p)) rotate(p);
				else rotate(x);
			}
			rotate(x);
		}
	}
	void access(node *x){
		splay(x);
		if(x->r){
			x->r->p = NULL;
			x->r->pp = x;
			x->r = NULL;
		}
		while(x->pp){
			node *nxt = x->pp;
			splay(nxt);
			if(nxt->r){
				nxt->r->p = NULL;
				nxt->r->pp = nxt;
			}
			nxt->r = x;
			x->p = nxt;
			x->pp = NULL;
			splay(x);
		}
	}
	void link(int par, int son){
		node *v = n[par];
		node *w = n[son];
		access(v);
		access(w);
		assert(w->l == NULL);
		v->r = w;
		w->p = v;
	}
	void cut(int v){
		node *x = n[v];
		access(x);
		if(x->l){
			x->l->p = NULL;
			x->l = NULL;
		}
	}
	int root(int v){
		access(n[v]);
		node *p = n[v];
		while(p->l) p = p->l;
		access(p);
		return p->idx;
	}
}lct;
 
 
vector<int> gph[MAXN];
int par[MAXN], s[MAXN], e[MAXN];
 
void dfs(int x, int p){
	par[x] = p;
	for(auto &i : gph[x]){
		if(i == p) continue;
		dfs(i, x);
	}
}
 
int chk[MAXN], las[MAXN], cnt[MAXN];
 
int main(){
	int n, m, q;
	scanf("%d %d %d",&n,&m,&q);
	lct.init(n);
	for(int i=1; i<n; i++){
		scanf("%d %d",&s[i],&e[i]);
		gph[s[i]].push_back(e[i]);
		gph[e[i]].push_back(s[i]);
	}
	dfs(1, -1);
	for(int i=1; i<n; i++) if(par[s[i]] == e[i]) swap(s[i], e[i]);
	fill(cnt + 1, cnt + n + 1, 1);
	for(int i=0; i<m; i++){
		int v;
		scanf("%d",&v);
		if(!chk[v]){
			int k = cnt[lct.root(s[v])] + cnt[lct.root(e[v])] - las[v];
			lct.link(s[v], e[v]);
			cnt[lct.root(s[v])] = k;
		}
		else{
			las[v] = cnt[lct.root(s[v])];
			lct.cut(e[v]);
			cnt[lct.root(e[v])] = las[v];
		}
		chk[v] ^= 1;
	}
	while(q--){
		int t;
		scanf("%d",&t);
		printf("%d\n", cnt[lct.root(t)]);
	}
}
