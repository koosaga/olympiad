#include <bits/stdc++.h>
using namespace std;
#if __cplusplus > 201703L
#include <ranges>
using namespace numbers;
#endif
template<class T> T &ctmin(T &x){ return x; }
template<class T, class Head, class ...Tail> T &ctmin(T &x, const Head &h, const Tail &... t){ return ctmin(x = min<T>(x, h), t...); }
template<class T> T &ctmax(T &x){ return x; }
template<class T, class Head, class ...Tail> T &ctmax(T &x, const Head &h, const Tail &... t){ return ctmax(x = max<T>(x, h), t...); }
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());
mt19937_64 rngll(chrono::high_resolution_clock::now().time_since_epoch().count());
using randint_t = uniform_int_distribution<int>;
using randll_t = uniform_int_distribution<long long>;
using randd_t = uniform_real_distribution<double>;
// return x with probability p, y with probability 1-p
template<class T>
T pick(T x, T y, double p = 0.5){
    assert(-0.0001 <= p && p <= 1.0001);
    return randd_t(0, 1)(rng) <= p ? x : y;
}
array<int, 2> get_range(int n){
    int l = rng() % n, r = rng() % n;
    if(l > r) swap(l, r);
    return {l, r + 1};
}

template<class F>
struct y_combinator_result{
    F f;
    template<class T> explicit y_combinator_result(T &&f): f(forward<T>(f)){ }
    template<class ...Args> decltype(auto) operator()(Args &&...args){ return f(ref(*this), forward<Args>(args)...); }
};
template<class F>
decltype(auto) y_combinator(F &&f){
    return y_combinator_result<decay_t<F>>(forward<F>(f));
}

int main(){
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(ios::badbit | ios::failbit);
    const int mx = 5982, mxd = 20000;
    array<array<char, mxd>, mx + 1> fact{};
    fact[0][0] = 1;
    for(auto x = 0; x < mx; ++ x){
        for(auto i = 0, up = 0; i < mxd; ++ i){
            up += fact[x][i] * (x + 1);
            fact[x + 1][i] = up % 10;
            up /= 10;
        }
    }
    vector<int> pool(mx), q{-1};
    vector<array<int, 10>> next(1);
    next.reserve(1248);
    iota(pool.begin(), pool.end(), 1);
    y_combinator([&](auto self, int u, int l, int r)->void{
        array<int, 2> opt{numeric_limits<int>::max(), -1};
        for(auto d = 0; d < 20; ++ d){
            array<int, 10> cnt{};
            for(auto i = l; i < r; ++ i){
                ++ cnt[fact[pool[i]][d]];
            }
            ctmin(opt, array{ranges::max(cnt), d});
        }
        for(auto rep = 0; rep < 3000; ++ rep){
            int d = rng() % 20000;
            array<int, 10> cnt{};
            for(auto i = l; i < r; ++ i){
                ++ cnt[fact[pool[i]][d]];
            }
            ctmin(opt, array{ranges::max(cnt), d});
        }
        q[u] = opt[1];
        y_combinator([&](auto self2, int vl, int vr, int l, int r)->void{
            if(vr - vl == 1){
                if(r - l == 1){
                    next[u][vl] = -pool[l];
                }
                else if(r - l >= 2){
                    int v = (int)q.size();
                    next[u][vl] = v;
                    q.push_back(-1);
                    next.push_back({});
                    self(v, l, r);
                }
                return;
            }
            int vm = vl + vr >> 1;
            int m = partition(pool.begin() + l, pool.begin() + r, [&](int x){ return fact[x][q[u]] < vm; }) - pool.begin();
            self2(vl, vm, l, m);
            self2(vm, vr, m, r);
        })(0, 10, l, r);
    })(0, 0, (int)pool.size());
    int _tn;
    cin >> _tn;
    while(_tn --){
        for(auto u = 0, qi = 0; qi <= 10; ++ qi){
            assert(qi < 10);
            cout << "? " << q[u] << endl;
            int x;
            cin >> x;
            assert(next[u][x]);
            if(next[u][x] < 0){
                cout << "! " << -next[u][x] << endl;
                string s;
                cin >> ws;
                getline(cin, s);
                if(s[0] == 'W'){
                    exit(0);
                }
                break;
            }
            u = next[u][x];
        }
    }
    return 0;
}

/*

*/

////////////////////////////////////////////////////////////////////////////////////////
//                                                                                    //
//                                   Coded by Aeren                                   //
//                                                                                    //
////////////////////////////////////////////////////////////////////////////////////////