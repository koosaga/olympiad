#define sz(v) ((lint)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using lint = long long;
typedef pair<int, int> pi;
const int MAXL = 18;
const int MAXN = 200005;

struct node{
	node *l, *r, *p;
	int x, y, subSize;
	char mask;
	node(){ 
		l = r = p = NULL; 
		x = y = subSize = 0;
		mask = 0;
	}
	node(int _x, int _y){
		l = r = p = NULL;
		x = _x;
		y = _y;
		subSize = 1;
		mask = 0;
	}
	void clear(int _x, int _y){
		l = r = p = NULL;
		x = _x;
		y = _y;
		subSize = 1;
		mask = 0;
	}

	void push(){

	}
	void pull(){
		subSize = 1;
		mask &= 3;
		mask |= (mask << 2);
		if(l){
			subSize += l->subSize;
			mask |= (l->mask & 12);
		}
		if(r){
			subSize += r->subSize;
			mask |= (r->mask & 12);
		}
	}
	void setLeft(node *p){
		l = p;
		p->p = this;
		pull();
	}
	void setRight(node *p){
		r = p;
		p->p = this;
		pull();
	}
	void rotate(){
		node *x = this;
		if(!x->p) return;
		x->p->push();
		x->push();
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
		p->pull();
		x->pull();
	}
	void splay(){
		node *x = this;
		while(x->p){
			node *p = x->p;
			node *g = p->p;
			if(g){
				if((p->l == x) ^ (g->l == p)) x->rotate();
				else p->rotate();
			}
			x->rotate();
		}
	}
	node* prev(){
		splay();
		if(!l) return NULL;
		auto prv = l;
		while(prv->r) prv = prv->r;
		prv->splay();
		return prv;
	}
	node* next(){
		splay();
		if(!r) return NULL;
		auto nxt = r;
		while(nxt->l) nxt = nxt->l;
		nxt->splay();
		return nxt;
	}
	void inorder(){
		if(l) l->inorder();
		if(l) assert(l->p == this);
		printf("[(%d, %d)]", x, y);
		if(r) r->inorder();
		if(r) assert(r->p == this);
	}
};

namespace HDLT{ // does not support duplicate edges
	struct ETT{
		set<int> gph[MAXN], insec[MAXN];
		map<pi, node*> mp;
		queue<node*> que;
		void init(int n){
		}
		node* vertexNode(int v){
			auto p = mp.lower_bound(pi(v, -1));
			if(p == mp.end() || p->first.first != v) return NULL;
			return p->second;
		}
		void charge(int v){
			int new_mask = (sz(gph[v]) > 0) * 2 + (sz(insec[v]) > 0);
			auto p = vertexNode(v);
			if(p){
				p->splay();
				p->mask = new_mask;
				p->pull();
			}
		}
		bool gph_find(int s, int e){
			return gph[s].find(e) != gph[s].end();
		}
		void gph_add(int s, int e){
			gph[s].insert(e);
			gph[e].insert(s);
			charge(s);
			charge(e);
		}
		void gph_del(int s, int e){
			gph[s].erase(e);
			gph[e].erase(s);
			charge(s);
			charge(e);
		}
		bool insec_find(int s, int e){
			return insec[s].find(e) != insec[s].end();
		}
		void insec_add(int s, int e){
			insec[s].insert(e);
			insec[e].insert(s);
			charge(s);
			charge(e);
		}
		void insec_del(int s, int e){
			insec[s].erase(e);
			insec[e].erase(s);
			charge(s);
			charge(e);
		}
		node* get_root(node *p){
			p->splay();
			while(p->l) p = p->l;
			p->splay();
			return p;
		}
		void reroot(node *p){
			p->splay();
			if(!p->l) return;
			auto pos = p->l;
			pos->p = NULL; p->l = NULL; p->pull();
			while(pos->l) pos = pos->l;
			pos->splay();
			pos->setLeft(p);
			p->splay();
		}
		void reroot(int x){
			node *p = vertexNode(x);
			if(!p) return;
			reroot(p);
		}
		void add_edge(pi p){
			int x = p.first, y = p.second;
			node *up, *dn;
			reroot(x);
			reroot(y);
			auto px = vertexNode(x);
			auto py = vertexNode(y);
			if(px) px->splay();
			if(py) py->splay();
			if(px){
				px->mask = 0; px->pull();
			}
			if(py){
				py->mask = 0; py->pull();
			}
			while(sz(que) < 2) que.push(new node(69, 420));
			up = mp[pi(y, x)] = que.front(); que.pop();
			dn = mp[pi(x, y)] = que.front(); que.pop();
			up->clear(y, x);
			dn->clear(x, y);

			if(!px && !py){
				dn->setRight(up);
			}
			else if(px && !py){
				dn->setRight(up);
				px->splay(); 
				px->setLeft(dn);
			}
			else if(!px && py){
				up->setRight(dn);
				py->splay();
				py->setLeft(up);
			}
			else{
				py->splay();
				up->setLeft(py);
				dn->setRight(up);
				px->splay(); px->setLeft(dn);
			}
			charge(x);
			charge(y);
		}
		void remove_edge(pi p){
			int x = p.first, y = p.second;
			node *up = mp[pi(y, x)];
			node *dn = mp[pi(x, y)]; 
			que.push(dn);
			que.push(up);
			mp.erase(pi(x, y));
			mp.erase(pi(y, x));

			reroot(dn); 
			dn->r->p = NULL;
			up->splay();
			if(up->l) up->l->p = NULL;
			if(up->r) up->r->p = NULL;
			charge(x);
			charge(y);
		}
		bool has_edge(int x, int y){
			return mp.find(pi(x, y)) != mp.end();
		}
		bool has_path(int x, int y){
			if(x == y) return 1;
			auto p1 = vertexNode(x);
			auto p2 = vertexNode(y);
			if(!p1 || !p2) return 0;
			return get_root(p1) == get_root(p2);
		}
		int get_size(int x){
			auto p = vertexNode(x);
			if(p == NULL) return 0;
			p->splay();
			return p->subSize;
		}

