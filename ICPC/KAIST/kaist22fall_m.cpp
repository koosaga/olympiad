#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = pair<lint, lint>;
#define sz(a) ((int)(a).size())
#define all(a) (a).begin(), (a).end()
const int MAXN = 10005;

struct mcmf
{
    struct edg
    {
        int pos, cap, rev;
        lint cost;
    };
    vector<edg> gph[MAXN];
    void clear()
    {
        for (int i = 0; i < MAXN; i++)
            gph[i].clear();
    }
    void add_edge(int s, int e, int x, lint c)
    {
        gph[s].push_back({e, x, sz(gph[e]), c});
        gph[e].push_back({s, 0, sz(gph[s]) - 1, -c});
    }
    lint dist[MAXN];
    int pa[MAXN], pe[MAXN], inque[MAXN];
    bool spfa(int src, int sink, int n)
    {
        memset(dist, 0x3f, sizeof(dist[0]) * n);
        memset(inque, 0, sizeof(inque[0]) * n);
        queue<int> que;
        que.push(src);
        dist[src] = 0;
        inque[src] = 1;
        bool ok = 0;
        while (sz(que))
        {
            int x = que.front();
            que.pop();
            if (x == sink)
                ok = 1;
            inque[x] = 0;
            for (int i = 0; i < sz(gph[x]); i++)
            {
                edg e = gph[x][i];
                if (e.cap > 0 && dist[e.pos] > dist[x] + e.cost)
                {
                    dist[e.pos] = dist[x] + e.cost;
                    pa[e.pos] = x;
                    pe[e.pos] = i;
                    if (!inque[e.pos])
                    {
                        inque[e.pos] = 1;
                        que.push(e.pos);
                    }
                }
            }
        }
        return ok;
    }
    lint match(int src, int sink, int n)
    {
        lint ret = 0;
        while (spfa(src, sink, n))
        {
            lint cap = 1e18;
            for (int pos = sink; pos != src; pos = pa[pos])
            {
                cap = min(cap, (lint)gph[pa[pos]][pe[pos]].cap);
            }
            ret += cap * dist[sink];
            for (int pos = sink; pos != src; pos = pa[pos])
            {
                int rev = gph[pa[pos]][pe[pos]].rev;
                gph[pa[pos]][pe[pos]].cap -= cap;
                gph[pos][rev].cap += cap;
            }
        }
        return ret;
    }
} mcmf;

int main()
{

    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n, m;
    cin >> n >> m;
    vector<vector<int>> p(n, vector<int>(m));
    vector<vector<int>> w(n, vector<int>(m));
    lint ret = 0;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            cin >> p[i][j];
            if (i)
                ret += p[i - 1][j] * p[i][j];
            if (j)
                ret += p[i][j - 1] * p[i][j];
        }
    }
    auto P = [&](int x, int y)
    {
        return x * m + y + 1;
    };
    auto X = [&](int x, int y)
    {
        return n * m + 1 + x * m + y;
    };
    auto Y = [&](int x, int y)
    {
        return 2 * n * m + 1 + x * m + y;
    };
    int Z = 3 * n * m + 10;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            cin >> w[i][j];
            mcmf.add_edge(0, P(i, j), 4 - w[i][j], 0);
        }
    }
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (i)
                mcmf.add_edge(P(i, j), X(i - 1, j), 1, 0);
            if (i + 1 < n)
                mcmf.add_edge(P(i, j), X(i, j), 1, 0);
            if (j)
                mcmf.add_edge(P(i, j), Y(i, j - 1), 1, 0);
            if (j + 1 < m)
                mcmf.add_edge(P(i, j), Y(i, j), 1, 0);
        }
    }
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (i)
            {
                int cost = p[i - 1][j] * p[i][j];
                mcmf.add_edge(X(i - 1, j), Z, 1, -cost);
            }
            if (j)
            {
                int cost = p[i][j] * p[i][j - 1];
                mcmf.add_edge(Y(i, j - 1), Z, 1, -cost);
            }
        }
    }
    cout << ret + mcmf.match(0, Z, Z + 1) << "\n";
}