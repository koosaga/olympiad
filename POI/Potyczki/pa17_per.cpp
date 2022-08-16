#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
typedef long long lint;
typedef long double llf;
typedef pair<lint, lint> pi;
const int MAXN = 250005;
const lint inf = 1.1e18;

struct bit{
    int tree[MAXN];
    void add(int x, int v){
        for(int i=x; i<MAXN; i+=i&-i){
            tree[i] += v;
        }
    }
    int kth(int x){
        int pos = 0;
        for(int i=17; i>=0; i--){
            if(pos + (1<<i) < MAXN && tree[pos + (1<<i)] < x){
                pos += (1<<i);
                x -= tree[pos];
            }
        }
        return pos + 1;
    }
}bit;

lint dp[205][20005];
lint n, k;

lint real_dp[MAXN][30];

lint fn(int x, int y){
    if(y < 0) return 0;
    if(y >= 40) return inf;
    return real_dp[x][y];
}

vector<int> solve(int n, int k, lint cnt){
    real_dp[0][0] = 1;
    for(int i=0; i<n; i++){
        for(int j=0; j<30; j++){
            for(int k=0; k<=i && k<=j; k++){
                real_dp[i+1][j] = min(real_dp[i+1][j] + real_dp[i][j-k], inf);
            }
        }
    }
    vector<int> v(n);
    for(int i=0; i<n; i++){
        for(int j=min(k,n-1-i); j>=0; j--){
            if(cnt > fn(n - i - 1, k - j)){
                cnt -= fn(n - i - 1, k - j);
            }
            else{
                k -= j;
                v[i] = j;
                break;
            }
        }
    }
    for(int i=0; i<n; i++) v[i] = n-1-i-v[i];
    return v;
}


void report(vector<int> v){
    assert(sz(v) == n);
    for(int i=1; i<=n; i++) bit.add(i, 1);
    puts("YES");
    for(int i=0; i<sz(v); i++){
        int pos = bit.kth(1+v[i]);
        bit.add(pos, -1);
        printf("%d ", pos);
    }
    exit(0);
}

int main(){
    cin >> n >> k;
    lint q = 1ll * n * (n - 1) / 2;
    if(q % 2){
        puts("NO");
        return 0;
    }
    q /= 2;
    if(n <= 200){
        dp[0][0] = 1;
        for(int i=0; i<n; i++){
            for(int j=0; j<=i*(i+1)/2; j++){
                for(int k=0; k<=i && k<=j; k++){
                    dp[i+1][j] = min(dp[i+1][j] + dp[i][j-k], inf);
                }
            }
        }
        if(dp[n][q] < k){
            puts("NO");
            return 0;
        }
        vector<int> v;
        for(int i=n; i>=0; i--){
            for(int j=0; j<i; j++){
                if(dp[i-1][q-j] < k){
                    k -= dp[i-1][q-j];
                }
                else{
                    v.push_back(j);
                    q -= j;
                    break;
                }
            }
        }
        report(v);
    }
    lint cur = 0;
    int s = n;
    for(int i=n-1; i>=0; i--){
        bool kill = (cur >= q);
        cur += n-1-i;
        s = i;
        if(kill) break;
    }
    auto v = solve(n - s, 1ll * (n - s) * (n - s - 1) / 2 - q, k);
    reverse(all(v));
    for(int i=0; i<s; i++) v.push_back(0);
    reverse(all(v));
    report(v);
}
