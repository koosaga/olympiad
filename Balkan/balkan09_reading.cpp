#include <cstdio>
#include <cstring>
const int mod = 1e9 + 7;
const int sz = 156;
 
int n,m;
char adj[26][26];
int dp[7][26];
 
struct matrix{
    int a[sz][sz];
    void init(int E){
        memset(a,0,sizeof(a));
        if(E == 0) return;
        for (int i=0; i<sz; i++) a[i][i] = 1;
    }
};
 
matrix operator*(matrix a, matrix b){
    matrix ret;
    ret.init(0);
    for (int i=0; i<sz; i++) {
        for (int j=0; j<sz; j++) {
            for (int k=0; k<sz; k++) {
                ret.a[i][j] += (1ll * a.a[i][k] * b.a[k][j]) % mod;
                ret.a[i][j] %= mod;
            }
        }
    }
    return ret;
}
 
void solve(){
    int ret = 0;
    matrix sol, piv;
    sol.init(1);
    piv.init(0);
    for (int i=1; i<6; i++) {
        for (int j=0; j<26; j++) {
            piv.a[i * 26 + j][(i-1) * 26 + j] = 1;
        }
    }
    for (int i=0; i<26; i++) {
        for (int j=0; j<26; j++) {
            piv.a[i][26 * adj[i][j] - 26 + j] += 1;
            piv.a[i][26 * adj[i][j] + j] += mod-1;
            piv.a[i][26 * adj[i][j] + j] %= mod;
        }
        piv.a[i][i] += 1;
    }
    n -= 6;
    while (n) {
        if(n&1) sol = sol * piv;
        piv = piv * piv;
        n >>= 1;
    }
    for (int i=0; i<26; i++) {
        for (int j=0; j<sz; j++) {
            // dp[j] =
            ret += (1ll * sol.a[i][j] * dp[6 - j/26][j%26]) % mod;
            ret %= mod;
        }
    }
    printf("%d",ret);
}
 
int main(){
    scanf("%d %d",&n,&m);
    for (int i=0; i<26; i++) {
        dp[0][i] = 1;
        for (int j=0; j<26; j++) {
            adj[i][j] = 1;
        }
    }
    while (m--) {
        char s1[5], s2[5];
        int t;
        scanf("%s %s %d",s1,s2,&t);
        adj[s1[0] - 'a'][s2[0] - 'a'] = t;
        adj[s2[0] - 'a'][s1[0] - 'a'] = t;
    }
    int ret = 0;
    for (int i=1; i<=6; i++) {
        for (int j=0; j<26; j++) {
            for (int k=0; k<26; k++) {
                if(i < adj[j][k]) continue;
                dp[i][j] += dp[i - adj[j][k]][k];
                dp[i][j] %= mod;
                if(i != adj[j][k])
                    dp[i][j] += mod - dp[i - adj[j][k] - 1][k];
                dp[i][j] %= mod;
            }
            dp[i][j] += dp[i-1][j];
            dp[i][j] %= mod;
        }
    }
    if(n <= 6){
        for (int i=0; i<26; i++) {
            ret += dp[n][i];
            ret %= mod;
        }
        printf("%d",ret);
    }
    else solve();
}