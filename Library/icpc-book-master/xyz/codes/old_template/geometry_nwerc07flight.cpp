///////////////////////////
//
// Geometry
// NWERC 07 flight
//
///////////////////////////
double getp (P a) { // a = le + (ri - le) * t  return t
  return (a-le).dot(ri-le)/(ri-le).abs2(); 
}
bool ccw (vector<P> a) { // test polygon ccw
  int n = (int) a.size(); 
  double S = 0; 
  for (int i = 1; i < n-1; i ++) 
  S += (a[i]-a[0]).crs(a[i+1]-a[0]);
  return S > 0; 
} 
bool inside (P b, vector<P> a) { // test inside polygon
  int n = (int) a.size(); bool s = 0; 
  for (int i = 0; i < n; i ++) {
  int i1 = (i+1)%n; 
  P a1 = a[i]-b, a2 = a[i1]-b; 
  if (fabs(a1.crs(a2)) < eps && a1.dot(a2) < eps) return 1; 
  int s1 = sgn(a1.y), s2 = sgn(a2.y); 
  if (s1 != s2 && s1 + s2 >= 0) {
    double x = (a1.x*a2.y - a2.x*a1.y)/(a2.y - a1.y); 
    if (x > -eps) s = !s; 
  }
  }
  return s; 
}
void add1 (vector<P> a) { // line segments covered by a polygon
  if (!ccw(a)) reverse(a.begin(), a.end()); 
  int n = (int) a.size(); L2 = 0;
  for (int i = 0; i < n; i ++) {
  int i1 = (i+1)%n; 
  if (sgn((le-a[i]).crs(ri-a[i])) != sgn((le-a[i1]).crs(ri-a[i1])) 
    && sgn((a[i]-le).crs(a[i1]-le)) != sgn((a[i]-ri).crs(a[i1]-ri))) {
    double c1 = (le-a[i]).crs(ri-a[i]);
    double c2 = (le-a[i1]).crs(ri-a[i1]);
    P c = (a[i]*c2-a[i1]*c1)/(c2-c1); 
    double x = getp(c); 
    if (x < eps) continue; 
    if (x > 1 - eps) continue; 
    p2[L2++] = x; 
  }
  }
  if (inside(le, a)) p2[L2++] = 0.0; 
  if (inside(ri, a)) p2[L2++] = 1.0; 
  sort (p2, p2+L2);  
  for (int i = 0; i < L2; i += 2) 
  p[L++] = P(p2[i], p2[i+1]); 
}
void add2 (P a, P b) { // get a rectangle that two edges are parallel to, same length as, distance d to, (a,b)
  vector<P> c; 
  P e = (b-a).norm().rot90()*d; 
  c.pb(a+e); c.pb(a-e); 
  c.pb(b-e); c.pb(b+e); 
  add1(c); 
}
void add3 (P a) { // line segment covered by a circle
  if (fabs(t.crs(a-le)) > d - eps) return; 
  double d1 = (a-le).crs(t);
  P b = a+t.rot90()*d1; 
  double d2 = sqrt(d*d-d1*d1); 
  P l = b - t*d2, r = b + t*d2; 
  double lm = getp(l), rm = getp(r); 
  lm = max(lm, 0.0); 
  rm = min(rm, 1.0); 
  if (lm > rm) return; 
  p[L++] = P(lm, rm); 
} 
