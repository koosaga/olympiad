#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using lint = long long;
using pi = pair<lint, lint>;

struct splaytree{
	struct node{
		node *l, *r, *p;
		int rev;
		node(){ rev = 0; l = r = p = NULL; }
	}*root[8005];
	void init(int n){
		for(int i=1; i<=n; i++) root[i] = new node();
	}
	void push(node *x){
		if(x->rev){
			x->rev = 0;
			swap(x->l, x->r);
			if(x->l) x->l->rev ^= 1;
			if(x->r) x->r->rev ^= 1;
		}
	}
	void pull(node *x){
	}
	void rotate(node *x){
		if(!x->p) return;
		push(x->p);  // if there's lazy stuff
		push(x);
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
		pull(p); // if there's something to pull up
		pull(x);
	}
	void splay(node *x){
		while(x->p){
			node *p = x->p;
			node *g = p->p;
			if(g){
				if((p->l == x) ^ (g->l == p)) rotate(x);
				else rotate(p);
			}
			rotate(x);
		}
	}
	bool check_same(int l, int r){
		splay(root[l]);
		splay(root[r]);
		auto p1 = root[l], p2 = root[r];
		while(p1->p) p1 = p1->p;
		while(p2->p) p2 = p2->p;
		return p1 == p2;
	}

	void link(int s, int e){
		splay(root[s]);
		splay(root[e]);
		push(root[s]); push(root[e]);
		if(root[s]->r) root[s]->rev ^= 1;
		if(root[e]->l) root[e]->rev ^= 1;
		push(root[s]); push(root[e]);
		root[s]->r = root[e];
		root[e]->p = root[s];
		pull(root[s]);
	}

	void cut(int s, int e){
		splay(root[s]);
		auto ptr = root[e];
		while(ptr->p->p) ptr = ptr->p;
		if(ptr == root[s]->r){
			ptr->p = NULL;
			root[s]->r = NULL;
		}
		else{
			ptr->p = NULL;
			root[s]->l = NULL;
		}
		pull(root[s]);
	}
}T[101];

int cnt[101][8005];

void solve(){
	memset(cnt, 0, sizeof(cnt));
	int n, m, c, q;
	scanf("%d %d %d %d",&n,&m,&c,&q);
	if(n == 0) exit(0);
	for(int i=1; i<=c; i++) T[i].init(n);
	vector<tuple<int, int, int>> v;
	for(int i=0; i<m; i++){
		int s, e, x; scanf("%d %d %d",&s,&e,&x);
		T[x].link(s, e);
		v.emplace_back(s, e, x);
		cnt[x][s]++;
		cnt[x][e]++;
	}
	sort(all(v));
	for(int i=0; i<q; i++){
		int s, e, x; scanf("%d %d %d",&s,&e,&x);
		auto l = lower_bound(all(v), make_tuple(s, e, -1));
		if(l == v.end() || get<0>(*l) != s || get<1>(*l) != e){
			printf("No such cable.\n");
		}
		else if(get<2>(*l) == x){
			printf("Already owned.\n");
		}
		else if(cnt[x][s] == 2 || cnt[x][e] == 2){
			printf("Forbidden: monopoly.\n");
		}
		else if(T[x].check_same(s, e)){
			printf("Forbidden: redundant.\n");
		}
		else{
			printf("Sold.\n");
			cnt[get<2>(*l)][s]--;
			cnt[get<2>(*l)][e]--;
			cnt[x][s]++;
			cnt[x][e]++;
			T[get<2>(*l)].cut(s, e);
			*l = make_tuple(s, e, x);
			T[x].link(s, e);
		}
	}
	puts("");
}

int main(){
	while(true){
		solve();
	}
}
