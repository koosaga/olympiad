#include <stdio.h>
#include <vector>
#include <queue>
#include <algorithm>
#include <iostream>
#include <string>
#include <bitset>
#include <map>
#include <set>
#include <tuple>
#include <string.h>
#include <math.h>
#include <random>
#include <functional>
#include <assert.h>
#include <math.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using pi = pair<int, int>;
using lint = long long;
const int MAXN = 100005;

int B, L, D;
int score[MAXN];

struct output_buffer {
    vector<vector<int>> v;
    void print(vector<int> w) {
        v.push_back(w);
    }
    void flush() {
        cout << sz(v) / 2 << endl;
        for (auto &i : v) {
            for (auto &j : i) {
                printf("%d ", j);
            }
            puts("");
        }
    }
}buf;

struct library {
    int signup, speed, id;
    vector<int> books;
}a[MAXN];

bool vis[MAXN];
bool procing[MAXN];

int extract_idx(int dates) {
    pair<double, int> ret(-1, -1);
    for (int i = 0; i<L; i++) {
        if (vis[i] || dates <= a[i].signup) continue;
        sort(all(a[i].books), [&](const int &a, const int &b) {
            return score[a] > score[b];
        });
        int siz = (int)min(1ll * (dates - a[i].signup) * a[i].speed, 1ll * sz(a[i].books));
        lint accm = 0;
        for (int j = 0; j < siz; j++)
            accm += score[a[i].books[j]];
        ret = max(ret, make_pair(1.0 * accm / pow(a[i].signup, 0.85), i));
    }
    return ret.second;
}
int main() {
    cin >> B >> L >> D;
    for (int i = 0; i<B; i++) cin >> score[i];
    for (int i = 0; i<L; i++) {
        int siz;
        cin >> siz >> a[i].signup >> a[i].speed;
        a[i].id = i;
        a[i].books.resize(siz);
        for (auto &j : a[i].books) {
            scanf("%d", &j);
        }
    }
    int tick = 0;
    while (tick < D) {
        int i = extract_idx(D - tick);
        if (i == -1) break;
        vis[i] = 1;
        tick += a[i].signup;
        int siz = (int)min(1ll * (D - tick) * a[i].speed, 1ll * sz(a[i].books));
        assert(siz > 0);
        buf.print({ a[i].id, siz });
        a[i].books.resize(siz);
        buf.print(a[i].books);
        for (auto &j : a[i].books) {
            score[j] = 0;
        }
    }
    buf.flush();
}
