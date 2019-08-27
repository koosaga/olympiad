///////////////////////////
//
// MinCostFlow
//
///////////////////////////
int he[NN], ne[MM], ad[MM], di[MM], wi[MM];
int pr[NN], ed[NN], d[NN]; bool v[NN];
int t; 

void addE(int x, int y, int z, int w) {
  ++t; ne[t] = he[x]; he[x] = t; ad[t] = y; di[t] = z; wi[t] = w;
  ++t; ne[t] = he[y]; he[y] = t; ad[t] = x; di[t] = 0; wi[t] = -w;
}

int q[NN*MM];

bool spfa(int s, int t, int c) {
  memset(v, 0, sizeof v);
  for (int i = 0; i < c; i++) d[i] = INF;
  int l = 0, r = 1;
  q[0] = s; v[s] = 1; d[s] = 0;
  while (l < r) {
    int x = q[l++]; v[x] = 0;
    for (int p = he[x]; p; p = ne[p]) {
      if (!di[p]) continue;
      if (d[x] + wi[p] < d[ad[p]]) {
        d[ad[p]] = d[x] + wi[p];
        pr[ad[p]] = x; ed[ad[p]] = p;
        if (!v[ad[p]]) {
          v[ad[p]] = 1; 
          q[r++] = ad[p];
        }
      }
    }
  }
  return d[t] < INF;
}

int ff(int s, int t, int c) {
  int S = 0;
  while (spfa(s, t, c)) {
    int nf = INF;
    for (int i = t; i != s; i = pr[i]) nf = min(nf, di[ed[i]]);
    S += nf*d[t];
    for (int i = t; i != s; i = pr[i]) {
      di[ed[i]] -= nf;
      di[ed[i]^1] += nf;
    }
  }
  return S;
}
