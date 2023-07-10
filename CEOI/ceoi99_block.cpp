#include <bits/stdc++.h>
using namespace std;

int n, m, a[100005], b[100005], cand[200005];

int main() {
    scanf("%d %d", &n, &m);
    map<int, int> m1, m2;
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
        cand[i] = a[i];
        m1[a[i]]++;
    }
    for (int i = 0; i < m; i++) {
        scanf("%d", &b[i]);
        cand[i + n] = b[i];
        m2[b[i]]++;
    }
    auto cmp = [&](const int &a, const int &b) { return a > b; };
    sort(a, a + n, cmp);
    sort(b, b + m, cmp);
    sort(cand, cand + n + m, cmp);
    int rhi = 0, rlo = 0, ca = 0, cb = 0;
    for (int i = 0; i < n + m; i++) {
        int hi = cand[i] - cand[i + 1];
        while (ca < n && a[ca] >= cand[i])
            ca++;
        while (cb < m && b[cb] >= cand[i])
            cb++;
        if (1ll * ca * cb == 0) {
            puts("-1");
            return 0;
        }
        rhi += hi * (ca * cb);
        if (cand[i] != cand[i + 1]) {
            rlo += cand[i] * max(m1[cand[i]], m2[cand[i]]);
        }
    }
    printf("%d %d", rlo, rhi);
}