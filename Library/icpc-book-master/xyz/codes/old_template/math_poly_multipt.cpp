///////////////////////////
//
// multipt evaluation
//
///////////////////////////
int ra[NN], rb[NN];
// n-1 = deg a, m-1 = deg b
void div(int* a, int* b, int* c, int n, int m) {
  int p = n-m+1;
  int mm = 1;
  while (mm <= p) mm *= 2;
  for (int i = 0; i < mm && i < n; i ++)
    ra[i] = a[n-1-i];
  if (mm > n) {
    memset(ra+n, 0, sizeof(int)*(mm-n));
  }
  for (int i = 0; i < mm && i < m; i ++)
    rb[i] = b[m-1-i];
  if (mm > m) {
    memset(rb+m, 0, sizeof(int)*(mm-m));
  }
  inv(rb, c, mm);
  mul(ra, c, mm);
  reverse(c, c+p);
}

int bb[NN];
void mod(int* a, int* b, int* c, int n, int m) {
  int n1 = n, m1 = m;
  while (n && a[n-1] == 0) n--;
  while (m && b[m-1] == 0) m--;
  if (!n) {
    memset(c, 0, sizeof(int)*n1);
    return;
  }
  assert(m != 0);
  div(a, b, c, n, m);
  int p = n-m+1;
  int mm = 1;
  while (mm < n) mm *= 2;
  memset(c+p, 0, sizeof(int)*(mm-p));
  memcpy(bb, b, sizeof(int)*m);
  memset(bb+m, 0, sizeof(int)*(mm-m));
  mul(bb, c, mm);
  for (int i = 0; i < n1; i ++)
    c[i] = (a[i]-c[i]+P)%P;
}

int a[NN];

void blt(int*a, int l, int r) {
  if (r-l == 1) {
    a[0] = l;
    a[1] = 1;
    return;
  }
  int m = (l+r+1)/2;
  int n = r-l+1;
  blt(a, l+1, m);
  blt(a+n, m, r);
  mul(a+n, a, n/2);
  // mult by (x+l)
  for (int i = n-1; i; i--) {
    a[i] = ((ll)a[i]*l + a[i-1])%P;
  }
  a[0] = (ll)a[0]*l%P;
}

#define L 15
int b[L][NN];
#define M 32767
void blt2(int p, int l, int r, int d) {
  int lm = (P-((ll)l*M+1)%P)%P;
  if (r-l == 1) {
    b[d][p+0] = lm;
    b[d][p+1] = 1;
    return;
  }
  int m = (l+r+1)/2;
  int n = r-l+1;
  blt2(p, l+1, m, d+1);
  blt2(p+n, m, r, d+1);
  memcpy(b[d]+p, b[d+1]+p+n, sizeof(int)*n);
  if (d) {
    mul(b[d+1]+p, b[d]+p, n/2);
    for (int i = n-1; i; i--) {
      b[d][p+i] = ((ll)b[d][p+i]*lm + b[d][p+i-1])%P;
    }
    b[d][p+0] = (ll)b[d][p+0]*lm%P;
  }
}

int S[NN];
int c1[NN], c2[NN];
void eval(int p, int l, int r, int d) {
  // eval at lm
  int n = r-l+1;
  int lm = ((ll)l*M+1)%P;
  int s = 0;
  int t = 1;
  for (int i = 0; i < n; i ++) {
    s = (s+(ll)a[p+i]*t%P)%P;
    t = (ll)t*lm%P;
  }
  S[l] = s;
  if (r-l <= 100) {
    for (int c = l+1; c < r; c ++) {
      lm = ((ll)c*M+1)%P;
      s = 0;
      t = 1;
      for (int i = 0; i < n; i ++) {
        s = (s+(ll)a[p+i]*t%P)%P;
        t = (ll)t*lm%P;
      }
      S[c] = s;
    }
    return;
  }
  if (l == r-1) return;
  int m = (l+r+1)/2;
  
  mod(a+p, b[d+1]+p, c1, n, n/2);
  mod(a+p, b[d+1]+p+n, c2, n, n/2);
  memcpy(a+p, c1, sizeof(int)*(n/2));
  memcpy(a+p+n, c2, sizeof(int)*(n/2));
  eval(p, l+1, m, d+1);
  eval(p+n, m, r, d+1);
}
////////////////
  blt(a, 0, M);
  blt2(0, 0, M, 0);
  eval(0, 0, M, 0);
