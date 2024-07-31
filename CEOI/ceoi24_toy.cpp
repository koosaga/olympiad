#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<int, 2>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);
const int MAXN = 1557;

int n, m, p, q;

char str[MAXN][MAXN];
int L[MAXN][MAXN], R[MAXN][MAXN];
int U[MAXN][MAXN], D[MAXN][MAXN];
bool vis[MAXN][MAXN];

bool ok(int x, int y) { return x >= 0 && x < n && y >= 0 && y < m && str[x][y] != 'X'; }

void dfs(int x, int y) {
    if (vis[x][y])
        return;
    vis[x][y] = 1;
    if (ok(x - 1, y) && min(R[x - 1][y], R[x][y]) - max(L[x - 1][y], L[x][y]) + 1 >= q)
        dfs(x - 1, y);
    if (ok(x + 1, y) && min(R[x + 1][y], R[x][y]) - max(L[x + 1][y], L[x][y]) + 1 >= q)
        dfs(x + 1, y);
    if (ok(x, y - 1) && min(D[x][y - 1], D[x][y]) - max(U[x][y - 1], U[x][y]) + 1 >= p)
        dfs(x, y - 1);
    if (ok(x, y + 1) && min(D[x][y + 1], D[x][y]) - max(U[x][y + 1], U[x][y]) + 1 >= p)
        dfs(x, y + 1);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    pi s, e;
    cin >> m >> n >> q >> p;
    {
        int z;
        cin >> z;
        cin >> s[0] >> s[1];
        cin >> z;
    }
    for (int i = 0; i < n; i++) {
        cin >> str[i];
        for (int j = 0; j < m; j++) {
            if (str[i][j] == '*') {
                e = pi{i, j};
                str[i][j] = '.';
            }
        }
    }
    for (int i = 0; i < n; i++) {
        int d = 0;
        for (int j = 0; j < m; j++) {
            if (str[i][j] == 'X')
                d = j + 1;
            else
                L[i][j] = d;
        }
        d = m;
        for (int j = m - 1; j >= 0; j--) {
            if (str[i][j] == 'X')
                d = j - 1;
            else
                R[i][j] = d;
        }
    }
    for (int j = 0; j < m; j++) {
        int d = 0;
        for (int i = 0; i < n; i++) {
            if (str[i][j] == 'X')
                d = i + 1;
            else
                U[i][j] = d;
        }
        d = n;
        for (int i = n - 1; i >= 0; i--) {
            if (str[i][j] == 'X')
                d = i - 1;
            else
                D[i][j] = d;
        }
    }
    dfs(s[0], s[1]);
    cout << (vis[e[0]][e[1]] ? "YES" : "NO") << "\n";
}