///////////////////////////
//
// all 2d geometry
//
///////////////////////////

const db eps = 1e-8;
const db inf = 1e10;
const db pi = 3.141592653589793238462643383279;

int sgn(db x) {
  if (x > eps) return 1; else
  if (x < -eps) return -1;
  return 0;
}

db ssqrt(db x) {
  return sqrt(max(x, 0.0));
}

struct P {
  db x, y;
  P() {}
  P(db _x, db _y):x(_x), y(_y) {}
  P operator + (const P&a) const {return P(x+a.x, y+a.y);}
  P operator - (const P&a) const {return P(x-a.x, y-a.y);}
  P operator * (db a) const {return P(x*a, y*a);}
  P operator / (db a) const {return P(x/a, y/a);}
  db crs (const P&a) const {return x*a.y - y*a.x;}
  db dot (const P&a) const {return x*a.x + y*a.y;}
  db abs2 () const {return x*x+y*y;}
  db abs () const {return sqrt(abs2());}
  db dis (const P&a) const {return (*this-a).abs();}
  db dis2 (const P&a) const {return (*this-a).abs2();}
  db tan() const {return atan2(y, x);}
  db rad(const P&a) const {return atan2(crs(a), dot(a));}
  P rot90() const {return P(-y, x);}
  bool operator < (const P&a) const {
    return x < a.x - eps || x < a.x + eps && y < a.y - eps;
  }
  bool operator == (const P&a) const {
    return fabs(x-a.x) < eps && fabs(y-a.y) < eps;
  }
  void get () {cin >> x >> y;}
  void out () const {printf ("%.9lf %.9lf\n", x, y);}
};

struct L {
  P x, y;
  L(){}
  L(const P&_x, const P&_y):x(_x), y(_y) {}
  L operator + (const P&a) const {return L(x+a, y+a);}
  L operator - (const P&a) const {return L(x-a, y-a);}
  // direction
  P vec () const {return y-x;}
  // normalized direction
  P nvec () const {return (y-x)/(y-x).abs();}
  // line = x+t*(y-x)
  // projection ratio of a point to a line
  db proj_rat (const P&a) const {
    // (x+t*(y-x)-a).dot(y-x) == 0
    return (a-x).dot(y-x)/(y-x).abs2();
  }
  // projection of a point to a line
  P proj (const P&a) const {
    db t = proj_rat(a);
    return x + (y-x)*t;
  }
  // reflection of a point wrt a line
  P refl (const P&a) const {
    return proj(a)*2-a;
  }
  // relative direction of (x,y) -> a
  // 0: counter clockwise
  // 1: clockwise
  // 2: on line back
  // 3: on line front
  // 4: on segment
  int reldir (const P&a) const {
    db c1 = (y-x).crs(a-x);
    if (c1 > eps) return 0; else
    if (c1 < -eps) return 1; else {
      db c2 = (a-x).dot(y-x);
      db c3 = (y-x).dot(y-x);
      if (c2 < -eps) return 2; else 
      if (c2 > c3 + eps) return 3;
      else return 4;
    }
  }
  // point on segment
  bool on_segment (const P&a) const {
    return reldir(a) == 4;
  }
  // point on line
  bool on_line (const P&a) const {
    return reldir(a) >= 2;
  }
  // relative direction to another line
  // 0: none
  // 1: parallel
  // 2: perp
  int reldir (const L&l) const {
    P v1 = vec();
    P v2 = l.vec();
    if (fabs(v1.crs(v2)) < eps) return 2; else
    if (fabs(v1.dot(v2)) < eps) return 1;
    else return 0;
  }
  // if intersect where self is line and a is segment
  // only allow proper intersection
  bool ints_ls_p(const L&a) const {
    return sgn((a.x-y).crs(x-y)) * sgn((a.y-y).crs(x-y)) == -1;
  }
  // if intersect as segments
  // only allow proper intersection
  bool ints_ss_p (const L&a) const {
    return ints_ls_p(a) && a.ints_ls_p(*this);
  }
  // if intersect as segments
  // allow non-proper intersection
  bool ints_ss_np(const L&a) const {
    if (ints_ss_p(a)) return true;
    if (a.on_segment(x) || a.on_segment(y) || on_segment(a.x) || on_segment(a.y)) return true;
    return false;
  }
  // intersection ratio as lines
  db ints_rat (const L&a) const {
    // (x+(y-x)*t-a.y).crs(a.x-a.y) == 0
    return (a.y-x).crs(a.x-a.y)/(y-x).crs(a.x-a.y);
  }
  // intersection point as lines
  P ints (const L&a) const {
    db t = ints_rat(a);
    return x + (y-x)*t;
  }
  // distance to a point as a segment
  // use disl for distance as a line
  db dis (const P&a) const {
    db t = proj_rat(a);
    if (t > -eps && t < 1+eps)
      return a.dis(x+(y-x)*t);
    return min(a.dis(x), a.dis(y));
  }
  // distance to a point as a line
  db disl (const P&a) const {
    return proj(a).dis(a);
  }
  // distance as segments
  db dis (const L&a) const {
    if (ints_ss_p(a)) return 0;
    return min(min(a.dis(x), a.dis(y)), min(dis(a.x), dis(a.y)));
  }
  void get () {x.get(); y.get();}
  void out () const {printf ("%.9lf %.9lf %.9lf %.9lf\n", x.x, x.y, y.x, y.y);}
};

