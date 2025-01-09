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
    int N;
    cin >> N;
    vector<int> A(N);
    for(int i = 0; i < N; i++){
        cin >> A[i];
    }
    int ans = 0;
    y_combinator([&](auto self, int l, int r) -> void {
        if(l == r){
            return;
        }
        int x = *min_element(A.begin() + l, A.begin() + r);
        ans += 1;
        int p = l;
        for(int i = l; i < r; i++){
            if(A[i] == x){
                if(p < i) self(p, i);
                p = i+1;
            }
        }
        if(p < r) self(p, r);
    })(0, N);
    cout << ans << '\n';
}

