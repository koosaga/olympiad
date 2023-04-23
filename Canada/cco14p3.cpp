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
const int mod = 1e9 + 7;

int n, w, m, deg[205];
vector<pi> graph[205];

vector<lint> dp[205][205][2];

lint f(int x, int sub, int k, int cur){
    if(sub == 0){
        k -= cur;
        if(k < 0) return 0;
    }
    if(sub == graph[x].size()) return (k == 0);
    if(~dp[x][k][cur][sub]) return dp[x][k][cur][sub];
    lint ret = 0;
    int pos = graph[x][sub].first;
    if(cur == 0){
        for(int i=0; i<=k; i++){
            lint subsol = f(pos, 0, i, 0) + f(pos, 0, i, 1);
            ret += subsol * f(x, sub + 1, k - i, cur);
            ret %= mod;
        }
    }
    else if(graph[x][sub].second){
        for(int i=0; i<=k; i++){
            ret += f(pos, 0, i, 1) * f(x, sub + 1, k - i, cur);
            ret %= mod;
        }
    }
    else{
        for(int i=0; i<=k; i++){
            ret += f(pos, 0, i, 0) * f(x, sub + 1, k - i, cur);
            ret %= mod;
        }
    }
    return dp[x][k][cur][sub] = ret;
}

int main(){
    scanf("%d %d %d",&n,&w,&m);
    for(int i=0; i<m; i++){
        char s[5];
        int a, b;
        scanf("%s %d %d",s,&a,&b);
        deg[b]++;
        if(s[0] == 'D'){
            graph[a].push_back(pi(b, 1));
            // (a -> b)
        }
        else{
            graph[a].push_back(pi(b, 0));
        }
    }
    for(int i=1; i<=n; i++){
        for(int j=0; j<=w; j++){
            for(int k=0; k<2; k++){
                dp[i][j][k].resize(graph[i].size(), -1);
            }
        }
    }
    lint ret[205] = {};
    ret[0] = 1;
    for(int i=1; i<=n; i++){
        if(deg[i] == 0){
            lint tmp[205], old[205];
            for(int j=w; j>=0; j--){
                old[j] = ret[j];
                tmp[j] = f(i, 0, j, 0) + f(i, 0, j, 1);
                ret[j] = 0;
            }
            for(int j=0; j<=w; j++){
                for(int k=0; k<=j; k++){
                    ret[j] += old[j - k] * tmp[k];
                    ret[j] %= mod;
                }
            }
        }
    }
    printf("%lld",ret[w]);
}
