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
typedef pair<lint, lint> pi;
 
int n, a[155];
int sum1[155], sum2[155];
 
bitset<1132501> bs[151];
 
inline int cost(int i, int j){
    return j * (sum1[j] - sum1[i-1]) - (sum2[j] - sum2[i-1]);
}
 
int main(){
    scanf("%d",&n);
    for(int i=1; i<=n; i++){
        scanf("%d",&a[i]);
        //a[i] = 100;
        sum1[i] = sum1[i-1] + a[i];
        sum2[i] = sum2[i-1] + (i - 1) * a[i];
    }
    int k;
    scanf("%d",&k);
    if(k > cost(1, n)){
        printf("%d",k);
        return 0;
    }
    bs[0].set(0, 1);
    for(int i=1; i<=n; i++){
        bs[i].set(cost(1, i), 1);
        if(i < n-30){
            for(int j=max(i-40, 0); j<i; j++){
                bs[i] |= bs[j] << cost(j+2, i);
            }
            continue;
        }
        for(int j=0; j<i; j++){
            bs[i] |= bs[j] << cost(j+2, i);
        }
    }
    for(int i=k; i<=1132500; i++){
        if(bs[n].test(i) == 0){
            printf("%d",i);
            return 0;
        }
    }
}