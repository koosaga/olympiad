/**
 * Description: Incremental 3D convex hull where not all points 
 	* are coplanar. Normals to returned faces point outwards. 
 	* If coordinates are ints at most $B$ then \texttt{T} 
 	* should be large enough to support ints on the order 
 	* of $B^3$. Changes order of points.
 * Time: O(N^2), O(N\log N)
 * Source: 
 	* KACTL
 	* https://codeforces.com/blog/entry/73366?#comment-575862 (mango_lassi)
 	* https://codeforces.com/blog/entry/81768 (Monogon)
 	* https://people.csail.mit.edu/indyk/6.838-old/handouts/lec10.pdf (presentation)
 	* https://www2.cs.duke.edu/courses/spring07/cps296.2/papers/clarkson-shor.pdf
 * Verification: https://www.spoj.com/problems/CH3D/
 	* https://code.google.com/codejam/contest/6314486/dashboard#s=p3
 */

using T = ll;
const T EPS = 0; // adjust as needed
using P = pair<T,T>; using vP = V<P>; using Line = pair<P,P>;
int sgn(T a) { return (a>EPS)-(a<-EPS); }
T sq(T a) { return a*a; }

bool close(const P& a, const P& b) { 
	return sgn(a.f-b.f) == 0 && sgn(a.s-b.s) == 0; } 
T norm(const P& p) { return sq(p.f)+sq(p.s); }
T abs(const P& p) { return sqrt(norm(p)); }
T arg(const P& p) { return atan2(p.s,p.f); }
P conj(const P& p) { return P(p.f,-p.s); }
P perp(const P& p) { return P(-p.s,p.f); }
P dir(T ang) { return P(cos(ang),sin(ang)); }

P operator-(const P& l) { return P(-l.f,-l.s); }
P operator+(const P& l, const P& r) { 
	return P(l.f+r.f,l.s+r.s); }
P operator-(const P& l, const P& r) { 
	return P(l.f-r.f,l.s-r.s); }
P operator*(const P& l, const T& r) { 
	return P(l.f*r,l.s*r); }
P operator*(const T& l, const P& r) { return r*l; }
P operator/(const P& l, const T& r) { 
	return P(l.f/r,l.s/r); }
P operator*(const P& l, const P& r) { 
	return P(l.f*r.f-l.s*r.s,l.s*r.f+l.f*r.s); }
P operator/(const P& l, const P& r) { 
	return l*conj(r)/norm(r); }
P& operator+=(P& l, const P& r) { return l = l+r; }
P& operator-=(P& l, const P& r) { return l = l-r; }
P& operator*=(P& l, const T& r) { return l = l*r; }
P& operator/=(P& l, const T& r) { return l = l/r; }
P& operator*=(P& l, const P& r) { return l = l*r; }
P& operator/=(P& l, const P& r) { return l = l/r; }

P unit(const P& p) { return p/abs(p); }
T dot(const P& a, const P& b) { return a.f*b.f+a.s*b.s; }
T dot(const P& p, const P& a, const P& b) { return dot(a-p,b-p); }
T cross(const P& a, const P& b) { return a.f*b.s-a.s*b.f; }
T cross(const P& p, const P& a, const P& b) {
	return cross(a-p,b-p); }
P reflect(const P& p, const Line& l) {
	P a = l.f, d = l.s-l.f;
	return a+conj((p-a)/d)*d; }
P foot(const P& p, const Line& l) {
	return (p+reflect(p,l))/(T)2; }
bool onSeg(const P& p, const Line& l) {
	return sgn(cross(l.f,l.s,p)) == 0 && sgn(dot(p,l.f,l.s)) <= 0; }


using P3 = AR<T,3>; using Tri = AR<P3,3>; using vP3 = V<P3>;
T norm(const P3& x) { 
	T sum = 0; F0R(i,3) sum += sq(x[i]);
	return sum; }
T abs(const P3& x) { return sqrt(norm(x)); }

P3& operator+=(P3& l, const P3& r) { F0R(i,3) l[i] += r[i]; 
	return l; }
P3& operator-=(P3& l, const P3& r) { F0R(i,3) l[i] -= r[i]; 
	return l; }
