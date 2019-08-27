///////////////////////////
//
// SAP 7k+
//
///////////////////////////
int he[N], ne[M], ad[M], di[M], t; 
int h[N], hi[N], ed[N], pr[N], d[N], co[N]; 

void addE(int x, int y, int z) {
  ++t; ne[t] = he[x]; he[x] = t; ad[t] = y; di[t] = z; 
  ++t; ne[t] = he[y]; he[y] = t; ad[t] = x; di[t] = 0; 
}

void pred(int s, int t) {
  if (s == t) return; 
  if (d[s] != 0) return; 
  d[s] = INF; 
  for (int p=he[s]; p; p=ne[p])
    if (di[p] > 0) {
      pred(ad[p], t); 
      d[s] = min(d[s], d[ad[p]] + 1); 
    }
}

int sap(int s, int t, int c) {
  memcpy(h, he, sizeof(int)*c); 
  memset(d, 0, sizeof(int)*c); pred(s, t); 
  memset(co, 0, sizeof(int)*c); 
  for (int i = 0; i < c; i ++) co[d[i]] ++; 
  int mf = 0, nf = INF; 
  int x = s; 
  while (d[s] < c) {
    bool F = 0; 
    hi[x] = nf; 
    for (int p = h[x]; p; p=ne[p]) 
      if (di[p] > 0 && d[ad[p]]+1 == d[x]) {
        h[x] = p; 
        F = 1; 
        nf = min(nf, di[p]); 
        ed[ad[p]] = p; 
        pr[ad[p]] = x; 
        x = ad[p]; 
        if (x == t) {
          mf += nf; 
          while (x != s) {
            di[ed[x]] -= nf;
            di[ed[x]^1] += nf; 
            x = pr[x]; 
          }
          nf = INF; 
        }
        break; 
      }
    if (!F) {
      int mi = c; 
      for (int p = he[x]; p; p=ne[p])
        if (di[p] > 0 && d[ad[p]] < mi) {
          mi = d[ad[p]]; 
          h[x] = p; 
        }
      co[d[x]] --; 
      if (co[d[x]] == 0) break; 
      d[x] = mi + 1; 
      co[d[x]] ++; 
      if (x != s) {
        x = pr[x]; 
        nf = hi[x]; 
      }
    }
  }
  return mf; 
}

