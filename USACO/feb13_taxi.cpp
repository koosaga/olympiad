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
#include <bitset>
#include <iostream>
using namespace std;
typedef long long lint;
typedef long double llf;
typedef pair<lint, lint> pi;
 
int n, m;
map<int, pi> mp;
 
int main(){
    cin >> n >> m;
    lint ret = m;
    for(int i=0; i<n; i++){
        int s, e;
        scanf("%d %d",&s,&e);
        if(s < e){
            mp[s].first++;
            mp[e].first--;
        }
        else{
            mp[e].second++;
            mp[s].second--;
        }
    }
    int d1 = 0, d2 = 0;
    auto nxt = ++mp.begin();
    for(auto &i : mp){
        d1 += i.second.first;
        d2 += i.second.second;
        if(nxt != mp.end()) ret += 2ll * max(d1-1, d2) * (nxt->first - i.first);
        if(nxt != mp.end()) nxt++;
    }
    cout << ret;
}