		void deal_ins(node *p, vector<pi> &toAdd){
			int idx = p->x;
			auto w = insec[idx];
			for(auto &v : w){
				toAdd.emplace_back(idx, v);
				insec_del(idx, v);
			}
		}
		
		void deal_gph(node *p, vector<pi> &toAdd){
			int idx = p->x;
			while(sz(gph[idx])){
				auto v = *gph[idx].begin();
				gph_del(idx, v);
				if(has_path(idx, v)){
					toAdd.emplace_back(idx, v);
				}
				else{
					throw pi(idx, v);
				}
			}
		}

		void gogogo1(int x, vector<pi> &ret){
			reroot(x);
			auto p = vertexNode(x);
			if(!p) return;
			p->splay();
			while(p->mask & 4){
				while(true){
					if(p->mask & 1) break;
					else if(p->l && (p->l->mask & 4)) p = p->l;
					else p = p->r;
				}
				p->splay();
				deal_ins(p, ret);
				p->splay();
				p->mask &= ~1;
				p->pull();
			};
		}

		pi gogogo2(int x, vector<pi> &ret){
			reroot(x);
			auto p = vertexNode(x);
			if(!p){
				int idx = x;
				while(sz(gph[idx])){
					auto v = *gph[idx].begin();
					gph_del(idx, v);
					return pi(idx, v);
				}
				return pi(-1, -1);
			}
			p->splay();
			try{
				while(p->mask & 8){
					while(true){
						if(p->mask & 2) break;
						else if(p->l && (p->l->mask & 8)) p = p->l;
						else p = p->r;
					}
					p->splay();
					deal_gph(p, ret);
					p->splay();
					p->mask &= ~2;
					p->pull();
				};
			}catch(pi v){
				return v;
			}
			return pi(-1, -1);
		}
	}tree[MAXL];

	int lvl, n;

	void init(int _n){
		n = _n;
		while((2 << lvl) < n) lvl++; 
		for(int i=0; i<=lvl; i++) tree[i].init(n);
	}

	int level(int s, int e){
		for(int i=lvl; i>=0; i--){
			if(tree[i].gph_find(s, e) || tree[i].insec_find(s, e)) return i;
		}
		assert(0);
	}

	bool add_edge(int s, int e, int l = lvl){ 
		if(s == e) return 0;
		if(s > e) swap(s, e);
		int ret = 0;
		if(!tree[l].has_path(s, e)){
			tree[l].add_edge(pi(s, e));
			tree[l].insec_add(s, e);
			ret = 1;
		}
		else{
			tree[l].gph_add(s, e);
		}
		return ret;
	}
	bool del_edge(int s, int e){
		if(s == e) return 0;
		if(s > e) swap(s, e);
		int l = level(s, e);
		if(!tree[lvl].has_edge(s, e)){
			tree[l].gph_del(s, e);
			return 0;
		}
		tree[l].insec_del(s, e);
		for(int j=l; j<=lvl; j++){
			tree[j].remove_edge(pi(s, e));
		}
		for(int j=l; j<=lvl; j++){
			int szs = tree[j].get_size(s);
			int sze = tree[j].get_size(e);
			int prom = (szs <= sze ? s : e); // which side to kill

			vector<pi> promote;
			tree[j].gogogo1(prom, promote);
			pi found_edge = tree[j].gogogo2(prom, promote);

			for(auto &[u, v] : promote){
				add_edge(u, v, j - 1);
			}

			if(~found_edge.first){
				add_edge(found_edge.first, found_edge.second, j);
				for(int k = j+1; k <= lvl; k++){
					tree[k].add_edge(found_edge);
				}
				return 0;
			}
		}
		return 1;
	}
	bool is_conn(int s, int e){
		return tree[lvl].has_path(s, e);
	}
} // orz
