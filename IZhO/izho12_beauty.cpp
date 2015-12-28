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
 
bool adj[20][20];
int a[20], n;
 
lint dp[1<<20][20];
 
lint f(int bit, int pos){
    if(bit == (1<<n) - 1) return 1;
    if(~dp[bit][pos]) return dp[bit][pos];
    lint ret = 0;
    for(int i=0; i<n; i++){
        if(((bit >> i) & 1) == 0 && adj[pos][i]){
            ret += f(bit | 1 << i, i);
        }
    }
    return ret;
}
 
bool mat(int p, int q){
    int cp = 0, cq = 0;
    for(int i=0; i<31; i++){
        if((p >> i) & 1) cp++;
        if((q >> i) & 1) cq++;
    }
    if(cp == cq) return 1;
    cp = cq = 0;
    while(p || q){
        if(p%3 == 1) cp++;
        if(q%3 == 1) cq++;
        p /= 3, q /= 3;
    }
    return cp == cq;
}
 
inline int get(int b, int x){
    return (b >> x) & 1;
}
 
int main(){
    scanf("%d",&n);
    for(int i=0; i<n; i++){
        scanf("%d",&a[i]);
    }
    for(int i=0; i<n; i++){
        for(int j=i+1; j<n; j++){
            if(mat(a[i], a[j])) adj[i][j] = adj[j][i] = 1;
        }
    }
    lint ret = 0;
    for(int i=0; i<n; i++){
        dp[(1<<n) - 1][i] = 1;
    }
    for(int i=(1<<n)-2; i>=0; i--){
        for(int j=0; j<n; j++){
            if(get(i, j) == 0) continue;
            for(int k=0; k<n; k++){
                if(get(i, k) == 0 && adj[j][k]){
                    dp[i][j] += dp[i |(1<<k)][k];
                }
            }
        }
    }
    for(int i=0; i<n; i++){
        ret += dp[1<<i][i];
    }
    printf("%lld",ret);
}