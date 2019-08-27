///////////////////////////
//
// 最小树形图
//
///////////////////////////

#include <cstdio>
#include <algorithm>
#include <math.h>
#include <string.h>
#include <cstdlib>
#include <vector>
using namespace std;

#define M 41000
#define INF 1e18
int v, n, m, len, len1, zhan[M], to[M], s1[M], s2[M], prep[M];
long long l[M], mincost[M];
bool used[M], cir[M], in[M];

void init() {
  len = 0;
}

void add(int x, int y, long long z) {
  len++;
  s1[len] = x;
  s2[len] = y;
  l[len] = z;
}

void dfs(int k) {
  zhan[++len1] = k;
  used[k] = in[k] = true;
  if (!used[prep[k]])  dfs(prep[k]);
}

void dfs1(int v) {
  if (used[v])
    return ;
  used[v] = true;
  for (int i = 1; i <= len; i++)
    if (s1[i] == v)
      dfs1(s2[i]);
}

long long calc(int root, int v, int len) {
  long long cost = 0;
  memset(prep, 0, sizeof prep);
  for (int i = 1; i <= v; i++)
    used[i] = false;
  dfs1(root);
  for (int i = 1; i <= v; i++)
    if (!used[i])
      return -1;
  for (int i = 1; i <= v; i++)
    to[i] = 0;
  while (true) {
    for (int i = 1; i <= v; i++)
      mincost[i] = INF;
    for (int i = 1; i <= len; i++)  if (s1[i] != s2[i] && l[i] < mincost[s2[i]] && s2[i] != root)  mincost[s2[i]] = l[i], prep[s2[i]] = s1[i];
    for (int i = 1; i <= v; i++)
      used[i] = false, cir[i] = false;
    bool Find = false;
    to[root] = root;
    used[0] = true;
    for (int i = 1; i <= v; i++) 
      if (i != root && mincost[i] < INF && !used[i]) {
        len1 = 0;
        dfs(i);
        if (in[prep[zhan[len1]]]) {
          Find = true;
          zhan[len1 + 1] = 0;
          int j; 
          for (j = len1; zhan[j + 1] != prep[zhan[len1]]; j--) {
            to[zhan[j]] = zhan[len1];
            cost += mincost[zhan[j]];
          }
          for (; j; j--)  to[zhan[j]] = zhan[j];
          cir[zhan[len1]] = true;
        }else for (int j = 1; j <= len1; j++) to[zhan[j]] = zhan[j];
        for (int j = 1; j <= len1; j++) in[zhan[j]] = false;
      }
    if (!Find) {
      for (int i = 1; i <= v; i++)
        if (i != root && mincost[i] < INF) {
          cost += mincost[i];
        }
      return cost;
    }
    for (int i = 1; i <= len; i++) {
      if (cir[to[s2[i]]]) l[i] -= mincost[s2[i]];
      s1[i] = to[s1[i]];
      s2[i] = to[s2[i]];
    }
  }
  return cost;
}

int main() {
  while (scanf("%d%d", &n, &m) != -1) {
    init();
    for (int i = 1; i <= m; i++) {
      int a, b, c;
      scanf("%d%d%d", &a, &b, &c);
      a++; b++;
      add(a, b, 10000LL * c);
    }
    for (int i = 1; i <= n; i++)
      add(n + 1, i, 1e12 + i);
    long long ans = calc(n + 1, n + 1, m + n);
    if (ans == -1 || ans >= 2e12)
      printf("impossible\n");
    else
      printf("%lld %lld\n", (ans - (long long) 1e12) / 10000, ans % 10000 - 1);
    puts("");
  }
}
