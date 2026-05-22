#include <algorithm>
#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;
typedef pair<int, int> pi;

struct disj {
    int pa[100005];
    void init(int n) {
        for (int i = 0; i <= n; i++)
            pa[i] = i;
    }
    int find(int x) { return pa[x] = (pa[x] == x ? x : find(pa[x])); }
    bool uni(int p, int q) {
        p = find(p);
        q = find(q);
        if (p == q)
            return 0;
        pa[q] = p;
        find(q);
        return 1;
    }
} disj1, disj2;

int n, m;
vector<int> gph[100005];
int *low, *dfn;
int piv;

void dfs(int x, int p) {
    dfn[x] = low[x] = ++piv;
    for (auto &y : gph[x]) {
        if (p == y)
            continue;
        if (!dfn[y]) {
            dfs(y, x);
            low[x] = min(low[x], low[y]);
            if (low[y] > dfn[x]) {
                int z = upper_bound(gph[x].begin(), gph[x].end(), y) - lower_bound(gph[x].begin(), gph[x].end(), y);
                if (z == 1)
                    printf("%d %d\n", x, y);
            }
        } else
            low[x] = min(low[x], dfn[y]);
    }
}
char str[15];

int main() {
    scanf("%d %d\n", &n, &m);
    disj1.init(n);
    disj2.init(n);
    while (m--) {
        int u = 0, v = 0;
        fgets(str, 15, stdin);
        int pos = 0;
        while (str[pos] != ' ') {
            u = (10 * u) + (str[pos] - '0');
            pos++;
        }
        pos++;
        while (str[pos] != '\n' && str[pos]) {
            v = (10 * v) + (str[pos] - '0');
            pos++;
        }
        if (disj1.uni(u, v)) {
            gph[u].push_back(v);
            gph[v].push_back(u);
        } else if (disj2.uni(u, v)) {
            gph[u].push_back(v);
            gph[v].push_back(u);
        }
    }
    low = disj1.pa;
    dfn = disj2.pa;
    for (int i = 1; i <= n; i++)
        low[i] = dfn[i] = 0;
    for (int i = 1; i <= n; i++)
        sort(gph[i].begin(), gph[i].end());
    for (int i = 1; i <= n; i++) {
        if (!dfn[i])
            dfs(i, -1);
    }
}