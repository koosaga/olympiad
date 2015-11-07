#include <cstdio>
#include <algorithm>
using namespace std;

int fact[9000005];
int dp[3005][3005];
int bino[3005][3005];
const int mod = 1e9 + 7;

int r,c,n;
int lx = 1e9, ly = 1e9, rx = -1, ry = -1;

int C(int x, int y){
    if(y == 0 || x == y) return 1;
    if(bino[x][y]) return bino[x][y];
    return bino[x][y] = (C(x-1,y-1) + C(x-1,y))%mod;
}

int f(int x, int y){
    if(x > r || y > c) return 0;
    if(x == r && y == c) return 1;
    if(dp[x][y]) return dp[x][y];
    long long t = 1ll * f(x,y+1) * fact[x] + 1ll * f(x+1,y) * fact[y];
    t %= mod;
    return dp[x][y] = t;
}

int main(){
    scanf("%d %d",&r,&c);
    fact[0] = 1;
    for (int i=1; i<r*c; i++) {
        fact[i] = 1ll * fact[i-1] * i % mod;
    }
    scanf("%d",&n);
    for (int i=0; i<n; i++) {
        int p,q;
        scanf("%d %d",&p,&q);
        lx = min(lx,p);
        ly = min(ly,q);
        rx = max(rx,p);
        ry = max(ry,q);
    }
    long long res = fact[(ry-ly+1)*(rx-lx+1) - n];
    res *= f(rx-lx+1,ry-ly+1);
    res %= mod;
    res *= 1ll * C(r - rx + lx - 1,lx - 1);
    res %= mod;
    res *= 1ll * C(c - ry + ly - 1,ly - 1);
    res %= mod;
    printf("%lld",res);
}