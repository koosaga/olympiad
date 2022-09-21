using P3 = array<lint,3>; 
P3& operator+=(P3& l, const P3& r) { for(int i = 0; i < 3; i++) l[i] += r[i]; 
	return l; }
P3& operator-=(P3& l, const P3& r) { for(int i = 0; i < 3; i++) l[i] -= r[i]; 
	return l; }
P3& operator*=(P3& l, const lint& r) { for(int i = 0; i < 3; i++) l[i] *= r; 
	return l; }
P3& operator/=(P3& l, const lint& r) { for(int i = 0; i < 3; i++) l[i] /= r; 
	return l; }
P3 operator-(P3 l) { l *= -1; return l; }
P3 operator+(P3 l, const P3& r) { return l += r; }
P3 operator-(P3 l, const P3& r) { return l -= r; }
P3 operator*(P3 l, const lint& r) { return l *= r; }
P3 operator/(P3 l, const lint& r) { return l /= r; }

lint dot(const P3& a, const P3& b) { 
	lint sum = 0; for(int i = 0; i < 3; i++) sum += a[i]*b[i]; 
	return sum; }
P3 cross(const P3& a, const P3& b) {
	return {a[1]*b[2]-a[2]*b[1],a[2]*b[0]-a[0]*b[2],
			a[0]*b[1]-a[1]*b[0]}; }
P3 cross(const P3& a, const P3& b, const P3& c) {
	return cross(b-a,c-a); }

bool isMult(const P3& a, const P3& b) { // for long longs
	P3 c = cross(a,b); for(int i = 0; i < sz(c); i++) if (c[i] != 0) return 0; 
	return 1; }
bool collinear(const P3& a, const P3& b, const P3& c) { 
	return isMult(b-a,c-a); }

lint DC(const P3&a,const P3&b,const P3&c,const P3&p) { 
	return dot(cross(a,b,c),p-a); }
bool coplanar(const P3&a,const P3&b,const P3&c,const P3&p) { 
	return DC(a,b,c,p) == 0; }

lint above(const P3&a,const P3&b,const P3&c,const P3&p) {
	return DC(a,b,c,p) > 0;
} // is p strictly above plane

void prep(vector<P3>& p) {
	shuffle(all(p), mt19937(0x14004));
	int dim = 1;
	for(int i = 1; i < sz(p); i++){
		if (dim == 1) {
			if (p[0] != p[i]) swap(p[1],p[i]), ++dim;
		} else if (dim == 2) {
			if (!collinear(p[0],p[1],p[i]))
				swap(p[2],p[i]), ++dim;
		} else if (dim == 3) {
			if (!coplanar(p[0],p[1],p[2],p[i]))
				swap(p[3],p[i]), ++dim;
		}
	}
		assert(dim == 4);
}

using F = array<int,3>; // face
vector<F> hull3dFast(vector<P3>& p) {
	prep(p);
	int N = sz(p); vector<F> hull;
	vector<int> active; vector<vector<int>> rvis; vector<array<pi,3>> other;
	// whether face is active
	// points visible from each face
	// other face adjacent to each edge of face
	vector<vector<int>> vis(N); // faces visible from each point
	auto ad = [&](int a, int b, int c) {
		hull.push_back({a,b,c}); active.push_back(1); rvis.emplace_back(); other.emplace_back(); 
	};
	auto ae = [&](int a, int b) { vis[b].push_back(a), rvis[a].push_back(b); };
	auto abv = [&](int a, int b) {
		F f=hull[a]; return above(p[f[0]],p[f[1]],p[f[2]],p[b]);};
	auto edge = [&](pi e) -> pi {
		return {hull[e.first][e.second],hull[e.first][(e.second+1)%3]}; };
	auto glue = [&](pi a, pi b) { // link two faces by an edge
		pi x = edge(a); assert(edge(b) == pi(x.second,x.first));
		other[a.first][a.second] = b;
		other[b.first][b.second] = a;
	}; // ensure face 0 is removed when i=3
	ad(0,1,2), ad(0,2,1); 
	if (abv(1,3)) swap(p[1],p[2]);

	for(int i = 0; i < 3; i++) glue({0,i},{1,2-i});
	for(int i = 3; i < N; i++) ae(abv(1,i),i); // coplanar points go in rvis[0]
	vector<int> label(N,-1);
	for(int i = 3; i < N; i++){ // incremental construction
		vector<int> rem; 
		for(auto &t : vis[i]) if (active[t]){
			active[t]=0, rem.push_back(t);
		}
		if (!sz(rem)) continue; // hull unchanged
		int st = -1;
		for(auto &r : rem){
			for(int j = 0; j < 3; j++){
				int o = other[r][j].first;
				if (active[o]) { // create new face!
					int a,b; tie(a,b) = edge({r,j}); ad(a,b,i); st = a;
					int cur = sz(rvis)-1; label[a] = cur;
					vector<int> tmp; set_union(all(rvis[r]),all(rvis[o]),
							back_inserter(tmp));
					// merge sorted vectors ignoring duplicates
					for(auto &x : tmp) if (abv(cur,x)) ae(cur,x);
					/// if no rounding errors then guaranteed that only x>i matters
					glue({cur,0},other[r][j]); // glue old w/ new face
				}
			}
		}
		for (int x = st, y; ; x = y) { // glue new faces together
			int X = label[x]; glue({X,1},{label[y=hull[X][1]],2});
			if (y == st) break;
		}
	}
	vector<F> ans; 
	for(int i = 0; i < sz(hull); i++){
		if(active[i]) ans.push_back(hull[i]);
	}
	return ans;
}
