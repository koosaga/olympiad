///////////////////////////
//
// geometry 2dhull
//
///////////////////////////

const int INF = 1000000007;

struct P {
  int x, y;
  P(){}
  P(int _x, int _y):x(_x), y(_y) {}
  P operator + (const P&a) const {return P(x+a.x, y+a.y);}
  P operator - (const P&a) const {return P(x-a.x, y-a.y);}
  ll dot (const P&a) const {return (ll)x*a.x + (ll)y*a.y;}
  ll crs (const P&a) const {return (ll)x*a.y - (ll)y*a.x;}
  P rot90 () const {return P(-y,x);} 
  bool operator < (const P&a) const {
  return x < a.x || x == a.x && y < a.y;
  }
  bool upper () const {return y > 0 || y == 0 && x > 0;}
  void get() {GN(x); GN(y);}
  void out() {printf ("%d %d\n", x, y);}
};

const P o(0, 0);
const PII none(-1, -1);

struct L {
  P x, y;
  L() {}
  L(P _x, P _y):x(_x), y(_y) {}
  P vec() const {return y-x;}
};

int sgn(ll a) {
  if (a < 0) return -1;
  else return a > 0;
}
 
vector<P> hull(vector<P> a) {
  int n = (int) a.size();
  sort(a.begin(), a.end());
  vector<P> s(n+1);
  int t = 0;
  for (int i = 0; i < n; i ++) {
    while (t > 1 && (a[i]-s[t-2]).crs(s[t-1]-s[t-2]) >= 0) t--;
    s[t++] = a[i];
  }
  int t0 = t;
  for (int i = n-2; i >= 0; i--) {
    while (t > t0 && (a[i]-s[t-2]).crs(s[t-1]-s[t-2]) >= 0) t--;
    s[t++] = a[i];
  }
  t--;
  s.resize(t);
  return s;
}
 
struct CH {
  int n, nl, nh;
  vector<P> a, lo, hi;
  
  CH () {}
  CH (const vector<P>& _a) {
  init(_a);
  }
  
  // assume nondegenerate & ccw
  void init(const vector<P>& _a) {
    a = _a;
    n = (int) a.size();
    rotate(a.begin(), min_element(a.begin(), a.end()), a.end());
    int at = max_element(a.begin(), a.end()) - a.begin();
    lo = vector<P>(a.begin(), a.begin() + at + 1);
    hi = vector<P>(a.begin() + at, a.end()); hi.pb(a[0]);
    nl = (int) lo.size();
    nh = (int) hi.size();
  }
   
  // check if p is contained in hull
  bool contain (P p) const {
    if (p.x < lo[0].x || p.x > hi[0].x) return false;
    int id = lower_bound(lo.begin(), lo.end(), P(p.x, -INF)) - lo.begin();
    if (lo[id].x == p.x) {
      if (lo[id].y > p.y) return false;
    } else {
      if ((lo[id]-p).crs(lo[id-1]-p) > 0) return false;
    }
    id = hi.rend() - lower_bound(hi.rbegin(), hi.rend(), P(p.x, INF));
    if (hi[id].x == p.x) {
      if (hi[id].y < p.y) return false;
    } else {
      if ((hi[id]-p).crs(hi[id-1]-p) > 0) return false;
    }
    return true;
  }
   
  // update tangent
  void upd_tan(int id, P p, PII&S) const {
    if ((a[S.fi]-p).crs(a[id]-p) > 0) S.fi = id;
    if ((a[S.se]-p).crs(a[id]-p) < 0) S.se = id;
  }
   
  // binary search tangent
  void bin_tan(int l, int r, P p, PII&S) const {
    if (l == r) return;
    upd_tan(l%n, p, S);
    int sl = sgn((a[l%n]-p).crs(a[(l+1)%n]-p));
    while (l+1 < r) {
      int m = (l+r)/2;
      if (sgn((a[m%n]-p).crs(a[(m+1)%n]-p)) == sl) l = m;
      else r = m;
    }
    upd_tan(r%n, p, S);
  }
   
  // get tangent
  // assume p not contained in hull
  // return (left tan, right tan)
  PII tangent(P p) const {
    PII S(0, 0);
    int id = lower_bound(lo.begin(), lo.end(), p) - lo.begin();
    bin_tan(0, id, p, S);
    bin_tan(id, nl, p, S);
    id = hi.rend() - lower_bound(hi.rbegin(), hi.rend(), p);
    bin_tan(nl-1, nl-1+id, p, S);
    bin_tan(nl-1+id, n+1, p, S);
    return S;
  }
  
  // binary search maxdot
  int bin_maxdot(int l, int r, P p) const {
    while (l+5 < r) {
    int l1 = (l*2+r)/3;
    int r1 = (l+r*2)/3;
    if (a[l1%n].dot(p) > a[r1%n].dot(p)) r = r1;
    else l = l1;
    }
    int s = l;
    for (int i = l+1; i < r; i ++)
    if (a[i%n].dot(p) > a[s%n].dot(p)) s = i;
    return s%n;
  }
  
