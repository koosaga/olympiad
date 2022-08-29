#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = pair<int, int>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
const int mod = 1e9 + 7;
const int MAXN = 1000005;


int n, a[MAXN];
pi spt[22][MAXN];
int lg[MAXN];

pi query(int s, int e){
    int l = lg[e - s + 1];
    return max(spt[l][s], spt[l][e - (1<<l) + 1]);
}

pi f(int s, int e){
    if(s > e) return pi(0, 0);
    auto Q = query(s, e);
    auto f1 = f(s, Q.second - 1);
    auto f2 = f(Q.second + 1, e);
    return pi(max(f1.first, f2.first) + 1, 1 + max({f1.second, f2.second, f1.first + f2.first}));

}
int main(){ 
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cin >> n;
    for(int i = 0; i < n; i++) cin >> a[i];
    for(int i = 0; i < n; i++){
        spt[0][i] = pi(a[i], i);
    }
    for(int i = 1; i < 20; i++){
        for(int j = 0; j < n; j++){
            spt[i][j] = spt[i-1][j];
            if(j + (1<<(i-1)) < n) spt[i][j] = max(spt[i][j], spt[i - 1][j + (1<<(i-1))]);
        }
    }
    int p = 0;
    for(int i = 1; i <= n; i++){
        while((2 << p) <= i) p++;
        lg[i] = p;
    }
    cout << f(0, n - 1).second - 1 << "\n";
}