P3& operator*=(P3& l, const T& r) { F0R(i,3) l[i] *= r; 
	return l; }
P3& operator/=(P3& l, const T& r) { F0R(i,3) l[i] /= r; 
	return l; }
P3 operator-(P3 l) { l *= -1; return l; }
P3 operator+(P3 l, const P3& r) { return l += r; }
P3 operator-(P3 l, const P3& r) { return l -= r; }
P3 operator*(P3 l, const T& r) { return l *= r; }
P3 operator*(const T& r, const P3& l) { return l*r; }
P3 operator/(P3 l, const T& r) { return l /= r; }

P3 unit(const P3& x) { return x/abs(x); }
T dot(const P3& a, const P3& b) { 
	T sum = 0; F0R(i,3) sum += a[i]*b[i]; 
	return sum; }
P3 cross(const P3& a, const P3& b) {
	return {a[1]*b[2]-a[2]*b[1],a[2]*b[0]-a[0]*b[2],
			a[0]*b[1]-a[1]*b[0]}; }
P3 cross(const P3& a, const P3& b, const P3& c) {
	return cross(b-a,c-a); }
P3 perp(const P3& a, const P3& b, const P3& c) {
	return unit(cross(a,b,c)); }

bool isMult(const P3& a, const P3& b) { // for long longs
	P3 c = cross(a,b); F0R(i,sz(c)) if (c[i] != 0) return 0; 
	return 1; }
bool collinear(const P3& a, const P3& b, const P3& c) { 
	return isMult(b-a,c-a); }

T DC(const P3&a,const P3&b,const P3&c,const P3&p) { 
	return dot(cross(a,b,c),p-a); }
bool coplanar(const P3&a,const P3&b,const P3&c,const P3&p) { 
	return DC(a,b,c,p) == 0; }
bool op(const P3& a, const P3& b) { 
	int ind = 0; // going in opposite directions?
	FOR(i,1,3) if (std::abs(a[i]*b[i])>std::abs(a[ind]*b[ind])) 
		ind = i;
	return a[ind]*b[ind] < 0;
}
// coplanar points, b0 and b1 on opposite sides of a0-a1?
bool opSide(const P3&a,const P3&b,const P3&c,const P3&d) { 
	return op(cross(a,b,c),cross(a,b,d)); }
// coplanar points, is a in Triangle b
bool inTri(const P3& a, const Tri& b) { 
	F0R(i,3)if(opSide(b[i],b[(i+1)%3],b[(i+2)%3],a))return 0;
	return 1; }

// point-seg dist
T psDist(const P3&p,const P3&a,const P3&b) { 
	if (dot(a-p,a-b) <= 0) return abs(a-p);
	if (dot(b-p,b-a) <= 0) return abs(b-p);
	return abs(cross(p,a,b))/abs(a-b);
}
// projection onto line
P3 foot(const P3& p, const P3& a, const P3& b) { 
	P3 d = unit(b-a); return a+dot(p-a,d)*d; }
// rotate p about axis
P3 rotAxis(const P3& p, const P3& a, const P3& b, T theta) {
	P3 dz = unit(b-a), f = foot(p,a,b); 
	P3 dx = p-f, dy = cross(dz,dx);
	return f+cos(theta)*dx+sin(theta)*dy;
}
// projection onto plane
P3 foot(const P3& a, const Tri& b) {
	P3 c = perp(b[0],b[1],b[2]);
	return a-c*(dot(a,c)-dot(b[0],c)); }
// line-plane intersection
P3 lpIntersect(const P3&a0,const P3&a1,const Tri&b) { 
	P3 c = unit(cross(b[2]-b[0],b[1]-b[0]));
	T x = dot(a0,c)-dot(b[0],c), y = dot(a1,c)-dot(b[0],c);
	return (y*a0-x*a1)/(y-x);
}


using T = ll;
T above(const P3&a,const P3&b,const P3&c,const P3&p) { 
	return DC(a,b,c,p) > 0; } // is p strictly above plane
