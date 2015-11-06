include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <limits.h>
#include <stack>
#include <queue>
#include <map>
#include <set>
#include <unordered_set>
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
 
const int mod = 1e9;
 
struct matrix{
    lint a[2][2];
    matrix operator*(const matrix &t){
        matrix r;
        for(int i=0; i<2; i++){
            for(int j=0; j<2; j++){
                r.a[i][j] = 0;
                for(int k=0; k<2; k++){
                    r.a[i][j] += a[i][k] * t.a[k][j] % mod;
                    r.a[i][j] %= mod;
                }
            }
        }
        return r;
    }
};
 
int n;
matrix base, ret;
lint t[2][2] = {{4,4},{1,0}};
lint e[2][2] = {{1,0},{0,1}};
 
int main(){
    memcpy(base.a,t,sizeof(base.a));
    memcpy(ret.a,e,sizeof(ret.a));
    int n;
    scanf("%d",&n); 
    if(n <= 2){
        puts("1");
        return 0;
    }
    n-=3;
    while(n){
        if(n&1) ret = ret * base;
        base = base * base;
        n >>= 1;
    }
    printf("%lld",(8ll * ret.a[0][0] + 2ll * ret.a[0][1])%mod);
}