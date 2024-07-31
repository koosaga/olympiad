#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
const int mod = 1e9 + 7;
const int MAXN = 1005;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);

char str[MAXN][MAXN];
int qr[MAXN * MAXN][4];
int n, m;

bitset<MAXN> L[MAXN * MAXN], R[MAXN * MAXN];

bitset<MAXN> dp[MAXN];
void dnc(int l, int r, vector<int> queries) {
    if (sz(queries) == 0)
        return;
    int t = (l + r) / 2;
    vector<int> LL, RR;
    vector<array<int, 3>> lq, rq;
    for (auto &qidx : queries) {
        if (qr[qidx][3] < t)
            LL.push_back(qidx);
        else if (qr[qidx][1] > t)
            RR.push_back(qidx);
        else {
            lq.push_back({qr[qidx][1], qr[qidx][0], qidx});
            rq.push_back({qr[qidx][3], qr[qidx][2], qidx});
        }
    }
    dnc(l, t, LL);
    dnc(t + 1, r, RR);
    sort(all(rq));
    sort(all(lq));
    reverse(all(lq));
    for (int i = 0; i < n; i++) {
        dp[i] = 0;
        if (str[i][t] == '.')
            dp[i].set(i);
    }
    int p = 0;
    for (int j = t; j < r; j++) {
        for (int i = 0; i < n; i++) {
            if (str[i][j] == '#')
                dp[i] = 0;
            else {
                if (i)
                    dp[i] |= dp[i - 1];
            }
            while (p < sz(rq) && pi{j, i} == pi{rq[p][0], rq[p][1]}) {
                R[rq[p][2]] = dp[i];
                p++;
            }
        }
    }
    p = 0;
    for (int i = 0; i < n; i++) {
        dp[i] = 0;
        if (str[i][t] == '.')
            dp[i].set(i);
    }
    for (int j = t; j >= l; j--) {
        for (int i = n - 1; i >= 0; i--) {
            if (str[i][j] == '#')
                dp[i] = 0;
            else {
                if (i + 1 < n)
                    dp[i] |= dp[i + 1];
            }
            while (p < sz(lq) && pi{j, i} == pi{lq[p][0], lq[p][1]}) {
                L[lq[p][2]] = dp[i];
                p++;
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int m, q;
    cin >> n >> m >> q;
    for (int i = 0; i < n; i++)
        cin >> str[i];
    for (int i = 0; i < q; i++) {
        for (int j = 0; j < 4; j++) {
            cin >> qr[i][j];
            qr[i][j]--;
        }
    }
    vector<int> idx;
    for (int i = 0; i < q; i++) {
        if (qr[i][0] <= qr[i][2] && qr[i][1] <= qr[i][3])
            idx.push_back(i);
    }
    dnc(0, m, idx);
    for (int i = 0; i < q; i++)
        cout << ((L[i] & R[i]).any() ? "YES" : "NO") << "\n";
}