void prep(vP3& p) { // rearrange points such that
	shuffle(all(p),rng); // first four are not coplanar
	int dim = 1; 
	FOR(i,1,sz(p)) 
		if (dim == 1) {
			if (p[0] != p[i]) swap(p[1],p[i]), ++dim;
		} else if (dim == 2) {
			if (!collinear(p[0],p[1],p[i])) 
				swap(p[2],p[i]), ++dim;
		} else if (dim == 3) {
			if (!coplanar(p[0],p[1],p[2],p[i]))
				swap(p[3],p[i]), ++dim;
		}
	assert(dim == 4);
}

using F = AR<int,3>; // face
V<F> hull3d(vP3& p) {
	// s.t. first four points form tetra
	prep(p); int N = sz(p); V<F> hull; // triangle for each face
	auto ad = [&](int a, int b, int c) { hull.pb({a,b,c}); }; 
	// +new face to hull
	ad(0,1,2), ad(0,2,1); // initialize hull as first 3 points
	V<vb> in(N,vb(N)); // is zero before each iteration
	FOR(i,3,N) { // incremental construction
		V<F> def, HULL; swap(hull,HULL); 
		// HULL now contains old hull
		auto ins = [&](int a, int b, int c) {
			if (in[b][a]) in[b][a] = 0; // kill reverse face
			else in[a][b] = 1, ad(a,b,c);
		};
		each(f,HULL) {
			if (above(p[f[0]],p[f[1]],p[f[2]],p[i])) 
				F0R(j,3) ins(f[j],f[(j+1)%3],i); 
				// recalc all faces s.t. point is above face
			else def.pb(f); 
		}
		each(t,hull) if (in[t[0]][t[1]]) // edge exposed, 
			in[t[0]][t[1]] = 0, def.pb(t); // add a new face
		swap(hull,def);
	}
	return hull;
}
V<F> hull3dFast(vP3& p) {
	prep(p); int N = sz(p); V<F> hull; 
	vb active; V<vi> rvis; V<AR<pi,3>> other;
	// whether face is active
	// points visible from each face
	// other face adjacent to each edge of face
	V<vi> vis(N); // faces visible from each point
	auto ad = [&](int a, int b, int c) { 
		hull.pb({a,b,c}); active.pb(1); rvis.eb(); other.eb(); };
	auto ae = [&](int a, int b) { vis[b].pb(a), rvis[a].pb(b); };
	auto abv = [&](int a, int b) {
		F f=hull[a]; return above(p[f[0]],p[f[1]],p[f[2]],p[b]);};
	auto edge = [&](pi e) -> pi { 
		return {hull[e.f][e.s],hull[e.f][(e.s+1)%3]}; };
	auto glue = [&](pi a, pi b) { // link two faces by an edge
		pi x = edge(a); assert(edge(b) == mp(x.s,x.f));
		other[a.f][a.s] = b, other[b.f][b.s] = a;
	}; // ensure face 0 is removed when i=3
	ad(0,1,2), ad(0,2,1); if (abv(1,3)) swap(p[1],p[2]); 
	F0R(i,3) glue({0,i},{1,2-i});
	FOR(i,3,N) ae(abv(1,i),i); // coplanar points go in rvis[0]
	vi label(N,-1);
	FOR(i,3,N) { // incremental construction
		vi rem; each(t,vis[i]) if (active[t]) active[t]=0, rem.pb(t);
		if (!sz(rem)) continue; // hull unchanged
		int st = -1; 
		each(r,rem) F0R(j,3) {
			int o = other[r][j].f;
			if (active[o]) { // create new face!
				int a,b; tie(a,b) = edge({r,j}); ad(a,b,i); st = a;
				int cur = sz(rvis)-1; label[a] = cur; 
				vi tmp; set_union(all(rvis[r]),all(rvis[o]),
									back_inserter(tmp)); 
				// merge sorted vectors ignoring duplicates
				each(x,tmp) if (abv(cur,x)) ae(cur,x);
				/// if no rounding errors then guaranteed that only x>i matters
				glue({cur,0},other[r][j]); // glue old w/ new face
			}
		}
		for (int x = st, y; ; x = y) { // glue new faces together
			int X = label[x]; glue({X,1},{label[y=hull[X][1]],2});
			if (y == st) break;
		}
	}
	V<F> ans; F0R(i,sz(hull)) if (active[i]) ans.pb(hull[i]);
	return ans;
}
