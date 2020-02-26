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
const int MAXN = 105005;
#include <chrono>
using namespace std;
long long seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
unsigned int rx = seed, ry = seed >> 12, rz = seed >> 24;
inline unsigned int r()
{
    unsigned int t;
    rx ^= rx << 16; rx ^= rx >> 5; rx ^= rx << 1;
    t = rx; rx = ry; ry = rz; rz = t ^ rx ^ ry;
    return t;
}
int range(int a, int b)
{
    return a + r() % (b - a + 1);
}
namespace MCMF{
    struct edg{ int pos, cap, rev, cost; };
    vector<edg> gph[MAXN];
    void clear(){ for (int i = 0; i < MAXN; i++) gph[i].clear(); }
    void add_edge(int s, int e, int x, int c){
        gph[s].push_back({ e, x, (int)gph[e].size(), c });
        gph[e].push_back({ s, 0, (int)gph[s].size() - 1, -c });
    }
    int phi[MAXN], inque[MAXN], dist[MAXN];
    void prep(int src, int sink){
        memset(phi, 0x3f, sizeof(phi));
        memset(dist, 0x3f, sizeof(dist));
        queue<int> que;
        que.push(src);
        inque[src] = 1;
        while (!que.empty()){
            int x = que.front();
            que.pop();
            inque[x] = 0;
            for (auto &i : gph[x]){
                if (i.cap > 0 && phi[i.pos] > phi[x] + i.cost){
                    phi[i.pos] = phi[x] + i.cost;
                    if (!inque[i.pos]){
                        inque[i.pos] = 1;
                        que.push(i.pos);
                    }
                }
            }
        }
        for (int i = 0; i < MAXN; i++){
            for (auto &j : gph[i]){
                if (j.cap > 0) j.cost += phi[i] - phi[j.pos];
            }
        }
        priority_queue<pi, vector<pi>, greater<pi> > pq;
        pq.push(pi(0, src));
        dist[src] = 0;
        while (!pq.empty()){
            auto l = pq.top();
            pq.pop();
            if (dist[l.second] != l.first) continue;
            for (auto &i : gph[l.second]){
                if (i.cap > 0 && dist[i.pos] > l.first + i.cost){
                    dist[i.pos] = l.first + i.cost;
                    pq.push(pi(dist[i.pos], i.pos));
                }
            }
        }
    }
    bool vis[MAXN];
    int ptr[MAXN];
    int dfs(int pos, int sink, int flow){
        vis[pos] = 1;
        if (pos == sink) return flow;
        for (; ptr[pos] < gph[pos].size(); ptr[pos]++){
            auto &i = gph[pos][ptr[pos]];
            if (!vis[i.pos] && dist[i.pos] == i.cost + dist[pos] && i.cap > 0){
                int ret = dfs(i.pos, sink, min(i.cap, flow));
                if (ret != 0){
                    i.cap -= ret;
                    gph[i.pos][i.rev].cap += ret;
                    return ret;
                }
            }
        }
        return 0;
    }
    int match(int src, int sink, int sz){
        prep(src, sink);
        for (int i = 0; i < sz; i++) dist[i] += phi[sink] - phi[src];
        int ret = 0;
        while (true){
            memset(ptr, 0, sizeof(ptr));
            memset(vis, 0, sizeof(vis));
            int tmp = 0;
            while ((tmp = dfs(src, sink, 1e9))){
                ret += dist[sink] * tmp;
                memset(vis, 0, sizeof(vis));
            }
            tmp = 1e9;
            for (int i = 0; i < sz; i++){
                if (!vis[i]) continue;
                for (auto &j : gph[i]){
                    if (j.cap > 0 && !vis[j.pos]){
                        tmp = min(tmp, (dist[i] + j.cost) - dist[j.pos]);
                    }
                }
            }
            if (tmp > 1e9 - 200) break;
            for (int i = 0; i < sz; i++){
                if (!vis[i]) dist[i] += tmp;
            }
        }
        return ret;
    }
};
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
}buf, pbuf;
struct library {
    int signup, speed, id;
    vector<int> books;
}a[MAXN];
bool chk[100100];
struct set{
    bool in[100100]; int rev[100100];
    vector<int> con;
    void push(int x){
        if (in[x]) return;
        in[x] = true;
        rev[x] = con.size();
        con.push_back(x);
    }
    void pop(int x){
        if (!in[x]) return;
        in[x] = false;
        if (con.back() != x){
            int i = con.back();
            rev[i] = rev[x];
            con[rev[i]] = i;
        }
        con.pop_back();
    }
    int rd(){
        if (con.empty()) return -1;
        return con[range(1, con.size()) - 1];
    }
}rlib;
int main() {
    freopen ("e_so_many_books.txt", "r", stdin);
    cin >> B >> L >> D;
    for (int i = 0; i < B; i++){
        cin >> score[i];
    }
    for (int i = 0; i < L; i++) {
        int siz;
        cin >> siz >> a[i].signup >> a[i].speed;
        a[i].id = i;
        a[i].books.resize(siz);
        for (auto &j : a[i].books) {
            scanf("%d", &j);
        }
    }
    fclose(stdin);
    vector<int> lib;
    if (true){
        freopen ("output.txt", "r", stdin);
        {
            int n; scanf ("%d", &n); while (n--){
                int i, k; scanf ("%d %d", &i, &k);
                while (k--) scanf ("%*d");
                lib.push_back(i);
                chk[i] = 1;
            }
        }
        fclose(stdin);
    }
    for (int i = 0; i < L; i++) if (!chk[i]) rlib.push(i);
    long long best = 0;
    for (int att = 0; ; att++){
        vector<int> v = lib;
        vector<pair<int, int> > hist;
        if (att){
            if (r() % 2 || v.size() <= 5){
                int k = 1;
                while (k--){
                    int j = rlib.rd();
                    rlib.pop(j);
                    v.insert(v.begin() + range(0, v.size()), j);
                    hist.push_back({ j,1 });
                    int days = 1;
                    for (auto &i : lib) days += a[i].signup;
                    while (days > D){
                        int p = range(1, v.size()) - 1;
                        int i = v[p];
                        rlib.push(i);
                        v.erase(v.begin() + p);
                        hist.push_back({ i,0 });
                        days -= a[i].signup;
                    }
                }
            }
            else{
                while (1){
                    int i = range(1, v.size()) - 1;
                    int j = range(1, v.size()) - 1;
                    if (i == j) continue;
                    swap(v[i], v[j]);
                    break;
                }
            }
        }
        int tick = 0;
        MCMF::clear();
        for (int i = 0; i < sz(v); i++){
            tick += a[v[i]].signup;
            int siz = (int)min(1ll * (D - tick) * a[v[i]].speed, 1ll * sz(a[v[i]].books));
            MCMF::add_edge(0, i + 1, siz, 0);
            for (auto &j : a[v[i]].books){
                MCMF::add_edge(i + 1, sz(v) + j + 1, 1, 0);
            }
        }
        for (int i = 0; i < B; i++){
            MCMF::add_edge(sz(v) + i + 1, sz(v) + B + 1, 1, -score[i]);
        }
        long long f = -MCMF::match(0, sz(v) + B + 1, sz(v) + B + 2);
        fprintf (stderr, "%lld %lld\n", best, f);
        if (best <= f){
            best = f;
            buf.v.clear();
            for (int i = 0; i < sz(v); i++){
                vector<int> novo;
                for (auto &j : MCMF::gph[i + 1]){
                    if (j.cap == 0 && j.pos > sz(v)){
                        novo.push_back(j.pos - sz(v) - 1);
                    }
                }
                if (sz(novo)){
                    buf.print({ a[v[i]].id,  sz(novo) });
                    buf.print(novo);
                }
            }
            lib = v;
            freopen ("output.txt", "w", stdout);
            buf.flush();
            fclose(stdout);
        }
        else{
            while (!hist.empty()){
                int i = hist.back().first;
                if (hist.back().second) rlib.push(i);
                else rlib.pop(i);
                hist.pop_back();
            }
        }
    }
}

