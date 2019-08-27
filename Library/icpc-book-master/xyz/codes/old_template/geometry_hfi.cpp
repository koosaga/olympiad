///////////////////////////
//
// halfplane intersection
//
///////////////////////////

// 可能会挂时要加inf的框
struct P {
  int quad() const {return y > eps || y > -eps && x > eps;}
}

struct L{
  bool include_p (const P&a) const {
    return (y-x).crs(a-x) > eps;
  }
  bool include (const P&a) const {
    return (y-x).crs(a-x) > -eps;
  }
  bool same_dir(const L&a) const {
    P av = a.vec(), v = vec();
    return fabs(v.crs(av)) < eps && v.dot(av) > eps;
  }
  bool operator < (const L&a) const {
    if (same_dir(a)) return a.include_p(x);
    P av = a.vec(), v = vec();
    if (v.quad() != av.quad()) return v.quad() < av.quad();
    return v.crs(av) > eps;
  }
}

#define N 100010
int n;
L a[N];
L q[N]; int l, r;
P A[N]; int LA;

void ff() {
  sort(a, a+n);
  l = r = 0;
  for (int i = 0; i < n; i ++) {
    if (i && a[i].same_dir(a[i-1])) continue;
    while (r-l > 1 && !a[i].include(q[r-1].ints(q[r-2]))) r--;
    while (r-l > 1 && !a[i].include(q[l].ints(q[l+1]))) l++;
    q[r++] = a[i];
  }
  while (r-l > 2 && !q[l].include(q[r-1].ints(q[r-2]))) r--;
  while (r-l > 2 && !q[r-1].include(q[l].ints(q[l+1]))) l++;
  // nonempty: r-l > 2
  LA = 0;
  for (int i = l; i < r; i ++) {
    int ne = i+1;
    if (ne == r) ne = l;
    A[LA++] = q[i].ints(q[ne]);
  }
}
