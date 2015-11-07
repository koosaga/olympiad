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
 
int n, m, q;
int a[505], idx[505];
int adj[505][505], ret[505][505];
 
int main(){
    memset(adj,0x3f,sizeof(adj));
    memset(ret,0x3f,sizeof(ret));
    scanf("%d %d %d",&n,&m,&q);
    for(int i=1; i<=n; i++){
        scanf("%d",&a[i]);
        idx[i] = i;
        adj[i][i] = 0;
    }
    for(int i=0; i<m; i++){
        int s, e, x;
        scanf("%d %d %d",&s,&e,&x);
        adj[s][e] = min(adj[s][e],x);
        adj[e][s] = min(adj[e][s],x);
    }
    sort(idx + 1, idx + n + 1, [&](const int &p, const int &q){
        return a[p] < a[q];
    });
    for(int i=1; i<=n; i++){
        int p = idx[i];
        for(int j=1; j<=n; j++){
            for(int k=1; k<=n; k++){
                adj[j][k] = min(adj[j][k], adj[j][p] + adj[p][k]);
                ret[j][k] = min(ret[j][k], adj[j][k] + max(a[j], max(a[k], a[p])));
            }
        }
    }
    while(q--){
        int s, e;
        scanf("%d %d",&s,&e);
        printf("%d\n",ret[s][e]);
    }
}