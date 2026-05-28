#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);
using namespace std;
using lint = long long;
using pi = array<int, 2>;

struct strongly_connected {

    static const unsigned NIL = 0xFFFFFFu;
    struct Packed24 {
        vector<unsigned char> a;
        void clear() { a.clear(); }
        void free_mem() { vector<unsigned char>().swap(a); }
        void reserve(size_t n) { a.reserve(3 * n); }
        void assign(size_t n, unsigned v) {
            if (v == 0)
                a.assign(3 * n, 0);
            else if (v == NIL)
                a.assign(3 * n, 255);
            else {
                a.resize(3 * n);
                for (size_t i = 0; i < n; i++)
                    set((int)i, v);
            }
        }
        int size() const { return (int)(a.size() / 3); }
        bool empty() const { return a.empty(); }
        unsigned get(int i) const {
            size_t p = 3ull * i;
            return (unsigned)a[p] | ((unsigned)a[p + 1] << 8) | ((unsigned)a[p + 2] << 16);
        }
        void set(int i, unsigned v) {
            size_t p = 3ull * i;
            a[p] = v & 255;
            a[p + 1] = (v >> 8) & 255;
            a[p + 2] = (v >> 16) & 255;
        }
        void push(unsigned v) {
            a.push_back(v & 255);
            a.push_back((v >> 8) & 255);
            a.push_back((v >> 16) & 255);
        }
        unsigned back() const { return get(size() - 1); }
        unsigned pop() {
            unsigned v = back();
            a.resize(a.size() - 3);
            return v;
        }
    };
    Packed24 head, to, nxt, low, st, call;
    vector<int> comp;
    int Time, ncomps, piv;
    void init(int n) {
        head.assign(n, NIL);
        to.clear();
        nxt.clear();
        size_t cap = min<size_t>(NIL - 1, 2ull * n + 5);
        to.reserve(cap);
        nxt.reserve(cap);
        comp.clear();
        low.clear();
        st.clear();
        call.clear();
    }
    void add_edge(int s, int e) {
        unsigned id = to.size();
        to.push(e);
        nxt.push(head.get(s));
        head.set(s, id);
    }
    void start(int v) {
        ++Time;
        comp[v] = -Time;
        low.set(v, Time);
        st.push(v);
        call.push(v);
    }
    void get_scc(int n) {
        comp.assign(n, 0);
        low.assign(n, 0);
        st.clear();
        call.clear();
        st.reserve(n);
        call.reserve(n);
        Time = ncomps = 0;
        for (int root = 0; root < n; root++) {
            if (comp[root])
                continue;
            start(root);
            while (!call.empty()) {
                int v = call.back();
                unsigned e = head.get(v);
                if (e != NIL) {
                    head.set(v, nxt.get(e));
                    int w = to.get(e);
                    if (comp[w] == 0) {
                        start(w);
                    } else if (comp[w] < 0) {
                        unsigned cur = low.get(v);
                        unsigned dw = -comp[w];
                        if (dw < cur)
                            low.set(v, dw);
                    }
                } else {
                    call.pop();
                    unsigned lv = low.get(v);
                    if (lv == (unsigned)(-comp[v])) {
                        while (true) {
                            int x = st.pop();
                            comp[x] = ncomps + 1;
                            if (x == v)
                                break;
                        }
                        ncomps++;
                    }
                    if (!call.empty()) {
                        int p = call.back();
                        unsigned lp = low.get(p);
                        if (lv < lp)
                            low.set(p, lv);
                    }
                }
            }
        }
        for (int i = 0; i < n; i++) {
            comp[i] = ncomps - comp[i];
        }
        piv = ncomps;
        head.free_mem();
        to.free_mem();
        nxt.free_mem();
        low.free_mem();
        st.free_mem();
        call.free_mem();
    }

} scc;

struct twosat {
    strongly_connected scc;
    int n;
    void init(int _n) {
        scc.init(2 * _n);
        n = _n;
    }
    int NOT(int x) { return x >= n ? (x - n) : (x + n); }
    void add_edge(int x, int y) {
        if ((x >> 31) & 1)
            x = (~x) + n;
        if ((y >> 31) & 1)
            y = (~y) + n;
        x = NOT(x);
        scc.add_edge(x, y), scc.add_edge(NOT(y), NOT(x));
    }
    bool satisfy(bool *res) {
        scc.get_scc(2 * n);
        for (int i = 0; i < n; i++) {
            if (scc.comp[i] == scc.comp[NOT(i)])
                return 0;
            if (scc.comp[i] < scc.comp[NOT(i)])
                res[i] = 0;
            else
                res[i] = 1;
        }
        return 1;
    }
} twosat;
const int MAXN = 1010101;
int incl[MAXN];
bool res[2 * MAXN];
int main() {
    int N, M, K;
    scanf("%d%d%d", &N, &M, &K);
    twosat.init(2 * N);
    for (int i = 0; i < M; ++i) {
        int u, v;
        scanf("%d%d", &u, &v);
        u--;
        v--;
        twosat.add_edge(u, v);
    }
    int tp = N - 1;
    for (int i = 0; i < K; ++i) {
        int T;
        vector<int> v;
        scanf("%d", &T);
        v.resize(T);
        for (int j = 0; j < T; ++j) {
            scanf("%d", &v[j]);
            v[j]--;
            incl[v[j]] = i;
        }
        for (int i = 0; i < v.size(); ++i) {
            ++tp;
            twosat.add_edge(~v[i], ~tp);
            if (i == v.size() - 1)
                break;
            twosat.add_edge(tp + 1, ~tp);
            twosat.add_edge(tp + 1, ~v[i]);
        }
    }
    if (!twosat.satisfy(res)) {
        puts("NIE");
        return 0;
    }
    vector<int> ans(K);
    for (int i = 0; i < N; ++i) {
        if (res[i])
            ans[incl[i]] = i + 1;
    }
    // puts("");
    puts("TAK");
    for (int i = 0; i < K; ++i)
        printf("%d ", ans[i]);
    puts("");
    return 0;
}