struct poly {
  int n;
  vector<P> a;
  // area of polygon
  // do not assume convex
  // assume ccw
  db area () const {
    db S = 0;
    for (int i = 0; i < n; i ++) {
      int ne = (i+1)%n;
      S += a[i].crs(a[ne]);
    }
    return S*.5;
  }
  // if is convex
  // assume ccw
  // allow three points in a row
  bool is_convex () const {
    for (int i = 0; i < n; i ++) {
      int ne = (i+1)%n;
      int nn = (i+2)%n;
      if ((a[ne]-a[i]).crs(a[nn]-a[i]) < -eps) return false;
    }
    return true;
  }
  // if point is in polygon
  // do not assume convex
  // assume ccw
  // 0: no
  // 1: on segment
  // 2: properly contain
  int in_poly(const P&p) const {
    int S = 0;
    for (int i = 0; i < n; i ++) {
      P x = a[i];
      P y = a[(i+1)%n];
      if (L(x, y).on_segment(p)) return 1;
      if (y < x) swap(x, y);
      if (p.x < x.x - eps || p.x > y.x - eps) continue;
      if ((y-x).crs(p-x) > eps) S ^= 1;
    }
    return S*2;
  }
  void get() {
    cin >> n;
    for (int i = 0; i < n; i ++) {
      P x; x.get(); a.pb(x);
    }
  }
};

