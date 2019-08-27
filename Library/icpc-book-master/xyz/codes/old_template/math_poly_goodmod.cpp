///////////////////////////
//
// poly goodmod
//
///////////////////////////
// 7*17*2^23+1
#define P 998244353
// primitive root
#define PR 806045032
#define N 524288
// PR^(P/N)
#define PE 657165624

#define NN N+10

int prim() {
  while (true) {
    int x = rand()%(P-1)+1;
    if (pow(x, P/5) != 1 && pow(x, P/47) != 1 && pow(x, P/2) != 1) return x;
  }
  return -1;
}

int pe[NN];
int E[NN];

void fft(int n, int t, int* a) {
  for (int m = n; m >= 2; ) {
    int h = m/2;
    if (!t) {
      for (int i = 0; i < h; i ++)
        E[i] = pe[N/m*i];
    } else {
      E[0] = 1;
      for (int i = 1; i < h; i ++)
        E[i] = pe[N/m*(m-i)];
    }
    for (int j = 0; j < n; j += m)
      for (int i = 0; i < h; i ++) {
        int x = (a[j+i]-a[j+i+h]+P)%P;
        (a[j+i] += a[j+i+h]) %= P;
        a[j+i+h] = (ll)E[i]*x%P;
      }
    m = h;
  }
  int i = 0;
  for (int j = 1; j < n-1; j ++) {
    for (int k = n/2; k > (i^=k); k /= 2);
    if (j < i) swap(a[i], a[j]);
  }
}

int aa[NN];

void mul(int* a, int* b, int n) {
  memcpy(aa, a, sizeof(int)*n);
  memset(aa+n, 0, sizeof(int)*n);
  memset(b+n, 0, sizeof(int)*n);
  fft(n*2, 0, aa);
  fft(n*2, 0, b);
  for (int i = 0; i < n*2; i ++)
    b[i] = (ll)aa[i]*b[i]%P;
  fft(n*2, 1, b);
  int INVn = pow(n*2, P-2);
  for (int i = 0; i < n*2; i ++)
    b[i] = (ll)b[i]*INVn%P;
}

void inv(int* a, int* b, int n) {
  if (n == 1) {
    // b[0] = 1/a[0]
    b[0] = pow(a[0], P-2);
    return;
  }
  // have done inv(a, b, n/2)
  inv(a, b, n/2);
  memcpy(aa, a, sizeof(int)*n);
  memset(aa+n, 0, sizeof(int)*n);
  memset(b+n/2, 0, sizeof(int)*(n+n/2));
  fft(n*2, 0, aa);
  fft(n*2, 0, b);
  for (int i = 0; i < n*2; i ++)
    b[i] = (ll)b[i]*(2-(ll)aa[i]*b[i]%P+P)%P;
  fft(n*2, 1, b);
  int INVn = pow(n*2, P-2);
  for (int i = 0; i < n; i ++)
    b[i] = (ll)b[i]*INVn%P;
  memset(b+n, 0, sizeof(int)*n);
}

int I[NN];
int bb[NN];

void fln(int *a, int *b, int n) {
  inv(a, b, n);
  for (int i = 0; i < n-1; i ++)
    bb[i] = (ll)a[i+1]*(i+1)%P;
  mul(bb, b, n);
  for (int i = n-1; i; i--)
    b[i] = (ll)b[i-1]*I[i]%P;
  b[0] = 0;
  memset(b+n, 0, sizeof(int)*n);
}

int cc[NN];

void fexp(int *a, int *b, int n) {
  if (n == 1) {
    b[0] = 1;
    return;
  }
  fexp(a, b, n/2);
  memset(b+n/2, 0, sizeof(int)*(n/2));
  fln(b, cc, n);
  for (int i = 0; i < n; i ++)
    cc[i] = (a[i]-cc[i]+P)%P;
  cc[0] = (cc[0]+1)%P;
  mul(cc, b, n);
}

// solve b' = 1/2 a b^2 + 1
int r[NN], dd[NN], ee[N];
void ff(int* a, int *b, int n) {
  if (n == 1) {
    b[0] = 0;
    b[1] = 1;
    return;
  }
  ff(a, b, n/2);
  memset(b+n/2+1, 0, sizeof(int)*(n/2-1));
  memcpy(ee, b, sizeof(int)*n);
  mul(a, b, n);
  dd[0] = 0;
  for (int i = 1; i < n; i ++)
    dd[i] = (P-(ll)b[i-1]*I[i]%P)%P;
  fexp(dd, r, n);
  inv(r, dd, n);
  mul(ee, b, n);
  for (int i = 0; i < n; i ++)
    b[i] = (P-(ll)b[i]*I[2]%P)%P;
  b[0] = (b[0]+1)%P;
  mul(r, b, n);
  for (int i = n; i; i --)
    b[i] = (ll)b[i-1]*I[i]%P;
  b[0] = 0;
  int bn = b[n];
  mul(dd, b, n);
  // (b*r)[n] = bn
  for (int i = 1; i < n; i ++)
    bn = (bn - (ll)b[i]*r[n-i]%P+P)%P;
  b[n] = bn;
}
///////////////////////////////////////
  I[1] = 1;
  for (int i = 2; i < N; i ++)
    I[i] = (ll)i*(P/i)%P*(P/i)%P*I[P%i]%P*I[P%i]%P;

  pe[0] = 1;
  for (int i = 1; i < N; i ++) pe[i] = (ll)pe[i-1]*PE%P;
