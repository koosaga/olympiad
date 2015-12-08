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
 
int n;
vector<pi> graph[200005];
int dp[200005][4];
 
int f(int x, int m, int p){
    if(~dp[x][m]) return dp[x][m];
    if(m >= 2){
        int maxv = -1e9, sum = 0;
        for(int i=0; i<graph[x].size(); i++){
            int pos = graph[x][i].second;
            if(pos == p) continue;
            int tmp = max(f(pos, 1, x), f(pos, 3, x) + graph[x][i].first);
            sum += tmp;
            maxv = max(maxv, f(pos, m-2, x) + graph[x][i].first - tmp);
        }
        return dp[x][m] = sum + maxv;
    }
    else if(m == 1){
        int ret = 0;
        for(int i=0; i<graph[x].size(); i++){
            int pos = graph[x][i].second;
            if(pos == p) continue;
            ret += max(f(pos, 1, x), f(pos, 3, x) + graph[x][i].first);
        }
        return dp[x][m] = ret;
    }
    else{
        int sum = 0, maxv = 0;
        for(int i=0; i<graph[x].size(); i++){
            int pos = graph[x][i].second;
            if(pos == p) continue;
            int tmp1 = max(f(pos, 1, x), f(pos, 3, x) + graph[x][i].first);
            int tmp2 = max(f(pos, 0, x), f(pos, 2, x) + graph[x][i].first);
            sum += tmp1;
            maxv = max(maxv, tmp2 - tmp1);
        }
        int ret = sum + maxv;
        vector<pi> tmp;
        sum = 0;
        for(int i=0; i<graph[x].size(); i++){
            int pos = graph[x][i].second;
            if(pos == p) continue;
            int tmp1 = max(f(pos, 1, x), f(pos, 3, x) + graph[x][i].first);
            int tmp2 = f(pos, 0, x) + graph[x][i].first;
            int tmp3 = f(pos, 1, x) + graph[x][i].first;
            tmp.push_back(pi(tmp2 - tmp1, tmp3 - tmp1));
            sum += tmp1;
        }
        int pmax = -1e9, smax = -1e9;
        for(int i=0; i<tmp.size(); i++){
            ret = max(ret, sum + tmp[i].first + pmax);
            pmax = max(pmax, tmp[i].second);
        }
        for(int i=tmp.size()-1; i>=0; i--){
            ret = max(ret, sum + tmp[i].first + smax);
            smax = max(smax, tmp[i].second);
        }
        return dp[x][m] = ret;
    }
}
int main(){
    memset(dp,-1,sizeof(dp));
    scanf("%d",&n);
    for(int i=0; i<n-1; i++){
        int s, e, x;
        scanf("%d %d %d",&s,&e,&x);
        graph[s].push_back(pi(x, e));
        graph[e].push_back(pi(x, s));
    }
    printf("%d",f(1, 0, 0));
}