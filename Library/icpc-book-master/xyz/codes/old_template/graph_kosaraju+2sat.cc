///////////////////////////
//
// Kosaraju + 2SAT
//
///////////////////////////
bool v[M];
int st[M], sn, cc[M], co, ch[M];
int S[M];

void ff1(int x) {
  v[x] = 1;
  for (int i = 0; i < (int) C[x].size(); i ++)
    if (!v[C[x][i]]) ff1(C[x][i]);
  st[sn++] = x;
}

void ff2(int x) {
  v[x] = 0;
  cc[x] = co;
  for (int i = 0; i < (int) IC[x].size(); i ++)
    if (v[IC[x][i]]) ff2(IC[x][i]);
}

void gg(int x, int c) {
  S[x] = c;
  if (S[x^1] == -1) gg(x^1, 1-c);
  if (c == 1) {
    for (int i = 0; i < (int) C[x].size(); i ++)
      if (S[C[x][i]] == -1) gg(C[x][i], 1);
  } else {
    for (int i = 0; i < (int) IC[x].size(); i ++)
      if (S[IC[x][i]] == -1) gg(IC[x][i], 0);
  }
}
////////////////////
  sn = 0;
  for (int i = 0; i < p*2; i ++)
    if (!v[i]) ff1(i);
  co = 0;
  for (int i = sn-1; i >= 0; i --)
    if (v[st[i]]) {
      ch[co] = st[i];
      ff2(st[i]);
      co++;
    }
  memset(S, -1, sizeof S);
  for (int i = co-1; i >= 0; i --) {
    if (S[ch[i]] == -1) gg(ch[i], 1);
  }
