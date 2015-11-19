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

int n, m, a[505][505], p, q;

bool trial2(int s, int e, int x){
    int cnt = 0;
    for(int i=1; i<=m; ){
        int p = i, sum = 0;
        while(p <= m && sum < x){
            sum += a[e][p] - a[s-1][p];
            p++;
        }
        if(sum >= x) cnt++;
        i = p;
    }
    return cnt >= q;
}

bool trial(int x){
    int ret = 0;
    for(int i=1; i<=n; ){
        int e = i;
        while(e <= n && !trial2(i, e, x)) e++;
        if(trial2(i, e, x)) ret++;
        i = e+1;
    }
    return ret >= p;
}
int main(){
    scanf("%d %d %d %d",&n,&m,&p,&q);
    for(int i=1; i<=n; i++){
        for(int j=1; j<=m; j++){
            scanf("%d",&a[i][j]);
            a[i][j] += a[i-1][j];
        }
    }
    int s = 0, e = 1e9;
    while(s != e){
        int m = (s+e+1)/2;
        if(trial(m)) s = m;
        else e = m-1;
    }
    printf("%d",s);
}