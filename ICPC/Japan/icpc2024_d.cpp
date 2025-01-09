#include <bits/stdc++.h>
using namespace std;

namespace std {

template<class Fun>
class y_combinator_result {
    Fun fun_;
public:
    template<class T>
    explicit y_combinator_result(T &&fun): fun_(std::forward<T>(fun)) {}

    template<class ...Args>
    decltype(auto) operator()(Args &&...args) {
        return fun_(std::ref(*this), std::forward<Args>(args)...);
    }
};

template<class Fun>
decltype(auto) y_combinator(Fun &&fun) {
    return y_combinator_result<std::decay_t<Fun>>(std::forward<Fun>(fun));
}

} // namespace std

namespace ecnerwala {

using std::swap;

struct level_ancestor {
    int N;
    std::vector<int> preorder;
    std::vector<int> idx;
    std::vector<std::pair<int, int>> heavyPar; // heavy parent, distance
    level_ancestor() : N(0) {}

    level_ancestor(const std::vector<int>& par) : N(int(par.size())), preorder(N), idx(N), heavyPar(N) {
        std::vector<std::vector<int>> ch(N);
        for (int i = 0; i < N; i++) {
            if (par[i] != -1) ch[par[i]].push_back(i);
        }
        std::vector<int> sz(N);
        int nxt_idx = 0;
        for (int i = 0; i < N; i++) {
            if (par[i] == -1) {
                std::y_combinator([&](auto self, int cur) -> void {
                    sz[cur] = 1;
                    for (int nxt : ch[cur]) {
                        self(nxt);
                        sz[cur] += sz[nxt];
                    }
                    if (!ch[cur].empty()) {
                        auto mit = max_element(ch[cur].begin(), ch[cur].end(), [&](int a, int b) { return sz[a] < sz[b]; });
                        swap(*ch[cur].begin(), *mit);
                    }
                })(i);
                std::y_combinator([&](auto self, int cur, int isRoot = true) -> void {
                    preorder[idx[cur] = nxt_idx++] = cur;
                    if (isRoot) {
                        heavyPar[idx[cur]] = {par[cur] == -1 ? -1 : idx[par[cur]], 1};
                    } else {
                        assert(idx[par[cur]] == idx[cur]-1);
                        heavyPar[idx[cur]] = heavyPar[idx[cur]-1];
                        heavyPar[idx[cur]].second++;
                    }
                    bool chRoot = false;
                    for (int nxt : ch[cur]) {
                        self(nxt, chRoot);
                        chRoot = true;
                    }
                })(i);
            }
        }
    }

    int get_ancestor(int a, int k) const {
        assert(k >= 0);
        a = idx[a];
        while (a != -1 && k) {
            if (k >= heavyPar[a].second) {
                k -= heavyPar[a].second;
                assert(heavyPar[a].first <= a - heavyPar[a].second);
                a = heavyPar[a].first;
            } else {
                a -= k;
                k = 0;
            }
        }
        if (a == -1) return -1;
        else return preorder[a];
    }

    int lca(int a, int b) const {
        a = idx[a], b = idx[b];
        while (true) {
            if (a > b) swap(a, b);
            assert(a <= b);
            if (a > b - heavyPar[b].second) {
                return preorder[a];
            }
            b = heavyPar[b].first;
            if (b == -1) return -1;
        }
    }

    int dist(int a, int b) const {
        a = idx[a], b = idx[b];
        int res = 0;
        while (true) {
            if (a > b) swap(a, b);
            assert(a <= b);
            if (a > b - heavyPar[b].second) {
                res += b - a;
                break;
            }
            res += heavyPar[b].second;
            b = heavyPar[b].first;
            if (b == -1) return -1;
        }
        return res;
    }
};

} // namespace ecnerwala

int main(){
    ios_base::sync_with_stdio(false), cin.tie(nullptr);
    vector<string> S(2);
    cin >> S[0] >> S[1];
    vector<vector<tuple<int, int, int, int> > > ivals(2);
    for(int t = 0; t < 2; t++){
        vector<int> par = {-1};

        vector<int> stk = {};
        int cur = 0;
        for(char c : S[t]){
            if(c == '('){
                if(!stk.empty()) par.push_back(stk.back());
                stk.push_back(cur);
                cur++;
            } else if(c == '1'){
                if(!stk.empty()) par.push_back(stk.back());
                cur++;
            } else if(c == ')'){
                stk.pop_back();
            }
        }
        vector<vector<int> > ch(cur);
        for(int i = 1; i < cur; i++){
            ch[par[i]].push_back(i);
        }
        ecnerwala::level_ancestor lca(par);
        vector<int> sz(cur);
        y_combinator([&](auto self, int v) -> void {
            if(ch[v].size() == 0){
                sz[v] = 1;
            } else {
                assert(ch[v].size() == 2);
                self(ch[v][0]);
                self(ch[v][1]);
                sz[v] = sz[ch[v][0]] + sz[ch[v][1]];
            }
        })(0);
        int cnt = 0;
        y_combinator([&](auto self, int v) -> void {
            if(ch[v].size() == 0){
                cnt += 1;
            } else {
                self(ch[v][0]);
                ivals[t].push_back({cnt-sz[ch[v][0]], cnt-1, cnt, cnt+sz[ch[v][1]]-1});
                self(ch[v][1]);
            }
        })(0);
    }
    if(ivals[0].size() != ivals[1].size()){
        cout << 0 << '\n';
    } else {

        using ll = int64_t;
        ll MOD = 998244353;
        ll ans = 1;

        for(int i = 0; i < ivals[0].size(); i++){
            auto [l1, r1, l2, r2] = ivals[0][i];
            auto [l3, r3, l4, r4] = ivals[1][i];
            ans *= (min(r1, r3) - max(l1, l3) + 1);
            ans %= MOD;
            ans *= (min(r2, r4) - max(l2, l4) + 1);
            ans %= MOD;
        }
        cout << ans << '\n';
    }
}

