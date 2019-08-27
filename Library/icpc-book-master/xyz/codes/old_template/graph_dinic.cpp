///////////////////////////
//
// Dinic
// Have to make sure e ^ e' = 1, where e' is the reverse edge of e
///////////////////////////
bool bfs() {
  int q, h, i;
  memset(D, 0, sizeof D);
  memset(cc, true, sizeof cc);
  for (D[n1[q = h = 1] = s] = 1; q <= h; q++)
    for (i = till[n1[q]]; i; i = next[i])
      if (f[i] && !D[go[i]])  D[n1[++h] = go[i]] = D[n1[q]] + 1;
  return D[t];
}
int dfs(int k, int mi) {
  if (k == t) return mi;
  int i, tmp, sum = 0;
  for (i = till[k]; i && mi; i = next[i])
    if (f[i] && D[go[i]] == D[k] + 1 && cc[go[i]]) {
      tmp = dfs(go[i], min(mi, f[i]));
      sum += tmp;
      mi -= tmp;
      f[i] -= tmp;
      f[i ^ 1] += tmp;
    }
  if (!sum) cc[k] = false;
  return sum;
}
int maxFlow() {
  int sum = 0;
  while (bfs()) sum += dfs(s, INF);
  return sum;
}