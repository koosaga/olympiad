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
typedef pair<int, lint> pi;

int n;
vector<int> graph[400005];

pi dp[400005];
pi ret;

void solve(int x, int pa){
    dp[x] = pi(0, 1);
    vector<pi> tmp;
    for(auto &i : graph[x]){
        if(i == pa) continue;
        solve(i, x);
        tmp.push_back(pi(dp[i].first + 1, dp[i].second));
    }
    if(tmp.empty()) return;
    if(tmp.size() == 1){
        if(ret.first < tmp[0].first){
            ret.first = tmp[0].first;
            ret.second = 0;
        }
        if(ret.first == tmp[0].first) ret.second += tmp[0].second;
        dp[x] = tmp[0];
        return;
    }
    sort(tmp.begin(), tmp.end());
    reverse(tmp.begin(), tmp.end());
    if(tmp[0].first == tmp[1].first){
        if(ret.first < tmp[0].first + tmp[1].first){
            ret.first = tmp[0].first + tmp[1].first;
            ret.second = 0;
        }
        if(ret.first == tmp[0].first + tmp[1].first){
            int cur = 0;
            for(int i=0; i<tmp.size(); i++){
                if(tmp[i].first != tmp[0].first) break;
                ret.second += 1ll * tmp[i].second * cur;
                cur += tmp[i].second;
            }
        }
        for(int i=1; i<tmp.size(); i++){
            if(tmp[0].first == tmp[i].first){
                tmp[0].second += tmp[i].second;
            }
        }
    }
    else{
        for(int i=2; i<tmp.size(); i++){
            if(tmp[i].first == tmp[1].first){
                tmp[1].second += tmp[i].second;
            }
        }
        if(ret.first < tmp[0].first + tmp[1].first){
            ret.first = tmp[0].first + tmp[1].first;
            ret.second = 0;
        }
        if(ret.first == tmp[0].first + tmp[1].first){
            ret.second += 1ll * tmp[0].second * tmp[1].second;
        }
    }
    dp[x] = tmp[0];
}

int main(){
    scanf("%d",&n);
    for(int i=0; i<n-1; i++){
        int u, v;
        scanf("%d %d",&u,&v);
        graph[u].push_back(v);
        graph[v].push_back(u);
    }
    solve(1, 0);
    printf("%d %lld",ret.first + 1, ret.second);
}