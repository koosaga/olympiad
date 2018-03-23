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

int a[4][1005];
int v1[1000*1000+2], v2[1000*1000+2];

int main(){
    int t;
    scanf("%d",&t);
    while(t--){
        int w, n;
        scanf("%d %d",&w,&n);
        for(int i=0; i<4; i++){
            for(int j=0; j<n; j++){
                scanf("%d",&a[i][j]);
            }
        }
        for(int i=0; i<n; i++){
            for(int j=0; j<n; j++){
                v1[i*n+j] = a[0][i] + a[1][j];
                v2[i*n+j] = a[2][i] + a[3][j];
            }
        }
        sort(v1, v1+n*n);
        sort(v2, v2+n*n);
        int low = -1e9, high = 1e9;
        for(int i=0; i<n*n; i++){
            auto p = lower_bound(v2, v2 + n * n, w - v1[i]);
            if(p != v2 + n * n) high = min(high, v1[i] + *p - w);
            if(p != v2) low = max(low, v1[i] + *--p - w);
        }
        if(abs(low) <= abs(high)) printf("%d\n",w + low);
        else printf("%d\n",w + high);
    }
}