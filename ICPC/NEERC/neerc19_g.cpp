#include <stdio.h> 
#include <stdlib.h>
#include <string.h> 
#include <memory.h> 
#include <math.h> 
#include <assert.h> 
#include <stack> 
#include <queue> 
#include <map> 
#include <set> 
#include <string> 
#include <algorithm> 
#include <iostream> 
#include <functional>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using llf = long double;

struct lint {
  uint64_t a, b;
  lint() : a(0), b(0) {}
  lint(uint64_t val) : a(val), b(0) {}

  lint operator -(const lint& other) const {
    lint result;
    result.a = a - other.a;
    result.b = b - other.b - (result.a > a ? 1 : 0);
    return result;
  }

  lint operator +(const lint& other) const {
    lint result;
    result.a = a + other.a;
    result.b = b + other.b + (result.a < a ? 1 : 0);
    return result;
  }

  lint& operator +=(const lint& other) {
    lint tmp = *this + other;
    *this = tmp;
    return *this;
  }
  lint& operator -=(const lint& other) {
    lint tmp = *this - other;
    *this = tmp;
    return *this;
  }

  long double approx() {
    long double v = a;
    long double w = b;
    w *= ((1ll << 62) - 1 + (long double)1.0) * 4;
    return v + w;
  }
};

const int MAXN = 105;
const int MAXS = 10005;

int n, x;
int a[MAXN];

lint bino[MAXN][MAXN];
lint sum[MAXN][MAXS];

void solve() {
  cin >> n;
  cin >> x;
  for (int i = 0; i < n; i++) {
    cin >> a[i];
  }
  for (int i = 0; i <= n; i++) {
    bino[i][0] = n;
    for (int j = 1; j <= i; j++) {
      bino[i][j] = bino[i - 1][j] + bino[i - 1][j - 1];
    }
  }
  llf ret = 0;
  sum[0][0] = 1;
  int tot = 0, cnt = 0;
  for (int j = 0; j<n; j++) {
    for (int k = cnt; k >= 0; k--) {
      for (int l = tot; l >= 0; l--) {
        sum[k + 1][l + a[j]] += sum[k][l];
      }
    }
    tot += a[j];
    cnt += 1;
  }
  for (int i = 0; i<n; i++) {
    for (int k = 0; k<n; k++) {
      for (int l = 0; l <= tot - a[i]; l++) {
        sum[k + 1][l + a[i]] -= sum[k][l];
      }
    }
    for (int j = 0; j<n; j++) {
      for (int k = 0; k <= tot - a[i]; k++) {
        lint p = sum[j][k];
        lint q = bino[n - 1][j];
        llf cost = a[i];
        if (k + a[i] >= 1.0 * x * (n + j + 1) / 2) {
          cost = x / 2.0 + x * n / ((j + 1) * 2.0);
        }
        ret += cost * p.approx() / q.approx();
      }
    }
    for (int k = n - 1; k >= 0; k--) {
      for (int l = tot - a[i]; l >= 0; l--) {
        sum[k + 1][l + a[i]] += sum[k][l];
      }
    }
  }
  printf("%.30f\n", (double)ret);
}
int main() {
  solve();
}