  // find vector with maximum dot with p
  int maxdot(P p) const {
    if (p.upper()) return bin_maxdot(nl-1, n+1, p);
    else return bin_maxdot(0, nl, p);
  }
  
  // binary search intersection
  int bin_ints(int l, int r, P x, P v) const {
    int sl = sgn(v.crs(a[l%n]-x));
    while (l+1 < r) {
    int m = (l+r)/2;
    if (sgn(v.crs(a[m%n]-x)) == sl) l = m;
    else r = m;
    }
    return l%n;
  }
  
  // intersection point with a line
  // -1 means no intersection
  PII ints(L l) const {
    P v = l.vec();
    int x = maxdot(v.rot90());
    int y = maxdot(o-v.rot90());
  int sx = sgn(v.crs(a[x]-l.x));
  int sy = sgn(v.crs(a[y]-l.x));
    if (sx * sy != -1) {
    // deal with the case intersection is a nonzero segment
    // only work for hull with >=3 pts
    if (sy == 0) swap(x, y), swap(sx, sy);
    if (sx == 0) {
    if (v.crs(a[(x+n-1)%n]-l.x) == 0) x = (x+n-1)%n;
    if (v.crs(a[(x+1)%n]-l.x) == 0) return mp((x+n-1)%n, (x+1)%n);
    }
    return none;
  }
    if (x > y) swap(x, y);
    return mp(bin_ints(x, y, l.x, v), bin_ints(y, x+n, l.x, v));
  }
};

int n;
vector<P> a;
CH c;

ll f[N*4];
void blt(int p, int l, int r) {
  if (l == r-1) {
  f[p] = a[l].crs(a[(l+1)%n]);
  return;
  }
  int mid = (l+r)/2;
  blt(p*2+1, l, mid);
  blt(p*2+2, mid, r);
  f[p] = f[p*2+1] + f[p*2+2];
}

ll ask(int p, int l, int r, int L, int R) {
  if (L <= l && r <= R) return f[p];
  int mid = (l+r)/2;
  ll S = 0;
  if (L < mid) S += ask(p*2+1, l, mid, L, R);
  if (mid < R) S += ask(p*2+2, mid, r, L, R);
  return S;
}

ll ask(int l, int r) {
  if (l == r) return 0;
  if (l < r) return ask(0, 0, n, l, r);
  return ask(l, n) + ask(0, r);
}

// intersection area of hull with arbitrary simple polygon
// blame POJ 2839 test data if it's wrong
db ints_a(vector<P> b) {
  int m = (int) b.size();
  bool xin = false;
  vector<pair<PD, PII> > s;
  for (int i = 0; i < m; i ++) {
  L l(b[i], b[(i+1)%m]);
  if (i == 0) xin = c.contain(l.x);
  bool yin = c.contain(l.y);
  if (xin^yin) {
    PII u = c.ints(l);
    if (u != none) {
    // take one with smaller dot
    PD p1 = LD(c.a[u.fi], c.a[(u.fi+1)%c.n]).ints(l);
    PD p2 = LD(c.a[u.se], c.a[(u.se+1)%c.n]).ints(l);
    if ((p1-l.x).dot(p1-l.y) < (p2-l.x).dot(p2-l.y)) {
      s.pb(mp(p1, mp(u.fi, yin)));
    } else {
      s.pb(mp(p2, mp(u.se, yin)));
    }
    }
  } else 
  if (!xin && !yin) {
    PII u = c.ints(l);
    if (u != none) {
    PD p1 = LD(c.a[u.fi], c.a[(u.fi+1)%c.n]).ints(l);
    PD p2 = LD(c.a[u.se], c.a[(u.se+1)%c.n]).ints(l);
    if ((p1-l.x).dot(p1-l.y) < 0 && (p2-l.x).dot(p2-l.y) < 0) {
      if ((p1-l.x).dot(l.y-l.x) < (p2-l.x).dot(l.y-l.x)) {
      s.pb(mp(p1, mp(u.fi, 1)));
      s.pb(mp(p2, mp(u.se, 0)));
      } else {
      s.pb(mp(p2, mp(u.se, 1)));
      s.pb(mp(p1, mp(u.fi, 0)));
      }
    }
    }
  }
  
  if (yin) s.pb(mp(PD(l.y), none));
  
  xin = yin;
  }
  
  db S = 0;
  int ss = (int) s.size();
  for (int i = 0; i < ss; i ++) {
  pair<PD, PII> p = s[i], q = s[(i+1)%ss];
  if (p.se == none || q.se == none || (p.se.se == 1 && q.se.se == 0) || p.se.fi == q.se.fi)
    S += p.fi.crs(q.fi);
  else {
    assert(p.se.se == 0 && q.se.se == 1);
    assert(p.se.fi != q.se.fi);
    S += p.fi.crs(c.a[(p.se.fi+1)%c.n]);
    S += ask((p.se.fi+1)%c.n, q.se.fi);
    S += PD(c.a[q.se.fi]).crs(q.fi);
  }
  }
  return S/2;
}
