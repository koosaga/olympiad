#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using llf = long double;
using pi = array<int, 2>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
const int MAXN = 1000;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
lint randint(lint lb, lint ub) { return uniform_int_distribution<lint>(lb, ub)(rng); }

int p[MAXN], n, k;
lint hashes[MAXN];

void recurse(int parent, vector<vector<int>> inords) {
    if (sz(inords[0]) == 1) {
        p[inords[0][0]] = parent;
        return;
    }
    lint totHash = 0;
    for (auto &x : inords[0])
        totHash ^= hashes[x];
    vector<lint> repHash(n, -1), mosoon(n);
    auto upload = [&](int v, lint z) {
        if (z == 0) {
            mosoon[v] = 1;
            return;
        }
        if (repHash[v] != -1 && repHash[v] != z) {
            mosoon[v] = 1;
        } else {
            repHash[v] = z;
        }
    };
    for (auto &x : inords) {
        lint L = 0;
        for (auto &y : x) {
            lint R = (L ^ hashes[y] ^ totHash);
            upload(y, min(L, R));
            L ^= hashes[y];
        }
    }
    int root = -1;
    for (auto &x : inords[0]) {
        if (mosoon[x] == 0) {
            root = x;
        }
    }
    assert(root != -1);
    p[root] = parent;
    vector<vector<int>> inordL, inordR;
    for (auto &x : inords) {
        vector<int> L, R;
        int f = find(all(x), root) - x.begin();
        int minL = 1e9, minR = 1e9;
        for (int j = 0; j < f; j++) {
            L.push_back(x[j]);
            minL = min(minL, x[j]);
        }
        for (int j = f + 1; j < sz(x); j++) {
            R.push_back(x[j]);
            minR = min(minR, x[j]);
        }
        if (minL < minR) {
            swap(minL, minR);
            swap(L, R);
        }
        inordL.push_back(L);
        inordR.push_back(R);
    }
    if (sz(inordL[0]))
        recurse(root, inordL);
    if (sz(inordR[0]))
        recurse(root, inordR);
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cout.precision(69);
    cin >> n >> k;
    vector<vector<int>> inords(k);
    for (auto &x : inords) {
        x.resize(n);
        for (auto &y : x)
            cin >> y, y--;
    }
    for (int i = 0; i < n; i++)
        hashes[i] = randint(0, (1ll << 62) - 1);
    recurse(-1, inords);
    for (int i = 0; i < n; i++) {
        if (p[i] == -1)
            cout << "-1 ";
        else
            cout << p[i] + 1 << " ";
    }
}