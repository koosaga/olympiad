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
 
pi dp[1<<18];
int fnd[1<<18];
int n, w, a[18];
 
void track(int x){
    vector<int> v;
    int cknap = dp[x].second;
    while(x){
        v.push_back(fnd[x] + 1);
        cknap -= a[fnd[x]];
        x ^= (1<<fnd[x]);
        if(cknap == 0){
            printf("%d ",v.size());
            for(auto &i : v){
                printf("%d ",i);
            }
            puts("");
            v.clear();
            cknap = dp[x].second;
        }
    }
}
 
int main(){
    scanf("%d %d",&n,&w);
    for(int i=0; i<n; i++){
        scanf("%d",&a[i]);
    }
    auto t = -1;
    dp[0].first = 1;
    for(int i=1; i<(1<<n); i++){
        dp[i] = pi(1e9, 1e9);
        for(int j=0; j<n; j++){
            if((i >> j) & 1){
                pi nw = dp[i ^ (1<<j)];
                if(nw.second + a[j] > w){
                    nw.first++;
                    nw.second = a[j];
                }
                else nw.second += a[j];
                if(dp[i] > nw){
                    dp[i] = nw;
                    fnd[i] = j;
                }
            }
        }
    }
    printf("%d\n",dp[(1<<n)-1].first);
    track((1<<n) - 1);
}