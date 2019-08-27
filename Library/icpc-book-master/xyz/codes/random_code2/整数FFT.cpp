/*
1004535809 = 2 ^ 21 * 479 + 1
50000000001507329 =  2^18*59*3232794293 + 1
*/
#include <cstdio>
#include <memory.h>
using namespace std;
#define N 140000
int n, i, s, a[N], b[N], c[N], d[N], ans[N], x[N], w[N];
#define P 1004535809
#define G 3
int Pow(int x, int y){
    int i, ans = 1;
    for (i = 1; i <= y; i *= 2, x = 1LL * x * x % P) if (y & i)  ans = 1LL * ans * x % P;
    return ans;
}
void DFT(int *a, int n){
    int m, i, d, p, q;
    for (m = 1; (1 << m) <= n; m++){
        for (i = 0; i < (n >> m); i++)
        for (q = 0, d = p = i; d < n; q += (n >> m), d += (n >> (m - 1)), p += (n >> m)){
            x[p] = (1LL * a[d + (n >> m)] * w[q] + a[d]) % P;
            x[p + n / 2] = (1LL * a[d + (n >> m)] * w[q + n / 2] + a[d]) % P;
        }
        for (i = 0; i < n; i++) a[i] = x[i];
    }
}

void DFT1(int *a, int n){
    int m, i, d, p, q;
    for (m = 1; (1 << m) <= n; m++){
        for (i = 0; i < (n >> m); i++)
        for (q = 0, d = p = i; d < n; q += (n >> m), d += (n >> (m - 1)), p += (n >> m)){
            x[p] = (1LL * a[d + (n >> m)] * w[n - q] + a[d]) % P;
            x[p + n / 2] = (1LL * a[d + (n >> m)] * w[n / 2 - q] + a[d]) % P;
        }
        for (i = 0; i < n; i++) a[i] = x[i];
    }
}
int main(){
    scanf("%d", &n);
    for (i = 1; i <= n; i++){
        scanf("%d", &s);
        a[s + 20000]++;
    }
    n = 131072;
    for (i = 0; i <= n; i++)    w[i] = Pow(G, (P - 1) / n * i);//注意要到n
    memcpy(b, a, sizeof(b));
    DFT(b, n);
    for (i = 0; i < n; i++) ans[i] = 1LL * b[i] * b[i] % P * b[i] % P;
    DFT1(ans, n);
    for (s = Pow(n, P - 2), i = 0; i < n; i++)  ans[i] = 1LL * ans[i] * s % P;
    for (i = 0; i <= 40000; i++)    c[2 * i] = a[i];
    DFT(c, n);
    for (i = 0; i < n; i++) d[i] = 1LL * b[i] * c[i] % P;
    DFT1(d, n);
    for (i = 0; i < n; i++) d[i] = 1LL * d[i] * s % P;
    for (i = 0; i < n; i++) ans[i] -= 3 * d[i];
    for (i = 0; i <= 40000; i++)    ans[i * 3] += 2 * a[i];
    for (s = Pow(6, P - 2), i = 0; i < n; i++)  ans[i] = 1LL * ans[i] * s % P;
    for (i = 0; i < n; i++)
    if ((ans[i] % P + P) % P != 0)  printf("%d : %d\n", i - 60000, (ans[i] % P + P) % P);
}