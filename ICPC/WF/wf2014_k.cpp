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
vector<pi> v1, v2;
vector<pi> intv;
int suc[1000005][20];

int query(int s, int e){
    if(s > e) return 0;
    s = lower_bound(intv.begin(), intv.end(), pi(s+1, -1e9)) - intv.begin() - 1;
    if(s < 0) return 1e9;
    int cnt = 1;
    for(int i=19; i>=0; i--){
        if(intv[suc[s][i]].second < e){
            s = suc[s][i];
            cnt += (1<<i);
        }
    }
    if(intv[s].second >= e) return cnt;
    s = suc[s][0];
    cnt++;
    if(intv[s].second >= e) return cnt;
    return 1e9;
}

int main(){
    scanf("%d %d",&k,&n);
    for(int i=0; i<n; i++){
        pi a;
        scanf("%d %d",&a.first,&a.second);
        if(a.first <= a.second){
            v1.push_back(a);
            a.first += k;
            a.second += k;
            v1.push_back(a);
        }
        else{
            a.second += k;
            v1.push_back(a);
        }
    }
    sort(v1.begin(), v1.end(),[&](const pi &a, const pi &b){
        return a.first == b.first ? (a.second > b.second) : (a.first < b.first);
    });
    for(auto &i : v1){
        if(intv.empty() || intv.back().second < i.second){
            intv.push_back(i);
        }
    }
    for(int i=0; i<intv.size(); i++){
        suc[i][0] = lower_bound(intv.begin(), intv.end(), pi(intv[i].second + 2, -1e9)) - intv.begin() - 1;
    }
    for(int j=1; j<=19; j++){
        for(int i=0; i<intv.size(); i++){
            suc[i][j] = suc[suc[i][j-1]][j-1];    
        }
    }
    int ret = 1e9;
    for(int i=1; i<=k; i++){
        ret = min(ret, query(i, i+k-1));
    }
    if(ret > 1e8) puts("impossible");
    else printf("%d",ret);
}