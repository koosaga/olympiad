///////////////////////////
//
// geometry 3dhull
//
///////////////////////////


P3 crs (const P3&a) const {
  return P3(y*a.z - z*a.y, z*a.x - x*a.z, x*a.y - y*a.x);
}

int n;
P3 a[N];

db vol(P3 x, P3 y, P3 z) {
  return x.dot(y.crs(z));
}

db vol(P3 x, P3 y, P3 z, P3 w) {
  return vol(w-x, w-y, w-z);
}

db vol(int x, int y, int z, int w) {
  return vol(a[x], a[y], a[z], a[w]);
}

map<PII, PI3> f;
set<PI3> fc;

void reg(int &x, int &y, int &z) {
  int t;
  if (y < x) {
    t = x; x = y; y = z; z = t;
  }
  if (y < x) {
    t = x; x = y; y = z; z = t;
  }
}

void add(int x, int y, int z) {
  reg(x, y, z);
  PI3 f3 = mp3(x, y, z);
  f[mp(x, y)] = f3;
  f[mp(y, z)] = f3;
  f[mp(z, x)] = f3;
  fc.insert(f3);
}

void del(int x, int y, int z) {
  reg(x, y, z);
  PI3 f3 = mp3(x, y, z);
  f.erase(mp(x, y));
  f.erase(mp(y, z));
  f.erase(mp(z, x));
  fc.erase(f3);
}

bool inside(int x) {
  db S = 0, T = 0;
  for (set<PI3>::iterator j = fc.begin(); j != fc.end(); j ++) {
    db U = vol(j->fi3, j->se3, j->th3, x);
    S += fabs(U);
    T += U;
  }
  T = fabs(T);
  if (fabs(S-T) > eps) return 0;
  return 1;
}

int main () {
  cin >> n;
  for (int i = 0; i < n; i ++) a[i].get();
  random_shuffle(a, a+n);
  while (vol(0, 1, 2, 3) > 0)
    random_shuffle(a, a+4);
  add(0, 1, 2);
  add(0, 2, 3);
  add(0, 3, 1);
  add(1, 3, 2);
  for (int i = 4; i < n; i ++) {
    if (inside(i)) continue;
    set<PII> ed;
    set<PI3> fc2 = fc;
    for (set<PI3>::iterator j = fc2.begin(); j != fc2.end(); j ++)
      if (vol(j->fi3, j->se3, j->th3, i) > 0) {
        del(j->fi3, j->se3, j->th3);
        ed.insert(mp(j->fi3, j->se3));
        ed.insert(mp(j->se3, j->th3));
        ed.insert(mp(j->th3, j->fi3));
      }
    for (set<PII>::iterator j = ed.begin(); j != ed.end(); j ++)
      if (f.find(mp(j->se, j->fi)) != f.end()) add(j->fi, j->se, i);
  }
  // fc are faces
}
