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

int k, n;
vector<int> v;

pi a[200005];
vector<pi> intv;
int suc[19][400005];

int main(){
    scanf("%d %d",&k,&n);
    for(int i=0; i<n; i++){
        scanf("%d %d",&a[i].first, &a[i].second);
        v.push_back(a[i].first);
        a[i].second += a[i].first;
        if(a[i].second <= k){
            v.push_back(a[i].second);
        }
        else{
            v.push_back(a[i].second - k);
        }
    }
    v.push_back(0);
    v.push_back(k);
    sort(v.begin(), v.end());
    v.resize(unique(v.begin(), v.end()) - v.begin());
    int nk = lower_bound(v.begin(), v.end(), k) - v.begin();
    int on = n;
    for(int i=0; i<on; i++){
        a[i].first = lower_bound(v.begin(), v.end(), a[i].first) - v.begin();
        if(a[i].second <= k){
            a[i].second = lower_bound(v.begin(), v.end(), a[i].second) - v.begin();
            a[n++] = pi(a[i].first + nk, a[i].second + nk);
        }
        else{
            a[i].second = lower_bound(v.begin(), v.end(), a[i].second - k) - v.begin() + nk;
        }
    }
    sort(a, a+n);
    k = nk;
    int cmax = 0, pt = 0;
    for(int i=0; i<2*k; i++){
        while(pt < n && a[pt].first <= i){
            cmax = max(cmax, a[pt++].second);
        }
        suc[0][i] = cmax;
    }
    for(int i=1; i<19; i++){
        for(int j=0; j<2*k; j++){
            suc[i][j] = suc[i-1][suc[i-1][j]];
        }
    }
    int ret = 1e9;
    for(int i=0; i<k; i++){
        int tmp = 0, p = i;
        for(int j=18; j>=0; j--){
            if(p < suc[j][p] && suc[j][p] < i + k){
                p = suc[j][p];
                tmp |= 1<<j;
            }
        }
        if(p < suc[0][p]) p = suc[0][p], tmp++;;
        if(p >= i + k) ret = min(ret, tmp);
    }
    printf("%d",ret);
}