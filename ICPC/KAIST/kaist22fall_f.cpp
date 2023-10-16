#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = pair<lint, lint>;
#define sz(a) ((int)(a).size())
#define all(a) (a).begin(), (a).end()
const int mod = 998244353;
const int MAXN = 2005;

vector<pi> gph[MAXN];
lint dp[MAXN][MAXN][3];
int sz[MAXN];

void solve(int x, int p)
{
    sz[x] = 1;
    dp[x][0][0] = dp[x][0][1] = dp[x][0][2] = 0;
    for (auto &[w, y] : gph[x])
    {
        if (y != p)
        {
            solve(y, x);
            for (int j = 0; j <= sz[y]; j++)
            {
                dp[y][j][1] += w;
            }
            for (int j = 1; j <= sz[y]; j++)
            {
                dp[y][j][0] = max(dp[y][j][0], dp[y][j - 1][2] + w);
            }
            lint nxt[MAXN][3];
            for (int i = 0; i < MAXN; i++)
            {
                for (int j = 0; j < 3; j++)
                {
                    nxt[i][j] = -1e18;
                }
            }
            for (int a = 0; a <= sz[x]; a++)
            {
                for (int b = 0; b <= sz[y]; b++)
                {
                    for (int p = 0; p <= 2; p++)
                    {
                        for (int q = 0; p + q <= 2; q++)
                        {
                            nxt[a + b][p + q] = max(nxt[a + b][p + q], dp[x][a][p] + dp[y][b][q]);
                        }
                    }
                }
            }
            sz[x] += sz[y];
            for (int i = 0; i <= sz[x]; i++)
            {
                for (int j = 0; j < 3; j++)
                {
                    dp[x][i][j] = nxt[i][j];
                }
            }
        }
    }
    for (int i = 0; i <= sz[x]; i++)
    {
        for (int j = 1; j < 3; j++)
        {
            dp[x][i][j] = max(dp[x][i][j], dp[x][i][j - 1]);
        }
    }
}
int main()
{
    int n, k;
    cin >> n >> k;
    for (int i = 0; i < n - 1; i++)
    {
        int u, v, w;
        cin >> u >> v >> w;
        gph[u].emplace_back(w, v);
        gph[v].emplace_back(w, u);
    }
    for (int i = 0; i < MAXN; i++)
    {
        for (int j = 0; j < MAXN; j++)
        {
            for (int k = 0; k < 3; k++)
            {
                dp[i][j][k] = -1e18;
            }
        }
    }
    solve(1, 0);
    lint cur = 0;
    for (int i = 0; i <= k; i++)
    {
        cur = max(cur, dp[1][i][2]);
        cout << cur << " ";
    }
}