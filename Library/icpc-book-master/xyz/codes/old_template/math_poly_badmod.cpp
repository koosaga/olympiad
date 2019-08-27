///////////////////////////
//
// poly badmod
//
///////////////////////////
#define P 1000000007
#define N 131072
#define M 31622
const cp II(0,1);
cp E[N];
void fft(int n, db t, cp *a) {
  for (int m = n; m >= 2; t *= 2) {
    int h = m/2;
    for (int i = 0; i < h; i ++)
      E[i] = exp(i*t*II);
    for (int j = 0; j < n; j += m)
      for (int i = 0; i < h; i ++) {
        cp x = a[j+i]-a[j+i+h];
        a[j+i] += a[j+i+h];
        a[j+i+h] = E[i]*x;
      }
    m = h;
  }
  int i = 0;
  for (int j = 1; j < n-1; j ++) {
    for (int k = n/2; k > (i^=k); k /= 2);
    if (j < i) swap(a[i], a[j]);
  }
}

cp aa[N], bb[N], cc[N], dd[N];
cp s0[N], s1[N], s2[N];

void mul(int* a, int* b, int n) {
  for (int i = 0; i < n; i ++) {
    aa[i] = a[i]/M;
    bb[i] = a[i]%M;
    cc[i] = b[i]/M;
    dd[i] = b[i]%M;
  }
  memset(aa+n, 0, sizeof(cp)*n);
  memset(bb+n, 0, sizeof(cp)*n);
  memset(cc+n, 0, sizeof(cp)*n);
  memset(dd+n, 0, sizeof(cp)*n);
  fft(n*2, M_PI/n, aa);
  fft(n*2, M_PI/n, bb);
  fft(n*2, M_PI/n, cc);
  fft(n*2, M_PI/n, dd);
  for (int i = 0; i < n*2; i ++) {
    s0[i] = aa[i]*cc[i];
    s1[i] = aa[i]*dd[i]+bb[i]*cc[i];
    s2[i] = bb[i]*dd[i];
  }
  fft(n*2, -M_PI/n, s0);
  fft(n*2, -M_PI/n, s1);
  fft(n*2, -M_PI/n, s2);
  for (int i = 0; i < n; i ++) {
    b[i] = ((ll)(s0[i].real()/(n*2)+0.5)*M%P*M%P +
    (ll)(s1[i].real()/(n*2)+0.5)*M%P + 
    (ll)(s2[i].real()/(n*2)+0.5)%P)%P;
  }
}

int c[N];

void inv(int* a, int* b, int n) {
  if (n == 1) {
    b[0] = pow(a[0], P-2);
    return;
  }
  inv(a, b, n/2);
  memcpy(c, b, sizeof(int)*(n/2));
  //memset(c+n/2, 0, sizeof(int)*(n/2));
  mul(a, c, n);
  for (int i = 0; i < n; i ++)
    c[i] = (P-c[i])%P;
  c[0] = (2+c[0])%P;
  mul(c, b, n);
}
