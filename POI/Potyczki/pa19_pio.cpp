#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = pair<int, int>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
const int MAXN = 10005;

lint a[MAXN][6][6];
lint dp[1 << 12];

int main(){ 
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int t; cin >> t;
    while(t--){
        int n, p, q; cin >> n >> p >> q;
        lint sum = 0;
        for(int i = 0; i < n; i++){
            for(int j = 0; j < p; j++){
                for(int k = 0; k < q; k++){
                    lint x; cin >> x;
                    sum += x;
                    a[i][j][k] = x;
                }
            }
        }
        for(int i = 0; i < n; i++){
            for(int j = 0; j < p; j++){
                for(int k = 0; k < q; k++){
                    lint x; cin >> x;
                    sum -= x;
                    a[i][j][k] -= x;
                }
            }
        }
        if(sum != 0){
            cout << "NIE\n";
            continue;
        }
        memset(dp, 0, sizeof(dp));
        vector<int> msk;
        for(int i = 0; i < (1 << (p + q)); i++){
            if(__builtin_popcount(i) == p) msk.push_back(i);
        }
        for(int i = 0; i < n; i++){
            for(auto &j : msk){
                int x = 0;
                int y = q;
                for(int k = 0; k < (p + q); k++){
                    if((j >> k) & 1){
                        for(int z = 0; z < y; z++) dp[j] += a[i][x][z];
                        x++;
                    }
                    else y--;
                }
            }
            for(auto &j : msk){
                for(int k = 0; k + 1 < (p + q); k++){
                    if((j >> k) % 2 == 1 && (j >> (k + 1)) % 2 == 0){
                        dp[j + (1 << k)] = min(dp[j + (1 << k)], dp[j]);
                    }
                }
            }
        }
        bool ok = 1;
        for(auto &x : msk) if(dp[x] < 0) ok = 0;
        cout << (ok ? "TAK" : "NIE") << "\n";
    }
}
