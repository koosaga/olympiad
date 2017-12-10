#include <bits/stdc++.h>
using namespace std;
const int mod = 1e9;

char str[305];
int dp[305][305];

int f(int s, int e){
    if(s == e) return 1;
    if(s > e) return 0;
    if(str[s] != str[e]) return 0;
    if(~dp[s][e]) return dp[s][e];
    int ret = f(s+1, e-1);
    for(int i=s+2; i<=e-2; i++){
        if(str[i] == str[s]){
            ret += 1ll * f(s+1, i-1) * f(i, e) % mod;
            ret %= mod;
        }
    }
    return dp[s][e] = ret;
}

int main(){
    memset(dp, -1, sizeof(dp));
    cin >> str;
    cout << f(0, strlen(str) - 1);
}
