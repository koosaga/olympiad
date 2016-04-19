#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <limits.h>
#include <stack>
#include <queue>
#include <map>
#include <set>
#include <algorithm>
#include <string>
#include <functional>
#include <vector>
#include <numeric>
#include <deque>
#include <utility>
#include <bitset>
#include <iostream>
using namespace std;
typedef long long lint;
typedef long double llf;
typedef pair<int, int> pi;
#define div shit
const int mod = 10007;
 
int n;
char str[205];
int bino[205][205];
 
int div(int a, int b, int c){
    return bino[a/2+b/2+c/2][a/2+b/2] * bino[a/2+b/2][a/2] % mod;
}
 
int dp[202][202][205];
int dp2[202][202][26];
 
 
int g(int s, int e, int c){
    return dp2[s][e][c];
}
 
bool vis[205][205];
int aux[205][205];
 
void solve(int s, int e){
    if(vis[s][e]) return;
    vis[s][e] = 1;
    if(s == e){
        for(int i=s; i<=e; i++){
            dp[s][e][i] = 1;
            dp2[s][e][str[i] - 'a']++;
        }
        return;
    }
    for(int i=s; i<=e; i+=2){
        for(int j=i+1; j<e; j+=2){
            solve(s, i);
            solve(i+1, j);
            solve(j+1, e);
        }
    }
    for(int i=s; i<e; i+=2){
        for(int j=i+1; j<e; j+=2){
            aux[i][j] = 0;
            for(int k=0; k<26; k++){
                aux[i][j] += dp2[s][i][k] * dp2[j+1][e][k] % mod;
                aux[i][j] %= mod;
            }
        }
    }
    for(int x=s; x<=e; x++){
        for(int i=s; i<e; i+=2){
            if(i+1 > x) continue;
            for(int j=i+1; j<e; j+=2){
                if(x > j) continue;
                dp[s][e][x] += (aux[i][j] * dp[i+1][j][x] % mod) * div(i-s+1, e-j, j-i) % mod;
                dp[s][e][x] %= mod;
            }
        }
        dp2[s][e][str[x] - 'a'] += dp[s][e][x];
        dp2[s][e][str[x] - 'a'] %= mod;
    }
}
 
int main(){
    cin >> n >> str;
    for(int i=0; i<n; i++) str[i+n] = str[i];
    for(int i=0; i<=2*n; i++){
        bino[i][0] = 1;
        for(int j=1; j<=i; j++){
            bino[i][j] = bino[i-1][j] + bino[i-1][j-1];
            bino[i][j] %= mod;
        }
    }
    if(n%2 == 0){
        int ret = 0;
        for(int i=0; i<n; i++){
            for(int j=i; j<=n+i-1; j+=2){
                solve(i, j);
                solve(j+1, n+i-1);
                int p1 = 0, p2 = 0;
                for(int k=0; k<26; k++){
                    p1 += g(i, j, k);
                    p2 += g(j+1, n+i-1, k);
                }
                p1 %= mod;
                p2 %= mod;
                ret += (p1 * p2 % mod) * div(j-i+1, n+i-1-j, 0) % mod;
                ret %= mod;
            }
        }
        ret *= (mod + 1) / 2;
        ret %= mod;
        cout << ret << endl;
    }
    else{
        int ret = 0;
        for(int i=0; i<n; i++){
            solve(i, n+i-1);
            for(int j=i; j<=n+i-1; j++){
                ret += dp[i][n+i-1][j];
            }
            ret %= mod;
        }
        cout << ret << endl;
    }
}