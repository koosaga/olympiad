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
#include <bitset>
#include <iostream>
using namespace std;
typedef long long lint;
typedef long double llf;
typedef pair<int, int> pi;
 
struct seg{
    int tree[1050000], lim;
    void init(int n){
        for(lim = 1; lim <= n; lim <<= 1);
    }
    void update(int x, int v){
        x += lim;
        tree[x] = v;
        while(x > 1){
            x >>= 1;
            tree[x] = max(tree[2*x], tree[2*x+1]);
        }
    }
    int query(int s, int e){
        s += lim;
        e += lim;
        int ret = 0;
        while(s < e){
            if(s%2 == 1) ret = max(ret, tree[s++]);
            if(e%2 == 0) ret = max(ret, tree[e--]);
            s >>= 1, e >>= 1;
        }
        if(s == e) ret = max(ret, tree[s]);
        return ret;
    }
}seg;
 
int n;
vector<int> graph[300005];
int c[300005];
 
int dfn[300005], size[300005], piv;
int par[19][300005], dep[300005];
 
void dfs(int x){
    dfn[x] = piv++;
    size[x] = 1;
    for(auto &i : graph[x]){
        dep[i] = dep[x] + 1;
        dfs(i);
        size[x] += size[i];
    }
}
 
inline int getcost(int x){
    return seg.query(dfn[x], dfn[x] + size[x] - 1);
}
 
int main(){
    scanf("%d %d",&n, &c[0]);
    for(int i=1; i<=n; i++){
        scanf("%d %d",&c[i], &par[0][i]);
        graph[par[0][i]].push_back(i);
    }
    dfs(0);
    for(int i=1; i<19; i++){
        for(int j=0; j<=n; j++){
            par[i][j] = par[i-1][par[i-1][j]];
        }
    }
    seg.init(n);
    seg.update(dfn[0], c[0]);
    for(int i=1; i<=n; i++){
        int dx = 0, p = i;
        for(int j=18; j>=0; j--){
            if(dx + (1<<j) <= dep[i] && getcost(par[j][p]) < c[i]){
                p = par[j][p];
                dx += (1<<j);
            }
        }
        if(p != 0 && getcost(par[0][p]) < c[i]) dx++;
        printf("%d\n",dx);
        seg.update(dfn[i], c[i]);
    }
}