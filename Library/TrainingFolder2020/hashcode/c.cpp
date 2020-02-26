#include <cstdio>
#include <vector>
#include <chrono>
#include <algorithm>
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
int B, N, D, score[100100], day[100100], ship[100100];
vector<int> id[100100];
struct set{
    bool in[100100]; int rev[100100], cnt[100100], days; long long scores;
    vector<int> con;
    void push(int x){
        if (in[x]) return;
        in[x] = true;
        rev[x] = con.size();
        con.push_back(x);
        days += day[x];
        for (auto &i : id[x]) if (cnt[i]++ == 0){
            scores += score[i];
        }
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
        days -= day[x];
        for (auto &i : id[x]) if (--cnt[i] == 0){
            scores -= score[i];
        }
    }
    int rd(){
        if (con.empty()) return -1;
        return con[range(1, con.size()) - 1];
    }
}lib,rlib;
int main()
{
    freopen ("c_incunabula.txt", "r", stdin);
    scanf ("%d %d %d", &B, &N, &D);
    for (int i = 0; i < B; i++) scanf ("%d", &score[i]);
    for (int i = 0; i < N; i++){
        int k; scanf ("%d %d %d", &k, &day[i], &ship[i]);
        while (k--){
            int x; scanf ("%d", &x);
            id[i].push_back(x);
        }
        day[i]++;
    }
    fclose(stdin);
    if (true){
        freopen ("output.txt", "r", stdin);
        {
            int n; scanf ("%d", &n); while (n--){
                int i, k; scanf ("%d %d", &i, &k);
                while (k--) scanf ("%*d");
                lib.push(i);
            }
        }
        fclose(stdin);
    }
    else{
        while (lib.days <= D){
            int i = range(1, N) - 1;
            lib.push(i);
        }
        lib.pop(lib.rd());
    }
    for (int i = 0; i < N; i++) if (!lib.in[i]) rlib.push(i);
    long long best = lib.scores, last = best;
    while (1){
        vector<pair<int, int> > hist;
        int k = range(1, 4);
        while (k--){
            int j = rlib.rd();
            hist.push_back({ j, 1 });
            rlib.pop(j);
            lib.push(j);
            while (lib.days > D){
                int i = lib.rd();
                hist.push_back({ i, 0 });
                lib.pop(i);
                rlib.push(i);
            }
        }
        long long now = lib.scores;
        printf ("%lld %lld %lld\n", best, last, now);
        if (last <= now){
            last = now;
            if (best <= now){
                best = now;
                freopen ("output.txt", "w", stderr);
                fprintf (stderr, "%d\n", lib.con.size());
                for (int i : lib.con){
                    fprintf (stderr, "%d %d\n", i, id[i].size());
                    for (auto &x : id[i]) fprintf (stderr, "%d ", x);
                    fprintf (stderr, "\n");
                }
                fclose(stderr);
            }
        }
        else{
            while (!hist.empty()){
                int i = hist.back().first;
                if (hist.back().second){
                    lib.pop(i);
                    rlib.push(i);
                }
                else{
                    rlib.pop(i);
                    lib.push(i);
                }
                hist.pop_back();
            }
            if ((r() & 63) == 0) last--;
        }
    }
    return 0;
}

