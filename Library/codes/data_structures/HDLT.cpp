struct node : public top_tree_node_base<node> {
	bool lazy_flip_path = false;
	int idx;
	char hack = 0; // (str, sbk, tr, bk, sz)
	int nodes = 0;
	void do_flip_path() {
		assert(is_path);
		std::swap(c[0], c[1]);
		lazy_flip_path ^= 1;
	}

	void downdate() {
		if (lazy_flip_path) {
			assert(is_path);
			if (!is_vert) {
				c[0]->do_flip_path();
				c[1]->do_flip_path();
			}
			lazy_flip_path = false;
		}
	}

	// NOTE: You may assume downdate() has been called on the current node, but
	// it may not have been called on the children! In particular, be careful
	// when accessing grandchildren information.
	void update() {
		nodes = (hack >> 4);
		hack &= ~3;
		hack |= ((hack & 12) >> 2);
		for (int i = 0; i < 3; i++) {
			if (c[i]) {
				nodes += c[i]->nodes;
				hack |= (c[i]->hack & 3);
			}
		}
	}
	void gather_tree(vector<int> &v) {
		if (hack & 4)
			v.push_back(idx);
		for (int i = 0; i < 3; i++) {
			if (c[i] && (c[i]->hack & 1))
				c[i]->gather_tree(v);
		}
	}
	int find_back() {
		if (hack & 8)
			return idx;
		for (int i = 0; i < 3; i++) {
			if (c[i] && (c[i]->hack & 2))
				return c[i]->find_back();
		}
		assert(0);
	}
};

// Online Dynamic Connectivity (no duplicate edges)
namespace HDLT {
int n;
vector<vector<node *>> ptr;
vector<vector<set<int>>> gph_tree, gph_back;
vector<map<pi, node *>> mp;
void make_new_level() {
	vector<node *> v(n);
	for (int j = 0; j < n; j++) {
		v[j] = new node();
		v[j]->is_path = v[j]->is_vert = true;
		v[j]->hack = 16;
		v[j]->idx = j;
		v[j]->update_all();
	}
	ptr.push_back(v);
	gph_tree.push_back(vector<set<int>>(n));
	gph_back.push_back(vector<set<int>>(n));
	mp.push_back(map<pi, node *>());
}
void init(int _n) {
	n = _n;
	make_new_level();
}
bool is_conn(int i, int u, int v) {
	if (u == v)
		return true;
	ptr[i][u]->make_root();
	ptr[i][v]->make_root();
	return ptr[i][u]->p != NULL;
}
void upd(int i, int u) {
	ptr[i][u]->make_root();
	ptr[i][u]->hack = 16;
	if (sz(gph_tree[i][u]))
		ptr[i][u]->hack |= 4;
	if (sz(gph_back[i][u]))
		ptr[i][u]->hack |= 8;
	ptr[i][u]->update_all();
}

void link_tree(int l, int u, int v) {
	if (u > v)
		swap(u, v);
	node *e = new node();
	link(e, ptr[l][u], ptr[l][v]);
	mp[l][pi{u, v}] = e;
}
void add_edge(int u, int v) {
	if (u > v)
		swap(u, v);
	//	cout << "add edge " << u << " " << v << endl;
	if (is_conn(0, u, v)) {
		//	cout << "add as back " << endl;
		gph_back[0][u].insert(v);
		gph_back[0][v].insert(u);
		upd(0, u);
		upd(0, v);
		return;
	} else {
		gph_tree[0][u].insert(v);
		gph_tree[0][v].insert(u);
		upd(0, u);
		upd(0, v);
		link_tree(0, u, v);
	}
}
void del_tree_edge(int l, int u, int v) {
	gph_tree[l][u].erase(v);
	gph_tree[l][v].erase(u);
	for (int i = 0; i <= l; i++) {
		node *e = mp[i][pi{u, v}];
		mp[i].erase(pi{u, v});
		upd(i, u);
		upd(i, v);
		cut(e);
	}
	for (int i = l; i >= 0; i--) {
		ptr[i][u]->make_root();
		ptr[i][v]->make_root();
		if (ptr[i][u]->nodes > ptr[i][v]->nodes)
			swap(u, v);
		if (ptr[i][u]->hack & 1) {
			vector<int> vect;
			ptr[i][u]->gather_tree(vect);
			if (i + 1 >= sz(ptr))
				make_new_level();
			for (auto &v : vect) {
				for (auto &w : gph_tree[i][v]) {
					gph_tree[i][w].erase(v);
					gph_tree[i + 1][w].insert(v);
					gph_tree[i + 1][v].insert(w);
					link_tree(i + 1, v, w);
					upd(i + 1, v);
					upd(i + 1, w);
				}
				gph_tree[i][v].clear();
			}
			for (auto &v : vect)
				upd(i, v);
			ptr[i][u]->make_root();
		}
		while (ptr[i][u]->hack & 2) {
			auto u1 = ptr[i][u]->find_back();
			ptr[i][u1]->make_root();
			int v1 = *gph_back[i][u1].begin();
			//	cout << "found back " << u1 << " " << v1 << endl;
			if (!is_conn(i, u1, v1)) {
				// if found something, add to all 0 ... i and halt
				//	cout << "found rep " << u1 << " " << v1 << endl;
				for (int j = 0; j <= i; j++) {
					link_tree(j, u1, v1);
				}
				gph_tree[i][u1].insert(v1);
				gph_tree[i][v1].insert(u1);
				gph_back[i][u1].erase(v1);
				gph_back[i][v1].erase(u1);
				upd(i, u1);
				upd(i, v1);
				return;
			} else {
				//	cout << "bye " << endl;
				gph_back[i][u1].erase(v1);
				gph_back[i][v1].erase(u1);
				gph_back[i + 1][u1].insert(v1);
				gph_back[i + 1][v1].insert(u1);
				upd(i, u1);
				upd(i, v1);
				if (i + 1 >= sz(ptr))
					make_new_level();
				upd(i + 1, u1);
				upd(i + 1, v1);
			}
			ptr[i][u]->make_root();
		}
	}
}
void del_edge(int u, int v) {
	if (u > v)
		swap(u, v);
	for (int i = sz(ptr) - 1; i >= 0; i--) {
		if (mp[i].count(pi{u, v})) {
			del_tree_edge(i, u, v);
			return;
		}
	}
	// then it's not a tree edge
	for (int i = 0; i < sz(ptr); i++) {
		if (gph_back[i][u].count(v)) {
			gph_back[i][u].erase(v);
			gph_back[i][v].erase(u);
			upd(i, u);
			upd(i, v);
		}
	}
}
}; // namespace HDLT
