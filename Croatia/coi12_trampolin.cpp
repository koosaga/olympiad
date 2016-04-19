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
 
int n, k, a[300005];
char str[300005];
bool vis[300005];
 
vector<int> dfn;
 
void dfs(int x){
    if(vis[x]) return;
    vis[x] = 1;
    if(x == 0){
        for(int i=1; i<=n; i++){
            dfs(i);
        }
    }
    else{
        if(x > 1 && a[x] >= a[x-1]) dfs(x-1);
        if(x < n && a[x] >= a[x+1]) dfs(x+1);
        if(str[x-1] == 'T') dfs(0);
    }
    dfn.push_back(x);
}
 
int comp[300005], csize[300005], p;
 
void rdfs(int x, int p){
    if(comp[x]) return;
    comp[x] = p;
    if(x == 0){
        for(int i=1; i<=n; i++){
            if(str[i-1] == 'T') rdfs(i, p);
        }
    }
    else{
        csize[p]++;
        if(x > 1 && a[x] <= a[x-1]) rdfs(x-1, p);
        if(x < n && a[x] <= a[x+1]) rdfs(x+1, p);
        rdfs(0, p);
    }
}
 
vector<int> dag[300005];
int dp[300005];
 
int main(){
    scanf("%d %d",&n,&k);
    for(int i=1; i<=n; i++){
        scanf("%d",&a[i]);
    }
    scanf("%s",str);
    for(int i=0; i<=n; i++){
        if(!vis[i]) dfs(i);
    }
    reverse(dfn.begin(), dfn.end());
    for(auto &i : dfn){
        if(!comp[i]) rdfs(i, ++p);
    }
    for(int i=1; i<=n; i++){
        if(comp[i] != comp[0]){
            dag[comp[0]].push_back(comp[i]);
        }
    }
    for(int x=1; x<=n; x++){
        if(x > 1 && a[x] >= a[x-1] && comp[x] != comp[x-1]){
            dag[comp[x]].push_back(comp[x-1]);
        }
        if(x < n && a[x] >= a[x+1] && comp[x] != comp[x+1]){
            dag[comp[x]].push_back(comp[x+1]);
        }
        if(str[x-1] == 'T' && comp[x] != comp[0]){
            dag[comp[x]].push_back(comp[0]);
        }
    }
    int ret = 0;
    for(int i=p; i; i--){
        for(auto &j : dag[i]){
            dp[i] = max(dp[i], dp[j]);
        }
        dp[i] += csize[i];
    }
    cout << dp[comp[k]];
}