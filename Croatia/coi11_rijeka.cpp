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
 
map<int,int> mp;
 
int main(){
    int n, m;
    scanf("%d %d",&n,&m);
    while(n--){
        int s, e;
        scanf("%d %d",&s,&e);
        if(s > e){
            mp[e]++;
            mp[s]--;
        }
    }
    if(mp.empty()){
        printf("%d",m);
        return 0;
    }
    int c = 0, ret = 0;
    auto nxt = ++mp.begin();
    for(auto &i : mp){
        if(nxt == mp.end()) break;
        c += i.second;
        if(c) ret += nxt->first - i.first;
        nxt++;
    }
    printf("%lld",m + 2ll * ret);
}