struct C {
  P x; db r;
  C(){}
  C(const P&_x, db _r):x(_x), r(_r) {}
  // relative position of two circles
  // 0: contain
  // 1: in tangent
  // 2: intersect
  // 3: out tangent
  // 4: separate
  int rel_pos(const C&c) const {
    db d = x.dis(c.x);
    if (d > r + c.r + eps) return 4;
    if (d > r + c.r - eps) return 3;
    if (d > fabs(r-c.r) + eps) return 2;
    if (d > fabs(r-c.r) - eps) return 1;
    return 0;
  }
  // two intersection points with a line
  // assume intersection
  L ints_l(const L&l) const {
    // (l.x + t*(l.y-l.x)).dis2(x) == r*r
    db A = l.vec().abs2();
    db B = (l.x-x).dot(l.vec())*2;
    db C = (l.x-x).abs2() - r*r;
    db d = ssqrt(B*B-4*A*C);
    db t1 = (-B-d)/(A*2);
    db t2 = (-B+d)/(A*2);
    return L(l.x + l.vec()*t1, l.x + l.vec()*t2);
  }
  // two intersection points with a circle
  // assume intersection
  L ints_c(const C&c) const {
    db d = x.dis(c.x);
    P dir = (c.x-x)/d;
    db d1 = (r*r-c.r*c.r+d*d)/(2*d);
    P p = x + dir*d1;
    db l = ssqrt(r*r-d1*d1);
    P q = dir.rot90()*l;
    return L(p-q, p+q);
  }
  // two tangent points from a point
  // assume not inside circle
  L tan_p(const P&a) const {
    db d = x.dis(a);
    P dir = (a-x)/d;
    db d1 = r*r/d;
    P p = x + dir*d1;
    db l = ssqrt(r*r-d1*d1);
    P q = dir.rot90()*l;
    return L(p-q, p+q);
  }
  // common tangent point with a circle
  // tangent point on the other circle is easy
  vector<P> tan_c(const C&c) const {
    vector<P> a;
    int po = rel_pos(c);
    // outer tangent
    if (po >= 1) {
      db d = x.dis(c.x);
      P dir = (c.x-x)/d;
      db d1 = (r-c.r)*r/d;
      P p = x + dir*d1;
      db l = ssqrt(r*r-d1*d1);
      P q = dir.rot90()*l;
      a.pb(p-q);
      a.pb(p+q);
    }
    // inner tangent
    if (po >= 3) {
      db d = x.dis(c.x);
      P dir = (c.x-x)/d;
      db d1 = (r+c.r)*r/d;
      P p = x + dir*d1;
      db l = ssqrt(r*r-d1*d1);
      P q = dir.rot90()*l;
      a.pb(p-q);
      a.pb(p+q);
    }
    return a;
  }
  // intersection area of two circles
  db inta_c(const C&c) const {
    db d = x.dis(c.x);
    if (d > r + c.r - eps) return 0.0;
    if (d < c.r - r + eps) return pi*r*r;
    if (d < r - c.r + eps) return pi*c.r*c.r;
    db x = (d*d + r*r - c.r*c.r)/(d*2);
    db t = acos(x/r);
    db t1 = acos((d-x)/c.r);
    return r*r*t + c.r*c.r*t1 - d*r*sin(t);
  }
  // oriented intersection area with a triangle
  // one vertex is center of circle
  // assume l is nondegenerate (for l.disl)
  db inta_t(const L&l0) const {
    //if (l.x.dis(l.y) < eps) return 0.0;
    L l = l0 - x;
    db lx = l.x.abs(), ly = l.y.abs();
    if (l0.disl(x) > r - eps) return l.x.rad(l.y)*r*r/2;
    L u = ints_l(l0) - x;
    if (lx < r + eps && ly < r + eps) return l.x.crs(l.y)/2;
    if (lx < r + eps) return (l.x.crs(u.y) + (u.y).rad(l.y)*r*r)/2;
    if (ly < r + eps) return (u.x.crs(l.y) + (l.x).rad(u.x)*r*r)/2;
    if ((u.x-l.x).dot(u.x-l.y) > -eps && (u.y-l.x).dot(u.y-l.y) > -eps)
      return l.x.rad(l.y)*r*r/2;
    return (u.x.crs(u.y) + (l.x.rad(u.x) + u.y.rad(l.y))*r*r)/2;
  }
  // point on circle at given angle
  P pt(db a) const {return x + P(r*cos(a), r*sin(a));}
  void get() {x.get(); cin >> r;}
};

// radius of circumcirle
// a.dis(b)*b.dis(c)*c.dis(a)/(fabs((b-a).crs(c-a))*2)

// circumcenter
P circtr(P a, P b, P c) {
  db aa = b.dis2(c), bb = a.dis2(c), cc = a.dis2(b);
  db wa = aa*(bb+cc-aa);
  db wb = bb*(aa+cc-bb);
  db wc = cc*(aa+bb-cc);
  return (a*wa+b*wb+c*wc)/(wa+wb+wc);
}

// incenter
P inctr(P a, P b, P c) {
  db aa = b.dis(c), bb = a.dis(c), cc = a.dis(b);
  return (a*aa+b*bb+c*cc)/(aa+bb+cc);
}

// change atan2 of line to 0 <= deg < 180
db ang(db t) {
  if (t < -eps) t += pi;
  if (t > pi-eps) t -= pi;
  return max(t, 0.0)*180.0/pi;
}

// points with given dis to a line and a pt
vector<P> pt_dis_pl(P x, L l, db r) {
  vector<P> a;
  if (l.on_line(x)) {
    P v = l.nvec().rot90()*r;
    a.pb(x+v);
    a.pb(x-v);
  } else {
    P y = l.proj(x);
    P v = (x-y)/(x-y).abs()*r;
    if (y.dis(x) < r*2 + eps) {
      L s = C(x, r).ints_l(l+v);
      a.pb(s.x); a.pb(s.y);
    }
  }
  sort(a.begin(), a.end());
  a.erase(unique(a.begin(), a.end()), a.end());
  return a;
}

// points with given dis to two lines
vector<P> pt_dis_ll(L l1, L l2, db r) {
  vector<P> a;
  P v1 = l1.nvec().rot90()*r;
  P v2 = l2.nvec().rot90()*r;
  a.pb((l1+v1).ints(l2+v2));
  a.pb((l1+v1).ints(l2-v2));
  a.pb((l1-v1).ints(l2+v2));
  a.pb((l1-v1).ints(l2-v2));
  sort(a.begin(), a.end());
  a.erase(unique(a.begin(), a.end()), a.end());
  return a;
}
