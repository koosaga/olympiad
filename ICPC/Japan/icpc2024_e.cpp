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

int main(){
    ios_base::sync_with_stdio(false), cin.tie(nullptr);
    int N, M;
    cin >> N >> M;
    vector<string> S(N);
    for(int i = 0; i < N; i++){
        cin >> S[i];
    }
    int V = N * M;
    vector<vector<int> > adj(V);
    for(int i = 0; i < N; i++){
        for(int j = 0; j < M; j++){
            if(i+1 < N){
                adj[i * M + j].push_back((i+1) * M + j);
                adj[(i+1) * M + j].push_back(i * M + j);
            }
            if(j+1 < M){
                adj[i * M + j].push_back(i * M + j + 1);
                adj[i * M + j + 1].push_back(i * M + j);
            }
        }
    }
    vector<vector<int> > tree(V);
    vector<char> label(V, '.');
    for(int i = 0; i < N; i++){
        for(int j = 0; j < M; j++){
            label[i * M + j] = S[i][j];
        }
    }
    for(int i = 0; i < V; i++){
        for(int j : adj[i]){
            if(label[i] == '.') continue;
            if(label[j] == '.') continue;
            tree[i].push_back(j);
        }
    }
    int root = -1;
    for(int i = 0; i < V; i++){
        if(label[i] == 'P') root = i;
    }
    using ll = int64_t;
    ll ans = y_combinator([&](auto self, int v, int p) -> ll {
        vector<ll> res;
        for(int w : tree[v]){
            if(w == p) continue;
            res.push_back(self(w, v));
        }
        if(res.empty()){
            return label[v] - '0';
        } else if(res.size() == 1){
            return res[0];
        } else {
            ll a = res[0], b = res[1];
            if(a < b) swap(a, b);
            if(label[v] == '+') return a + b;
            if(label[v] == '-') return a - b;
            if(label[v] == '*') return a * b;
            if(label[v] == '/') return a / b;
            assert(false);
        }
    })(root, -1);
    cout << ans << '\n';
}


